/// \date    Thu Apr 21 19:18:18 MSK 2011 -- 

// Project specific includes
#include <start_round/application.hpp>
#include <libs/round.hpp>
#include <libs/duel.hpp>
#include <libs/details/state.hpp>
#include <libs/participant.hpp>
#include <libs/details/states/factory.hpp>

// Standard includes
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <list>

namespace po = boost::program_options;

namespace  tournament { namespace  start_round {

void show_help()
{
	std::cout << "start_round v.0.0.1 beta (C)Sergey Stepanov 2011-2012, MIT" << std::endl;
	std::cout << "Usage: start_round [OPTIONS]" << std::endl;
	std::cout << "starts round and waits until all duels are resolved " << std::endl;
	std::cout << "accepts lines in form of: " << std::endl;
	std::cout << "round_name%participant1%duel status%partisipant2%details" << std::endl;
	std::cout << "If no File parameter is specified, awaits input from StdIn." << std::endl;
}

application::application(int argument_count, char* argument_values[])
    : m_exit(false)
    , m_winners_only(false)
	, m_debug_level(0)
	, m_from_file(false)
{
    po::options_description description("Allowed options");
    description.add_options()
    (
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
        , "Read list of round events from file"
    )
    (
          "round-name,r"
        , po::value<std::string>(&m_round_name)
        , "Used if no round name specified"
    )
    (
          "winners-only,w"
        , "only winners survive in result table"
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
        std::cout << description << std::endl;
        m_exit = true;
    }

	if (properties.count("file")) {
		m_from_file = true;
	}

	if (properties.count("winners-only")) {
        m_winners_only = true;
    }
}

void application::parce( const std::string& record )
{
	std::string trimed_record = boost::algorithm::trim_copy(record);
	if (trimed_record.empty()) return;
	if (trimed_record[0] == '#') return;
	duel::properties a_properties = duel::read_state(record);

	if (a_properties["winner"].empty() || a_properties["loser"].empty()) {
		std::cerr << "record " + record + " is invalid" << std::endl;
		return;
	}

	duel::state_t new_state = details::states::factory::create(a_properties);

	std::string round_name = a_properties["round"];
	if (round_name.empty()) {
		round_name = m_round_name;
	}

	rounds::iterator found = std::find_if (
		  m_rounds.begin()
		, m_rounds.end()
		, boost::bind(&round::name, _1) == round_name
	);

	if (m_rounds.end() == found) {
		round new_round = round(round_name);
		new_round.update(new_state);
		m_rounds.push_back(new_round);
	} else {
		found->update(new_state);
	}
}

bool all_rounds_are_complete(const application::rounds& a_collection)
{
	if (a_collection.empty()) return false;
	application::rounds::const_iterator itr = a_collection.begin();
	application::rounds::const_iterator end = a_collection.end();
	for ( ; itr != end ; ++itr ) {
		if (!itr->complete()) return false;
	}
	return true;
}


void application::process_stream( std::istream& is )
{
	using namespace boost::algorithm;
	std::string input_line;
	while(getline(is, input_line)) 
	{
		input_line = trim_copy(input_line);
		if ("end" == input_line) {
			break;
		} else if ("ls" == input_line)
		{
			std::cout << m_rounds;
			break;
		} else {
			parce(input_line);
		}
	}
}

void application::process_file( const std::string& name )
{
	std::ifstream is(name.c_str());
	if(is.bad() || !is.is_open()) {
		std::ostringstream os;
		os << "Unable to open file " << name;
		throw std::runtime_error(os.str());
	}
	process_stream(is);

	while(!all_rounds_are_complete(m_rounds)) {
		process_stream(std::cin);
	}
}


int application::run()
{
	if (m_exit) { return 1; }

	if (m_from_file) {
		process_file(m_file_name);
	} else {
		while(!all_rounds_are_complete(m_rounds)) {
			if(std::cin.eof()) break;
			process_stream(std::cin);
		}
	}

	if (!m_rounds.empty()) {
		round last_round = m_rounds.back();
		std::cout << "# winners :" << std::endl << last_round.winners();
		if(!m_winners_only) {
			std::cout << "# losers :" << std::endl << last_round.losers();
		}
	}
	return 0;
}

} }
