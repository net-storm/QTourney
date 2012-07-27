/// \date    Thu Apr 21 16:29:33 MSK 2011 -- 

#ifndef _63924F58_1871_4621_A7F2_F76A0DBA83DF_
#define _63924F58_1871_4621_A7F2_F76A0DBA83DF_

// Standard includes
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

namespace tournament { namespace details { 

// forward declarations
class state;

namespace states {

class factory
{
public:
//	void register 
private:
    typedef std::map<std::string, std::string> prototype_id;
    typedef boost::shared_ptr<details::state> prototype;
public:
    static const prototype create(prototype_id const& id);
};

} } }

#endif
