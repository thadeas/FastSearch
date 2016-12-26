#pragma once
#include "types.h"

/*
This file contains all error codes which could be returned from the application
*/

// check result error code from functions
// param[in] result Result of the function.
// return true if result contains success; false if it contains fail.
inline bool SUCCESS_RESULT(ErrorCode result) { return result == EXIT_SUCCESS; }

// check result error code from functions
// param[in] result Result of the function.
// return false if result contains success; true if it contains fail.
inline bool FAILED_RESULT(ErrorCode result) { return result != EXIT_SUCCESS; }