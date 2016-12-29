#pragma once
#include "stdafx.h"
#include "kmplps_intf.h"

using namespace std;

class CKmpLps : public IKmpLps {
public:
	// \copydoc IKmpLps::Compute
	TKmpLps Compute(const string & pattern) override;

public:
	// this struct is used for creating object.
	struct Factory {
		/* Creates instance of CKmpLps object
		param[out] spKmpLps instance of CKmpLps
		*/
		virtual void CreateKmpLps(shared_ptr<IKmpLps> & spKmpLps);
	};
};
