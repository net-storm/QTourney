/// \date    Wed Apr 20 17:42:02 MSK 2011 -- 

#ifndef _A1EBF9F4_9B2E_4A43_B1AC_E343793C1C22_
#define _A1EBF9F4_9B2E_4A43_B1AC_E343793C1C22_

// Project specific includes
#  include <libs/details/state.hpp>

// Standard includes
#  include <string>

namespace tournament { 

// internal forward declarations
class duel;

namespace details { namespace states {

class canceled
    : public state
{
public:
	canceled(state::properties const& properties) 
	  : state(properties)
	{}

	bool complete()	const { return true; }

	const participant winner() const;

	const participant loser() const;

	bool is_valid_state_change_to( const std::string& state_name ) const;

	void change_context( const duel & new_context );
};

} } }

#endif // _A1EBF9F4_9B2E_4A43_B1AC_E343793C1C22_
