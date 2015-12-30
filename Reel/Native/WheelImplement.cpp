
#include "..\Source\common.h"
#include "WheelImplement.h"


VGame::Native::WheelImplement::WheelImplement() :
	_Scroll(_Reel, _GameCheck),
	_GameCheck(_Scroll , _Slave ,_AdjustValue ,_Record , _Reel , _WupChance),
	_Chance(_WupChance , _AdjustValue , _Record , _Slave , _GameAssign , _Scroll , _GameCheck , _Master, stcGameInfo),
	_GameAssign(_GameCheck , _Reel ,_Scroll ,  _AdjustValue , _Chance , stcGameInfo),
	_Reel(stcGameInfo),
	_WupChance(_Record , _Slave,_AdjustValue)
{
}

VGame::Native::WheelImplement::~WheelImplement()
{
}

VGame::CLR::Output VGame::Native::WheelImplement::Spin(const VGame::CLR::Input& rule)
{
	//ULONG i, ulTemp,slLoop,ulRate,ulValue; 
	ULONG ulValue, ulTemp;
	ulPlayTimes = 0;
	ulWinTimes = 0;
	dlPlayTotal = 0;
	dlWinTotal = 0;
	//ulAsnFillTimes = 0;
	//ulLoseTimes = 0;
	ulWupPlayTimes = 0;

	slFeverWin = 0;
	slFreeWin = 0;

	// Reset
	{
		//		vMaster_Reset( ) ;
		//		vSlave_Reset( ) ;
		//		vChance_Reset( ) ;
	}

	_Initial(rule);
	// ORIGINAL vFastTest_OpenInputInfo();
	//vFastTest_OutInfo();

	
	//ORIGINAL : if (slSlave_ReadBet() < mGame_ReadMinBet())
	if (_Slave.ReadBet() < _AdjustValue.ReadMin())
	{
		_Slave.BetSet(_AdjustValue.ReadMin());
		//ORIGINAL : vSlave_BetSet(mGame_ReadMinBet());
	}

	if (_Slave.ReadBet() > _AdjustValue.ReadMax())
	//ORIGINAL : if (slSlave_ReadBet() > mGame_ReadMaxBet())
	{
		_Slave.BetSet(_AdjustValue.ReadMax());
		//ORIGINAL : vSlave_BetSet(mGame_ReadMaxBet());
	}
	if (ulSwitch == 0)
	{
		return _BuildResult();
	}
	// Init
	{
		_Scroll.Reset();
		//ORIGINAL : vScroll_Reset();

		_Chance.Update();
		//ORIGINAL : vChance_Update(0);
	}

	while (_Chance.GetPlayTimes() < dlRunTime)	
	//ORIGINAL : while (stcChance.ulPlayTimes < dlRunTime)
	{
		slFeverWin = 0;
		slFreeWin = 0;

		if (stcGameInfo.ulFreeNowLife)
		{
		}
		else
		{
			ulPlayTimes++;

			dlPlayTotal += _Slave.ReadTotalBet();
			// ORIGINAL dlPlayTotal += slSlave_ReadTotalBet();
			
			_Slave.WinSet(0);
			// ORIGINAL vSlave_WinSet(0);
			ulTemp = 0;
		}

		// vMaster_Game_Chance
		{
			_Chance.GameProcess();
			// ORIGINAL vChance_GameProcess();

			ulValue = _Slave.ReadTotalBet();
			// ORIGINAL ulValue = slSlave_ReadTotalBet();
			stcGameInfo.ulBonusValue = 80 * ulValue + ulRand_ReadMod(220 * ulValue);

			_Scroll.StartAllRun();
			// ORIGINAL vScroll_StartAllRun();
		}
		_Reel.AllNowStopRun();
		// ORIGINAL vReel_AllNowStopRun();
		// vMaster_Game_Check
		{
			_GameCheck.CheckOdds((GAMEINFO*)&stcGameInfo);
			// ORIGINAL vGameCheck_CheckOdds((GAMEINFO*)&stcGameInfo);

			ulValue = _GameCheck.GameWinRule((GAMEINFO*)&stcGameInfo);
			// ORIGINAL ulValue = slGameCheck_GameWinRule((GAMEINFO*)&stcGameInfo);
			_Slave.WinAdd(ulValue);
			// ORIGINAL vSlave_WinAdd(ulValue);

			_Chance.WinProcess(ulValue);
			// ORIGINAL vChance_WinProcess(ulValue);
			stcGameInfo.ulBonusWin = 0;
			if (stcGameInfo.ulBonusType == 3)
			{
				stcGameInfo.ulBonusWin = stcGameInfo.ulBonusValue;
			}
			if (stcGameInfo.ulBonusType == 2)
			{
				stcGameInfo.ulBonusWin = stcGameInfo.ulBonusValue / 5;
			}
			if (stcGameInfo.ulBonusType == 1)
			{
				stcGameInfo.ulBonusWin = stcGameInfo.ulBonusValue / 10;
			}
		}

		if (stcGameInfo.ulBonusType)
		{

			if (_Chance.GetActBuf() == DEF_CHANCE_BUF_MAIN)
			// ORIGINAL if (stcChance.ulActBuf == DEF_CHANCE_BUF_MAIN)
			{
				//vFastTest_AssertOut(__LINE__);
			}

			_Slave.WinAdd(stcGameInfo.ulBonusWin);
			// ORGINAL vSlave_WinAdd(stcGameInfo.ulBonusWin);
			
			_Chance.WinBonusProcess();
			// ORIGINAL vChance_WinBonusProcess();
			//vSlave_WinAdd(stcGameInfo.ulBonusWin);
		}
		if (stcGameInfo.ulFeverSetLife)
		{
			if (stcGameInfo.ulFreeSetLife)
			{
				//vFastTest_AssertOut(__LINE__);
			}
			
			if (_Chance.GetActBuf() == DEF_CHANCE_BUF_MAIN)			
			// ORIGINAL if (stcChance.ulActBuf == DEF_CHANCE_BUF_MAIN)
			{
				//vFastTest_AssertOut(__LINE__);
			}

			_Scroll.FeverReset();
			// ORIGINAL vScroll_FeverReset();
			while (stcGameInfo.ulFeverNowLife)
			{
				
				_Chance.FeverProcess();
				// ORIGINAL vChance_FeverProcess();

				_Scroll.FeverStartAllRun();
				// ORIGINAL vScroll_FeverStartAllRun();

				_Scroll.FeverAllStop();
				// ORIGINAL vScroll_FeverAllStop();

				_Chance.SetChanceData(_GameCheck.FeverValue());				
				// ORIGINAL stcFeverChance.ubData = slGameCheck_FeverValue();

				
				if (_Chance.GetChanceData() < 7)
				// ORIGINAL if (stcFeverChance.ubData < 7)
				{
					if (_Chance.GetChanceData() == 6)
					// ORIGINAL if (stcFeverChance.ubData == 6)
					{
						stcGameInfo.ulFeverNowLife--;
					}
					else
					{
						_Chance.SetChanceWin(ulFeverGameWinOdds[_Chance.GetChanceData() - 1] * _Slave.ReadTotalBet());
						// ORIGINAL stcFeverChance.ulWin = ulFeverGameWinOdds[stcFeverChance.ubData - 1] * slSlave_ReadTotalBet();

						_Chance.AddFeverTotalWin(_Chance.GetChanceWin());
						// ORIGINAL stcChance.ulFeverTotalWin += stcFeverChance.ulWin;

						_Slave.WinAdd(_Chance.GetChanceWin());
						// ORIGINAL vSlave_WinAdd(stcFeverChance.ulWin);
					}
				}			
			}

			_Chance.WinFeverProcess();
			// ORIGINAL vChance_WinFeverProcess();
		}
		if (stcGameInfo.ulFreeSetLife)
		{
			
			if (_Chance.GetActBuf() == DEF_CHANCE_BUF_MAIN)
			//ORIGINAL if (stcChance.ulActBuf == DEF_CHANCE_BUF_MAIN)
			{
				//vFastTest_AssertOut(__LINE__);
			}

			/*
			if((ulPlayTimes%ulRecCycle)==0)
			{
			vFastTest_OpenOutputRecord_one( );
			}
			*/
			stcGameInfo.ulFreeNowLife += stcGameInfo.ulFreeSetLife;
		}

		if(_Slave.WinRead())
		// ORIGNAL if (slSlave_WinRead())
		{
			ulWinTimes++;
			dlWinTotal += _Slave.WinRead();
			// ORIGINAL dlWinTotal += slSlave_WinRead();
		}

		if (stcGameInfo.ulFreeNowLife)
		{
			if (stcGameInfo.ulFreeType)
			{
				ulTemp += stcGameInfo.ulFreeType;
			}
			stcGameInfo.ulFreeNowLife--;
			if (stcGameInfo.ulFreeNowLife == 0)
			{
				stcGameInfo.ulFreeType = ulTemp;	

				_Chance.SetActBuf(DEF_CHANCE_BUF_FREE);
				// ORIGINAL stcChance.ulActBuf = DEF_CHANCE_BUF_FREE;

			}
		}
		if (stcGameInfo.ulFreeNowLife) continue;
		if ((ulPlayTimes%ulRecCycle) == 0)
		{
#ifdef DEF_OPEN_PCFILEOUT
			vFastTest_OpenOutputRecord_one();
#endif			
		}

		if (rule.WinSet > 0)
		{
			_Slave.WinSet(rule.WinSet);
		}
		if(_Slave.WinRead())
		// ORIGINAL if (slSlave_WinRead())
		{
			
			_FastWup(_Slave.WinRead());
			// ORIGINAL : vFastWup_Test(slSlave_WinRead());
		}
	}
	//vFastTest_OpenOutputRecord_all();
	//vFastWupTest_OpenOutputRecord_all();
	return _BuildResult();
}
VGame::CLR::Output VGame::Native::WheelImplement::SpinNormal(const VGame::CLR::Input & rule)
{
	//ULONG i, ulTemp,slLoop,ulRate,ulValue; 
	ULONG ulValue, ulTemp;
	ulPlayTimes = 0;
	ulWinTimes = 0;
	dlPlayTotal = 0;
	dlWinTotal = 0;
	//ulAsnFillTimes = 0;
	//ulLoseTimes = 0;
	ulWupPlayTimes = 0;

	slFeverWin = 0;
	slFreeWin = 0;

	// Reset
	{
		//		vMaster_Reset( ) ;
		//		vSlave_Reset( ) ;
		//		vChance_Reset( ) ;
	}

	_Initial(rule);
	// ORIGINAL vFastTest_OpenInputInfo();
	//vFastTest_OutInfo();


	//ORIGINAL : if (slSlave_ReadBet() < mGame_ReadMinBet())
	if (_Slave.ReadBet() < _AdjustValue.ReadMin())
	{
		_Slave.BetSet(_AdjustValue.ReadMin());
		//ORIGINAL : vSlave_BetSet(mGame_ReadMinBet());
	}

	if (_Slave.ReadBet() > _AdjustValue.ReadMax())
		//ORIGINAL : if (slSlave_ReadBet() > mGame_ReadMaxBet())
	{
		_Slave.BetSet(_AdjustValue.ReadMax());
		//ORIGINAL : vSlave_BetSet(mGame_ReadMaxBet());
	}
	if (ulSwitch == 0)
	{
		return _BuildResult();
	}
	// Init
	{
		_Scroll.Reset();
		//ORIGINAL : vScroll_Reset();

		_Chance.Update();
		//ORIGINAL : vChance_Update(0);
	}
	while (_Chance.GetPlayTimes() < dlRunTime)
		//ORIGINAL : while (stcChance.ulPlayTimes < dlRunTime)
	{
		slFeverWin = 0;
		slFreeWin = 0;

		ulPlayTimes++;

		dlPlayTotal += _Slave.ReadTotalBet();
		// ORIGINAL dlPlayTotal += slSlave_ReadTotalBet();

		_Slave.WinSet(0);
		// ORIGINAL vSlave_WinSet(0);
		ulTemp = 0;

		// vMaster_Game_Chance
		{
			_Chance.GameProcess();
			// ORIGINAL vChance_GameProcess();

			ulValue = _Slave.ReadTotalBet();
			// ORIGINAL ulValue = slSlave_ReadTotalBet();
			stcGameInfo.ulBonusValue = 80 * ulValue + ulRand_ReadMod(220 * ulValue);

			_Scroll.StartAllRun();
			// ORIGINAL vScroll_StartAllRun();
		}
		_Reel.AllNowStopRun();
		// ORIGINAL vReel_AllNowStopRun();
		// vMaster_Game_Check
		{
			_GameCheck.CheckOdds((GAMEINFO*)&stcGameInfo);
			// ORIGINAL vGameCheck_CheckOdds((GAMEINFO*)&stcGameInfo);

			ulValue = _GameCheck.GameWinRule((GAMEINFO*)&stcGameInfo);
			// ORIGINAL ulValue = slGameCheck_GameWinRule((GAMEINFO*)&stcGameInfo);
			_Slave.WinAdd(ulValue);
			// ORIGINAL vSlave_WinAdd(ulValue);

			_Chance.WinProcess(ulValue);
			// ORIGINAL vChance_WinProcess(ulValue);
			stcGameInfo.ulBonusWin = 0;
			if (stcGameInfo.ulBonusType == 3)
			{
				stcGameInfo.ulBonusWin = stcGameInfo.ulBonusValue;
			}
			if (stcGameInfo.ulBonusType == 2)
			{
				stcGameInfo.ulBonusWin = stcGameInfo.ulBonusValue / 5;
			}
			if (stcGameInfo.ulBonusType == 1)
			{
				stcGameInfo.ulBonusWin = stcGameInfo.ulBonusValue / 10;
			}
		}

		if (stcGameInfo.ulBonusType)
		{

			if (_Chance.GetActBuf() == DEF_CHANCE_BUF_MAIN)
				// ORIGINAL if (stcChance.ulActBuf == DEF_CHANCE_BUF_MAIN)
			{
				//vFastTest_AssertOut(__LINE__);
			}

			_Slave.WinAdd(stcGameInfo.ulBonusWin);
			// ORGINAL vSlave_WinAdd(stcGameInfo.ulBonusWin);

			_Chance.WinBonusProcess();
			// ORIGINAL vChance_WinBonusProcess();
			//vSlave_WinAdd(stcGameInfo.ulBonusWin);
		}
		

		if (_Slave.WinRead())
			// ORIGNAL if (slSlave_WinRead())
		{
			ulWinTimes++;
			dlWinTotal += _Slave.WinRead();
			// ORIGINAL dlWinTotal += slSlave_WinRead();
		}

				
		if ((ulPlayTimes%ulRecCycle) == 0)
		{
#ifdef DEF_OPEN_PCFILEOUT
			vFastTest_OpenOutputRecord_one();
#endif			
		}

		
	}
	
	return _BuildResult();
}
void VGame::Native::WheelImplement::Import(VGame::CLR::Dump::WheelFieldSet& set)
{
	auto a = set.slFeverWin;
	slFeverWin	= set.slFeverWin;
	slFreeWin = set.slFreeWin;
	ulPlayTimes = set.ulPlayTimes;
	ulWinTimes = set.ulWinTimes;
	dlPlayTotal = set.dlPlayTotal;
	dlWinTotal = set.dlWinTotal;
	dlRunTime = set.dlRunTime;

	ulSwitch = set.ulSwitch;
	ulRecCycle = set.ulRecCycle;

	slWupBet = set.slWupBet;
	ulWupTime = set.ulWupTime;
	ulWupPlayTimes = set.ulWupPlayTimes;

	ulWupCondi1 = set.ulWupCondi1;
	ulWupCondi2 = set.ulWupCondi2;
}
VGame::CLR::Dump::WheelFieldSet VGame::Native::WheelImplement::Export()
{
	VGame::CLR::Dump::WheelFieldSet set = VGame::CLR::Dump::WheelFieldSet();

	set.slFeverWin = slFeverWin;
	set.slFreeWin = slFreeWin;
	set.ulPlayTimes = ulPlayTimes;
	set.ulWinTimes = ulWinTimes;
	set.dlPlayTotal = dlPlayTotal;
	set.dlWinTotal = dlWinTotal;
	set.dlRunTime = dlRunTime;

	set.ulSwitch = ulSwitch;
	set.ulRecCycle = ulRecCycle;

	set.slWupBet = slWupBet;
	set.ulWupTime = ulWupTime;
	set.ulWupPlayTimes = ulWupPlayTimes;

	set.ulWupCondi1 = ulWupCondi1;
	set.ulWupCondi2 = ulWupCondi2;

	
	return set;
}

