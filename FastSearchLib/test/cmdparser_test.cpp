#include "common.h"
#include "CppUnitTest.h"
#include "../cmdparser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

#define TEXT_WITH_128_CHARS "01234567890123456789012345678901234567890123456789" \
							"01234567890123456789012345678901234567890123456789" \
							"0123456789012345678901234567"

#define TEXT_WITH_129_CHARS "01234567890123456789012345678901234567890123456789" \
							"01234567890123456789012345678901234567890123456789" \
							"01234567890123456789012345678"

namespace CCmdParser_unitTest
{
	TEST_CLASS(CCmdParser_Test)
	{
	public:
		// Verify that invalid inputs throw an exception.  
		TEST_METHOD(CCmdParser_Initialize__Less_parameters_from_command_line_Failed)
		{
			char * argv[] = { "param0", "path", "pattern" };
			for (int paramCount = 0; paramCount < 3; paramCount++) {
				try
				{
					// test
					CCmdParser cmdParser;
					cmdParser.Initialize(paramCount, argv);

					_swprintf(message, L"No exception for input %i", (int)paramCount);
					Assert::Fail(message, LINE_INFO());
				}
				catch (std::invalid_argument ex)
				{
					continue; // Correct exception.  
				}
				catch (...)
				{
					_swprintf(message, L"Incorrect exception for %i", (int)paramCount);
					Assert::Fail(message, LINE_INFO());
				}
			}
		}

		// Verify that invalid inputs throw an exception.  
		TEST_METHOD(CCmdParser_Initialize__pattern_is_longer_than_128_chars_Failed)
		{
			char * argv[3] = { "param0", "path", TEXT_WITH_129_CHARS };
			const int patternLen = strlen(argv[2]);
			Assert::IsTrue(patternLen == 129, L"Pattern contains 129 chars.", LINE_INFO());   // check prerequisite
			auto argc = end(argv) - begin(argv);
			try
			{
				// test
				CCmdParser cmdParser;
				cmdParser.Initialize(argc, argv);

				_swprintf(message, L"No exception for input with %i chars", (int)patternLen);
				Assert::Fail(message, LINE_INFO());
			}
			catch (std::invalid_argument ex)
			{
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception for input with %i chars.", (int)patternLen);
				Assert::Fail(message, LINE_INFO());
			}
		}

		// parse input from command line success  
		TEST_METHOD(CCmdParser_Initialize__Parse_command_line_Success)
		{
			char * argv[] = { "param0", "path", "pattern" };
			auto argc = end(argv) - begin(argv);

			// test
			CCmdParser cmdParser;
			cmdParser.Initialize(argc, argv);

			// result
			Assert::AreEqual(cmdParser.GetSearchPath().c_str(), L"path", "Path is parsed.", LINE_INFO());
			Assert::AreEqual(cmdParser.GetPattern().c_str(), "pattern", "Patten is parsed.", LINE_INFO());
		}

		// parse input from command line success  
		TEST_METHOD(CCmdParser_Initialize__parse_pattern_with_128_chars)
		{
			char * argv[3] = { "param0", "path", TEXT_WITH_128_CHARS };
			const int patternLen = strlen(argv[2]);
			Assert::IsTrue(patternLen == 128, L"Pattern contains 128 chars.", LINE_INFO());   // check prerequisite
			auto argc = end(argv) - begin(argv);

			// test
			CCmdParser cmdParser;
			cmdParser.Initialize(argc, argv);

			// result
			Assert::AreEqual(cmdParser.GetSearchPath().c_str(), L"path", "Path is parsed.", LINE_INFO());
			Assert::AreEqual(cmdParser.GetPattern().c_str(), TEXT_WITH_128_CHARS, "Patten is parsed.", LINE_INFO());
		}

		wchar_t message[200];

	};
}