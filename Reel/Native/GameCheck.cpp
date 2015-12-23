#include "GameCheck.h"

#include "Scroll.h"
#include "Slave.h"
#include "AdjustValue.h"
#include "Record.h"
#include "Reel.h"
#include "WupChance.h"

// All Same ¥þ??
ULONG const ulGameCheckAllSameOddsTable[DEF_SYMBOL_MAX] =
{
	3000 , 2000 , 1600 , 1000 , 400 , 200 , 160 ,  100 , 80 ,60 , 0 , 0 , 0
};

// ???
ULONG const ulGameCheckOddsTable[6][DEF_SYMBOL_MAX] = {
	//   SYM00  SYM01  SYM02  SYM03  SYM04  SYM05  SYM06  SYM07  SYM08  SYM09  WILD   FEVER  FREE
	{ 0 ,    0 ,   0 ,   0 ,    0 ,    0 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,    0 } ,// 0 Link
	{ 0 ,    0 ,   0 ,   0 ,    0 ,    0 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,    0 } ,// 1 Link
	{ 0 ,    0 ,   0 ,   0 ,    0 ,    0 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,    0 } ,// 2 Link
	{ 50 ,   30 ,  20 ,  15 ,   10 ,    8 ,    5 ,   4 ,    3 ,    2 ,    0 ,    0 ,    0 } ,// 3 Link
	{ 200 ,  120 , 100 ,  50 ,   30 ,   20 ,   15 ,  10 ,    8 ,    5 ,    0 ,    0 ,    0 } ,// 4 Link
	{ 1500 , 1000 , 800 , 500 ,  200 ,  100 ,   80 ,  50 ,   40 ,   30 ,    0 ,    0 ,    0 } ,// 5 Link
};

// ??±Æ¦C
UBYTE const ubGameCheckLineLocInformation[9][5] =
{
	{ 5 ,  6 ,  7 ,  8 ,  9 } ,
	{ 0 ,  1 ,  2 ,  3 ,  4 } ,
	{ 10 , 11 , 12 , 13 , 14 } ,
	{ 0 ,  6 , 12 ,  8 ,  4 } ,
	{ 10 ,  6 ,  2 ,  8 , 14 } ,
	{ 0 ,  1 ,  7 ,  3 ,  4 } ,
	{ 10 , 11 ,  7 , 13 , 14 } ,
	{ 5 , 11 , 12 , 13 ,  9 } ,
	{ 5 ,  1 ,  2 ,  3 ,  9 } ,
};

NAMESPACE_NATIVE_BEGIN



GameCheck::GameCheck(const Scroll & scroll
	, Slave& slave
	, AdjustValue& adjust_value
	, Record& record
	, Reel& reel
	, WupChance& wup_chance) :
_Scroll(scroll)
,_Slave(slave)
, _AdjustValue(adjust_value)
, _Record(record)
, _Reel(reel)
,_WupChance(wup_chance)
{

}

SLONG GameCheck::_CheckWinSpecial(UBYTE * ubAllSymbol, UBYTE ubSymID)
{
	SLONG slLoop, slCal;

	slCal = 0;
	for (slLoop = 0; slLoop < 15; slLoop++)
	{
		if (ubAllSymbol[slLoop] == ubSymID)
		{
			slCal++;
		}
	}

	if (slCal >= 3)
	{
		return (slCal);
	}
	return (0);
}

void GameCheck::_GetLineData(UBYTE * ubPutData, ULONG ulLine) const
{
	SLONG slLoop;

	if (ulLine >= 9)
	{
		return;
	}
	for (slLoop = 0; slLoop < 5; slLoop++)
	{
		ubPutData[slLoop] = _Scroll.GetData(ubGameCheckLineLocInformation[ulLine][slLoop]);
		//ORIGINAL ubPutData[slLoop] = ubScroll_GetData(ubGameCheckLineLocInformation[ulLine][slLoop]);
	}
}

