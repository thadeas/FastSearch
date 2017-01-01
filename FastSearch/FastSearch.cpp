// FastSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "application.h"
#include <memory>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{	
	try {
		auto_ptr<CApplication> spApplication (new CApplication);
		spApplication->Initialize(argc, argv);
		spApplication->Run();
	}
	catch (std::exception& e) {
		cout << "ERROR: " << e.what();
	}
	catch (...) {
		// operation failed
		cout << "ERROR: Fast search failed from unknown reason.";
		return EXIT_FAILURE;
	}
	
    return EXIT_SUCCESS;
}

