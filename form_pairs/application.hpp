///
/// Copyright &copy; Sergey Stepanov 2010-2011. All rights reserved.
/// \file    form_pairs.hpp, v 1.0 2011/04/05 15:47:28 Garret
/// \brief    module ()
/// \author  Sergey Stepanov (net_storm@rambler.ru)
/// \date    Tue Apr 05 15:47:28 MSK 2011 -- Initial design
/// \par     Maintenance person:
///          Sergey Stepanov (net_storm@rambler.ru)
///

#ifndef   __TOURMANENT__FORM_PAIRS__FORM_PAIRS_HPP__
#  define __TOURMANENT__FORM_PAIRS__FORM_PAIRS_HPP__

// Project specific includes
#include <libs/participant.hpp>
#include <libs/duel.hpp>

// Standard includes
#include <istream>
#include <vector>
#include <string>

namespace  tournament {

// forward declarations
class participant;
class round;
class duel;

namespace  form_pairs {

class application
{
public: // typedefs
	typedef std::vector<participant> collection;
	typedef std::vector<duel> series;
	enum seed_type {
		  as_is = 0
		, by_score
		, by_advantage
		, random
		, by_teams
	};

public: // interface
	application(int argument_count, char* argument_values[]);

	int run();

private: // methods

	void process_file(const std::string& name);

	void process_stream(std::istream& is);

	void compute_pairs();

	void form_pairs_as_is(const collection& a_collection);

	void form_pairs_randomly(collection& a_collection);

	void form_pairs_by_score(collection& a_collection);

	void form_pairs_by_advantage(collection& a_collection);

	void form_pairs_by_teams(const collection& a_collection);

private: // members
	seed_type m_seed_type;
	bool m_exit;
	int m_debug_level;
	collection m_participants;
	series m_series;
	bool m_from_file;
	std::string m_file_name;
};

} }

#endif
