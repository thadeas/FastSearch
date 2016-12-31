#include "stdafx.h"
#include "kmplps.h"

using namespace std;

TKmpLps CKmpLps::Compute(const string & pattern)
{
	if (pattern.empty()) {
		throw invalid_argument("KMP LPS receive empty pattern.");
#ifdef _DEBUG
		assert(false);
#endif
	}

	// create lps[] that will hold the longest prefix suffix
	TKmpLps lps(pattern.size(), 0);

	// length of the previous longest prefix suffix
	size_t len = 0;

	lps[0] = 0; // lps[0] is always 0

	// the loop calculates lps[i] for index = 1 to pattern.size()-1
	size_t index = 1;
	while (index < pattern.size())
	{
		if (pattern[index] == pattern[len])	{
			len++;
			lps[index] = len;
			index++;
		}
		else { // (patttern[index] != patttern[len])
			if (len != 0) {
				len = lps[len - 1];
				// Also, note that we do not increment
				// index here
			}
			else { // if (len == 0)
				lps[index] = 0;
				index++;
			}
		}
	}

	return lps;
}

void CKmpLps::Factory::CreateKmpLps(shared_ptr<IKmpLps> & spKmpLps)
{
	shared_ptr<CKmpLps> spImpl = make_shared<CKmpLps>();
	spKmpLps = spImpl;
}
