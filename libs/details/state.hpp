/// \date    Wed Apr 20 17:41:25 MSK 2011 -- 

#ifndef _BEE028E9_E47E_4128_87BD_3A13E3253229_
#define _BEE028E9_E47E_4128_87BD_3A13E3253229_

// Standard includes
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

namespace tournament {

// forward declarations
class participant;
class duel;

namespace details {

class state
{
private:
	typedef	boost::shared_ptr<participant> participant_t;
public:
	typedef std::map<std::string, std::string> properties;		
	typedef boost::shared_ptr<state> shared;

public:
        state(const state::properties& properties);
	
    virtual ~state() {}

    // common interface

	virtual const std::string name();

    // state indications

    virtual bool complete() const = 0;

	virtual const participant winner() const = 0;

	virtual const participant loser() const = 0;
	
	const std::string details() const
	{
		return m_details;
	}

	const std::string the_rest() const
	{
		return m_the_rest;
	}

	void update_context(const shared& context);

    // available state changes (default implementations)
		
	virtual bool is_valid_state_change_to(const std::string& state_name) const = 0;

protected:
	participant_t m_winner;
	participant_t m_loser;
        std::string m_details;
	std::string m_the_rest;
};

} }


#endif // _BEE028E9_E47E_4128_87BD_3A13E3253229_
