/// \date    Fri Apr 22 14:58:29 MSK 2011 -- 

#ifndef _8F66FAAF_77EA_40AA_9C98_DEED62C2300C_
#define _8F66FAAF_77EA_40AA_9C98_DEED62C2300C_

#include <string>
#include <map>

namespace tournament {

struct score
{
	score()
		: hits(0)
		, forfeits(0)
		, rating(0)
		, winner(false)
	{}

	int hits;
	int forfeits;
	int rating;
	bool winner;
};

}

#endif