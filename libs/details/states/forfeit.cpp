/// \date    Thu Apr 21 16:25:00 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/forfeit.hpp>
#include <libs/details/state.hpp>
#include <libs/duel.hpp>
#include <libs/participant.hpp>

// Standard includes
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

bool forfeits::is_valid_state_change_to( const std::string& state_name ) const
{
	return false;
}

const participant forfeits::winner() const
{
	int mean = m_winner->compare_rating_with(m_loser->score());
		
	int score = 10 - m_loser->hits();
	
	int experience_factor = m_winner->experience_factor();
	
	int rating_delta = experience_factor * (score  - mean);
	
	participant result(*m_winner);
	
	result.set_rating(rating_delta);
	
	return result;
}

const participant forfeits::loser() const
{
	m_loser->set_state("Kick");
	return *m_loser;
}

} } }