UBYTE GameCheck::_CheckAllSame(UBYTE * ubAllSymbol)
{
	SLONG slLoop;
	UBYTE ubFstSym;

	ubFstSym = ubAllSymbol[0];

	for (slLoop = 0; slLoop < 15; slLoop++)
	{
		if (ubAllSymbol[slLoop] == DEF_SYMBOL_WILD)
		{
			continue;
		}
		if (ubAllSymbol[slLoop] == ubFstSym)
		{
		}
		else
		{
			return (DEF_SYMBOL_MAX);
		}
	}
	return (ubFstSym);
}

// ¥Ñ¥k¦Ü¥ª?¬d??
// Input :
//     ubLineData 
// Output :
//     (return) 
//          15~8 Bits -> ??
//          7~0  Bits -> Symbol ID
ULONG GameCheck::_RightType(UBYTE * ubLineData)
{
	SLONG slLoop;
	UBYTE ubFstSym, ubCal;
	UBYTE ubWildCal;
	ULONG ulWildOdds, ulOdds;

	ubFstSym = ubLineData[4];
	ubCal = 1;
	ubWildCal = 0;
	ulWildOdds = 0;
	ulOdds = 0;

	// ¦pªG²Ä¤@? Symbol ¬O Fever Symbol ªí¥Ü?ªk??
	if (ubFstSym == DEF_SYMBOL_FEVER)
	{
		return (0);
	}
	// ”W¦pªG²Ä¤@? Symbol ¬O Free Symbol ªí¥Ü?ªk??
	if (ubFstSym == DEF_SYMBOL_FREE)
	{
		return (0);
	}
	// ¦pªG²Ä¤@? Symbol ¬O Wild Symbol
	if (ubFstSym == DEF_SYMBOL_WILD)
	{
		// ?ºâ Wild ????
		ubWildCal = 1;
		for (slLoop = 3; slLoop >= 0; slLoop--)
		{
			if (ubLineData[slLoop] == DEF_SYMBOL_WILD)
			{
				ubWildCal++;
			}
			else
			{
				break;
			}
		}
	}

	// ?ºâ¥¿±` Symbol ???? , ¥]§t Wild
	for (slLoop = 3; slLoop >= 0; slLoop--)
	{
		// Symbol ¬O Wild ª½±µ?ºâ
		if (ubLineData[slLoop] == DEF_SYMBOL_WILD)
		{
			ubCal++;
			continue;
		}

		// ¦pªG²Ä¤@? Symbol ¬O Wild , ??·sªº Symbol ¨ú¥N FstSym
		if (ubFstSym == DEF_SYMBOL_WILD)
		{
			ubFstSym = ubLineData[slLoop];
			ubCal++;
		}
		else
		{
			if (ubFstSym == ubLineData[slLoop])
			{
				ubCal++;
			}
			else
			{
				break;
			}
		}
	}

	// ?¨ú¥¿±`???
	ulOdds = ulGameCheckOddsTable[ubCal][ubFstSym];

	// ¦pªG¦³ Wild ??
	if (ubWildCal)
	{
		// ?¨ú Wild ???
		ulWildOdds = ulGameCheckOddsTable[ubWildCal][DEF_SYMBOL_WILD];

		// ¤ñ?­þ?­¿?¤ñ?¤j
		if (ulWildOdds > ulOdds)
		{
			return ((((ULONG)ubWildCal) << 8) | ((ULONG)DEF_SYMBOL_WILD));
		}
	}
	return ((((ULONG)ubCal) << 8) | ((ULONG)ubFstSym));
}

