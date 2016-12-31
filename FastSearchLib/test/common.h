// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"
#include <memory.h>

template<typename T>
inline bool IsEqual(const T & vector1, const T & vector2)
{
	bool is_equal = false;
	if (vector1.size() < vector2.size()) {
		is_equal = std::equal(vector1.begin(), vector1.end(), vector2.begin());
	}
	else {
		is_equal = std::equal(vector2.begin(), vector2.end(), vector1.begin());
	}
	return is_equal;
}

