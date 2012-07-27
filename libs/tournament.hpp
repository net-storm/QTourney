#ifndef PAIRS_MODEL_HPP
#define PAIRS_MODEL_HPP

#include <libs/round.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace tournament {

class participant;
class round;

}

class Tournament
{
	typedef std::vector<tournament::round> round_collection;
	typedef std::vector<tournament::participant> participants;
	typedef round_collection::const_iterator const_round_iter;
	typedef round_collection::iterator round_iter;
public:
	int duels_count() const;

	int rounds_count() const;

	bool update_pair(const std::string &record);

	bool select_round(const std::string &new_name);

	tournament::round get_round(std::size_t index);

	tournament::round get_current_round();

	void add_round(const tournament::round& new_round);

	void open_next_round();

	int round_index(const std::string & round_name) const;

private:
	std::string m_current_round;
	round_collection m_rounds;
};



#endif // PAIRS_MODEL_HPP
