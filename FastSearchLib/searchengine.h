#pragma once
#include "stdafx.h"
#include "searchengine_intf.h"

class CSearchEngine : public ISearchEngine {
public:
	void Initialize();

	// \copydoc ISearchEngine::Search
	void Search(const string & filePath, const string & pattern) override;
};
