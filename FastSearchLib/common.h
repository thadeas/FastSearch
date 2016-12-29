#pragma once

//////////////////////////////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////////////////////////////


static const long PATTERN_PREFIX_LENGTH = 3;              // prefix length (characters before the pattern)
static const long PATTERN_SUFIX_LENGTH = 3;               // sufix length (characters after the pattern)
static const size_t MAXIMUM_PATTERN_LENGTH = 128;         // max length of pattern
static const size_t MAXIMUM_THREADS = 10;                 // maximum threads to be used in single search block

static const wchar_t PATH_SEPARATOR = L'\\';              // UNC path separator


														  // size of chunk read from the input (if possible)
														  // this is just a magic number - this only have to be longer then pattern 
														  // (otherwise search algorithm must be changed in read from buffer (chunk) part)
const long MAX_CHUNK_SIZE = (PATTERN_PREFIX_LENGTH + MAXIMUM_PATTERN_LENGTH + PATTERN_SUFIX_LENGTH) * 10;

static const char INVALID_BUFFER_CHARACTER = '\0';        // invalid buffer character

