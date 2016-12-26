#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\FastSearchLib\cmdparser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace CCmdParser_unitTest
{
	TEST_CLASS(CCmdParser_Test)
	{
	public:
		// Verify that invalid inputs throw an exception.  
		TEST_METHOD(CCmdParser_Initialize__Less_parameters_from_command_line_Failed)
		{
			CCmdParser cmdParser;
			char * argv[] = { "param0", "param1", "param2" };
			for (int paramCount = 0; paramCount < 3; paramCount++) {
				try
				{
					cmdParser.Initialize(paramCount, argv);

					_swprintf(message, L"No exception for input %i", paramCount);
					Assert::Fail(message, LINE_INFO());
				}
				catch (std::invalid_argument ex)
				{
					continue; // Correct exception.  
				}
				catch (...)
				{
					_swprintf(message, L"Incorrect exception for %i", paramCount);
					Assert::Fail(message, LINE_INFO());
				}
			}
		}

		// parse input from command line success  
		TEST_METHOD(CCmdParser_Initialize__Parse_command_line_Success)
		{
			try
			{
				CCmdParser cmdParser;
				char * argv[] = { "param0", "path", "pattern" };
				auto argc = end(argv) - begin(argv);
				cmdParser.Initialize(argc, argv);

				Assert::AreEqual(cmdParser.GetSearchPath().c_str(), "path", "Path is parsed.", LINE_INFO());

				Assert::AreEqual(cmdParser.GetPattern().c_str(), "pattern", "Patten is parsed.", LINE_INFO());
			}
			catch (...)
			{
				_swprintf(message, L"Exception has been captured.");
				Assert::Fail(message, LINE_INFO());
			}
		}

		wchar_t message[200];

	};
}