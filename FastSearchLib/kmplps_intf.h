#pragma once
#include <vector>

using namespace std;

/* Preprocessed LPS in KMP search algorithm
LPS indicates longest proper prefix which is also suffix. A proper prefix is prefix with whole string not allowed.
*/

// type for LPS (longest proper prefix which is also suffix) from KMP algorithm
using TKmpLps = vector<size_t>;

class IKmpLps {
public:
	virtual ~IKmpLps() {}

public:
	// Creates KMP lps vector from pattern
	// \param[out] lps longest proper prefix which is also suffix
	// \param[in] pattern search pattern
	virtual TKmpLps Compute(const string & pattern) = 0;
};
