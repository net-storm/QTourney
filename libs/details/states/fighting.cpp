/// \date    Thu Apr 21 16:21:19 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/fighting.hpp>
#include <libs/details/state.hpp>
#include <libs/details/states/challenge.hpp>
#include <libs/duel.hpp>
#include <libs/participant.hpp>

// Standard includes
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

bool fighting::is_valid_state_change_to( const std::string& state_name ) const
{
	if ("challenges" == state_name) 
	{
		return false;
	}
	else
	{
		return true;
	}
}

const participant fighting::winner() const
{
	return *m_winner;
}

const participant fighting::loser() const
{
	return *m_loser;	
}

} } }
