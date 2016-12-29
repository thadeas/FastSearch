#pragma once
#include "stdafx.h"
#include "kmpsearch_intf.h"
#include "kmplps_intf.h"

using namespace std;

class CKmpSearch : public IKmpSearch 
{
public:
	// constructor
	// params[in] pattern Pattern to be searched in file
	// params[in] lps longest proper prefix which is also suffix (used by KMP - preprocessed from pattern)
	explicit CKmpSearch(const string & pattern, const TKmpLps & lps);

public:
	// \copydoc IKmpSearch::Run
	TSearchResults Run() override;

protected:
	const TKmpLps & m_lps;
	const string & m_pattern;
};
