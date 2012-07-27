// Project specific includes
#  include <form_pairs/application.hpp>
#  include <libs/participant.hpp>
#  include <libs/duel.hpp>

// Standard includes
#  include <boost/program_options.hpp>
#  include <boost/tokenizer.hpp>
#  include <boost/algorithm/string.hpp>
#  include <boost/lexical_cast.hpp>
#  include <algorithm>
#  include <functional>
#  include <iostream>
#  include <fstream>
#  include <iterator>
#  include <list>

namespace  tournament { namespace  form_pairs {

void show_help()
{
	std::cout << "form_pairs v.0.0.1 beta (C)Sergey Stepanov 2011-2012, MIT" << std::endl;
	std::cout << "Usage: form_pairs [OPTIONS]" << std::endl;
	std::cout << "Distributes pairs from list of participants in form of:" << std::endl;
	std::cout << "name:team:hits:forfeits:score:first_name:mid_name:surname:tours:wins:ties:loses:..." << std::endl;
	std::cout << "If no File parameter is specified, awaits input from StdIn." << std::endl;
}

const application::seed_type get_seed_type(const std::string& seed)
{
	if ("as_is" == seed)     return application::as_is;
	if ("score" == seed)     return application::by_score;
	if ("advantage" == seed) return application::by_advantage;
	if ("random" == seed)    return application::random;
	if ("team" == seed)      return application::by_teams;
	return application::as_is;
}

application::application(int argument_count, char* argument_values[])
	: m_exit(false)
	, m_debug_level(0)
	, m_from_file(false)
{
	namespace po = boost::program_options;

	std::string seed;
	po::options_description description("Allowed options");
	description.add_options() (
		  "help,h"
		, "Shows this help message"
	)
	(
		  "debug,d"
		, po::value<int>(&m_debug_level)->default_value(0)
		, "Sets debug messages verbosity level"
	)
	(
		  "file,f"
		, po::value<std::string>(&m_file_name)
		, "Read list of participants from file"
	)
	(
		  "seed_type,s"
		, po::value<std::string>(&seed)->default_value("as_is")
		, "Seed type for pair distribution, possible variants:"
		   "\n\t* as_is - seed in order, given by list"
		   "\n\t* score - sort and seed by score"
		   "\n\t* advantage - places top seeded participants as far as possible from each other"
		   "\n\t* random - total random distribution"
		   "\n\t* team - teammates are seeded as far as possible from each other"
	);

	po::variables_map properties;

	po::store (
		po::parse_command_line (
			  argument_count
			, argument_values
			, description
		)
		, properties
	);

	po::notify(properties);

	if (properties.count("help")) {
		show_help();
		std::cout << description << "\n";
		m_exit = true;
	}

	if (properties.count("seed_type")) {
		m_seed_type = get_seed_type(seed);
	}

	if (properties.count("file")) {
		m_from_file = true;
	}
}

void application::process_file(const std::string& name)
{
	std::ifstream is(name.c_str());
	if(is.bad()) {
		std::ostringstream os;
		os << "Unable to open file " << name;
		throw std::runtime_error(os.str());
	}
	process_stream(is);
}

void application::process_stream(std::istream& is)
{
	using namespace boost::algorithm;
	std::string input_line;
	while(getline(is, input_line)) {
		std::string trimed_record = trim_copy(input_line);
		if ("END" != trimed_record ) {
			try {
				update_participant_list(m_participants, trimed_record);
			} catch (const std::runtime_error& e) {
				std::cerr << "error: " << e.what() << std::endl;
			}
		} else {
			break;
		}
	}
}


void application::compute_pairs()
{
	switch(m_seed_type) {
		case by_score :     form_pairs_by_score(m_participants); break;
		case by_advantage : form_pairs_by_advantage(m_participants); break;
		case by_teams :     form_pairs_by_teams(m_participants); break;
		case random :       form_pairs_randomly(m_participants); break;
		case as_is:
		default:            form_pairs_as_is(m_participants); break;
	}
}

void application::form_pairs_as_is(const collection& a_collection)
{
	int i = 0;
	for ( collection::const_iterator item = a_collection.begin()
		; item != a_collection.end()
		; ++item
	) {
		i++;
		participant first  = *item;
		participant second = participant::bye();

		collection::const_iterator next_item = ++item;
		if (next_item != a_collection.end()) {
			second = *next_item;
		}
		else --item;

		m_series.push_back(duel(first, second));
	}
}

void application::form_pairs_by_score(collection& a_collection)
{
	sort(a_collection.begin(),a_collection.end());
	form_pairs_as_is(m_participants);
}

void application::form_pairs_randomly(collection& a_collection)
{
	random_shuffle(a_collection.begin(), a_collection.end());
	form_pairs_as_is(a_collection);
}

void application::form_pairs_by_advantage(collection& a_collection)
{
	sort(a_collection.begin(),a_collection.end());
	int winner_count = a_collection.size() / 2;

	collection winners (
		  a_collection.begin()
		, a_collection.begin() + winner_count
	);

	collection losers (
		  a_collection.begin() + winner_count
		, a_collection.end()
	);

	random_shuffle(losers.begin(), losers.end());

	for ( collection::iterator item = winners.begin()
		; item != winners.end()
		; ++item
	) {
		participant first  = *item;
		participant second = losers.back();
		m_series.push_back(duel(first, second));
		losers.pop_back();
	}

	form_pairs_randomly(losers);
}

void application::form_pairs_by_teams(const collection& a_collection)
{
	std::list<participant> collection_list (
		  a_collection.begin()
		, a_collection.end()
	);

	collection_list.sort();

	while(!collection_list.empty()) {
		const participant first = collection_list.front();
		collection_list.pop_front();

		participant second = participant::bye();

		if(!collection_list.empty()) {
			second = collection_list.front();
		}

		std::list<participant>::iterator
			found = collection_list.begin();

		while (found != collection_list.end()) {
			if (found->team() != first.team()) {
				second = *found;
				collection_list.erase(found);
				break;
			}
			++found;
		}

		if (collection_list.end() == found) // not found
		{
			collection_list.pop_front();
		}

		m_series.push_back
		(
			duel(first, second)
		);
	}
}

int application::run()
{
	if (m_exit) return 1;

	if (m_from_file) {
		process_file(m_file_name);
	} else {
		process_stream(std::cin);
	}
	compute_pairs();

	std::cout << m_series;

	return 0;
}

} }                                                        // tournament, form_pairs
