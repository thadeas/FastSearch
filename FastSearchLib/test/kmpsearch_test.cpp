#include "common.h"
#include "CppUnitTest.h"
#include "../kmpsearch.h"
#include "../fakes/fakes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace CKmpSearch_unitTest
{

	TEST_CLASS(CKmpSearch_Test)
	{
	public:

		TEST_METHOD(CKmpSearch_Process_search_A_in_x)
		{
			// prepare
			string pattern = "A";
			TKmpLps lps = { 0 };

			CFileBufferFake buffer;
			buffer.m_bufferCurrent = { 'x' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 0, L"Check empty result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_1_search_A_in_A) 
		{
			// prepare
			string pattern = "A";
			TKmpLps lps = { 0 };

			CFileBufferFake buffer;
			buffer.m_bufferCurrent = { 'A' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 0, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix.empty(), L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix.empty(), L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_1_search_A_in_AA)
		{
			// prepare
			string pattern = "A";
			TKmpLps lps = { 0 };

			CFileBufferFake buffer;
			buffer.m_bufferCurrent = { 'A', 'A' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 0, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix.empty(), L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "A", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 0, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "A", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix.empty(), L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_1_search_AAAA_in_AAAAABAAABA)
		{
			// prepare
			string pattern = "AAAA";
			TKmpLps lps = { 0, 1, 2, 3 };

			CFileBufferFake buffer;
			buffer.m_bufferCurrent = { 'A', 'A', 'A', 'A', 'A', 'B', 'A', 'A', 'A', 'B', 'A'};

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 0, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix.empty(), L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "ABA", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "A", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "BAA", L"Check result", LINE_INFO());
		}

	};
}