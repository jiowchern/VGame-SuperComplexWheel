#pragma once

#include "../Source/common.h"

NAMESPACE_NATIVE_BEGIN

class Record;
class Slave;
class AdjustValue;
class WupChance
{
	friend class VGame::Native::Dump::WheelDumper;
	Slave&			_Slave;
	Record&			_Record;
	AdjustValue&	_AdjustValue;
	WUPCHANCE_BUF	stcWupChance;
	void	_ResetAsnLose	(ULONG ulWin);
	
	void	_ResetAsnKill	(void);
	ULONG	_TakeValueNum	(ULONG const *ulData, ULONG ulValue, ULONG ulSize);
	void	_Reset			(void);
public:
	WupChance(Record& record , Slave& slave , AdjustValue& value);
	~WupChance();

	void	SetRate		();
	void	BetProcess	(void);
	void	WinProcess	(ULONG ulWin);
	UBYTE	GetData		();
	void	SetGuess	(UBYTE val);

	void	DealProcess	(void);
};

NAMESPACE_NATIVE_END

