#include "Reel.h"

UBYTE const ubScrollSymbolFreeData[DEF_REEL_MAX_SYM] =
{

	DEF_SYMBOL_00,	DEF_SYMBOL_04,  DEF_SYMBOL_01,  DEF_SYMBOL_05,	DEF_SYMBOL_10,  DEF_SYMBOL_07,  DEF_SYMBOL_02,	DEF_SYMBOL_06,
	DEF_SYMBOL_12,	DEF_SYMBOL_05,	DEF_SYMBOL_03, 	DEF_SYMBOL_02,	DEF_SYMBOL_07,	DEF_SYMBOL_00,	DEF_SYMBOL_06,	DEF_SYMBOL_05,
	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_07, 	DEF_SYMBOL_10,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_07,
	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_04, 	DEF_SYMBOL_06,	DEF_SYMBOL_00,	DEF_SYMBOL_07,	DEF_SYMBOL_04,	DEF_SYMBOL_11,
	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_10, 	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_07,	DEF_SYMBOL_04,	DEF_SYMBOL_00,
	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_06, 	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_00,	DEF_SYMBOL_07,
	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_01, 	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_10,	DEF_SYMBOL_07,	DEF_SYMBOL_02,
	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_00, 	DEF_SYMBOL_03,	DEF_SYMBOL_07,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_02,
	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03, 	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_07,	DEF_SYMBOL_04,	DEF_SYMBOL_11,
	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_05, 	DEF_SYMBOL_02,	DEF_SYMBOL_07,	DEF_SYMBOL_10,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_07, 	DEF_SYMBOL_00,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,
	DEF_SYMBOL_07,	DEF_SYMBOL_02,	DEF_SYMBOL_06, 	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_10,	DEF_SYMBOL_03,	DEF_SYMBOL_05,
	DEF_SYMBOL_03,	DEF_SYMBOL_07,	DEF_SYMBOL_00, 	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_07,
	DEF_SYMBOL_00,	DEF_SYMBOL_05,	DEF_SYMBOL_06, 	DEF_SYMBOL_01,	DEF_SYMBOL_07,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
	DEF_SYMBOL_12,	DEF_SYMBOL_04,	DEF_SYMBOL_07, 	DEF_SYMBOL_01,	DEF_SYMBOL_06,	DEF_SYMBOL_00,	DEF_SYMBOL_05,	DEF_SYMBOL_03,
	DEF_SYMBOL_07,	DEF_SYMBOL_10,	DEF_SYMBOL_04, 	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_07,	DEF_SYMBOL_02,	DEF_SYMBOL_05


};


NAMESPACE_NATIVE_BEGIN
Reel::Reel(GAMEINFO& info) : stcGameInfo(info)
{ 
	memset(stcReelData , 0 , sizeof(REEL) * DEF_REEL_MAX);
	memset(stcReelFeverData, 0, sizeof(REEL) * DEF_FEVER_REEL_MAX);	
	ulReelNeedSoundEft = 0;
}


Reel::~Reel()
{
}

void Reel::Initial(SLONG slReel, UBYTE *ubReelData)
{
	SLONG slLoop;

	if (slReel < DEF_REEL_MAX)
	{
		stcReelData[slReel].ubReelData = ubReelData;

		stcReelData[slReel].uwGetIndex = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData);
		for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
		{
			stcReelData[slReel].ubShowID[slLoop] = stcReelData[slReel].ubReelData[stcReelData[slReel].uwGetIndex];
			stcReelData[slReel].ubStopID[slLoop] = stcReelData[slReel].ubShowID[slLoop];
			stcReelData[slReel].uwGetIndex++;
			if (stcReelData[slReel].uwGetIndex >= stcReelInfoData[slReel].ulMaxData)
			{
				stcReelData[slReel].uwGetIndex = 0;
			}
		}
		stcReelData[slReel].ubState = DEF_REEL_STOP;
		stcReelData[slReel].ubAdjustIndex = 0;
		stcReelData[slReel].swMoveY = 0;
		stcReelData[slReel].swSpeed = 0;
		stcReelData[slReel].swCount = 0;
	}
}

