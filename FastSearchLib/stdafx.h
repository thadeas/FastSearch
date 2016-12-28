// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma comment(lib, "Shlwapi.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include "types.h"
#include "errors.h"

//////////////////////////////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////////////////////////////


static const size_t PATTERN_PREFIX_LENGTH = 3;            // prefix length (characters before the pattern)
static const size_t PATTERN_SUFIX_LENGTH = 3;             // sufix length (characters after the pattern)
static const size_t MAXIMUM_PATTERN_LENGTH = 128;         // max length of pattern
static const size_t MAXIMUM_THREADS = 10;                 // maximum threads to be used in single search block

static const wchar_t PATH_SEPARATOR = L'\\';              // UNC path separator


// size of chunk read from the input (if possible)
// this is just a magic number - this only have to be longer then pattern 
// (otherwise search algorithm must be changed in read from buffer (chunk) part)
const size_t MAX_CHUNK_SIZE = (PATTERN_PREFIX_LENGTH + MAXIMUM_PATTERN_LENGTH + PATTERN_SUFIX_LENGTH) * 10;

// convert string to wstring
inline std::wstring string_to_wstring(const std::string& text) {
	return std::wstring(text.begin(), text.end());
}