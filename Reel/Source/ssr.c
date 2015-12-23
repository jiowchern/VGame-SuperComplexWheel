#define DEF_SSR_C
#include "../../h/common.h"
#define FILE_NAME "SSR.C"

ULONG ulSSRONFlag[DEF_SSR_MAX] ;

void vSSR_Initial( void )
{
	vSSR_AllOff( ) ;
}

void vSSR_On( ULONG ulSSRID )
{
	if ( ulSSRID >= DEF_SSR_MAX )
	{
		return ;
	}
	if ( stcSSROutputInformation[ulSSRID].ubDrive != IO_EMPTY )
	{
		vIO_Write( stcSSROutputInformation[ulSSRID].ubDrive , stcSSROutputInformation[ulSSRID].ubPort , stcSSROutputInformation[ulSSRID].ubBit , stcSSROutputInformation[ulSSRID].ubBit ) ;
		ulSSRONFlag[ulSSRID] = 1 ;
	}
}

void vSSR_Off( ULONG ulSSRID )
{
	if ( ulSSRID >= DEF_SSR_MAX )
	{
		return ;
	}
	if ( stcSSROutputInformation[ulSSRID].ubDrive != IO_EMPTY )
	{
		vIO_Write( stcSSROutputInformation[ulSSRID].ubDrive , stcSSROutputInformation[ulSSRID].ubPort , stcSSROutputInformation[ulSSRID].ubBit , 0 ) ;
		ulSSRONFlag[ulSSRID] = 0 ;
	}
}

void vSSR_AllOff( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_SSR_MAX ; slLoop ++ )
	{
		vSSR_Off( slLoop ) ;
	}
}

ULONG ulSSR_IsON(ULONG ulID)
{
	if ( ulID >= DEF_SSR_MAX )
	{
		return 0 ;
	}
	
	return ulSSRONFlag[ulID] ;
}
