/// \date    Wed Apr 20 17:52:02 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/canceled.hpp>
#include <libs/details/state.hpp>
#include <libs/participant.hpp>
#include <libs/duel.hpp>

// Standard includes
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

bool canceled::is_valid_state_change_to( const std::string& state_name ) const
{
	return false; // not any state change
}

const participant canceled::winner() const
{
	return *m_winner;
}

const participant canceled::loser() const
{
	return *m_loser;	
}

} } }
