/// \date    Thu Apr 21 18:22:43 MSK 2011 -- 

// Project specific includes
#include <libs/duel.hpp>
#include <libs/participant.hpp>
#include <libs/details/states/factory.hpp>
#include <libs/details/state.hpp>

// Standard includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>

namespace tournament {

duel::duel
( 
	const std::string& round_name,
	const duel::state_t& initial_state 
)
:	m_round_name(round_name)
{
	m_states.push_back(initial_state );
}

duel::duel( participant const& first, participant const& second )
:	m_round_name("")
{
	std::ostringstream os;
	os << " % " << first << " % challenges % " << second << " % ";
	
	m_states.push_back
	(
		details::states::factory::create(duel::read_state(os.str()))
	);
}

const duel::properties duel::read_state(const std::string record)
{
	using namespace boost::algorithm;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> separators("%", "", boost::keep_empty_tokens);
	tokenizer tokens(record, separators);
	int token_index = 0;
 	duel::properties properties;
	for 
	(
		  tokenizer::iterator tok_iter = tokens.begin()
		; tok_iter != tokens.end()
		; ++tok_iter 
	)
	{
		token_index++;
		const std::string value = trim_copy(*tok_iter);
		switch (token_index)
		{
			case 1: properties["round"] = value; break;
			case 2: properties["winner"] = value; break;
			case 3: properties["state"] = value; break;
			case 4: properties["loser"] = value; break;
			case 5: properties["details"] = value; break;
            default: 
            {
                if(!value.empty()) 
                {
                    properties["the_rest"] = trim_copy(properties["the_rest"] + " " + value);
                }
                break;
            }
		}
	}
	return properties;
}


void duel::update( const duel::state_t& a_state )
{
	if (can_change_state_to(a_state))
	{
		m_states.push_back(a_state);

		m_states.back()->update_context
		(
			m_states.front()
		);
	}
	else
	{
//		std:: cerr << "invalid state change : " << a_state << endl;
	}
}

bool duel::can_change_state_to( const state_t& new_state )
{
	if (m_states.empty()) 
	{
		return true;
	}
	return m_states.back()->is_valid_state_change_to(new_state->name());
}

const participant duel::winner() const
{
	participant result = m_states.back()->winner();
//	participant initial = get_by_name(result.id());
//	result = initial.add(result);
	return result;

}

const participant duel::loser() const
{
	participant result = m_states.back()->loser();
//	participant initial = get_by_name(result.id());
//	result = initial.add(result);
	return result;
}

bool duel::complete() const
{
	return m_states.back()->complete();
}

const std::string duel::state() const
{
	return m_states.back()->name();
}

const std::string duel::details() const
{
	return "";
}

const std::string duel::serialize() const
{
	std::ostringstream os;
	os  << " % " << winner()
		<< " % " << state()
		<< " % " << loser()
		<< " % " << details()
		;
	return os.str();
}

const participant duel::get_by_name( const std::string& id ) const
{
	if ( m_states.front()->winner().id() == id)
	{
		return m_states.front()->winner();
	}
	if ( m_states.front()->loser().id() == id)
	{
		return m_states.front()->loser();
	}
	assert(!"cannot find by id");
	return participant::bye();
}

bool duel::participating( const std::string& id ) const
{
	return ( m_states.back()->winner().id() == id) 
		|| ( m_states.back()->loser().id() == id);
}

std::ostream& operator<<(std::ostream& os, std::vector<duel> a_collection)
{
	int i = 0;
	std::vector<duel>::const_iterator itr = a_collection.begin();
	std::vector<duel>::const_iterator end = a_collection.end();
	for ( ; itr != end; ++itr ) {
		std::cout
		//<< ++i << "\t"
		<< *itr << std::endl;
	}
	return os;
}

}
