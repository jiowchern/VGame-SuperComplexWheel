#include "Scroll.h"
#include "Reel.h"
#include "GameCheck.h"
NAMESPACE_NATIVE_BEGIN

UBYTE const ubScrollSymbolDataCS[3][DEF_REEL_MAX_SYM] = {
	{
		DEF_SYMBOL_00,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,
		DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,
	DEF_SYMBOL_01,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_04,
	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_06,
	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_04,
	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_03,
	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_06,
	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_03,
	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_03,
	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_05,
	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_01,
	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_06,
	DEF_SYMBOL_02,	DEF_SYMBOL_06
	},

	{
		DEF_SYMBOL_00,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_03,
		DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_04,
	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_01,
	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_05,
	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_05,
	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_05,
	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,
	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_01,
	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_06,
	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,
	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_03,
	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,
	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_05,
	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
	DEF_SYMBOL_01,	DEF_SYMBOL_05


	},
	{
		DEF_SYMBOL_00,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_01,
	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_01,
	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_05,
	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_01,
	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_02,
	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_02,
	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,
	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_02,
	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,
	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_04,
	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_03,
	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
	DEF_SYMBOL_01,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_03,
	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,
	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
	DEF_SYMBOL_02,	DEF_SYMBOL_06
	}


};

UBYTE const ubScrollSymbolData[DEF_REEL_MAX_SYM] =
{

	DEF_SYMBOL_00,DEF_SYMBOL_09,DEF_SYMBOL_08,DEF_SYMBOL_07,DEF_SYMBOL_10,DEF_SYMBOL_01,DEF_SYMBOL_04,DEF_SYMBOL_06,
	DEF_SYMBOL_11,DEF_SYMBOL_05,DEF_SYMBOL_02,DEF_SYMBOL_08,DEF_SYMBOL_00,DEF_SYMBOL_09,DEF_SYMBOL_07,DEF_SYMBOL_03,
	DEF_SYMBOL_06,DEF_SYMBOL_04,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_07,DEF_SYMBOL_05,DEF_SYMBOL_01,DEF_SYMBOL_07,
	DEF_SYMBOL_03,DEF_SYMBOL_00,DEF_SYMBOL_08,DEF_SYMBOL_02,DEF_SYMBOL_06,DEF_SYMBOL_08,DEF_SYMBOL_09,DEF_SYMBOL_12,
	DEF_SYMBOL_03,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_04,DEF_SYMBOL_07,DEF_SYMBOL_02,DEF_SYMBOL_08,DEF_SYMBOL_05,
	DEF_SYMBOL_01,DEF_SYMBOL_09,DEF_SYMBOL_06,DEF_SYMBOL_04,DEF_SYMBOL_00,DEF_SYMBOL_08,DEF_SYMBOL_02,DEF_SYMBOL_03,
	DEF_SYMBOL_09,DEF_SYMBOL_05,DEF_SYMBOL_07,DEF_SYMBOL_06,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_08,DEF_SYMBOL_04,
	DEF_SYMBOL_05,DEF_SYMBOL_06,DEF_SYMBOL_01,DEF_SYMBOL_09,DEF_SYMBOL_07,DEF_SYMBOL_03,DEF_SYMBOL_08,DEF_SYMBOL_06,
	DEF_SYMBOL_07,DEF_SYMBOL_01,DEF_SYMBOL_03,DEF_SYMBOL_09,DEF_SYMBOL_00,DEF_SYMBOL_06,DEF_SYMBOL_04,DEF_SYMBOL_12,
	DEF_SYMBOL_08,DEF_SYMBOL_07,DEF_SYMBOL_02,DEF_SYMBOL_05,DEF_SYMBOL_04,DEF_SYMBOL_10,DEF_SYMBOL_09,DEF_SYMBOL_05,
	DEF_SYMBOL_06,DEF_SYMBOL_07,DEF_SYMBOL_03,DEF_SYMBOL_08,DEF_SYMBOL_00,DEF_SYMBOL_04,DEF_SYMBOL_06,DEF_SYMBOL_05,
	DEF_SYMBOL_01,DEF_SYMBOL_08,DEF_SYMBOL_05,DEF_SYMBOL_02,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_08,DEF_SYMBOL_03,
	DEF_SYMBOL_07,DEF_SYMBOL_02,DEF_SYMBOL_04,DEF_SYMBOL_03,DEF_SYMBOL_05,DEF_SYMBOL_06,DEF_SYMBOL_09,DEF_SYMBOL_00,
	DEF_SYMBOL_01,DEF_SYMBOL_08,DEF_SYMBOL_07,DEF_SYMBOL_06,DEF_SYMBOL_02,DEF_SYMBOL_04,DEF_SYMBOL_05,DEF_SYMBOL_09,
	DEF_SYMBOL_11,DEF_SYMBOL_07,DEF_SYMBOL_08,DEF_SYMBOL_04,DEF_SYMBOL_01,DEF_SYMBOL_06,DEF_SYMBOL_03,DEF_SYMBOL_05,
	DEF_SYMBOL_04,DEF_SYMBOL_10,DEF_SYMBOL_09,DEF_SYMBOL_07,DEF_SYMBOL_06,DEF_SYMBOL_08,DEF_SYMBOL_02,DEF_SYMBOL_05


};