ULONG GameCheck::_LeftType(UBYTE * ubLineData)
{
	SLONG slLoop;
	UBYTE ubFstSym, ubCal;
	UBYTE ubWildCal;
	ULONG ulWildOdds, ulOdds;

	ubFstSym = ubLineData[0];
	ubCal = 1;
	ubWildCal = 0;
	ulWildOdds = 0;
	ulOdds = 0;

	// ”W¦pªG²Ä¤@? Symbol ¬O Fever Symbol ªí¥Ü?ªk??
	if (ubFstSym == DEF_SYMBOL_FEVER)
	{
		return (0);
	}
	// ”W¦pªG²Ä¤@? Symbol ¬O Free Symbol ªí¥Ü?ªk??
	if (ubFstSym == DEF_SYMBOL_FREE)
	{
		return (0);
	}
	// ”WªG²Ä¤@? Symbol ¬O Wild Symbol
	if (ubFstSym == DEF_SYMBOL_WILD)
	{
		//?ºâ Wild ????
		ubWildCal = 1;
		for (slLoop = 1; slLoop < 5; slLoop++)
		{
			if (ubLineData[slLoop] == DEF_SYMBOL_WILD)
			{
				ubWildCal++;
			}
			else
			{
				break;
			}
		}
	}

	// ?ºâ¥¿±` Symbol ???? , ¥]§t Wild
	for (slLoop = 1; slLoop < 5; slLoop++)
	{
		//Symbol ¬O Wild ª½±µ?ºâ
		if (ubLineData[slLoop] == DEF_SYMBOL_WILD)
		{
			ubCal++;
			continue;
		}

		// ¦pªG²Ä¤@? Symbol ¬O Wild , ??·sªº Symbol ¨ú¥N FstSym
		if (ubFstSym == DEF_SYMBOL_WILD)
		{
			ubFstSym = ubLineData[slLoop];
			ubCal++;
		}
		else
		{
			if (ubFstSym == ubLineData[slLoop])
			{
				ubCal++;
			}
			else
			{
				break;
			}
		}
	}

	// ?¨ú¥¿±`???
	ulOdds = ulGameCheckOddsTable[ubCal][ubFstSym];

	// ¦pªG¦³ Wild ??
	if (ubWildCal)
	{
		// ?¨ú Wild ???
		ulWildOdds = ulGameCheckOddsTable[ubWildCal][DEF_SYMBOL_WILD];

		// ¤ñ?­þ?­¿?¤ñ?¤j
		if (ulWildOdds > ulOdds)
		{
			return ((((ULONG)ubWildCal) << 8) | ((ULONG)DEF_SYMBOL_WILD));
		}
	}
	return ((((ULONG)ubCal) << 8) | ((ULONG)ubFstSym));
}

void GameCheck::_GetLineData(UBYTE * ubPutData, ULONG ulLine)
{
	SLONG slLoop;

	if (ulLine >= 9)
	{
		return;
	}
	for (slLoop = 0; slLoop < 5; slLoop++)
	{
		ubPutData[slLoop] = _Scroll.GetData(ubGameCheckLineLocInformation[ulLine][slLoop]);
		// ORIGINAL ubPutData[slLoop] = ubScroll_GetData(ubGameCheckLineLocInformation[ulLine][slLoop]);
	}
}

GameCheck::~GameCheck()
{
}

SLONG  GameCheck::IsSpecial(UBYTE ubSymID)
{
	SLONG slLoop;
	UBYTE ubAllSymbol[15];

	for (slLoop = 0; slLoop < 15; slLoop++)
	{
		
		ubAllSymbol[slLoop] = _Scroll.GetData(slLoop);
		//ORIGINAL : ubAllSymbol[slLoop] = ubScroll_GetData(slLoop);
	}

	return _CheckWinSpecial(ubAllSymbol, ubSymID);
	// ORIGINAL : return (slGameCheck_CheckWinSpecial(ubAllSymbol, ubSymID));
}

