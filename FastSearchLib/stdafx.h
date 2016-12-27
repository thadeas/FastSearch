// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <memory>
#include "types.h"
#include "errors.h"

//////////////////////////////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////////////////////////////


static const size_t PATTERN_PREFIX_LENGTH = 3;            // prefix length (characters before the pattern)
static const size_t PATTERN_SUFIX_LENGTH = 3;             // sufix length (characters after the pattern)
static const size_t MAXIMUM_PATTERN_LENGTH = 128;         // max length of pattern
static const size_t MAXIMUM_THREADS = 10;                 // maximum threads to be used in single search block
