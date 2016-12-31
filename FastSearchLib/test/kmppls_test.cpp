#include "common.h"
#include "CppUnitTest.h"
#include "..\kmplps.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace CKmpPls_unitTest
{
	TEST_CLASS(CKmpPls_Test)
	{
	public:
		// Verify that invalid inputs throw an exception.  
		TEST_METHOD(CKmpPls_Compute_Empty_Pattern)
		{
			try {
				string pattern = "";
				// test
				CKmpLps kmpPls;
				TKmpLps plsResult = kmpPls.Compute(pattern);
			}
			catch (std::invalid_argument ex)
			{
				// Correct exception.  
			}
			catch (...)
			{
				_swprintf(message, L"Incorrect exception from compute LPS");
				Assert::Fail(message, LINE_INFO());
			}
		}

		TEST_METHOD(CKmpPls_Compute_1char_Pattern)
		{
			string pattern = "a";
			// test
			CKmpLps kmpPls;
			TKmpLps plsResult = kmpPls.Compute(pattern);
			// result
			TKmpLps kmpPls_expected = {0};
			Assert::IsTrue(IsEqual(plsResult, kmpPls_expected), L"Expected PLS in KMP algorithm.", LINE_INFO());
		}	

		TEST_METHOD(CKmpPls_Compute_AAAA_Pattern)
		{
			string pattern = "AAAA";
			// test
			CKmpLps kmpPls;
			TKmpLps plsResult = kmpPls.Compute(pattern);
			// result
			TKmpLps kmpPls_expected = { 0, 1, 2, 3 };
			Assert::IsTrue(IsEqual(plsResult, kmpPls_expected), L"Expected PLS in KMP algorithm.", LINE_INFO());
		}

		TEST_METHOD(CKmpPls_Compute_ABCDE_Pattern)
		{
			string pattern = "ABCDE";
			// test
			CKmpLps kmpPls;
			TKmpLps plsResult = kmpPls.Compute(pattern);
			// result
			TKmpLps kmpPls_expected = { 0, 0, 0, 0, 0 };
			Assert::IsTrue(IsEqual(plsResult, kmpPls_expected), L"Expected PLS in KMP algorithm.", LINE_INFO());
		}

		TEST_METHOD(CKmpPls_Compute_AABAACAABAA_Pattern)
		{
			string pattern = "AABAACAABAA";
			// test
			CKmpLps kmpPls;
			TKmpLps plsResult = kmpPls.Compute(pattern);
			// result
			TKmpLps kmpPls_expected = { 0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5 };
			Assert::IsTrue(IsEqual(plsResult, kmpPls_expected), L"Expected PLS in KMP algorithm.", LINE_INFO());
		}

		TEST_METHOD(CKmpPls_Compute_AAACAAAAAC_Pattern)
		{
			string pattern = "AAACAAAAAC";
			// test
			CKmpLps kmpPls;
			TKmpLps plsResult = kmpPls.Compute(pattern);
			// result
			TKmpLps kmpPls_expected = { 0, 1, 2, 0, 1, 2, 3, 3, 3, 4 };
			Assert::IsTrue(IsEqual(plsResult, kmpPls_expected), L"Expected PLS in KMP algorithm.", LINE_INFO());
		}

		TEST_METHOD(CKmpPls_Compute_AAABAAA_Pattern)
		{
			string pattern = "AAABAAA";
			// test
			CKmpLps kmpPls;
			TKmpLps plsResult = kmpPls.Compute(pattern);
			// result
			TKmpLps kmpPls_expected = { 0, 1, 2, 0, 1, 2, 3 };
			Assert::IsTrue(IsEqual(plsResult, kmpPls_expected), L"Expected PLS in KMP algorithm.", LINE_INFO());
		}

		wchar_t message[200];

	};
}