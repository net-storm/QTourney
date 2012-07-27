/// \date	Fri Apr 22 15:33:58 MSK 2011 --

// Project specific includes
#include <libs/participant.hpp>

// Standard includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <math.h>


namespace {

std::pair<std::string, std::string> parce( const std::string& value )
{
	if ( std::string::npos != value.find_first_of("()") ){
		std::size_t first_opening_braket = value.find('(');
		std::size_t first_closing_braket = value.find(')');

		if (   ')' == value.at(value.length()-1)
			&& first_opening_braket < first_closing_braket
		) {
			// in case there are whitespace at the end of the string
			std::string new_value = boost::algorithm::trim_copy(value.substr(0, first_opening_braket));
			std::string old_value = value.substr(first_opening_braket+1, value.length()-first_opening_braket-2);
			old_value = parce(old_value).second; // to check internal syntaxis (i.e. 1(2(3(4))))
			return std::make_pair(new_value,old_value);
		} else {
			std::ostringstream os;
			os << "Incorrect syntaxis near " << value << " invalid brackets use";
			throw std::runtime_error(os.str());
		}
	} else {
		return std::make_pair(value,value);;
	}

}

static std::string to_string( const std::string& value )
{
	return parce(value).first;
}

static int to_integer( const std::string& value )
{
	try {
		return boost::lexical_cast<int>(parce(value).first);
	} catch (boost::bad_lexical_cast const&) {
		return 0;
	}
}

}

namespace tournament {

participant::participant(const std::string& record)
	: m_winner(false)
	, m_everybody_in_team(false)
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	, m_##prop_name(default_value)
#include <libs/participant.inc>
{
	using namespace boost::algorithm;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> separators(":", "", boost::keep_empty_tokens);
	tokenizer tokens(record, separators);
	std::string value;
	int token_index = 0;
	for ( tokenizer::iterator tok_iter = tokens.begin()
		; tok_iter != tokens.end()
		; ++tok_iter, ++token_index
	) {
		value = trim_copy(*tok_iter);
		switch (prop_role(token_index)) {
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
			case prop_role_##prop_name : m_##prop_name = to_##type_of_prop(value); break;
#include <libs/participant.inc>
			default: {
				if(!value.empty()) {
					m_the_rest = trim_copy(m_the_rest + " " + value);
				}
				break;
			}
		}
		// special case for team renaming
		if ( prop_role_team == token_index) {
			m_former_team_name = parce(value).second;
		}
	}
	if ("*" == m_name) { // means this is pattern for all members in the team
		m_everybody_in_team = true;
	}
	if (m_status.empty()) {
		m_status = "Add";
	}
	if (m_name.empty()) { // validate and fill name
		std::string full_name = m_first_name;
		full_name = trim_copy(full_name + " " + m_middle_name);
		full_name = trim_copy(full_name + " " + m_last_name);
		m_name = full_name;
	}
	if (is_invalid()) {
		std::ostringstream os;
		os << "Record " + record + " is invalid";
		throw std::runtime_error(os.str());
	}
}

const std::string participant::stats() const
{
	std::ostringstream os;
	os	<< m_wins  << " wins, "
		<< m_ties  << " ties, "
		<< m_loses << " loses "
		<< "in " << m_tours << " tourneys"
		;
	return boost::algorithm::trim_copy(os.str());
}


std::string participant::serialize_all() const
{
	std::ostringstream os;
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) { \
		os << " " << prop_name() << " " << ":"; \
	}
#include <libs/participant.inc>
	return boost::algorithm::trim_copy(os.str());
}

std::string participant::serialize() const
{
	std::ostringstream os;
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) { \
		const bool mandatory = true; \
		const bool optional = false; \
		if (mandatory == req && optional != req){ \
			os << " " << prop_name() << " "; \
		} \
		os << ":"; \
	}
#include <libs/participant.inc>
	std::string str = os.str();

	const size_t found = str.find_last_not_of(":");
	if (found != string::npos) {
		str.erase(found+1);
	}
	return boost::algorithm::trim_copy(str);
}

static double round(double v, int decimals)
{
	double p = pow(10.0,-decimals);
	return floor(p*v + 0.5)/p;
}

int participant::compare_rating_with(const int a_score) const
{
	return static_cast<int>
	(
		round( 10.0 / ( 1.0 + pow( 10.0, (a_score - m_score) / 100.0 ) ) , 0 )
	);
}

bool participant::is_invalid() const
{
	return name().empty();
}

std::ostream& operator<<(std::ostream& os, std::vector<participant> a_collection)
{
	int i = 0;
	std::vector<participant>::const_iterator itr = a_collection.begin();
	std::vector<participant>::const_iterator end = a_collection.end();
	for ( ; itr != end; ++itr ) {
		std::cout
		//<< ++i << "\t"
		<< *itr << std::endl;
	}
	return os;
}


std::vector<std::size_t> update_participant_list(std::vector<participant>& a_collection, const std::string& trimed_record)
{
	std::vector<std::size_t> changed_indexes;
	if (!trimed_record.empty() && '#' != trimed_record[0]) {
		participant new_participant(trimed_record);

		if ( new_participant.matches_everybody_in_the_team() ){
			// changes shall be applied to all members of the team
			const std::string old_team = new_participant.former_team_name();
			const std::string new_team = new_participant.team();
			if ( old_team != new_team ) {
				// team was renamed
				std::vector<participant>::iterator itr = a_collection.begin();
				std::vector<participant>::iterator end = a_collection.end();
				for ( ; itr != end; ++itr ) {
					if ( old_team == itr->team()) {
						itr->set_team(new_team);
					}
				}
			}
		} else {
			const std::string action = new_participant.status();

			typedef std::vector<participant>::iterator participant_iter;
			participant_iter beg = a_collection.begin();
			participant_iter end = a_collection.end();
			participant_iter found = find (beg, end, new_participant);
			if (found != end) {
				changed_indexes.push_back(found - beg);
				if ("Upd" == action) {
					found->add(new_participant);
				} else if ("Kick" == action) {
					found->set_state("Add");
				} else if ("Reg" == action) {
					found->set_state("Reg");
				} else if ("Add" == action) {
					if ("Add" != found->status()) {
						found->set_state("Add");
					} else {
						std::ostringstream os;
						os << "Cannot add " << trimed_record << " - already exists";
						throw std::runtime_error(os.str());
					}
				} else {
					// some other actions
				}
			} else {
				if ("Add" == action) {
					a_collection.push_back(new_participant);
					changed_indexes.push_back(a_collection.size());
				} else {
					std::ostringstream os;
					os << "Cannot update " << trimed_record << " - not exists";
					throw std::runtime_error(os.str());
				}
			}
		}
	}
	return changed_indexes;
}

}

