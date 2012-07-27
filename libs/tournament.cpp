#include <libs/tournament.hpp>
#include <libs/round.hpp>
#include <libs/duel.hpp>
#include <libs/details/state.hpp>
#include <libs/participant.hpp>
#include <libs/details/states/factory.hpp>

// Standard includes
#  include <boost/make_shared.hpp>
#  include <boost/program_options.hpp>
#  include <boost/tokenizer.hpp>
#  include <boost/algorithm/string.hpp>
#  include <boost/lexical_cast.hpp>
#  include <algorithm>
#  include <functional>
#  include <iostream>
#  include <fstream>
#  include <iterator>
#  include <list>

namespace {

struct by_name
{
	by_name(const std::string & a_name) : m_name(a_name) {}

	bool operator()( const tournament::round& a_round ) {
		return a_round.name() == m_name;
	}

	std::string m_name;
};

}

int Tournament::duels_count() const
{
	const_round_iter beg = m_rounds.begin();
	const_round_iter end = m_rounds.end();
	const_round_iter found = std::find_if(beg, end, by_name(m_current_round));
	if (end != found) {
		return found->duels_count();
	}
	return 0;
}

int Tournament::rounds_count() const
{
	return m_rounds.size();
}

bool Tournament::update_pair(const std::string &record)
{
	if (record.empty() || record[0] == '#') return false;

	using namespace tournament;
	duel::properties a_properties = duel::read_state(record);
	duel::state_t new_state = details::states::factory::create(a_properties);

	round_iter beg = m_rounds.begin();
	round_iter end = m_rounds.end();
	round_iter found = std::find_if(beg, end, by_name(m_current_round));
	if (end == found) { // add new round to add a new pair
		// todo : insert after active round or throw an error
		m_rounds.push_back(tournament::round(":" + m_current_round));
		beg = m_rounds.begin();
		end = m_rounds.end();
		found = std::find_if(beg, end, by_name(m_current_round));
		assert (found != end);
	}

	tournament::round& a_round = *found;
	if (!a_round.complete()) {
		a_round.update(new_state);
	}

	if (a_round.complete()){
		if (end != found++) { // round is over, lets open next one
			open_next_round();
		} else { // tourney is over
			return false;
		}
	}
	return true;
}

bool Tournament::select_round(const std::string &new_name)
{
	m_current_round = new_name;
	return true;
}

void Tournament::open_next_round()
{
	round_iter itr = m_rounds.begin();
	round_iter end = m_rounds.end();
	for(; itr != end; ++itr) {
		if (!itr->complete()){
			itr->open();
			break;
		}
	}
}

int Tournament::round_index(const std::string &round_name) const
{
	const_round_iter beg = m_rounds.begin();
	const_round_iter end = m_rounds.end();
	const_round_iter found = std::find_if(beg, end, by_name(round_name));
	if (end != found) return found - beg;
	else return -1;
}

tournament::round Tournament::get_current_round()
{
	round_iter beg = m_rounds.begin();
	round_iter end = m_rounds.end();
	round_iter found = std::find_if(beg, end, by_name(m_current_round));
	if (end != found) {
		return *found;
	}
	throw std::runtime_error(std::string("not found") + m_current_round);
}

void Tournament::add_round(const tournament::round &new_round)
{
	m_rounds.push_back(new_round);
}

tournament::round Tournament::get_round(std::size_t index)
{
	return m_rounds[index];
}
