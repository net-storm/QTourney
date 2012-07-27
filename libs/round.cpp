#include <libs/round.hpp>

// Standard includes
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <string>

namespace {

static std::string to_string( const std::string& value )
{
	return value;
}

static int to_integer( const std::string& value )
{
	try {
		return boost::lexical_cast<int>(value);
	} catch (boost::bad_lexical_cast const&) {
		return 0;
	}
}

static bool to_deathmatch_t( const std::string& value )
{
	if (value == "deathmatch") {
		return true;
	} else {
		return false;
	}
}

}

namespace tournament {

round::round(const std::string& record)
: m_opened(false)
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
	, m_##prop_name(default_value)
#include <libs/round.inc>
{
	using namespace boost::algorithm;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> separators(":", "", boost::keep_empty_tokens);
	tokenizer tokens(record, separators);
	std::string value;
	int token_index = 0;
	for ( tokenizer::iterator tok_iter = tokens.begin()
		; tok_iter != tokens.end()
		; ++tok_iter, ++token_index
	) {
		value = trim_copy(*tok_iter);
		switch (prop_role(token_index)) {
#define ROUND_PROPERTY(type_of_prop, prop_name, default_value, req) \
			case prop_role_##prop_name : m_##prop_name = to_##type_of_prop(value); break;
#include <libs/round.inc>
			default: {
				if(!value.empty()) {
					m_the_rest = trim_copy(m_the_rest + " " + value);
				}
				break;
			}
		}
	}
	if (m_status.empty()) {
		m_status = "Plan";
	}
}

void round::update(const duel::state_t a_state)
{
	duels::iterator found = m_duels.end();// = std::find
	for ( found = m_duels.begin()
		; found != m_duels.end()
		; ++found
	) {
		if (found->participating(a_state->winner().id())
		&&  found->participating(a_state->loser().id())
		) {
			break;
		}
	}
	if (m_duels.end() != found) {
		found->update(a_state);
	} else {
		duel a_duel("", a_state);
		m_duels.push_back(a_duel);
	}
}

const round::partisipants round::winners() const
{
	partisipants results;
	duels::const_iterator itr = m_duels.begin();
	duels::const_iterator end = m_duels.end();
	for ( ; itr != end ; ++itr ) {
		if (itr->complete()) {
			const participant& a_participant = itr->winner();
			if (a_participant != participant::bye()) {
				results.push_back(a_participant);
			}
		}
	}
	return results;
}

const round::partisipants round::losers() const
{
	partisipants results;
	duels::const_iterator itr = m_duels.begin();
	duels::const_iterator end = m_duels.end();
	for ( ; itr != end ; ++itr ) {
		if (itr->complete()) {
			const participant& a_participant = itr->loser();
			if (a_participant != participant::bye()) {
				results.push_back(a_participant);
			}
		}
	}
	return results;
}

bool round::complete() const
{
	if (m_duels.empty()) return false;

	duels::const_iterator itr = m_duels.begin();
	duels::const_iterator end = m_duels.end();
	for (; itr != end; ++itr) {
		if (!itr->complete()) return false;
	}
	return true;
}

bool round::is_invalid() const
{
	return name().empty();
}

std::string round::status() const
{
	std::string result = "planned";
	if (m_opened) {
		result = "opened";
		if (!m_duels.empty()){
			result = "started";
			if (complete()){
				result = "finished";
			}
		}
	}
	return result;
}

std::string round::name() const { return m_name; }

std::string round::seed() const { return m_seed; }

int round::size() const { return m_size; }

bool round::deathmatch() const { return m_deathmatch; }

std::string round::the_rest() const { return m_the_rest; }

std::ostream& operator<<(std::ostream& os, std::vector<round> a_collection)
{
	int i = 0;
	std::vector<round>::const_iterator itr = a_collection.begin();
	std::vector<round>::const_iterator end = a_collection.end();
	for ( ; itr != end; ++itr ) {
		std::cout
		//<< ++i << "\t"
		<< *itr << std::endl;
	}
	return os;
}

}
