/// \date    Wed Apr 20 17:41:11 MSK 2011 --

// Project specific includes
#include <libs/details/state.hpp>
#include <libs/participant.hpp>

// Standard includes
#include <boost/make_shared.hpp>
#include <string>
#include <sstream>
#include <stdexcept>

namespace tournament { namespace details { 

static const std::string get(const state::properties & properties, const std::string& key, bool mandatory = true)
{
    state::properties::const_iterator found = properties.find(key);
    if(properties.end() != found){
        state::properties copy(properties);
        return copy[key];
	} else if (mandatory) {
		std::ostringstream os;
		os << "Mandatory field '" << key << "' not found";
		throw std::runtime_error(os.str());
    }
	return "";
}

state::state(const state::properties & properties)
        : m_winner(boost::make_shared<participant>(get(properties,"winner")))
        , m_loser(boost::make_shared<participant>(get(properties,"loser")))
        , m_details(get(properties, "details"))
		, m_the_rest(get(properties, "the_rest", false))
{ }
	
const std::string state::name()
{
	std::string result = typeid(*this).name();	
	std::size_t found = 0;
	std::size_t end = 0;	
	
#  ifdef WIN32
	found = result.find_last_of(" :");
	return result.substr(found+1);
#  else
	found = result.find_last_of("0123456789");
	end = result.find_last_of("N");	
	result = result.substr(found+1);
	return result.substr(0,result.size()-1);	
#  endif
}

void state::update_context(const state::shared& context)
{
	if (*m_winner == context->winner())
	{
		m_winner->set_rating(context->winner().score());
	}
	if (*m_winner == context->loser())
	{
		m_winner->set_rating(context->loser().score());
	}
	if (*m_loser == context->loser())
	{
		m_loser->set_rating(context->loser().score());
	}
	if (*m_loser == context->winner())
	{
		m_loser->set_rating(context->winner().score());
	}
	m_winner->set_state("Upd");
	m_loser->set_state("Upd");
}


} }

