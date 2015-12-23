
#include "wheel.h"
#include "WheelDumper.h"

VGame::CLR::Wheel::Wheel() : _Impl(new VGame::Native::WheelImplement())
{
	
}

VGame::CLR::Wheel::~Wheel()
{
	if (_Impl != NULL)
	{
		delete _Impl;
		_Impl = NULL;
	}
	
}

VGame::CLR::Wheel::!Wheel()
{
	if (_Impl != NULL)
	{
		delete _Impl;
		_Impl = NULL;
	}

}


VGame::CLR::Output VGame::CLR::Wheel::Spin(Input rule)
{

	if (rule.Free == 0 && rule.Fever == 0 && rule.WinSet == 0)
	{
		return _Impl->SpinNormal(rule);
	}
	else
		return _Impl->Spin(rule);
}

void VGame::CLR::Wheel::Import(const VGame::CLR::Dump::WheelFieldSet% set )
{
	VGame::Native::Dump::WheelDumper dumper = VGame::Native::Dump::WheelDumper(*_Impl);

	dumper.Import(set);
}
VGame::CLR::Dump::WheelFieldSet VGame::CLR::Wheel::Export()
{
	VGame::Native::Dump::WheelDumper dumper = VGame::Native::Dump::WheelDumper(*_Impl);	
	
	return dumper.Export();
}


