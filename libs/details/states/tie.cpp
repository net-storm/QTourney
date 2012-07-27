/// \date    Thu Apr 21 16:17:16 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/tie.hpp>
#include <libs/details/state.hpp>
#include <libs/duel.hpp>
#include <libs/participant.hpp>

// Standard includes
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

bool ties::is_valid_state_change_to( const std::string& state_name ) const
{
	return false; // not any state change
}

const participant ties::winner() const
{
	int mean = m_winner->compare_rating_with(m_loser->score());
		
	int score = 5  + m_winner->hits() - m_loser->hits();
	
	int experience_factor = m_winner->experience_factor();
	
	int rating_delta = experience_factor * (score  - mean);
	
	participant result(*m_winner);
	
	result.set_rating(rating_delta);
	
	return result;
}

const participant ties::loser() const
{
	int mean = m_loser->compare_rating_with(m_winner->score());
		
	int score = 5  + m_loser->hits() - m_winner->hits();
	
	int experience_factor = m_loser->experience_factor();
	
	int rating_delta = experience_factor * (score  - mean);
	
	participant result(*m_loser);
	
	result.set_rating(rating_delta);
	
	return result;
}

} } }
