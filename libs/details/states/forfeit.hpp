/// \date    Thu Apr 21 16:23:11 MSK 2011 -- 

#ifndef _9527878F_49D8_4168_B966_4C5EEB04306B_
#define _9527878F_49D8_4168_B966_4C5EEB04306B_

// Project specific includes
#include <libs/details/state.hpp>

// Standard includes
#include <map>
#include <string>

namespace tournament { 

// internal forward declarations
class duel;

namespace details { namespace states {

class forfeits
    : public state
{
public:
	forfeits(state::properties const& properties) 
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
