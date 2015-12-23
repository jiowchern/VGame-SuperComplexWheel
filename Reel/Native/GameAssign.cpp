#include "GameAssign.h"
#include "GameCheck.h"
#include "Reel.h"
#include "Scroll.h"
#include "AdjustValue.h"
#include "Chance.h"

NAMESPACE_NATIVE_BEGIN


GameAssign::GameAssign(GameCheck& check , Reel& reel, Scroll& scroll , AdjustValue& value,Chance& chance , GAMEINFO& info) :
	_GameCheck(check),
	_Reel(reel),
	_Scroll(scroll),
	_AdjustValue(value),
	_Chance(chance),
	stcGameInfo(info)
{
}


void GameAssign::_5Line(UBYTE ubSymID)
{
	UBYTE ubAllSymID[3][5];
	SLONG slLine, slX, slY;
	SLONG slLoop, slLoop1, slTimes;
	ULONG ulValue;
	for (slTimes = 0; slTimes < 10; slTimes++)
	{
		for (slLoop = 0; slLoop < 3; slLoop++)
		{
			for (slLoop1 = 0; slLoop1 < 5; slLoop1++)
			{
				ubAllSymID[slLoop][slLoop1] = 0xFF;
			}
		}
#ifdef DEF_FIX_CHANCE_20150212
		slLine = ulRand_ReadMod(9);  //wcm 150212 ?机的（9?1）        
#else
		slLine = ulRand_ReadMod(slSlave_ReadLine());  //防止?制??押到?
#endif
		for (slLoop = 0; slLoop < 5; slLoop++)
		{
			slY = ubGameCheckLineLocInformation[slLine][slLoop] / 5;
			slX = ubGameCheckLineLocInformation[slLine][slLoop] % 5;
			ubAllSymID[slY][slX] = ubSymID;
		}
		for (slLoop = 0; slLoop < 15; slLoop++)
		{
			slY = slLoop / 5;
			slX = slLoop % 5;
			ulValue = ulRand_ReadMod(32768);
			if (ubAllSymID[slY][slX] != 0xFF)
			{
				if (ulValue<6553)
				{
					_Scroll.SetStopData(slLoop, DEF_SYMBOL_WILD);
					// ORIGINAL vScroll_SetStopData(slLoop, DEF_SYMBOL_WILD);
				}
				else
				{
					_Scroll.SetStopData(slLoop, ubAllSymID[slY][slX]);
					// ORIGNAL vScroll_SetStopData(slLoop, ubAllSymID[slY][slX]);
				}
			}
			else
			{
				if (ulValue<3276)
				{
					_Scroll.SetStopData(slLoop, DEF_SYMBOL_WILD);
					// ORIGINAL vScroll_SetStopData(slLoop, DEF_SYMBOL_WILD);
				}
				else if (ulValue<3276 + 6553)
				{
					_Scroll.SetStopData(slLoop, ubAllSymID[slY][slX]);
					// ORIGINAL vScroll_SetStopData(slLoop, ubAllSymID[slY][slX]);
				}
				else
				{
					_Scroll.SetRandData(slLoop);
					// ORIGINAL vScroll_SetRandData(slLoop);
				}


			}
		}
		
		if (_GameCheck.IsSpecial(DEF_SYMBOL_WILD))
		// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_WILD))
		{
			continue;
		}
		if (_GameCheck.IsSpecial(DEF_SYMBOL_FEVER))
		//ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FEVER))
		{
			continue;
		}

		if (_GameCheck.IsSpecial(DEF_SYMBOL_FREE))
		// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FREE))
		{
			continue;
		}
		break;
	}
}

