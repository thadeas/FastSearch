#pragma once
#include <vector>

using namespace std;

/* Preprocessed lps in KMP search algorithm
lps indicates longest proper prefix which is also suffix. A proper prefix is prefix with whole string not allowed.
*/

// type for lps (longest proper prefix which is also suffix) from KMP algorithm
using TKmpLps = vector<size_t>;

class IKmpLps {
public:
	// Creates KMP lps vector from pattern
	// \param[out] lps longest proper prefix which is also suffix
	// \param[in] pattern search pattern
	virtual TKmpLps Compute(const string & pattern) = 0;
};
