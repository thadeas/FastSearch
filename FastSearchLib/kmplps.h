#pragma once
#include "stdafx.h"
#include "kmplps_intf.h"

using namespace std;

class CKmpLps : public IKmpLps {
public:
	// \copydoc IKmpLps::Compute
	TKmpLps Compute(const string & pattern) override;
};