void GameCheck::CheckOdds(GAMEINFO * stcGame)
{
	SLONG slLine, slLoop, slLoop1;
	ULONG ulType, ulSym, ulCal;
	UBYTE ubAllSymbol[15];

	// ªì©l??
	for (slLoop = 0; slLoop < 15; slLoop++)
	{
		ubAllSymbol[slLoop] = _Scroll.GetData(slLoop);
		// ORIGINAL ubAllSymbol[slLoop] = ubScroll_GetData(slLoop);
	}

	stcGame->ulAllSameOdds = 0;
	stcGame->ulAllSameSym = 0;
	stcGame->ulFeverSetLife = 0;
	stcGame->ulFeverNowLife = 0;

	stcGame->ulBonusType = 0;
	stcGame->ulBonusWin = 0;
	stcGame->ulFreeSetLife = 0;
	stcGame->ulFreeType = 0;
	for (slLine = 0; slLine < 9; slLine++)
	{
		for (slLoop1 = 0; slLoop1 < 2; slLoop1++)
		{
			stcGame->stcLine[slLine].ulWinSym[slLoop1] = 0;
			stcGame->stcLine[slLine].ulWinNum[slLoop1] = 0;
			stcGame->stcLine[slLine].ulOdds[slLoop1] = 0;
			for (slLoop = 0; slLoop < 5; slLoop++)
			{
				stcGame->stcLine[slLine].ubAct[slLoop1][slLoop] = 0;
			}

		}
		_GetLineData(stcGame->stcLine[slLine].ubSym, slLine);
		// ORIGINAL vGameCheck_GetLineData(stcGame->stcLine[slLine].ubSym, slLine);
	}

	// ?¬d AllSame ?
	ulSym = _CheckAllSame(ubAllSymbol);
	// ORIGINAL ulSym = ubGameCheck_CheckAllSame(ubAllSymbol);
	if (ulSym < DEF_SYMBOL_MAX)
	{
		stcGame->ulAllSameSym = ulSym;
		stcGame->ulAllSameOdds = ulGameCheckAllSameOddsTable[ulSym];
		return;
	}

	// ?¬d Fever Game
	ulCal = _CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FEVER);
	// ORIGINAL ulCal = slGameCheck_CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FEVER);
	if (ulCal >= 3)
	{
		if (ulCal == 3)
		{
			stcGame->ulFeverSetLife = 1;
			stcGame->ulFeverNowLife = 1;
		}
		else if (ulCal == 4)
		{
			stcGame->ulFeverSetLife = 2;
			stcGame->ulFeverNowLife = 2;
		}
		else
		{
			stcGame->ulFeverSetLife = 3;
			stcGame->ulFeverNowLife = 3;
		}
	}

	// ?¬d Free Game
	ulCal = _CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FREE);
	// ORIGINAL ulCal = slGameCheck_CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FREE);
	if (ulCal >= 3)
	{
		if (ulCal == 3)
		{
			stcGame->ulFreeSetLife = 10;
			stcGame->ulFreeType = 1;

		}
		else if (ulCal == 4)
		{
			stcGame->ulFreeSetLife = 20;
			stcGame->ulFreeType = 2;
		}
		else
		{
			stcGame->ulFreeSetLife = 30;
			stcGame->ulFreeType = 3;
		}
	}
	ulCal = _CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_WILD);
	// ORIGINAL ulCal = slGameCheck_CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_WILD);
	if (ulCal >= 3)
	{
		if (ulCal == 3)
		{
			stcGame->ulBonusType = 1;
		}
		else if (ulCal == 4)
		{
			stcGame->ulBonusType = 2;
		}
		else
		{
			stcGame->ulBonusType = 3;
		}

	}
	// ?¬d Link ?
	ulSym = 0;
	ulCal = 0;

	for (slLine = 0; slLine < 9; slLine++)
	{
		

		if (slLine < _Slave.ReadLine())	// ??¨½Á×?¥¼©ãª`ªº?       
		// ORIGINAL if (slLine < slSlave_ReadLine())	// ??¨½Á×?¥¼©ãª`ªº?       
		{
			for (slLoop = 0; slLoop < 2; slLoop++)
			{
				if (slLoop)
				{
					ulType = _RightType(stcGame->stcLine[slLine].ubSym);
					// ORIGINAL ulType = ulGameCheck_RightType(stcGame->stcLine[slLine].ubSym);
				}
				else
				{
					ulType = _LeftType(stcGame->stcLine[slLine].ubSym);
					// ORIGINAL ulType = ulGameCheck_LeftType(stcGame->stcLine[slLine].ubSym);
				}
				ulSym = (ulType & 0xFF);
				ulCal = ((ulType >> 8) & 0xFF);

				if ((ulCal >= 6) || (ulSym >= DEF_SYMBOL_MAX))
				{
					continue;
				}
				stcGame->stcLine[slLine].ulWinSym[slLoop] = ulSym;
				stcGame->stcLine[slLine].ulWinNum[slLoop] = ulCal;
				stcGame->stcLine[slLine].ulOdds[slLoop] = ulGameCheckOddsTable[ulCal][ulSym];
				if (stcGame->stcLine[slLine].ulOdds[slLoop])
				{
					if (slLoop)
					{
						for (slLoop1 = 4; slLoop1 >= (5 - ulCal); slLoop1--)
						{
							stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1;
						}
					}
					else
					{
						for (slLoop1 = 0; slLoop1 < ulCal; slLoop1++)
						{
							stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1;
						}

					}
					if (ulCal >= 4)
					{
						break;	//¨¾¤î5???­«Î`?ºâ
					}
				}

			}
		}
	}
}

