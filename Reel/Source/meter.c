#define DEF_METER_C
#include "../../h/common.h"
#define FILE_NAME "METER.C"

enum __METER_STATE__ {
	PROC_METER_NORMAL   ,
	PROC_METER_OUTHIGH  ,
	PROC_METER_WAITHIGH ,
	PROC_METER_OUTLOW   ,
	PROC_METER_WAITLOW
} ;

#define DEF_METER_WAIT_TIMES  6

ULONG ulMeterWaitTimes ;
ULONG ulMeterValue0[DEF_METER_MAX] ;
ULONG ulMeterValue1[DEF_METER_MAX] ;
ULONG ulMeterRate[DEF_METER_MAX] ;
ULONG ulMeterState[DEF_METER_MAX] ;
ULONG ulMeterCount[DEF_METER_MAX] ;

ULONG *ulMeterDefineAdr ;

// �Ĥ@���}����l���
void vMeter_Reset( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_METER_MAX ; slLoop ++ )
	{
		ulMeterValue0[slLoop] = 0 ;
		ulMeterValue1[slLoop] = 0 ;
		ulMeterState[slLoop]  = 0 ;
		ulMeterCount[slLoop]  = 0 ;
		ulMeterRate[slLoop]   = 1 ;
	}
	ulMeterWaitTimes = DEF_METER_WAIT_TIMES ;
}

// �C���}����������l���ܼ�
void vMeter_Initial( void )
{
	SLONG slLoop ;

	for ( slLoop = 0 ; slLoop < DEF_METER_MAX ; slLoop ++ )
	{
		ulMeterState[slLoop] = 0 ;
		ulMeterCount[slLoop] = 0 ;
	}
}

// �֥[ Meter
void vMeter_Add( ULONG ulMeterID , ULONG ulValue )   
{ 
	if ( ulMeterID >= DEF_METER_MAX )
	{
		return ;
	}

	vBoot_DisableIRQ() ; 
	ulMeterValue1[ulMeterID] += ulValue ; 
	if ( ulMeterValue1[ulMeterID] >= ulMeterRate[ulMeterID] )
	{
		ulMeterValue0[ulMeterID] ++ ;
		ulMeterValue1[ulMeterID] -= ulMeterRate[ulMeterID] ;
	}
	vBoot_EnableIRQ() ; 
}

// �֥[ Meter
void vMeter_AddInInterrupt( ULONG ulMeterID , ULONG ulValue )   
{
	if ( ulMeterID >= DEF_METER_MAX )
	{
		return ;
	}

	ulMeterValue1[ulMeterID] += ulValue ; 
	if ( ulMeterValue1[ulMeterID] >= ulMeterRate[ulMeterID] )
	{
		ulMeterValue0[ulMeterID] ++ ;
		ulMeterValue1[ulMeterID] -= ulMeterRate[ulMeterID] ;
	}
}

// �]�w Meter ����v
void vMeter_SetRate( ULONG ulMeterID , ULONG ulValue )   
{
	if ( ulMeterID >= DEF_METER_MAX )
	{
		return ;
	}
	ulMeterRate[ulMeterID] = ulValue ; 
}

// �]�w�C���b�U�����ݪ��ɶ�
void vMeter_SetWaitTimes( ULONG ulValue )   
{ 
	ulMeterWaitTimes = ulValue ;
}

// �B�z Meter ���D�禡
void vMeter_Process( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_METER_MAX ; slLoop ++ )
	{
		switch( ulMeterState[slLoop] )
		{
			case PROC_METER_NORMAL   :
				if ( ulMeterValue1[slLoop] >= ulMeterRate[slLoop] )
				{
					ulMeterValue0[slLoop] ++ ;
					ulMeterValue1[slLoop] -= ulMeterRate[slLoop] ;
				}
				if ( ulMeterValue0[slLoop] )
				{
					ulMeterValue0[slLoop] -- ;
					ulMeterState[slLoop] = PROC_METER_OUTHIGH ;
					ulMeterCount[slLoop] = 0 ;
				}
				break ;
			case PROC_METER_OUTHIGH  :
				vIO_Write( stcMeterOutputInformation[slLoop].ubDrive , stcMeterOutputInformation[slLoop].ubPort , stcMeterOutputInformation[slLoop].ubBit , stcMeterOutputInformation[slLoop].ubBit ) ;
				ulMeterState[slLoop] = PROC_METER_WAITHIGH ;
				ulMeterCount[slLoop] = 0 ;
				break ;
			case PROC_METER_WAITHIGH :
				ulMeterCount[slLoop] ++ ;
				if ( ulMeterCount[slLoop] >= ulMeterWaitTimes )
				{
					ulMeterState[slLoop] = PROC_METER_OUTLOW ;
					ulMeterCount[slLoop] = 0 ;
				}
				break ;
			case PROC_METER_OUTLOW   :
				vIO_Write( stcMeterOutputInformation[slLoop].ubDrive , stcMeterOutputInformation[slLoop].ubPort , stcMeterOutputInformation[slLoop].ubBit , 0 ) ;
				ulMeterState[slLoop] = PROC_METER_WAITLOW ;
				ulMeterCount[slLoop] = 0 ;
				break ;
			case PROC_METER_WAITLOW  :
				ulMeterCount[slLoop] ++ ;
				if ( ulMeterCount[slLoop] >= ulMeterWaitTimes )
				{
					ulMeterState[slLoop] = PROC_METER_NORMAL ;
					ulMeterCount[slLoop] = 0 ;
				}
				break ;
			default :
				ulMeterState[slLoop] = PROC_METER_NORMAL ;
				ulMeterCount[slLoop] = 0 ;
				break ;
		}
	}
}

