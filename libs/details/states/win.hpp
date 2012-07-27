/// \date    Thu Apr 21 15:49:23 MSK 2011 -- 

#ifndef _CD93B29E_79B6_4206_A50A_03B51B66541B_ 
#define _CD93B29E_79B6_4206_A50A_03B51B66541B_

// Project specific includes
#include <libs/details/state.hpp>

// Standard includes
#include <map>
#include <string>

namespace tournament { 

// internal forward declarations
class duel;

namespace details { namespace states {

class wins
    : public state
{
public:
	wins(state::properties const& properties) 
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
