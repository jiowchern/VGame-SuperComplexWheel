#pragma once
#include "Slave.h"
#include "AdjustValue.h"
#include "Scroll.h"
#include "Reel.h"
#include "GameCheck.h"
#include "Chance.h"
#include "WupChance.h"
#include "Record.h"
#include "GameAssign.h"
#include "Master.h"
#include "../Input.h"
#include "../Output.h"
#include "../Field.h"
namespace VGame
{
	namespace Native
	{
		namespace Dump
		{
			class WheelDumper;
		}
	}
}

namespace VGame
{
	namespace Native
	{
		class WheelImplement
		{

			friend class VGame::Native::Dump::WheelDumper;
			SLONG slFeverWin;
			SLONG slFreeWin;
			ULONG ulPlayTimes;
			ULONG ulWinTimes;
			DLONG dlPlayTotal;
			DLONG dlWinTotal;
			DLONG dlRunTime;
			//ULONG ulFstGiftTimes[DEF_ITEM_MAX];
			//ULONG ulGiftTimes[DEF_ITEM_MAX];
			ULONG ulSwitch;
			ULONG ulRecCycle;
			//ULONG ulFillClass;
			//ULONG ulFillTimes;
			//ULONG ulLoseTimes;
			//ULONG ulAsnFillTimes;
			SLONG slWupBet;
			ULONG ulWupTime;
			ULONG ulWupPlayTimes;
			//ULONG ulWupSavemoney;
			ULONG ulWupCondi1;  //0不比倍、1比一? ,2比二?,3比三?,4比四?,5比到爆机?止
			ULONG ulWupCondi2;  //0?比倍、1比倍、2半比倍

			GameAssign _GameAssign;
			Record	_Record;
			Reel _Reel;
			WupChance _WupChance;
			Chance _Chance;
			GameCheck _GameCheck;
			Scroll _Scroll;
			AdjustValue _AdjustValue;
			Slave _Slave;
			GAMEINFO stcGameInfo;
			Master _Master;

			void				_FastWup		(SLONG ulWin);
			void				_Initial		(const VGame::CLR::Input& rule);

			VGame::CLR::Output	_BuildResult	();

			VGame::CLR::Dump::RecordFieldSet _DumpRecord();
		public:
			WheelImplement();
			~WheelImplement();
			VGame::CLR::Output		Spin		(const VGame::CLR::Input& rule);
			VGame::CLR::Output		SpinNormal	(const VGame::CLR::Input& rule);

			void					Import		(VGame::CLR::Dump::WheelFieldSet& set);
			VGame::CLR::Dump::WheelFieldSet	Export();

		};
	}
}