void Reel::SaveData(SLONG slReel)
{
	SLONG slLoop;

	if (slReel >= DEF_REEL_MAX)
	{
		return;
	}

	for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
	{
		stcReelData[slReel].ubSaveID[slLoop] = stcReelData[slReel].ubShowID[slLoop];
	}
}

void Reel::SetRandData(SLONG slReel)
{
	SLONG slIndex, slPointer;
	UBYTE *ubTurnData;

	if (slReel < DEF_REEL_MAX)
	{
		if (stcGameInfo.ulFreeNowLife == 0)
		{
			ubTurnData = (UBYTE *)stcReelData[slReel].ubReelData;
		}
		else
		{
			ubTurnData = (UBYTE *)ubScrollSymbolFreeData;
		}


		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData);

		if (slPointer < 2)
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 2;
		}
		else
		{
			slPointer -= 2;
		}
		for (slIndex = (DEF_REEL_MAX_SHOW - 1); slIndex >= 0; slIndex--)
		{
			stcReelData[slReel].ubStopID[slIndex] = ubTurnData[slPointer];
			slPointer = slPointer + 1;
			if (slPointer >= stcReelInfoData[slReel].ulMaxData)
			{
				slPointer = 0;
			}
		}
	}
}

void Reel::StopDataToShowData(SLONG slReel)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
	{
		stcReelData[slReel].ubShowID[slLoop] = stcReelData[slReel].ubStopID[slLoop];
	}
}

void Reel::LoadStopData(SLONG slReel)
{
	SLONG slLoop;

	if (slReel >= DEF_REEL_MAX)
	{
		return;
	}

	for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
	{
		stcReelData[slReel].ubStopID[slLoop] = stcReelData[slReel].ubSaveID[slLoop];
	}
}

void Reel::SaveStopData(SLONG slReel)
{
	SLONG slLoop;

	if (slReel >= DEF_REEL_MAX)
	{
		return;
	}

	for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
	{
		stcReelData[slReel].ubSaveID[slLoop] = stcReelData[slReel].ubStopID[slLoop];
	}
}

