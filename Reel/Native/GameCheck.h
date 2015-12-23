#pragma once
#include "..\Source\common.h"

NAMESPACE_NATIVE_BEGIN
class Scroll;
class Slave;
class AdjustValue;
class Record;
class Reel;
class WupChance;
class GameCheck
{
	const Scroll&	_Scroll;

	Reel&			_Reel;
	Slave&			_Slave;
	AdjustValue&	_AdjustValue;
	Record&			_Record;

	WupChance&		_WupChance;

	SLONG	_CheckWinSpecial	(UBYTE *ubAllSymbol, UBYTE ubSymID);
	void	_GetLineData		(UBYTE *ubPutData, ULONG ulLine) const ;
	UBYTE	_CheckAllSame		(UBYTE *ubAllSymbol);	
	ULONG	_RightType			(UBYTE *ubLineData);
	ULONG	_LeftType			(UBYTE *ubLineData);
	void	_GetLineData		(UBYTE *ubPutData, ULONG ulLine);
	
public:
	GameCheck(const Scroll& scroll
		, Slave& slave
		, AdjustValue& adjust_value
		, Record& record 
		, Reel& reel
		, WupChance& wup_chance);
	~GameCheck();


	SLONG	IsSpecial			(UBYTE ubSymID);
	// ?¬d­¿?
	void	CheckOdds			(GAMEINFO *stcGame);
	SLONG	ReadAllOdds			(GAMEINFO *stcGame);

	void	CheckAllLineOdds	(GAMEINFO *stcGame);
	SLONG	GameWinRule			(GAMEINFO *stcGame);
	SLONG	FeverValue			(void);
	void	SaveWinRule			(GAMEINFO *stcGame);

	void	WupWinRule			(void);
};

NAMESPACE_NATIVE_END

