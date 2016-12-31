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

		TEST_METHOD(CKmpSearch_Process_search_A_in_A) 
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

		TEST_METHOD(CKmpSearch_Process_search_A_in_AA)
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

			Assert::IsTrue(results[1].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "A", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix.empty(), L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_search_AAAA_in_AAAAABAAABA)
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

		TEST_METHOD(CKmpSearch_Process_prefixFromPreviousBuffer)
		{
			// prepare
			string pattern = "AAAA";
			TKmpLps lps = { 0, 1, 2, 3 };

			CFileBufferFake buffer;
			buffer.m_bufferPrev = { 'w', 'x', 'y', 'z' };
			buffer.m_bufferCurrent = { 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'A', 'A', 'B', 'A' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 3, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 0, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "xyz", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "AAB", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "yzA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "ABA", L"Check result", LINE_INFO());

			Assert::IsTrue(results[2].position == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].prefix == "zAA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].sufix == "BAA", L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_prefixFromPreviousBuffer_short)
		{
			// prepare
			string pattern = "AAAA";
			TKmpLps lps = { 0, 1, 2, 3 };

			CFileBufferFake buffer;
			buffer.m_bufferPrev = { 'z' };
			buffer.m_bufferCurrent = { 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'A', 'A', 'B', 'A' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 3, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 0, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "z", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "AAB", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "zA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "ABA", L"Check result", LINE_INFO());

			Assert::IsTrue(results[2].position == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].prefix == "zAA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].sufix == "BAA", L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_sufixFromNextBuffer)
		{
			// prepare
			string pattern = "AAAA";
			TKmpLps lps = { 0, 1, 2, 3 };

			CFileBufferFake buffer;
			buffer.m_bufferCurrent = { 'B', 'A', 'A', 'A', 'A', 'A', 'A' };
			buffer.m_bufferNext = { 'w', 'x', 'y', 'z' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 3, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "B", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "AAw", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "BA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "Awx", L"Check result", LINE_INFO());

			Assert::IsTrue(results[2].position == 3, L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].prefix == "BAA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].sufix == "wxy", L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_sufixFromNextBuffer_short)
		{
			// prepare
			string pattern = "AAAA";
			TKmpLps lps = { 0, 1, 2, 3 };

			CFileBufferFake buffer;
			buffer.m_bufferCurrent = { 'B', 'A', 'A', 'A', 'A', 'A', 'A' };
			buffer.m_bufferNext = { 'w' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 3, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "B", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "AAw", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "BA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "Aw", L"Check result", LINE_INFO());

			Assert::IsTrue(results[2].position == 3, L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].prefix == "BAA", L"Check result", LINE_INFO());
			Assert::IsTrue(results[2].sufix == "w", L"Check result", LINE_INFO());
		}


		TEST_METHOD(CKmpSearch_Process_replaceSpecialCharacters)
		{
			// prepare
			string pattern = "AB";
			TKmpLps lps = { 0, 0 };

			CFileBufferFake buffer;
			buffer.m_bufferPrev = { 'i', 'j', '\t', '\n' };
			buffer.m_bufferCurrent = {  '\t', 'A', 'B', '\n' };
			buffer.m_bufferNext = { '\t', '\n', 'x', 'y' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "\\t\\n\\t", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "\\n\\t\\n", L"Check result", LINE_INFO());

		}

		TEST_METHOD(CKmpSearch_Process_across_boundary_of_buffer)
		{
			// prepare
			string pattern = "ABBCDDD";
			TKmpLps lps = { 0, 0, 1, 0, 0, 1, 2 };

			CFileBufferFake buffer;
			buffer.m_bufferPrev = { 'w', 'x', 'y', 'z' };
			buffer.m_bufferCurrent = { 'A', 'B', 'C', 'D', 'A', 'B' };
			buffer.m_bufferNext = { 'B', 'C', 'D', 'D', 'D', 'i', 'j', 'k', 'l' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 4, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "BCD", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "ijk", L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_complex_test)
		{
			// prepare
			string pattern = "DDABBCDDD";
			TKmpLps lps = { 0, 1, 0, 0, 1, 0, 0, 1, 2 };

			CFileBufferFake buffer;
			buffer.m_bufferPrev = { 'w', 'x', 'y', 'z' };
			buffer.m_bufferCurrent = { 'D', 'D', 'D', 'A', 'B', 'B', 'C', 'D', 'D', 'D', 'A', 'B' };
			buffer.m_bufferNext = { 'B', 'C', 'D', 'D', 'D', 'i' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 1, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "yzD", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "ABB", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 8, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "BCD", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "i", L"Check result", LINE_INFO());
		}

		TEST_METHOD(CKmpSearch_Process_offset_affects_position)
		{
			// prepare
			string pattern = "DDABBCDDD";
			TKmpLps lps = { 0, 1, 0, 0, 1, 0, 0, 1, 2 };

			CFileBufferFake buffer;
			buffer.m_fileOffset = 500;
			buffer.m_bufferPrev = { 'w', 'x', 'y', 'z' };
			buffer.m_bufferCurrent = { 'D', 'D', 'D', 'A', 'B', 'B', 'C', 'D', 'D', 'D', 'A', 'B' };
			buffer.m_bufferNext = { 'B', 'C', 'D', 'D', 'D', 'i' };

			// test
			CKmpSearch kmpSearch = CKmpSearch(pattern, lps);

			// test
			const auto results = kmpSearch.Process(&buffer);

			// verify
			Assert::IsTrue(results.size() == 2, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].position == 501, L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].prefix == "yzD", L"Check result", LINE_INFO());
			Assert::IsTrue(results[0].sufix == "ABB", L"Check result", LINE_INFO());

			Assert::IsTrue(results[1].position == 508, L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].prefix == "BCD", L"Check result", LINE_INFO());
			Assert::IsTrue(results[1].sufix == "i", L"Check result", LINE_INFO());
		}
	};

}