SLONG GameCheck::ReadAllOdds(GAMEINFO * stcGame)
{
	ULONG ulOdds;
	SLONG slLine;
	ulOdds = stcGame->ulAllSameOdds;
	for (slLine = 0; slLine < 9; slLine++)
	{
		ulOdds += stcGame->stcLine[slLine].ulOdds[0];
		ulOdds += stcGame->stcLine[slLine].ulOdds[1];
	}

	return (ulOdds);
}

void GameCheck::CheckAllLineOdds(GAMEINFO * stcGame)
{
	SLONG slLine, slLoop, slLoop1;
	ULONG ulType, ulSym, ulCal;
	UBYTE ubAllSymbol[15];

	// ªì©l??
	for (slLoop = 0; slLoop < 15; slLoop++)
	{
		ubAllSymbol[slLoop] = _Scroll.GetData(slLoop);
		// ORIGINAL ubAllSymbol[slLoop] = ubScroll_GetData(slLoop);
	}

	stcGame->ulAllSameOdds = 0;
	stcGame->ulAllSameSym = 0;
	stcGame->ulFeverSetLife = 0;
	stcGame->ulFeverNowLife = 0;

	stcGame->ulBonusType = 0;
	stcGame->ulBonusWin = 0;
	stcGame->ulFreeSetLife = 0;
	stcGame->ulFreeType = 0;
	for (slLine = 0; slLine < 9; slLine++)
	{
		for (slLoop1 = 0; slLoop1 < 2; slLoop1++)
		{
			stcGame->stcLine[slLine].ulWinSym[slLoop1] = 0;
			stcGame->stcLine[slLine].ulWinNum[slLoop1] = 0;
			stcGame->stcLine[slLine].ulOdds[slLoop1] = 0;
			for (slLoop = 0; slLoop < 5; slLoop++)
			{
				stcGame->stcLine[slLine].ubAct[slLoop1][slLoop] = 0;
			}

		}
		
		_GetLineData(stcGame->stcLine[slLine].ubSym, slLine);
		// ORIGINAL vGameCheck_GetLineData(stcGame->stcLine[slLine].ubSym, slLine);
	}

	// ?¬d AllSame ?
	ulSym = _CheckAllSame(ubAllSymbol);
	// ORIGINAL ulSym = ubGameCheck_CheckAllSame(ubAllSymbol);
	if (ulSym < DEF_SYMBOL_MAX)
	{
		stcGame->ulAllSameSym = ulSym;
		stcGame->ulAllSameOdds = ulGameCheckAllSameOddsTable[ulSym];
		return;
	}

	// ?¬d Fever Game
	ulCal = _CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FEVER);
	//ORIGINAL ulCal = slGameCheck_CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FEVER);
	if (ulCal >= 3)
	{
		if (ulCal == 3)
		{
			stcGame->ulFeverSetLife = 1;
			stcGame->ulFeverNowLife = 1;
		}
		else if (ulCal == 4)
		{
			stcGame->ulFeverSetLife = 2;
			stcGame->ulFeverNowLife = 2;
		}
		else
		{
			stcGame->ulFeverSetLife = 3;
			stcGame->ulFeverNowLife = 3;
		}
	}

	// ?¬d Free Game
	ulCal = _CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FREE);
	// ORIGINAL ulCal = slGameCheck_CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_FREE);
	if (ulCal >= 3)
	{
		if (ulCal == 3)
		{
			stcGame->ulFreeSetLife = 10;
			stcGame->ulFreeType = 1;

		}
		else if (ulCal == 4)
		{
			stcGame->ulFreeSetLife = 20;
			stcGame->ulFreeType = 2;
		}
		else
		{
			stcGame->ulFreeSetLife = 30;
			stcGame->ulFreeType = 3;
		}
	}
	ulCal = _CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_WILD);
	// ORIGINAL ulCal = slGameCheck_CheckWinSpecial(ubAllSymbol, DEF_SYMBOL_WILD);
	if (ulCal >= 3)
	{
		if (ulCal == 3)
		{
			stcGame->ulBonusType = 1;
		}
		else if (ulCal == 4)
		{
			stcGame->ulBonusType = 2;
		}
		else
		{
			stcGame->ulBonusType = 3;
		}

	}
	// ?¬d Link ?
	ulSym = 0;
	ulCal = 0;

	for (slLine = 0; slLine < 9; slLine++)
	{
		//if( slLine < slSlave_ReadLine() )	// ??¨½Á×?¥¼©ãª`ªº?       
		{
			for (slLoop = 0; slLoop < 2; slLoop++)
			{
				if (slLoop)
				{
					ulType = _RightType(stcGame->stcLine[slLine].ubSym);
					// ORIGINAL ulType = ulGameCheck_RightType(stcGame->stcLine[slLine].ubSym);
				}
				else
				{
					ulType = _LeftType(stcGame->stcLine[slLine].ubSym);
					// ORIGINAL ulType = ulGameCheck_LeftType(stcGame->stcLine[slLine].ubSym);
				}
				ulSym = (ulType & 0xFF);
				ulCal = ((ulType >> 8) & 0xFF);

				if ((ulCal >= 6) || (ulSym >= DEF_SYMBOL_MAX))
				{
					continue;
				}
				stcGame->stcLine[slLine].ulWinSym[slLoop] = ulSym;
				stcGame->stcLine[slLine].ulWinNum[slLoop] = ulCal;
				stcGame->stcLine[slLine].ulOdds[slLoop] = ulGameCheckOddsTable[ulCal][ulSym];
				if (stcGame->stcLine[slLine].ulOdds[slLoop])
				{
					if (slLoop)
					{
						for (slLoop1 = 4; slLoop1 >= (5 - ulCal); slLoop1--)
						{
							stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1;
						}
					}
					else
					{
						for (slLoop1 = 0; slLoop1 < ulCal; slLoop1++)
						{
							stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1;
						}

					}
					if (ulCal >= 4)
					{
						break;	//¨¾¤î5???­«Î`?ºâ
					}
				}

			}
		}
	}
}

