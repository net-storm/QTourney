/// \date    Wed Apr 20 17:58:51 MSK 2011 -- 

#ifndef _C12CAF10_B4C5_401A_B9AD_5D6E3D880642_
#define _C12CAF10_B4C5_401A_B9AD_5D6E3D880642_

// Project specific includes
#include <libs/details/state.hpp>

namespace tournament { 

// internal forward declarations
class duel;

namespace details { namespace states {

class challenges
    : public state
{
public:
	challenges(state::properties const& properties) 
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
