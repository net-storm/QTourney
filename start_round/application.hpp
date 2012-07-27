/// \date    Thu Apr 21 16:26:44 MSK 2011 -- 

#ifndef _12B5B79B_59DC_44F9_85C3_A8E6A25083F7_  
#define _12B5B79B_59DC_44F9_85C3_A8E6A25083F7_

// Project specific includes
#include <libs/round.hpp>

// Standard includes
#include <istream>
#include <vector>
#include <string>

namespace  tournament { 

// forward declarations
class participant;
class round;
class duel;

namespace  start_round {

class application
{
public: // typedefs
	typedef std::vector<participant> participants;
	typedef std::vector<round> rounds;

public: // interface

	application(int argument_count, char * argument_values[]);
 
	int run();

private: // methods

	void parce(const std::string& record);

	void process_file(const std::string& name);

	void process_stream(std::istream& is);

private: // members
	bool m_exit;
	bool m_winners_only;
	int m_debug_level;
	rounds m_rounds;
	bool m_from_file;
	std::string m_file_name;
	std::string m_round_name;
};

} }

#endif