void GameAssign::_SpecialSymbol(UBYTE ubSymID, UBYTE ubLoc)
{
	UBYTE ubAllSymID[3][5];
	SLONG slLoc, slX, slY;
	SLONG slLoop, slLoop1, slTimes;
	if ((ubLoc == 0) || (ubLoc>15))
	{
		return;
	}
	for (slTimes = 0; slTimes < 10; slTimes++)
	{
		for (slLoop = 0; slLoop < 3; slLoop++)
		{
			for (slLoop1 = 0; slLoop1 < 5; slLoop1++)
			{
				ubAllSymID[slLoop][slLoop1] = 0xFF;
			}
		}
		for (slLoop = 0; slLoop < ubLoc; slLoop++)
		{
			slLoc = ulRand_ReadMod(15);
			slY = slLoc / 5;
			slX = slLoc % 5;
			if (ubAllSymID[slY][slX] == 0xFF)
			{
				ubAllSymID[slY][slX] = ubSymID;
			}
		}
		for (slLoop1 = 0; slLoop1 < 10; slLoop1++)
		{
			for (slLoop = 0; slLoop < 15; slLoop++)
			{
				slY = slLoop / 5;
				slX = slLoop % 5;
				if (ubAllSymID[slY][slX] != 0xFF)
				{
					_Scroll.SetStopData(slLoop, ubAllSymID[slY][slX]);
					// ORIGINAL vScroll_SetStopData(slLoop, ubAllSymID[slY][slX]);
				}
				else
				{
					_Scroll.SetRandData(slLoop);
					// ORIGINAL vScroll_SetRandData(slLoop);
				}
			}
			if (_GameCheck.IsSpecial(ubSymID) == ubLoc)
			// ORIGINAL if (slGameCheck_IsSpecial(ubSymID) == ubLoc)
			{
				if (ubSymID == DEF_SYMBOL_WILD)
				{
					if (_GameCheck.IsSpecial(DEF_SYMBOL_FEVER) == 0)
					// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FEVER) == 0)
					{
						if (_GameCheck.IsSpecial(DEF_SYMBOL_FREE) == 0)
						//if (slGameCheck_IsSpecial(DEF_SYMBOL_FREE) == 0)
						{
							return;
						}
					}
				}
				if (ubSymID == DEF_SYMBOL_FEVER)
				{
					if (_GameCheck.IsSpecial(DEF_SYMBOL_WILD) == 0)
					// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_WILD) == 0)
					{
						if (_GameCheck.IsSpecial(DEF_SYMBOL_FREE) == 0)
						// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FREE) == 0)
						{
							return;
						}
					}
				}
				if (ubSymID == DEF_SYMBOL_FREE)
				{
					if (_GameCheck.IsSpecial(DEF_SYMBOL_WILD) == 0)
					// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_WILD) == 0)
					{
						if (_GameCheck.IsSpecial(DEF_SYMBOL_FEVER) == 0)
						// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FEVER) == 0)
						{
							return;
						}
					}
				}

			}
		}


	}
}

GameAssign::~GameAssign()
{
}