Scroll::Scroll(Reel& reel , GameCheck& check) :
_Reel(reel) , 
_GameCheck(check)
{
}

Scroll::~Scroll()   
{
}

void Scroll::Reset()
{
	SLONG slLoop, slLoop1;
	for (slLoop1 = 0; slLoop1 < 10; slLoop1++)
	{
		for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
		{
			_Reel.Initial(slLoop, (UBYTE *)&ubScrollSymbolData[0]);
			// ORIGINAL :�@vReel_Initial(slLoop, (UBYTE *)&ubScrollSymbolData[0]);

			_Reel.SaveData(slLoop);
			// ORIGINAL :�@vReel_SaveData(slLoop);

			_Reel.SetRandData(slLoop);
			// ORIGINAL :�@vReel_SetRandData( slLoop ) ;

			_Reel.StopDataToShowData(slLoop);
			// ORIGINAL :�@vReel_StopDataToShowData( slLoop ) ;
		}

		
		if (_GameCheck.IsSpecial(DEF_SYMBOL_WILD))
		// ORIGINAL :�@if (slGameCheck_IsSpecial(DEF_SYMBOL_WILD))
		{
			continue;
		}

		if (_GameCheck.IsSpecial(DEF_SYMBOL_FEVER))
		// ORIGINAL :�@if (slGameCheck_IsSpecial(DEF_SYMBOL_FEVER))
		{
			continue;
		}

		if (_GameCheck.IsSpecial(DEF_SYMBOL_FREE))
		// ORIGINAL :�@if (slGameCheck_IsSpecial(DEF_SYMBOL_FREE))
		{
			continue;
		}
		break;
		 
	}
}

UBYTE  Scroll::GetData(SLONG ulReel) const
{
	if (ulReel >= DEF_REEL_MAX)
	{
		return (0);
	}
	return _Reel.GetData(ulReel);
	// ORIGINAL : return (ubReel_GetData(ulReel));
}

void Scroll::SaveStopData(void)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
	{
		_Reel.SaveStopData(slLoop);
		// ORIGINAL vReel_SaveStopData(slLoop);
	}
}

void Scroll::LoadStopData(void)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
	{
		_Reel.LoadStopData(slLoop);
		//ORIGINAL vReel_LoadStopData(slLoop);
	}
}

void Scroll::SetStopData(ULONG ulReel, UBYTE ubData)
{
	if (ulReel >= DEF_REEL_MAX)
	{
		return;
	}
	_Reel.SetStopData(ulReel, ubData);
	// ORIGINAL vReel_SetStopData(ulReel, ubData);
}

void Scroll::SetRandData(ULONG ulReel)
{
	if (ulReel >= DEF_REEL_MAX)
	{
		return;
	}
	_Reel.SetRandData(ulReel);
	// ORIGINAL vReel_SetRandData(ulReel);
}

void Scroll::StartAllRun(void)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_REEL_MAX; slLoop++)
	{
		_Reel.StartRun(slLoop);
		// ORIGINAL vReel_StartRun(slLoop);
	}
}

void Scroll::FeverReset(void)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_FEVER_REEL_MAX; slLoop++)
	{

		_Reel.FeverInitial(slLoop, (UBYTE *)&ubScrollSymbolDataCS[slLoop][0]);
		// ORIGINAL vReel_FeverInitial(slLoop, (UBYTE *)&ubScrollSymbolDataCS[slLoop][0]);
		
		_Reel.FeverSaveData(slLoop);
		//ORIGINAL vReel_FeverSaveData(slLoop);

		//vReel_SetRandData( slLoop ) ;
		//vReel_StopDataToShowData( slLoop ) ;
	}
}

void Scroll::FeverStartAllRun(void)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_FEVER_REEL_MAX; slLoop++)
	{
		_Reel.FeverStartRun(slLoop);
		// ORIGINAL vReel_FeverStartRun(slLoop);
	}
}

void Scroll::FeverAllStop(void)
{
	SLONG slLoop;

	for (slLoop = 0; slLoop < DEF_FEVER_REEL_MAX; slLoop++)
	{
		_Reel.FeverStopRun(slLoop);
		// ORIGINAL vReel_FeverStopRun(slLoop);
	}
}

NAMESPACE_NATIVE_END