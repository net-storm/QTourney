/// \date	Thu Apr 21 21:54:08 MSK 2011 --

#ifndef _9CDAF33B_934D_4149_8BA7_A1F1C1D14372_
#define _9CDAF33B_934D_4149_8BA7_A1F1C1D14372_

// Standard includes
#include <string>
#include <vector>

namespace  tournament { 

class participant
{
private:
	typedef int integer;
	typedef std::string string;

public:
	enum prop_role {
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	prop_role_##prop_name,
#include <libs/participant.inc>
	};

	participant()
		: m_winner(false)
		, m_everybody_in_team(false)
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
		, m_##prop_name(default_value)
#include <libs/participant.inc>
	{ }

	explicit participant(const std::string & record);

	static const participant bye() {
		return participant(":BYE:BYE:");
	}

	participant& add(const participant&	update)
	{
		m_hits += update.m_hits; 
		m_forfeits += update.m_forfeits;
		m_score += update.m_score;
		m_wins += update.m_wins;
		m_ties += update.m_ties;
		m_loses += update.m_loses;

		return *this;
	}

	const std::string id() const
	{
		return m_name + " : " + m_team;
	}

	const std::string former_team_name() const
	{
		return m_former_team_name;
	}

	const std::string stats() const;

#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	type_of_prop prop_name() const { return m_##prop_name; }
#include <libs/participant.inc>

	void set_rating(const int new_rating)
	{
		m_score = new_rating;
	}

	void set_state(const std::string new_state)
	{
		m_status = new_state;
	}

	void set_team(const std::string new_team)
	{
		m_team = new_team;
	}

	bool is_invalid() const;

	bool matches_everybody_in_the_team() const
	{
		return m_everybody_in_team;
	}

	int experience_factor() const
	{
		return (m_tours < 3) ? 5 : 3;
	}

	std::string serialize_all() const;

	std::string serialize() const;
	
	void set_winner()
	{
		m_winner = true;
	}

	int compare_rating_with(const int rating) const;

	friend std::ostream& operator<<(std::ostream& os ,participant obj)
	{
		return os << obj.serialize();
	}

private:
	bool m_winner;
	bool m_everybody_in_team;
	std::string m_former_team_name;
#define PARTICIPANT_PROPERTY(type_of_prop, prop_name, default_value, req) \
	type_of_prop m_##prop_name;
#include <libs/participant.inc>
};

inline bool operator==(const participant& lhs, const participant& rhs)
{
	return lhs.id() == rhs.id();
}

inline bool operator!=(participant const& lhs, participant const& rhs) /* throw() */
{
	return !(lhs == rhs);
}

inline bool operator < (const participant& lhs, const participant& rhs)
{
	return lhs.score() > rhs.score();
}

inline bool operator>(participant const& lhs, participant const& rhs) /* throw() */
{
	return rhs < lhs;
}
inline bool operator<=(participant const& lhs, participant const& rhs) /* throw() */
{
	return !(rhs < lhs);
}

inline bool operator>=(participant const& lhs, participant const& rhs) /* throw() */
{
	return !(lhs < rhs);
}

//inline void swap(participant& lhs, participant& rhs) /* throw() */
//{
	//lhs.swap(rhs);
//}

std::ostream& operator<<(std::ostream& os, std::vector<participant> a_collection);


std::vector<std::size_t> update_participant_list(std::vector<participant>& a_collection, const std::string& input_line);

}

#endif
