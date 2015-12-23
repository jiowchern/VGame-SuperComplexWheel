#include "WupChance.h"

#include "Record.h"
#include "Slave.h"
#include "AdjustValue.h"
NAMESPACE_NATIVE_BEGIN
ULONG const ulWupChanceOdds[6] = {
	0,    //猜?
	0,    //重猜 	
	2,    //中1次
	3,
	4,
	5
};
ULONG const ulWupChanceAsnGift[6] = {
	DEF_CHANCE_WUP_LOSE,    //猜?
	DEF_CHANCE_WUP_NULL,    //重猜 	
	DEF_CHANCE_WUP_WIN_X1,  //中1次
	DEF_CHANCE_WUP_WIN_X2,
	DEF_CHANCE_WUP_WIN_X3,
	DEF_CHANCE_WUP_WIN_X4
};
ULONG const ulWupChanceInfoData[4][6] = {
	{ 32359,4400,26754,1258,640,125 },
	{ 32523,4400,26590,1258,640,125 },
	{ 32687,4400,26426,1258,640,125 },
	{ 32850,4400,26263,1258,640,125 },
};

WupChance::WupChance(Record& record , Slave& slave, AdjustValue& value):
_Record(record),
_Slave(slave),
_AdjustValue(value)
{
	_Reset();
}


WupChance::~WupChance()
{
}

void WupChance::SetRate()
{
	
	stcWupChance.ulRate = 990 - (_AdjustValue.ReadWupRateLevel() % 4) * 5;
}
void WupChance::BetProcess(void)
{
	ULONG	ulBet;

	ulBet = _Slave.WupWinRead();
	// ORIGINAL ulBet = slSlave_WupWinRead();
	slBuffer_AddRate(&stcWupChance.Buffer, ulBet, stcWupChance.ulRate);

	_Record.Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_DATA_TOTALPLAY, ulBet);
	_Record.Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_PLAYTOTAL, ulBet);
	_Record.Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_PLAYTIMES, 1);
	/*ORIGINAL 
	vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_DATA_TOTALPLAY, ulBet);
	vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_PLAYTOTAL, ulBet);
	vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_PLAYTIMES, 1);*/
#ifdef DEF_USE_VGAME_UART_SLAVE
	ulUartCmdRec[DEF_RECORD_DATA_TOTALPLAY][0] += ulBet;
	ulUartCmdRec[DEF_RECORD_WUP_PLAYTOTAL][0] += ulBet;
	ulUartCmdRec[DEF_RECORD_WUP_PLAYTIMES][0] += 1;
#endif
}
void WupChance::WinProcess(ULONG ulWin)
{
	if (ulWin)
	{

		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_DATA_TOTALWIN, ulWin);
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_WINTOTAL, ulWin);
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_WINTIMES, 1);
		/*
		ORIGINAL 
		vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_DATA_TOTALWIN, ulWin);
		vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_WINTOTAL, ulWin);
		vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_RECORD_WUP_WINTIMES, 1);*/
#ifdef DEF_USE_VGAME_UART_SLAVE
		ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += ulWin;
		ulUartCmdRec[DEF_RECORD_WUP_WINTOTAL][0] += ulWin;
		ulUartCmdRec[DEF_RECORD_WUP_WINTIMES][0] += 1;
