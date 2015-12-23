#pragma once
#include "..\Source\common.h"
namespace VGame
{
	namespace Native
	{
		class AdjustValue
		{
			friend class VGame::Native::Dump::WheelDumper;
			UBYTE ubAdjustValueDataForSW[DEF_ADJUSTVALUE_MAX];
			UBYTE ubAdjustValueTempDataForSW[DEF_ADJUSTVALUE_MAX];

			void	_Set	(ULONG ulID, ULONG ulValue);
		public:
					AdjustValue	();
					~AdjustValue();

			ULONG	Read				(ULONG ulID);

			ULONG	ReadMin				();
			ULONG	ReadMax				();
			ULONG	ReadGameRateLevel	();

			ULONG	ReadRateModeLevel	();

			ULONG	ReadBetForGift		();

			ULONG	ReadWupLimitTop		();
			
			ULONG	ReadWupAsnLose		();
			ULONG	ReadWupRateLevel	();

			ULONG	ReadWupAsnKill		();

			void	Setup				(void);

			void	SetMinBet			(int val);
			void	SetMaxBet			(int val);
			void	SetGameRate			(int val);
			void	SetGameUndulate		(int val);
			void	SetWupRate			(int val);


			void	UpDate				();
		};
	}
}

