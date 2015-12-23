#pragma once
#include <windows.h>
#include <vcclr.h>
#using <System.dll>
#include "Source\common.h"
#include "Native\WheelImplement.h"
#include "Input.h"
#include "Output.h"
using namespace System;
namespace VGame
{
	namespace CLR
	{
		
			public ref class Wheel
			{
				
				VGame::Native::WheelImplement* _Impl;
			protected:
					!Wheel	();

				
			public:
					Wheel	();
					~Wheel	();


				Output	Spin		(Input rule);	

				Dump::WheelFieldSet	Export();
				void Import(const Dump::WheelFieldSet% set);
			};
		}
		
	
	
}
