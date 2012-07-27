/// \date    Thu Apr 21 15:50:55 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/win.hpp>
#include <libs/details/state.hpp>
#include <libs/duel.hpp>
#include <libs/participant.hpp>

// Standard includes
#include <iostream>
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

bool wins::is_valid_state_change_to( const std::string& state_name ) const
{
	return false;
}

const participant wins::winner() const
{
	int mean = m_winner->compare_rating_with(m_loser->score());
	
	int score = 10 - m_loser->hits();
	
	int experience_factor = m_winner->experience_factor();

	int rating_delta = experience_factor * (score  - mean);
	
	participant result(*m_winner);
	
	result.set_rating(rating_delta);
	
	//std::cout << "mean = " << mean << std::endl	<< "score = " << score << std::endl	<< "experience_factor = " << experience_factor << std::endl	<< "rating_delta = " << rating_delta << std::endl;
	
	return result;
}

const participant wins::loser() const
{
	int mean = m_loser->compare_rating_with(m_winner->score());
		
	int score = 0 + m_loser->hits();
	
	int experience_factor = m_loser->experience_factor();
	
	int rating_delta = experience_factor * (score  - mean);

	participant result(*m_loser);
	
	result.set_rating(rating_delta);
	
	//std::cout << "mean = " << mean << std::endl	<< "score = " << score << std::endl	<< "experience_factor = " << experience_factor << std::endl	<< "rating_delta = " << rating_delta << std::endl;
	
	return result;
}

} } }