#define DEF_GameAssign_Natural_case_1
void GameAssign::Natural()
{
	SLONG slLoop;
#ifdef DEF_GameAssign_Natural_case_1
	{
		while (1)//for ( slLoop1 = 0 ; slLoop1 < 10 ; slLoop1 ++ )
		{
			for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
			{
				_Reel.SetRandData(slLoop);
				//ORIGINAL vReel_SetRandData(slLoop);				
			}

			if (_GameCheck.IsSpecial(DEF_SYMBOL_WILD))			
			// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_WILD))
			{
				continue;
			}

			if (_GameCheck.IsSpecial(DEF_SYMBOL_FEVER))
			// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FEVER))
			{
				continue;
			}

			if (_GameCheck.IsSpecial(DEF_SYMBOL_FREE))
			// ORIGINAL if (slGameCheck_IsSpecial(DEF_SYMBOL_FREE))
			{
				continue;
			}
			break;
		}
	}
#endif

#ifdef DEF_GameAssign_Natural_case_2
	{
		SLONG slBonus, slFever, slFree;
		UBYTE ubSym;

		slBonus = 0; slFever = 0; slFree = 0;
		for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
		{
			while (1)
			{
				vReel_SetRandData(slLoop);

				ubSym = ubReel_GetData(slLoop);

				if ((ubSym == DEF_SYMBOL_10) && (slBonus >= 2)) continue;
				if ((ubSym == DEF_SYMBOL_11) && (slFever >= 2)) continue;
				if ((ubSym == DEF_SYMBOL_12) && (slFree >= 2)) continue;

				break;
			}
			if (ubSym == DEF_SYMBOL_10) slBonus++;
			if (ubSym == DEF_SYMBOL_11) slFever++;
			if (ubSym == DEF_SYMBOL_12) slFree++;
		}

		for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
		{
			slLoop1 = ulRand_ReadMod(DEF_REEL_MAX);
			if (slLoop1 == slLoop) continue;

			vReel_LocSwap(slLoop, slLoop1);
		}
	}
#endif
}
void GameAssign::Spec5Line(UBYTE ubSymID, ULONG ulLoc)
{
	SLONG slLoop, slOdds, slValue;

	_5Line(ubSymID);
	// ORIGINAL vGameAssign_5Line(ubSymID);
#ifdef DEF_FIX_CHANCE_20150212
	_GameCheck.CheckAllLineOdds((GAMEINFO*)&stcGameInfo);
	// ORIGINAL vGameCheck_CheckAllLineOdds((GAMEINFO*)&stcGameInfo);
#else
	vGameCheck_CheckOdds((GAMEINFO*)&stcGameInfo);
#endif
	_Scroll.SaveStopData();
	// ORIGINAL vScroll_SaveStopData();
#ifdef DEF_FIX_CHANCE_20150212
	slOdds = _GameCheck.ReadAllOdds((GAMEINFO*)&stcGameInfo)* _AdjustValue.ReadMax();
	// ORIGINAL slOdds = slGameCheck_ReadAllOdds((GAMEINFO*)&stcGameInfo)* mGame_ReadMaxBet();
#else
	slOdds = slGameCheck_ReadAllOdds((GAMEINFO*)&stcGameInfo);
#endif
	for (slLoop = 0; slLoop < 9; slLoop++) //取十次，取「最接近、又不超過觸頂值」的一局給獎
	{
		_5Line(ubSymID);
		// ORIGINAL vGameAssign_5Line(ubSymID);
#ifdef DEF_FIX_CHANCE_20150212
		_GameCheck.CheckAllLineOdds((GAMEINFO*)&stcGameInfo);
		// ORIGINAL vGameCheck_CheckAllLineOdds((GAMEINFO*)&stcGameInfo);
#else
		vGameCheck_CheckOdds((GAMEINFO*)&stcGameInfo);
#endif
		
		slValue = _GameCheck.ReadAllOdds((GAMEINFO*)&stcGameInfo)*_AdjustValue.ReadMax();
		// ORIGINAL slValue = slGameCheck_ReadAllOdds((GAMEINFO*)&stcGameInfo)*mGame_ReadMaxBet();
		
		if(slValue < _Chance.GetVirtualBufTopValue(ulLoc) )
		// ORIGINALif (slValue< stcChance.slVirtualBufTopValue[ulLoc])
		{
			if (slValue>slOdds)
			{
				slOdds = slValue;
				_Scroll.SaveStopData();
				// ORIGINAL vScroll_SaveStopData();
			}
		}
	}
	_Scroll.LoadStopData();
	// ORIGINAL vScroll_LoadStopData();
}
void GameAssign::AllSame(UBYTE ubSymID)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < 15; slLoop++)
	{
		_Scroll.SetStopData(slLoop, ubSymID);
		// ORIGINAL vScroll_SetStopData(slLoop, ubSymID);
	}
}
void GameAssign::MinSpecialSymbol(UBYTE ubSymID, UBYTE ubLoc)
{
	SLONG slLoop;
	ULONG ulOdds, ulValue;
	_SpecialSymbol(ubSymID, ubLoc);
	// ORIGINAL vGameAssign_SpecialSymbol(ubSymID, ubLoc);
	_GameCheck.CheckOdds((GAMEINFO*)&stcGameInfo);
	// ORIGINAL vGameCheck_CheckOdds((GAMEINFO*)&stcGameInfo);

	_Scroll.SaveStopData();
	// ORIGINAL vScroll_SaveStopData();

	ulOdds = _GameCheck.ReadAllOdds((GAMEINFO*)&stcGameInfo);
	// ORIGINAL ulOdds = slGameCheck_ReadAllOdds((GAMEINFO*)&stcGameInfo);
	for (slLoop = 0; slLoop < 4; slLoop++) //取5次，取最小給獎
	{
		_SpecialSymbol(ubSymID, ubLoc);
		// ORIGINAL vGameAssign_SpecialSymbol(ubSymID, ubLoc);

		_GameCheck.CheckOdds((GAMEINFO*)&stcGameInfo);
		// ORIGINAL vGameCheck_CheckOdds((GAMEINFO*)&stcGameInfo);

		ulValue = _GameCheck.ReadAllOdds((GAMEINFO*)&stcGameInfo);
		//ulValue = slGameCheck_ReadAllOdds((GAMEINFO*)&stcGameInfo);
		if (ulValue<ulOdds)
		{
			ulOdds = ulValue;
			_Scroll.SaveStopData();
			// ORIGINAL vScroll_SaveStopData();
		}
	}
	_Scroll.LoadStopData();
	// ORIGINAL vScroll_LoadStopData();
}
void GameAssign::FeverSymbol(UBYTE ubSymID)
{
	SLONG slLoop;
	if ((ubSymID >= DEF_SYMBOL_01) && (ubSymID <= DEF_SYMBOL_06))
	{
		for (slLoop = 0; slLoop < DEF_FEVER_REEL_MAX; slLoop++)
		{
			_Reel.FeverSetStopData(slLoop, ubSymID);
			// ORIGINAL vReel_FeverSetStopData(slLoop, ubSymID);
		}

	}
}
NAMESPACE_NATIVE_END