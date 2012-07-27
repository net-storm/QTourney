/// \date    Thu Apr 21 19:17:20 MSK 2011 -- 

// Project specific includes
#include <start_round/application.hpp>

// Standard includes
#include <iostream>
#include <typeinfo>

//#define HOLD_CONSOLE_OPEN

int main(int ac, char* av[])
{
	try {
		using namespace tournament::start_round;
		application app = application(ac,av);
		int result = app.run();
#		ifdef HOLD_CONSOLE_OPEN
		{
			std::cin.get();
		}
#		endif
		return result;
	} catch(const std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
	} catch(...) {
		std::cerr << "Exception of unknown type!\n";
	}
#	ifdef HOLD_CONSOLE_OPEN
	{
		std::cin.get();
	}
#	endif
	return 1;
}

