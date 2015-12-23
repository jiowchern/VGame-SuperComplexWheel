#include "Master.h"

NAMESPACE_NATIVE_BEGIN

Master::Master()
{
}


Master::~Master()
{
}
UBYTE Master::GetDemoFlag()
{
	return stcMaster.ubDemoFlag;
}
NAMESPACE_NATIVE_END