SLONG GameCheck::GameWinRule(GAMEINFO * stcGame)
{
	SLONG slValue;
	SLONG slLine;

	
	slValue = stcGame->ulAllSameOdds *  _Slave.ReadTotalBet();
	// ORIGINAL slValue = stcGame->ulAllSameOdds *  slSlave_ReadTotalBet();
	for (slLine = 0; slLine < 9; slLine++)
	{
		
		slValue += stcGame->stcLine[slLine].ulOdds[0] * _Slave.ReadBet();
		// ORIGINAL slValue += stcGame->stcLine[slLine].ulOdds[0] * slSlave_ReadBet();

		slValue += stcGame->stcLine[slLine].ulOdds[1] * _Slave.ReadBet();
		// ORIGINAL slValue += stcGame->stcLine[slLine].ulOdds[1] * slSlave_ReadBet();
	}
	return (slValue);
}

SLONG GameCheck::FeverValue(void)
{
	SLONG slLine, slLoop;
	UBYTE ubAllSymbol[3];

	// ªì©l??
	for (slLoop = 0; slLoop < DEF_FEVER_REEL_MAX; slLoop++)
	{
		
		ubAllSymbol[slLoop] = _Reel.GetFerverStopID(slLoop, 2);
		// ORIGINAL ubAllSymbol[slLoop] = stcReelFeverData[slLoop].ubStopID[2];
	}
	for (slLine = 0; slLine < 7; slLine++)
	{
		for (slLoop = 0; slLoop < DEF_FEVER_REEL_MAX; slLoop++)
		{
			if (ubAllSymbol[slLoop] != slLine)
			{
				break;
			}
		}
		if (slLoop == DEF_FEVER_REEL_MAX)
		{
			return(slLine);
		}

	}

	return(7);
}

