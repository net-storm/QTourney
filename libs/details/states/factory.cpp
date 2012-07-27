/// \date    Thu Apr 21 16:54:54 MSK 2011 -- 

// Project specific includes
#include <libs/details/states/factory.hpp>
#include <libs/details/states/challenge.hpp>
#include <libs/details/states/fighting.hpp>
#include <libs/details/states/canceled.hpp>
#include <libs/details/states/tie.hpp>
#include <libs/details/states/forfeit.hpp>
#include <libs/details/states/win.hpp>

// Standard includes
#include <boost/make_shared.hpp>

namespace tournament { namespace details { namespace states {

const factory::prototype factory::create(factory::prototype_id const& record)
{
	factory::prototype_id properties = record;
	std::string id = properties["state"];
	
    if ("challenges" == id ) return boost::make_shared<challenges>(properties);
    if ("fighting"   == id ) return boost::make_shared<fighting>(properties);
    if ("ties"       == id ) return boost::make_shared<ties>(properties);
    if ("forfeits"   == id ) return boost::make_shared<forfeits>(properties);
    if ("canceled"   == id ) return boost::make_shared<canceled>(properties);
    if ("wins"       == id ) return boost::make_shared<wins>(properties);

    return boost::make_shared<challenges>(properties); // default
}

} } }
