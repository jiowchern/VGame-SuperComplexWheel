#define DEF_ADJUSTVALUE_C
#include "common.h"
#define FILE_NAME "ADJUSTVALUE.C"

ULONG ulAdjustValue_VersionValue ;

volatile UBYTE ubAdjustValueDataForSW[DEF_ADJUSTVALUE_MAX] ;
volatile UBYTE ubAdjustValueTempDataForSW[DEF_ADJUSTVALUE_MAX] ;
//#ifdef DEF_ENABLE_MULTI_SELECT
volatile ULONG ulAdjustGameSel ;
volatile ULONG ulAdjustTempGameSel ;
//#endif
#ifdef __NO_UART__
#else
volatile ULONG ulAdjustSlaveIDSel ;
volatile ULONG ulAdjustTempSlaveIDSel ;
#endif

void vAdjustValue_Reset( void )
{
	SLONG slLoop ;
	UBYTE ubDefault ;
	
	for ( slLoop = 0 ; slLoop < DEF_ADJUSTVALUE_MAX ; slLoop ++ )
	{
		ubDefault = stcAdjustValueInformationForSW[slLoop].uwDefault ;
		
		ubAdjustValueDataForSW[slLoop]     = ubDefault ;
		ubAdjustValueTempDataForSW[slLoop] = ubDefault ;
	}
}

ULONG ulAdjustValue_Initial( ULONG version )
{
	ULONG	ulReset ;
	
	ulReset = 0 ;
	
	if ( ulAdjustValue_VersionValue != version )
	{
		ulReset ++ ;
	}
	
	if( ulReset )
	{
		vAdjustValue_Reset( ) ;
		
		ulAdjustValue_VersionValue = version ;
	}
	
	return ulReset ;
}

void vAdjustValue_Break( void )
{
	ulAdjustValue_VersionValue = 0 ;
}

void vAdjustValue_SetBitValue( ULONG ulID , ULONG ulValue )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ;
	}
	if ( ulValue < stcAdjustValueInformationForSW[ulID].uwMax )
	{
		ubAdjustValueDataForSW[ulID] = ulValue ;
	}
}

ULONG ulAdjustValue_ReadBitValue( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ( 0 ) ;
	}
	return ( ubAdjustValueDataForSW[ulID] ) ;
}

void vAdjustValue_Setup( void )
{
	SLONG slLoop ;

	for ( slLoop = 0 ; slLoop < DEF_ADJUSTVALUE_MAX ; slLoop ++ )
	{
		ubAdjustValueTempDataForSW[slLoop] = ubAdjustValueDataForSW[slLoop] ;
	}
}

void vAdjustValue_Set( ULONG ulID , ULONG ulValue )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ;
	}
	if ( ulValue < stcAdjustValueInformationForSW[ulID].uwMax )
	{
		ubAdjustValueTempDataForSW[ulID] = ulValue ;
	}
}

void vAdjustValue_Inc( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ;
	}
	ubAdjustValueTempDataForSW[ulID] ++ ;
	if ( ubAdjustValueTempDataForSW[ulID] >= stcAdjustValueInformationForSW[ulID].uwMax )
	{
		ubAdjustValueTempDataForSW[ulID] = stcAdjustValueInformationForSW[ulID].uwMax-1 ;
	}
}

void vAdjustValue_IncLoop( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ;
	}
	ubAdjustValueTempDataForSW[ulID] ++ ;
	if ( ubAdjustValueTempDataForSW[ulID] >= stcAdjustValueInformationForSW[ulID].uwMax )
	{
		ubAdjustValueTempDataForSW[ulID] = 0 ;
	}
}

void vAdjustValue_Dec( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ;
	}
	if ( ubAdjustValueTempDataForSW[ulID] )
	{
		ubAdjustValueTempDataForSW[ulID] -- ;
	}
}

void vAdjustValue_DecLoop( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ;
	}
	if ( ubAdjustValueTempDataForSW[ulID] )
	{
		ubAdjustValueTempDataForSW[ulID] -- ;
	}
	else
	{
		ubAdjustValueTempDataForSW[ulID] = stcAdjustValueInformationForSW[ulID].uwMax-1 ;
	}
}

void vAdjustValue_UpDate( void )
{
	SLONG slLoop ;

	for ( slLoop = 0 ; slLoop < DEF_ADJUSTVALUE_MAX ; slLoop ++ )
	{
		ubAdjustValueDataForSW[slLoop] = ubAdjustValueTempDataForSW[slLoop] ;
	}
}

ULONG ulAdjustValue_Read( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ( 0 ) ;
	}
	if( ubAdjustValueDataForSW[ulID] >= DEF_ADJUSTVALUE_MAX )
	{
		return ( 0 ) ;
	}

	return ( stcAdjustValueInformationForSW[ulID].ulValue[ubAdjustValueDataForSW[ulID]] ) ;
}

