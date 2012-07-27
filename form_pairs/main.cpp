///
/// Copyright &copy; Sergey Stepanov 2010-2011. All rights reserved.
/// \file    main.cpp, v 1.0 2011/04/05 15:54:34 Garret
/// \brief    module ()
/// \author  Sergey Stepanov (net_storm@rambler.ru)
/// \date    Tue Apr 05 15:54:34 MSK 2011 -- Initial design
/// \par     Maintenance person:
///          Sergey Stepanov (net_storm@rambler.ru)
///

// Project specific includes
#include <form_pairs/application.hpp>

// Standard includes
#include <iostream>

//#define HOLD_CONSOLE_OPEN

int main(int ac, char* av[])
{
	try {
		using namespace tournament::form_pairs;
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