UBYTE Reel::GetData(SLONG slReel) const
{
	if (slReel >= DEF_REEL_MAX)
	{
		return (0);
	}
	return (stcReelData[slReel].ubStopID[2]);
}
void Reel::SetStopData(SLONG slReel, UBYTE ubData)
{
	SLONG slIndex, slPointer;
	UBYTE *ubTurnData;

	if (slReel < DEF_REEL_MAX)
	{
		ubTurnData = (UBYTE *)stcReelData[slReel].ubReelData;
		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData);

		for (slIndex = 0; slIndex < stcReelInfoData[slReel].ulMaxData; slIndex++)
		{
			if (ubTurnData[slPointer] == ubData)
			{
				break;
			}
			slPointer = slPointer + 1;
			if (slPointer >= stcReelInfoData[slReel].ulMaxData)
			{
				slPointer = 0;
			}
		}

		if (slPointer < 2)
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 2;
		}
		else
		{
			slPointer -= 2;
		}

		for (slIndex = (DEF_REEL_MAX_SHOW - 1); slIndex >= 0; slIndex--)
		{
			stcReelData[slReel].ubStopID[slIndex] = ubTurnData[slPointer];
			slPointer = slPointer + 1;
			if (slPointer >= stcReelInfoData[slReel].ulMaxData)
			{
				slPointer = 0;
			}
		}
	}
}
void Reel::StartRun(SLONG slReel)
{
	if (slReel < DEF_REEL_MAX)
	{
		stcReelData[slReel].ubState = DEF_REEL_START;
	}
}
void Reel::AllNowStopRun()
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
	{

		//if ( stcReelData[slReel].ubState == DEF_REEL_RUN )
		{
			stcReelData[slLoop].ubState = DEF_REEL_STOP;
			stcReelData[slLoop].swCount = 0;
			stcReelData[slLoop].ubAdjustIndex = 0;
		}

	}
}
void Reel::FeverSetStopData(SLONG slReel, UBYTE ubData)
{
	SLONG slIndex, slPointer;
	UBYTE *ubTurnData;

	if (slReel < DEF_FEVER_REEL_MAX)
	{
		ubTurnData = (UBYTE *)stcReelFeverData[slReel].ubReelData;
		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData);

		for (slIndex = 0; slIndex < stcReelInfoData[slReel].ulMaxData; slIndex++)
		{
			if (ubTurnData[slPointer] == ubData)
			{
				break;
			}
			slPointer = slPointer + 1;
			if (slPointer >= stcReelInfoData[slReel].ulMaxData)
			{
				slPointer = 1;
			}
		}

		if (slPointer < 3)
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 3;
		}
		else
		{
			slPointer -= 2;
		}

		for (slIndex = (DEF_REEL_MAX_SHOW - 1); slIndex >= 0; slIndex--)
		{
			stcReelFeverData[slReel].ubStopID[slIndex] = ubTurnData[slPointer];
			slPointer = slPointer + 1;
			if (slPointer >= stcReelInfoData[slReel].ulMaxData)
			{
				slPointer = 1;
			}
		}
	}
}
UBYTE Reel::GetFerverStopID(SLONG slReel, UBYTE ubData)
{
	return stcReelFeverData[slReel].ubStopID[ubData];
}
void Reel::FeverInitial(SLONG slReel, UBYTE * ubReelData)
{
	SLONG slLoop;

	if (slReel < DEF_FEVER_REEL_MAX)
	{
		stcReelFeverData[slReel].ubReelData = ubReelData;

		stcReelFeverData[slReel].uwGetIndex = 126;
		for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
		{
			stcReelFeverData[slReel].ubShowID[slLoop] = stcReelFeverData[slReel].ubReelData[stcReelFeverData[slReel].uwGetIndex];
			stcReelFeverData[slReel].ubStopID[slLoop] = stcReelFeverData[slReel].ubShowID[slLoop];
			stcReelFeverData[slReel].uwGetIndex++;
			if (stcReelFeverData[slReel].uwGetIndex >= stcReelInfoData[slReel].ulMaxData)
			{
				stcReelFeverData[slReel].uwGetIndex = 0;
			}
		}
		stcReelFeverData[slReel].ubState = DEF_REEL_STOP;
		stcReelFeverData[slReel].ubAdjustIndex = 0;
		stcReelFeverData[slReel].swMoveY = 0;
		stcReelFeverData[slReel].swSpeed = 0;
		stcReelFeverData[slReel].swCount = 0;
	}

	ulReelNeedSoundEft = 0;
}
void Reel::FeverSaveData(SLONG slReel)
{
	SLONG slLoop;

	if (slReel >= DEF_FEVER_REEL_MAX)
	{
		return;
	}

	for (slLoop = 0; slLoop < DEF_REEL_MAX_SHOW; slLoop++)
	{
		stcReelFeverData[slReel].ubSaveID[slLoop] = stcReelFeverData[slReel].ubShowID[slLoop];
	}
}
void Reel::FeverStartRun(SLONG slReel)
{
	if (slReel < DEF_FEVER_REEL_MAX)
	{
		stcReelFeverData[slReel].ubState = DEF_REEL_START;
	}
}
void Reel::FeverStopRun(SLONG slReel)
{
	if (slReel < DEF_FEVER_REEL_MAX)
	{
		if (stcReelFeverData[slReel].ubState == DEF_REEL_RUN)
		{
			stcReelFeverData[slReel].ubState = DEF_REEL_ADJUST;
			stcReelFeverData[slReel].swCount = 0;
			stcReelFeverData[slReel].ubAdjustIndex = 0;
		}
	}
}
NAMESPACE_NATIVE_END