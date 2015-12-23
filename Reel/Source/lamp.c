#define DEF_LAMP_C
#include "../../h/common.h"
#define FILE_NAME "LAMP.C"

void vLamp_Initial( void )
{
	vLamp_AllOff() ;
}

void vLamp_On( ULONG ulLamp )
{	
	if ( ulLamp >= DEF_LAMP_MAX )
	{
		return ;
	}
	if ( stcLampOutputInformation[ulLamp].ubDrive != IO_EMPTY )
	{
		vIO_Write( stcLampOutputInformation[ulLamp].ubDrive , stcLampOutputInformation[ulLamp].ubPort , stcLampOutputInformation[ulLamp].ubBit , stcLampOutputInformation[ulLamp].ubBit ) ;
	}
}

void vLamp_Off( ULONG ulLamp )
{
	if ( ulLamp >= DEF_LAMP_MAX )
	{
		return ;
	}
	if ( stcLampOutputInformation[ulLamp].ubDrive != IO_EMPTY )
	{
		vIO_Write( stcLampOutputInformation[ulLamp].ubDrive , stcLampOutputInformation[ulLamp].ubPort , stcLampOutputInformation[ulLamp].ubBit , 0 ) ;	
	}
}

void vLamp_AllOn( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_LAMP_MAX ; slLoop ++ )
	{
		vLamp_On( slLoop ) ;
	}
}

void vLamp_AllOff( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_LAMP_MAX ; slLoop ++ )
	{
		vLamp_Off( slLoop ) ;
	}
}

