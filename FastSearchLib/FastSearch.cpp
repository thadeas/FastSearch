// FastSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "application.h"

using namespace std;

int main(int argc, char* argv[])
{	
	try {
		auto_ptr<CApplication> spApplication (new CApplication);
		spApplication->Run(argc, argv);
	}
	catch (...) {
		// operation failed
		return EXIT_FAILURE;
	}
	



    return EXIT_SUCCESS;
}

