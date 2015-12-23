#include "AdjustValue.h"




namespace VGame
{
	namespace Native
	{
		void AdjustValue::_Set(ULONG ulID, ULONG ulValue)
		{
			if (ulID >= DEF_ADJUSTVALUE_MAX)
			{
				return;
			}
			if (ulValue < stcAdjustValueInformationForSW[ulID].uwMax)
			{
				ubAdjustValueTempDataForSW[ulID] = ulValue;
			}
		}
		AdjustValue::AdjustValue()
		{
			SLONG slLoop;
			UBYTE ubDefault;

			for (slLoop = 0; slLoop < DEF_ADJUSTVALUE_MAX; slLoop++)
			{

				
				ubDefault = stcAdjustValueInformationForSW[slLoop].uwDefault;

				ubAdjustValueDataForSW[slLoop] = ubDefault;
				ubAdjustValueTempDataForSW[slLoop] = ubDefault;
			}
		}


		AdjustValue::~AdjustValue()
		{
		}
		ULONG AdjustValue::Read(ULONG ulID)
		{
			if (ulID >= DEF_ADJUSTVALUE_MAX)
			{
				return (0);
			}
			if (ubAdjustValueDataForSW[ulID] >= DEF_ADJUSTVALUE_MAX)
			{
				return (0);
			}

			return (stcAdjustValueInformationForSW[ulID].ulValue[ubAdjustValueDataForSW[ulID]]);
		}
		ULONG AdjustValue::ReadMin()
		{
			return Read(DEF_ADJUSTVALUE_MIN_BET);
		}
		ULONG AdjustValue::ReadMax()
		{
			return Read(DEF_ADJUSTVALUE_MAX_BET);
		}
		ULONG AdjustValue::ReadGameRateLevel()
		{
			return Read(DEF_ADJUSTVALUE_GAME_RATE);
		}
		ULONG AdjustValue::ReadRateModeLevel()
		{
			return Read(DEF_ADJUSTVALUE_GAME_UNDULATE);
		}
		ULONG AdjustValue::ReadBetForGift()
		{
			return Read(DEF_ADJUSTVALUE_GIFT_BET);
		}
		ULONG AdjustValue::ReadWupLimitTop()
		{
			return Read(DEF_ADJUSTVALUE_WUP_LIMIT);
		}
		ULONG AdjustValue::ReadWupAsnLose()
		{
			return Read(DEF_ADJUSTVALUE_WUP_LOSE);	// ¡¨ ‰≤π≈∆
		}
		ULONG AdjustValue::ReadWupRateLevel()
		{
			return Read(DEF_ADJUSTVALUE_WUP_RATE);
		}
		ULONG AdjustValue::ReadWupAsnKill()
		{
			return Read(DEF_ADJUSTVALUE_WUP_KILL);
		}
		void AdjustValue::Setup(void)
		{
			SLONG slLoop;

			for (slLoop = 0; slLoop < DEF_ADJUSTVALUE_MAX; slLoop++)
			{
				ubAdjustValueTempDataForSW[slLoop] = ubAdjustValueDataForSW[slLoop];
			}
		}
		void AdjustValue::SetMinBet(int val)
		{
			_Set(DEF_ADJUSTVALUE_MIN_BET , val);
		}
		void AdjustValue::SetMaxBet(int val)
		{
			_Set(DEF_ADJUSTVALUE_MAX_BET, val);
		}
		void AdjustValue::SetGameRate(int val)
		{
			_Set(DEF_ADJUSTVALUE_GAME_RATE, val);
		}
		void AdjustValue::SetGameUndulate(int val)
		{
			_Set(DEF_ADJUSTVALUE_GAME_UNDULATE, val);
		}
		void AdjustValue::SetWupRate(int val)
		{
			_Set(DEF_ADJUSTVALUE_WUP_RATE, val);
		}
		void AdjustValue::UpDate()
		{
			SLONG slLoop;

			for (slLoop = 0; slLoop < DEF_ADJUSTVALUE_MAX; slLoop++)
			{
				ubAdjustValueDataForSW[slLoop] = ubAdjustValueTempDataForSW[slLoop];
			}
		}
	}
}