#endif

		stcWupChance.Buffer.slValue -= ulWin;
	}

	_ResetAsnLose(ulWin);
	// ORIGINAL vWupChance_ResetAsnLose(ulWin);
	switch (stcWupChance.ubData)
	{
	case DEF_CHANCE_WUP_LOSE:
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_LOSE, 1);
		// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_LOSE, 1);
		break;
	case DEF_CHANCE_WUP_WIN_X1:
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X2, 1);
		// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X2, 1);
		break;
	case DEF_CHANCE_WUP_WIN_X2:
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X3, 1);
		// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X3, 1);
		break;
	case DEF_CHANCE_WUP_WIN_X3:
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X4, 1);
		// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X4, 1);
		break;
	case DEF_CHANCE_WUP_WIN_X4:
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X5, 1);
		// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_WUP_X5, 1);
		break;
		//case DEF_CHANCE_WUP_NULL:	
		//vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_NULL , 1 ) ;	// 搬到 vMaster_Wup_Effect ??理		
		//break ;	
	}
}
UBYTE WupChance::GetData()
{
	return stcWupChance.ubData;
}
void WupChance::SetGuess(UBYTE val)
{
	stcWupChance.ubGuess = val;
}
void WupChance::DealProcess(void)
{
	SLONG slNextWin, slValue;
	ULONG ulNum, ulMaxBet;

	
	ulMaxBet = _AdjustValue.ReadMax() * 9;

	if ((stcWupChance.ulPlayTimes == 0) && (stcWupChance.Buffer.slValue == 0))
	{
		stcWupChance.Buffer.slValue = ulMaxBet * 10; //固定灌十倍的 MaxBet

	}
	
	ulNum = _TakeValueNum(&ulWupChanceInfoData[_AdjustValue.ReadWupRateLevel()][0], ulRand_ReadMod(0x10000), 6);
	// ORIGINAL ulNum = ulWupChance_TakeValueNum(&ulWupChanceInfoData[mGame_ReadWupRateLevel()][0], ulRand_ReadMod(0x10000), 6);

	stcWupChance.ubData = ulWupChanceAsnGift[ulNum];

#ifdef DEF_TEST_WUPWIN
	stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
	return;
#endif

	slNextWin = _Slave.WupWinRead() * ulWupChanceOdds[ulNum];
	// ORIGINAL slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[ulNum];

	slValue = stcWupChance.Buffer.slValue - slNextWin;

	if (slValue > 400 * (SLONG)ulMaxBet)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(200)) && (stcWupChance.ubData == DEF_CHANCE_WUP_LOSE))
		{
			slNextWin = _Slave.WupWinRead() * ulWupChanceOdds[2];
			// ORIGINAL slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[2];
			slValue -= slNextWin;
			if (slValue > (-100)*(SLONG)ulMaxBet)
			{
				stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
				stcWupChance.ulRecAsnValue[0] += _Slave.WupWinRead() * 2;
				// ORIGINAL stcWupChance.ulRecAsnValue[0] += slSlave_WupWinRead() * 2;
				stcWupChance.ulRecAsnTimes[0]++;
			}
		}

	}
	else if (slValue > 200 * (SLONG)ulMaxBet)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(100)) && (stcWupChance.ubData == DEF_CHANCE_WUP_LOSE))
		{
			slNextWin = _Slave.WupWinRead() * ulWupChanceOdds[2];
			// ORIGINAL slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[2];
			slValue -= slNextWin;
			if (slValue > (-100)*(SLONG)ulMaxBet)
			{
				stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
				stcWupChance.ulRecAsnValue[1] += _Slave.WupWinRead() * 2;
				// ORIGINAL stcWupChance.ulRecAsnValue[1] += slSlave_WupWinRead() * 2;
				stcWupChance.ulRecAsnTimes[1]++;
			}
		}
	}
	else if (slValue > 100 * (SLONG)ulMaxBet)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(50)) && (stcWupChance.ubData == DEF_CHANCE_WUP_LOSE))
		{
			slNextWin = _Slave.WupWinRead() * ulWupChanceOdds[2];
			// ORIGINAL slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[2];
			slValue -= slNextWin;
			if (slValue > (-100)*(SLONG)ulMaxBet)
			{
				stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
				stcWupChance.ulRecAsnValue[2] += _Slave.WupWinRead() * 2;
				// ORIGINAL stcWupChance.ulRecAsnValue[2] += slSlave_WupWinRead() * 2;
				stcWupChance.ulRecAsnTimes[2]++;
			}
		}

	}
	else if (slValue < (-200)*(SLONG)ulMaxBet)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(1000)) && slNextWin)
		{
			stcWupChance.ubData = DEF_CHANCE_WUP_LOSE;
			stcWupChance.ulRecAsnValue[6] += slNextWin;
			stcWupChance.ulRecAsnTimes[6]++;
		}
	}
	else if (slValue < (-100)*(SLONG)ulMaxBet)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(150)) && slNextWin)
		{
			stcWupChance.ubData = DEF_CHANCE_WUP_LOSE;
			stcWupChance.ulRecAsnValue[5] += slNextWin;
			stcWupChance.ulRecAsnTimes[5]++;
		}
	}
	else if (slValue < (-50)*(SLONG)ulMaxBet)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(100)) && slNextWin)
		{
			stcWupChance.ubData = DEF_CHANCE_WUP_LOSE;
			stcWupChance.ulRecAsnValue[4] += slNextWin;
			stcWupChance.ulRecAsnTimes[4]++;
		}
	}
	else if (slValue < 0)
	{
		if ((ulRand_ReadMod(0x10000) < mMacro_Rate(50)) && slNextWin)
		{
			stcWupChance.ubData = DEF_CHANCE_WUP_LOSE;
			stcWupChance.ulRecAsnValue[3] += slNextWin;
			stcWupChance.ulRecAsnTimes[3]++;
		}
	}
	stcWupChance.ulRecTimes[ulNum]++;
	stcWupChance.ulPlayTimes++;
	if (stcWupChance.ulPlayTimes > 100001000) stcWupChance.ulPlayTimes -= 100000000;



}
void WupChance::_ResetAsnLose(ULONG ulWin)
{
	if (ulWin)
	{
		// 有?就重新算

		switch (_AdjustValue.ReadWupAsnLose())
		// ORIGINAL switch (mGame_ReadWupAsnLose())
		{
		case 2:
			stcWupChance.ulAsnLose = ulRand_ReadMod(3) + 2;
			break;
		case 3:
			stcWupChance.ulAsnLose = ulRand_ReadMod(4) + 2;
			break;
		case 4:
		default:
			stcWupChance.ulAsnLose = ulRand_ReadMod(3) + 3;
			break;
		}
	}
	else
	{
		// ?一次扣一，直到?零，??制?一次
		if (stcWupChance.ulAsnLose) stcWupChance.ulAsnLose--;
	}
}
// 周期砍牌，?制?
void WupChance::_ResetAsnKill(void)
{
	if (stcWupChance.ulAsnKill)
	{
		// 不管??，每局都扣一	
		stcWupChance.ulAsnKill--;
	}
	else
	{
		// 直到?零，??制?一次

		switch (_AdjustValue.ReadWupAsnKill())		
		// ORIGINAL switch (mGame_ReadWupAsnKill())
		{
		case 2:
			stcWupChance.ulAsnKill = ulRand_ReadMod(5) + 4;
			break;
		case 3:
			stcWupChance.ulAsnKill = ulRand_ReadMod(5) + 5;
			break;
		case 4:
			stcWupChance.ulAsnKill = ulRand_ReadMod(5) + 6;
			break;
		case 5:
			stcWupChance.ulAsnKill = ulRand_ReadMod(5) + 7;
			break;
		case 6:
			stcWupChance.ulAsnKill = ulRand_ReadMod(5) + 8;
			break;
		case 7:
		default:
			stcWupChance.ulAsnKill = ulRand_ReadMod(5) + 9;
			break;
		}
	}
}
ULONG WupChance::_TakeValueNum(ULONG const * ulData, ULONG ulValue, ULONG ulSize)
{
	ULONG	i;
	if (ulSize >= 100)
	{
		return 0;
	}
	for (i = 0; i<ulSize; i++)
	{
		if (ulValue < ulData[i]) break;
		ulValue -= ulData[i];
	}
	if (i >= ulSize)
	{
		i = ulSize - 1;
	}
	return 	i;
}
void WupChance::_Reset(void)
{
	//UBYTE i ; //ubFl , ubNum,i ;
	vMemory_Set((UBYTE *)&stcWupChance, 0x00, sizeof(stcWupChance));
	/*
	for(i=0;i<6;i++)
	{
	stcWupChance.ubHistory[i] = ubWupChanceDefaultLastCard[i];
	stcWupChance.ubDemoHistory[i] = ubWupChanceDefaultLastCard[i];

	}
	*/
	_ResetAsnLose(1);
	_ResetAsnKill();
}
NAMESPACE_NATIVE_END