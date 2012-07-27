/// \date    Thu Apr 21 13:28:25 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/challenge.hpp>
#include <libs/details/state.hpp>
#include <libs/duel.hpp>
#include <libs/participant.hpp>

// Standard includes
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

bool challenges::is_valid_state_change_to( const std::string& state_name ) const
{
	return true; // any state change
}

const participant challenges::winner() const
{
	return *m_winner;
}

const participant challenges::loser() const
{
	return *m_loser;	
}

} } }
