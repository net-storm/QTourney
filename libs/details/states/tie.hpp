/// \date    Thu Apr 21 16:14:08 MSK 2011 -- 

#ifndef _23FA76B5_3CA8_4352_BE7A_DA9D9CA39178_
#define _23FA76B5_3CA8_4352_BE7A_DA9D9CA39178_

// Project specific includes
#include <libs/details/state.hpp>

// Standard includes
#include <map>
#include <string>

namespace tournament { 

// internal forward declarations
class duel;

namespace details { namespace states {

class ties
    : public state
{
public:
	ties(state::properties const& properties) 
	  : state(properties)
	{}

	bool complete()	const { return true; }

	const participant winner() const;

	const participant loser() const;

	bool is_valid_state_change_to( const std::string& state_name ) const;

	void change_context( const duel & new_context );
};

} } }

#endif
