/// \date    Thu Apr 21 16:17:48 MSK 2011 -- 

#ifndef _E869CB2B_CDF0_4172_B9D7_FFF800764750_
#define _E869CB2B_CDF0_4172_B9D7_FFF800764750_

// Project specific includes
#include <libs/details/state.hpp>

namespace tournament { 

// internal forward declarations
class duel;

namespace details { namespace states {

class fighting
    : public state
{
public:
	fighting(state::properties const& properties) 
	  : state(properties)
	{}

	bool complete()	const { return false; }

	const participant winner() const;

	const participant loser() const;

	bool is_valid_state_change_to( const std::string& state_name ) const;

	void change_context( const duel & new_context );
};

} } }

#endif
