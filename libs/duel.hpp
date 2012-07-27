/// \date	Thu Apr 21 18:16:32 MSK 2011 --

#ifndef _F5F27565_1F86_4A41_BF1E_9A2C91E345AC_
#define _F5F27565_1F86_4A41_BF1E_9A2C91E345AC_

// Project specific includes
#include <libs/participant.hpp>

// Standard includes
#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace  tournament { namespace details {

// forward declarations
class state;

}

class duel
{
public:
	typedef std::map<std::string, std::string> properties;	
	typedef boost::shared_ptr<details::state> state_t;	
	typedef std::vector<participant> participants;
	typedef std::vector<state_t> states;
public:  
	duel (
		  const std::string& round_name
		, const duel::state_t& initial_state 
	);

	duel (
		  participant const& first
		, participant const& second
	);

	static const properties read_state(const std::string record);
	
	const std::string round() const
	{
		return m_round_name;
	}

	const std::string state() const;

	const std::string details() const;
	
	bool complete() const;

	const participant winner() const;

	const participant loser() const;

	void update(const state_t& a_state);

	const std::string serialize() const;

	friend std::ostream& operator<<( std::ostream& os, duel obj )
	{
		os << obj.serialize();
		return os;
	}

	const participant get_by_name( const std::string& id ) const;

	bool participating( const std::string& id ) const;

private:
	bool can_change_state_to( const state_t& new_state );
	
private:
	states m_states;
	std::string m_round_name;
};

inline bool operator==(duel const& lhs, duel const& rhs)
{
	return ((lhs.winner() == rhs.winner()) && (lhs.loser() == rhs.loser()) || (lhs.winner() == rhs.loser()) && (lhs.loser() == rhs.winner()));
}

inline bool operator!=(duel const& lhs, duel const& rhs) /* throw() */
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, std::vector<duel> a_collection);

}

#endif
