// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <assert.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <process.h>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include "types.h"
#include "errors.h"
#include "common.h"

// convert string to wstring
inline std::wstring string_to_wstring(const std::string& text) {
	return std::wstring(text.begin(), text.end());
}

inline std::string wstring_to_string(const std::wstring& text) {
	return std::string(text.begin(), text.end());
}