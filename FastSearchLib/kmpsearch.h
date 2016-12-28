#pragma once
#include "stdafx.h"
#include "kmpsearch_intf.h"
#include "kmplps_intf.h"

using namespace std;

class CKmpSearch : public IKmpSearch 
{
public:
	// constructor
	// params[in] lps longest proper prefix which is also suffix (used by KMP - preprocessed from pattern)
	explicit CKmpSearch(const vector<size_t> & lps);

public:
	vector<SearchResult> Run() override;

protected:
	const TKmpLps & m_lps;
};
