#pragma once
#include "../Source/common.h"



NAMESPACE_NATIVE_BEGIN
class Record
{
	friend class VGame::Native::Dump::WheelDumper;
	RECORD stcRecordData[DEF_RECORD_PLR_MAX][DEF_RECORD_DATA_MAX];
	RECORD stcRecordSymbolGift[DEF_RECORD_DATA_MAX];
	RECORD_EVENT_WIN stcRecordEvent_Win[100];
public:
	Record();
	~Record();


	void	Add				(UBYTE ubPlr, UBYTE ubDataID, ULONG ulAdd);
	DLONG	ReadCurrTotal	(UBYTE ubPlr, UBYTE ubDataID);
	void	Add_GiftBet		(UBYTE ubDataID, ULONG ulAdd);
	void	Save_WinEvent	(ULONG ulWin, ULONG ulMode, ULONG ulSymbol);	

	
};

NAMESPACE_NATIVE_END

