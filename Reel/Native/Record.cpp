#include "Record.h"


NAMESPACE_NATIVE_BEGIN
Record::Record()
{
}

Record::~Record()
{
}

void Record::Add(UBYTE ubPlr, UBYTE ubDataID, ULONG ulAdd)
{
	if (ubPlr >= DEF_RECORD_PLR_MAX)       return;
	if (ubDataID >= DEF_RECORD_DATA_MAX)       return;

	if (ubPlr < DEF_RECORD_PLR_ALL)
	{
		stcRecordData[ubPlr][ubDataID].dlCurTotal += ulAdd;
	}
	stcRecordData[DEF_RECORD_PLR_ALL][ubDataID].dlCurTotal += ulAdd;
}

DLONG Record::ReadCurrTotal(UBYTE ubPlr, UBYTE ubDataID)
{
	if (ubPlr >= DEF_RECORD_PLR_MAX)       return (0);
	if (ubDataID >= DEF_RECORD_DATA_MAX)       return (0);

	return (stcRecordData[ubPlr][ubDataID].dlCurTotal);
}

void Record::Add_GiftBet(UBYTE ubDataID, ULONG ulAdd)
{
	if (ubDataID >= DEF_RECORD_DATA_MAX)       return;

	stcRecordSymbolGift[ubDataID].dlCurTotal += ulAdd;
}

void Record::Save_WinEvent(ULONG ulWin, ULONG ulMode, ULONG ulSymbol)
{
	ULONG	i;//, ulTemp ;
	UBYTE ubShowRTC[DEF_RECORD_EVENT_STR_LEN];

	for (i = 0; i<99; i++)
	{
		// 99<=98 , 98<=97 , ... 1<=0 , 0<=New
		stcRecordEvent_Win[99 - i].ulWin = stcRecordEvent_Win[98 - i].ulWin;
		vMemory_Copy((UBYTE *)&stcRecordEvent_Win[99 - i].ubStr[0], (UBYTE *)&stcRecordEvent_Win[98 - i].ubStr[0], DEF_RECORD_EVENT_STR_LEN);
	}

	vRtc3021_ReadTime();
	ubShowRTC[0] = '0' + (stcRtc3021Data.ubMonth / 10) % 10;
	ubShowRTC[1] = '0' + (stcRtc3021Data.ubMonth) % 10;
	ubShowRTC[2] = '/';
	ubShowRTC[3] = '0' + (stcRtc3021Data.ubDay / 10) % 10;
	ubShowRTC[4] = '0' + (stcRtc3021Data.ubDay) % 10;
	ubShowRTC[5] = ' ';
	ubShowRTC[6] = '0' + (stcRtc3021Data.ubHours / 10) % 10;
	ubShowRTC[7] = '0' + (stcRtc3021Data.ubHours) % 10;
	ubShowRTC[8] = ':';
	ubShowRTC[9] = '0' + (stcRtc3021Data.ubMinutes / 10) % 10;
	ubShowRTC[10] = '0' + (stcRtc3021Data.ubMinutes) % 10;
	ubShowRTC[11] = ':';
	ubShowRTC[12] = '0' + (stcRtc3021Data.ubSeconds / 10) % 10;
	ubShowRTC[13] = '0' + (stcRtc3021Data.ubSeconds) % 10;
	ubShowRTC[14] = 0x00;

	stcRecordEvent_Win[0].ulWin = ((ulMode & 0x0F) << 28) + ((ulSymbol & 0x0F) << 24) + (ulWin & 0xFFFFFF);
	vMemory_Copy((UBYTE *)&stcRecordEvent_Win[0].ubStr[0], (UBYTE *)&ubShowRTC[0], DEF_RECORD_EVENT_STR_LEN);
}

/*VGame::CLR::Dump::RecordFieldSet Record::Dump()
{
	VGame::CLR::Dump::RecordFieldSet set = VGame::CLR::Dump::RecordFieldSet();
	System::Collections::Generic::Dictionary<VGame::CLR::Dump::__RECORD_PLR__ , System::Collections::Generic::Dictionary<VGame::CLR::Dump::__RECORD_DATA__ , VGame::CLR::Dump::RecordRecordFieldSet>^> setRecordData = set.stcRecordData;
	


	
	
	return set;
}*/

NAMESPACE_NATIVE_END