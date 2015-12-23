#pragma once

#include "Native\WheelImplement.h"

namespace VGame
{
	namespace Native
	{
		namespace Dump
		{
			class WheelDumper
			{
				VGame::Native::WheelImplement& _Wheel;

				void _SetRecord(VGame::Native::Record& record, const VGame::CLR::Dump::RecordFieldSet% set) const;
				void _SetAdjustValue(VGame::Native::AdjustValue& adjust_value , const VGame::CLR::Dump::AdjustValueSet% set) const;
				void _SetWupChance(WUPCHANCE_BUF& wupchance_buf , const VGame::CLR::Dump::WupChanceBuf% set)const;
				void _SetSlave(VGame::Native::Slave& slave , const VGame::CLR::Dump::SlaveSet% set)const;
				void _SetReel(VGame::Native::Reel& reel , const VGame::CLR::Dump::ReelSet% set)const;
				void _SetMaster(MASTERINFO& master , const VGame::CLR::Dump::MasterInfo% set)const;
				void _SetChance(VGame::Native::Chance& chance, const VGame::CLR::Dump::ChanceSet% set)const;

				VGame::CLR::Dump::RecordFieldSet _GetRecord(const VGame::Native::Record& record) const;
				VGame::CLR::Dump::AdjustValueSet _GetAdjustValue(const VGame::Native::AdjustValue& adjust_value) const ;
				VGame::CLR::Dump::WupChanceBuf _GetWupChance(const WUPCHANCE_BUF& wupchance_buf)const ;

				VGame::CLR::Dump::SlaveSet _GetSlave(const VGame::Native::Slave& slave)const ;
				VGame::CLR::Dump::ReelSet _GetReel(const VGame::Native::Reel& reel)const;
				VGame::CLR::Dump::MasterInfo _GetMaster(const MASTERINFO& master)const;
				VGame::CLR::Dump::ChanceSet _GetChance(const VGame::Native::Chance& chance)const;

			public:
				WheelDumper(VGame::Native::WheelImplement& wheel);

				VGame::CLR::Dump::WheelFieldSet Export() const;

				void Import(const VGame::CLR::Dump::WheelFieldSet% set);
			};
		}
		
	}
}

