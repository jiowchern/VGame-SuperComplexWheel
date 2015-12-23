#pragma once
#include "../Source/common.h"


NAMESPACE_NATIVE_BEGIN
class WupChance;
class AdjustValue;
class Record;
class Slave;
class GameAssign;
class Scroll;
class GameCheck;
class Master;
class Chance
{

	friend class VGame::Native::Dump::WheelDumper;
	MAINCHANCE_BUF	stcChance	;
	FEVERCHANCE_BUF stcFeverChance;
	
	WupChance&		_WupChance;
	AdjustValue&	_AdjustValue;
	Record&			_Record;
	Slave&			_Slave;
	GameAssign&		_GameAssign;
	Scroll&			_Scroll;
	GameCheck&		_GameCheck;
	Master&			_Master;
	GAMEINFO&		stcGameInfo;
	void	_SetBase			();
	void	_AddBet				(SLONG ulBet);
	void	_VirtualBufAdd		(SLONG ulBet);
	void	_VirtualGate		();	
	void	_VirtualReturnBuf	();
	void	_RecArray			();
	void	_VirtualProcess		();
	void	_NaturalDeal		();	
	ULONG	_TakeMinValue		(ULONG ulMin, ULONG ulMax, ULONG ulCount);	
	void	_VirtualAllTopValue	();
	void	_VirtualTopValue	(ULONG ulLoc);
	void	_GameRateSet		();
	ULONG	_TakeValueNum		(VIRTUALINFO *stcVirtual, ULONG ulValue, ULONG ulSize);
	void	_AsnBufProcess		(void);
public:
	Chance(WupChance& chance 
		, AdjustValue& value
		,Record& record 
		, Slave& slave 
		, GameAssign& assign
		, Scroll& scroll
		, GameCheck& check
		, Master& master
		, GAMEINFO& info);
	~Chance();
	ULONG	GetPlayTimes			() const ;
	ULONG	GetActBuf				() const;
	void	SetActBuf				(ULONG val);
	void	Update					();
	void	AddFeverTotalWin		(ULONG val);

	void	GameProcess				();

	SLONG	GetVirtualBufTopValue	(ULONG ulLoc);

	void	WinProcess				(ULONG	ulWin);
	void	WinBonusProcess			(void);
	void	FeverProcess			(void);
	void	WinFeverProcess			(void);
	void	SetChanceData			(UBYTE data);
	UBYTE	GetChanceData			();
	void	SetChanceWin			(ULONG val);
	ULONG	GetChanceWin			();
};
NAMESPACE_NATIVE_END