ULONG ulAdjustValue_ReadTemp( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ( 0 ) ;
	}
	if( ubAdjustValueTempDataForSW[ulID] >= DEF_ADJUSTVALUE_MAX )
	{
		return ( 0 ) ;
	}

	return ( stcAdjustValueInformationForSW[ulID].ulValue[ubAdjustValueTempDataForSW[ulID]] ) ;
}

ULONG ulAdjustValue_ReadTempBits( ULONG ulID )
{
	if ( ulID >= DEF_ADJUSTVALUE_MAX )
	{
		return ( 0 ) ;
	}

	return ( ubAdjustValueTempDataForSW[ulID] ) ;
}

#ifdef DEF_ENABLE_MULTI_SELECT
void vAdjustGameSel_Initial( void )
{
    if( (ulAdjustGameSel < 1) || (ulAdjustGameSel > DEF_ADJUSTGAMESEL_MAX) )
    {
        ulAdjustGameSel = 1 ;
    }
    vAdjustGameSel_Setup() ; 
}

void vAdjustGameSel_Setup( void )       { ulAdjustTempGameSel = ulAdjustGameSel ; }
void vAdjustGameSel_Inc( void )       
{
    ulAdjustTempGameSel ++ ;
    if( ulAdjustTempGameSel > DEF_ADJUSTGAMESEL_MAX )
    {
        ulAdjustTempGameSel = DEF_ADJUSTGAMESEL_MAX ;
    }       
}
void vAdjustGameSel_IncLoop( void )
{
    ulAdjustTempGameSel ++ ;
    if( ulAdjustTempGameSel > DEF_ADJUSTGAMESEL_MAX )
    {
        ulAdjustTempGameSel = 1 ;
    }       
} 
void vAdjustGameSel_Dec( void )
{
    if( ulAdjustTempGameSel > 1 )
    {
        ulAdjustTempGameSel -- ;
    }       
}
void vAdjustGameSel_DecLoop( void )
{
    if( ulAdjustTempGameSel > 1 )
    {
        ulAdjustTempGameSel -- ;
    }
    else
    {
        ulAdjustTempGameSel = DEF_ADJUSTGAMESEL_MAX ;
    }       

}
void vAdjustGameSel_UpDate( void )      { ulAdjustGameSel = ulAdjustTempGameSel ; }

ULONG ulAdjustGameSel_Read( void )      { return (ulAdjustGameSel) ; }
ULONG ulAdjustGameSel_ReadTemp( void )  { return (ulAdjustTempGameSel) ; }
#endif

#ifdef __NO_UART__
#else

#define DEF_ADJUSTSLAVEIDSEL_MIN		1 
#define DEF_ADJUSTSLAVEIDSEL_MAX		20

void vAdjustSlaveIDSel_Initial( void )
{
    if( ulAdjustSlaveIDSel > DEF_ADJUSTSLAVEIDSEL_MAX )
    {
        ulAdjustSlaveIDSel = DEF_ADJUSTSLAVEIDSEL_MIN ;
    }
    vAdjustSlaveIDSel_Setup() ; 
}

void vAdjustSlaveIDSel_Setup( void )       { ulAdjustTempSlaveIDSel = ulAdjustSlaveIDSel ; }
void vAdjustSlaveIDSel_Inc( void )       
{
    if( ulAdjustTempSlaveIDSel < DEF_ADJUSTSLAVEIDSEL_MAX )
    {
        ulAdjustTempSlaveIDSel ++ ;
    }       
}
void vAdjustSlaveIDSel_IncLoop( void )
{
    if( ulAdjustTempSlaveIDSel < DEF_ADJUSTSLAVEIDSEL_MAX )
    {
        ulAdjustTempSlaveIDSel ++ ;
    }       
    else
    {
    	ulAdjustTempSlaveIDSel = DEF_ADJUSTSLAVEIDSEL_MIN ;
    }
} 
void vAdjustSlaveIDSel_Dec( void )
{
    if( ulAdjustTempSlaveIDSel > DEF_ADJUSTSLAVEIDSEL_MIN )
    {
        ulAdjustTempSlaveIDSel -- ;
    }       
}
void vAdjustSlaveIDSel_DecLoop( void )
{
    if( ulAdjustTempSlaveIDSel > DEF_ADJUSTSLAVEIDSEL_MIN )
    {
        ulAdjustTempSlaveIDSel -- ;
    }       
    else
    {
        ulAdjustTempSlaveIDSel = DEF_ADJUSTSLAVEIDSEL_MAX ;
    }       

}
void vAdjustSlaveIDSel_UpDate( void )      { ulAdjustSlaveIDSel = ulAdjustTempSlaveIDSel ; }

ULONG ulAdjustSlaveIDSel_Read( void )      { return (ulAdjustSlaveIDSel) ; }
ULONG ulAdjustSlaveIDSel_ReadTemp( void )  { return (ulAdjustTempSlaveIDSel) ; }
#endif
