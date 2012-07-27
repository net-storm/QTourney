///
/// Copyright &copy; Sergey Stepanov 2010-2011. All rights reserved.
/// \file    round.hpp, v 1.0 2011/04/05 15:47:28 Garret
/// \brief    module ()
/// \author  Sergey Stepanov (net_storm@rambler.ru)
/// \date    Tue Apr 05 15:47:28 MSK 2011 -- Initial design
/// \par     Maintenance person:
///          Sergey Stepanov (net_storm@rambler.ru)
///

#ifndef __TOURMANENT__LIBS__ROUND_HPP__
#define __TOURMANENT__LIBS__ROUND_HPP__

// Project specific includes
#include <libs/duel.hpp>
#include <libs/participant.hpp>
#include <libs/details/state.hpp>

// Standard includes
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

namespace  tournament { 

class round
{
private:
	typedef int integer;
	typedef std::string string;
	typedef bool deathmatch_t;
	typedef std::vector<participant> partisipants;
	typedef std::vector<duel> duels;

public:
	enum prop_role {
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
		prop_role_##prop_name,
#include <libs/round.inc>
	};

public:
	explicit round(const std::string &record);

	void update(const duel::state_t a_state);

	const partisipants winners() const;

	const partisipants losers() const;

	bool complete() const;

	std::size_t duels_count() const	{ return m_duels.size(); }

	const duel get_duel(std::size_t index) const {
		assert(index < duels_count()); return m_duels[index];
	}

	void open() { m_opened = true; }

	bool is_invalid() const;

	friend std::ostream& operator<<(std::ostream& os, round obj)
	{
		duels::const_iterator itr = obj.m_duels.begin();
		duels::const_iterator end = obj.m_duels.end();
		for ( ; itr != end ; ++itr ) {
			os 	<< obj.name() << *itr << std::endl;
		}
		return os;
	}

// accessors
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
	type_of_prop prop_name() const;
#include <libs/round.inc>

private:

	bool m_opened;
// members
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
	type_of_prop m_##prop_name;
#include <libs/round.inc>

	duels m_duels;
};

inline bool operator==(const round& lhs, const round& rhs)
{
	return lhs.name() == rhs.name();
}

std::ostream& operator<<(std::ostream& os, std::vector<round> a_collection);

}

#endif

