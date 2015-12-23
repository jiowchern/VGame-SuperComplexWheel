#pragma once
#include "../Source/common.h"
NAMESPACE_NATIVE_BEGIN

class GameCheck;
class Reel;
class Scroll;
class AdjustValue;
class Chance;
class GameAssign
{
	AdjustValue&	_AdjustValue;
	GameCheck&		_GameCheck;
	Reel&			_Reel;
	Scroll&			_Scroll;

	Chance&			_Chance;

	GAMEINFO&		stcGameInfo;
	void _5Line			(UBYTE ubSymID);
	void _SpecialSymbol	(UBYTE ubSymID, UBYTE ubLoc);
public:
	GameAssign(GameCheck& check,Reel& reel, Scroll& scroll, AdjustValue& value , Chance& chance , GAMEINFO& info);
	~GameAssign();

	void Natural			();
	void Spec5Line			(UBYTE ubSymID, ULONG ulLoc);
	void AllSame			(UBYTE ubSymID);

	void MinSpecialSymbol	(UBYTE ubSymID, UBYTE ubLoc);
	void FeverSymbol		(UBYTE ubSymID);
};

NAMESPACE_NATIVE_END