void GameCheck::SaveWinRule(GAMEINFO * stcGame)
{
	//    SLONG slValue ;
    SLONG slLine, slLoop;
	//slValue = stcGame->ulAllSameOdds *  slSlave_ReadTotalBet() ;
	SLONG slGiftBet;
	SLONG slInFree;

	slGiftBet = 0;

	
	if (_Slave.ReadTotalBet() >= _AdjustValue.ReadBetForGift() ) slGiftBet = 1;
	// ORIGINAL if (slSlave_ReadTotalBet() >= mGame_ReadBetForGift()) slGiftBet = 1;

	slInFree = 0;
	if (stcGame->ulFreeNowLife) slInFree = 8;

	if (stcGame->ulAllSameOdds)
	{
		_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_ALL + stcGame->ulAllSameSym, 1);
		// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_ALL + stcGame->ulAllSameSym, 1);
		if (slGiftBet)
		{
			_Record.Add_GiftBet(DEF_REC_SYM00_ALL + stcGame->ulAllSameSym, 1);
			// ORIGINAL vRecord_Add_GiftBet(DEF_REC_SYM00_ALL + stcGame->ulAllSameSym, 1);
		}
		_Record.Save_WinEvent((stcGame->ulAllSameOdds * _Slave.ReadTotalBet()), 2 + slInFree, stcGame->ulAllSameSym);
		// ORIGINAL vRecord_Save_WinEvent((stcGame->ulAllSameOdds * slSlave_ReadTotalBet()), 2 + slInFree, stcGame->ulAllSameSym);
	}
	for (slLine = 0; slLine < 9; slLine++)
	{
		for (slLoop = 0; slLoop < 2; slLoop++)
		{
			if (stcGame->stcLine[slLine].ulOdds[slLoop])
			{
				if (stcGame->stcLine[slLine].ulWinNum[slLoop] == 3)
				{
					_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_X3 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_X3 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					if (slGiftBet)
					{
						_Record.Add_GiftBet(DEF_REC_SYM00_X3 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
						// ORIGINAL vRecord_Add_GiftBet(DEF_REC_SYM00_X3 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					}
					if (stcGame->stcLine[slLine].ulOdds[slLoop] >= 100)
					{
						_Record.Save_WinEvent((stcGame->stcLine[slLine].ulOdds[slLoop] * _Slave.ReadBet()), 3 + slInFree, stcGame->stcLine[slLine].ulWinSym[slLoop]);
						// ORIGINAL vRecord_Save_WinEvent((stcGame->stcLine[slLine].ulOdds[slLoop] * slSlave_ReadBet()), 3 + slInFree, stcGame->stcLine[slLine].ulWinSym[slLoop]);
					}
				}
				else if (stcGame->stcLine[slLine].ulWinNum[slLoop] == 4)
				{
					_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_X4 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					// ORGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_X4 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					if (slGiftBet)
					{
						_Record.Add_GiftBet(DEF_REC_SYM00_X4 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
						// ORIGINAL vRecord_Add_GiftBet(DEF_REC_SYM00_X4 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					}
					if (stcGame->stcLine[slLine].ulOdds[slLoop] >= 100)
					{
						_Record.Save_WinEvent((stcGame->stcLine[slLine].ulOdds[slLoop] * _Slave.ReadBet()), 4 + slInFree, stcGame->stcLine[slLine].ulWinSym[slLoop]);
						// ORIGINAL vRecord_Save_WinEvent((stcGame->stcLine[slLine].ulOdds[slLoop] * slSlave_ReadBet()), 4 + slInFree, stcGame->stcLine[slLine].ulWinSym[slLoop]);
					}
				}
				else if (stcGame->stcLine[slLine].ulWinNum[slLoop] == 5)
				{
					_Record.Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_X5 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					// ORIGINAL vRecord_Add(DEF_GAME_ONLY_PLAY, DEF_REC_SYM00_X5 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					if (slGiftBet)
					{
						_Record.Add_GiftBet(DEF_REC_SYM00_X5 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
						// ORIGINAL vRecord_Add_GiftBet(DEF_REC_SYM00_X5 + stcGame->stcLine[slLine].ulWinSym[slLoop], 1);
					}
					if (stcGame->stcLine[slLine].ulOdds[slLoop] >= 100)
					{
						_Record.Save_WinEvent((stcGame->stcLine[slLine].ulOdds[slLoop] * _Slave.ReadBet()), 5 + slInFree, stcGame->stcLine[slLine].ulWinSym[slLoop]);
						// ORIGNAL vRecord_Save_WinEvent((stcGame->stcLine[slLine].ulOdds[slLoop] * slSlave_ReadBet()), 5 + slInFree, stcGame->stcLine[slLine].ulWinSym[slLoop]);
					}
				}
			}

		}

	}
}

void GameCheck::WupWinRule(void)
{
	SLONG slValue;
	slValue = _Slave.WupWinRead();
	// ORIGINAL slValue = slSlave_WupWinRead();
	
	switch (_WupChance.GetData())
	// ORIGINAL switch (stcWupChance.ubData)
	{
	case DEF_CHANCE_WUP_WIN_X1:
		_Slave.WupWinSet(slValue * 2);
		// ORIGNAL vSlave_WupWinSet(slValue * 2);
		break;
	case DEF_CHANCE_WUP_WIN_X2:
		_Slave.WupWinSet(slValue * 3);
		// ORIGNAL vSlave_WupWinSet(slValue * 3);
		break;
	case DEF_CHANCE_WUP_WIN_X3:
		_Slave.WupWinSet(slValue * 4);
		// ORIGINAL vSlave_WupWinSet(slValue * 4);
		break;
	case DEF_CHANCE_WUP_WIN_X4:
		_Slave.WupWinSet(slValue * 5);
		// ORIGINAL vSlave_WupWinSet(slValue * 5);
		break;

	case DEF_CHANCE_WUP_LOSE:
		_Slave.WupWinSet(0);
		// ORIGINAL vSlave_WupWinSet(0);
		break;
	}
}

NAMESPACE_NATIVE_END