#include <iostream>
#include <string>
#include <exception>

#include "classifier.h"


int main(int argc, char *argv[])
{
	try
	{
		run_prediction(argc, argv);
	}
	catch (std::string error)
	{
		std::cerr << std::string("Runtime Error: ") + error;
	}
	catch (std::exception error)
	{
		std::cerr << std::string("Runtime Error: ") + std::string(error.what());
	}
	catch (...)
	{
		std::cerr << "Runtime Error: Unknown Error";
	}

	return 0;
}