VGame::CLR::Output VGame::Native::WheelImplement::_BuildResult()
{
	
	VGame::CLR::Output output = VGame::CLR::Output();
	output.Reels = gcnew array<int>(DEF_REEL_MAX);
	int length = output.Reels->Length;
	for (int i = 0; i < length; i++)
	{
		output.Reels[i] = _Reel.GetData(i);
	}
	
	output.WupData = _WupChance.GetData();
	output.Score = _GameCheck.GameWinRule((GAMEINFO*)&stcGameInfo);
	return output;
}


void VGame::Native::WheelImplement::_FastWup(SLONG ulWin)
{
	ulWupPlayTimes = 0;//
	switch (ulWupCondi2)
	{
	case 0:
		_Slave.WupWinSet(ulWin * 2);
		// ORIGINAL vSlave_WupWinSet(ulWin * 2);
		break;
	case 2:
		_Slave.WupWinSet(ulWin / 2);
		// ORIGINAL vSlave_WupWinSet(ulWin / 2);
		break;
	default:
		_Slave.WupWinSet(ulWin);
		// ORIGINAL vSlave_WupWinSet(ulWin);
		break;
	}
	if (ulWupCondi1) //是否是要比倍
	{
		while (1)
		{
			slWupBet = _Slave.WupWinRead();
			// ORIGINAL slWupBet = slSlave_WupWinRead();
			ulWupPlayTimes++;
			/*if (ulRand_ReadMod(2))
			{
				_WupChance.SetGuess(DEF_WUP_GUESS_BIG);
				// ORIGINAL stcWupChance.ubGuess = DEF_WUP_GUESS_BIG;
			}
			else
			{
				_WupChance.SetGuess(DEF_WUP_GUESS_SMALL);
				// ORIGINAL stcWupChance.ubGuess = DEF_WUP_GUESS_SMALL;
			}*/

			_WupChance.DealProcess();
			// ORIGINAL vWupChance_DealProcess();

			if (_WupChance.GetData() != DEF_CHANCE_WUP_NULL)
			// ORIGINAL if (stcWupChance.ubData != DEF_CHANCE_WUP_NULL)
			{
				_WupChance.BetProcess();//不需要把?局押注?入?算	
				// ORIGINAL vWupChance_BetProcess();//不需要把?局押注?入?算	

				_GameCheck.WupWinRule();
				// ORIGINAL vGameCheck_WupWinRule();

				_WupChance.WinProcess(_Slave.WupWinRead());//不需要把?局押注?入?算	
				// ORIGINAL vWupChance_WinProcess(slSlave_WupWinRead());//不需要把?局押注?入?算	
			}
			if ((ulPlayTimes%ulRecCycle) == 0)
			{
#ifdef DEF_OPEN_PCFILEOUT
				vFastWupTest_OpenOutputRecord_one();
#endif			
			}
			if(_Slave.WupWinRead())
			// ORIGINAL if (slSlave_WupWinRead())
			{
				
				if (_Slave.WupWinRead() >= _AdjustValue.ReadWupLimitTop())
				// ORIGINAL if (slSlave_WupWinRead() >= mGame_ReadWupLimitTop())
				{
					break;
				}
				if (ulWupCondi1 == 1)
				{
					break;
				}
				else if (ulWupCondi1 == 2)
				{
					if (ulWupPlayTimes >= 2)
					{
						break;
					}
				}
				else if (ulWupCondi1 == 3)
				{
					if (ulWupPlayTimes >= 3)
					{
						break;
					}
				}
				else if (ulWupCondi1 == 4)
				{
					if (ulWupPlayTimes >= 4)
					{
						break;
					}
				}

			}
			else
			{
				break;
			}

			ulWin = _Slave.WupWinRead();
			// ORIGINAL ulWin = slSlave_WupWinRead();

			
			switch (_WupChance.GetData())
			//ORIGINAL switch (stcWupChance.ubData)
			{
			case DEF_CHANCE_WUP_WIN_X1:
			case DEF_CHANCE_WUP_WIN_X2:
			case DEF_CHANCE_WUP_WIN_X3:
			case DEF_CHANCE_WUP_WIN_X4:
				switch (ulWupCondi2)
				{
				case 0:
					_Slave.WupWinSet(ulWin * 2);
					// ORIGINAL vSlave_WupWinSet(ulWin * 2);
					break;
				case 2:
					_Slave.WupWinSet(ulWin / 2);
					// ORIGINAL vSlave_WupWinSet(ulWin / 2);
					break;
				}
				break;
			}


		}
	}

}

void VGame::Native::WheelImplement::_Initial(const VGame::CLR::Input& rule)
{
	vRand_Reset();
	ulSwitch = rule.Switch;
	if (ulSwitch)
	{
		_AdjustValue.Setup();
		dlRunTime = rule.RunTime;
		_Slave.BetSet(rule.Bet);
		_AdjustValue.SetMinBet(rule.MinBet);
		_AdjustValue.SetMaxBet(rule.MaxBet);		
		_Slave.SetLine(rule.Line);
		_AdjustValue.SetGameRate(rule.GameRate);
		_AdjustValue.SetGameUndulate(rule.GameUndulate);
		_AdjustValue.SetWupRate(rule.WupRate);
		ulRecCycle = rule.RecCycle;
		ulWupCondi1 = rule.WupCondi1;
		ulWupCondi2 = rule.WupCondi2;
		_AdjustValue.UpDate();

		stcGameInfo.ulFreeNowLife = rule.Free;
		stcGameInfo.ulFeverNowLife = rule.Fever;

		_WupChance.SetGuess(rule.Guess);
	}
	

	
}
