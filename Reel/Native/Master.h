#pragma once
#include "../Source/common.h"
NAMESPACE_NATIVE_BEGIN
class Master
{

	friend class VGame::Native::Dump::WheelDumper;
	MASTERINFO stcMaster;
public:
	
	Master();
	~Master();

	UBYTE	GetDemoFlag	();
};

NAMESPACE_NATIVE_END

