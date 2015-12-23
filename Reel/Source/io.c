#define DEF_IO_C
#include "../../h/common.h"
#define FILE_NAME "IO.C"

void (* const ubIO_ChipInitial[IO_DEVICE_MAX])(void) =  {
	0                  ,
	vIOCPU_Initial     ,
	vIOMap_Initial     ,
	vPCInput_Initial   ,
	vIOCMDBUF_Initial  ,
	vIOKeyBuf_Initial  ,
	0                  ,
	0                  ,
};

UBYTE (* const ubIO_ReadSaveData[IO_DEVICE_MAX])(UBYTE) =  {
	0                        ,
	ubIOCPU_ReadSaveData     ,
	ubIOMap_ReadSaveData     ,
	ubPCInput_ReadSaveData   ,
	ubIOCMDBUF_ReadData    	 ,
	vIOKeyBuf_ReadData       ,
	0                        ,
	0                        ,
};

UBYTE (* const ubIO_ReadData[IO_DEVICE_MAX])(UBYTE) =  {
	0                        ,
	ubIOCPU_ReadData         ,
	ubIOMap_ReadData         ,
	ubPCInput_ReadData       ,
	ubIOCMDBUF_ReadData      ,
	vIOKeyBuf_ReadData       ,
	0                        ,
	0                        ,
};

void (* const vIO_WriteData[IO_DEVICE_MAX])(UBYTE,UBYTE) =  {
	0                        ,
	vIOCPU_WriteData         ,
	vIOMap_WriteData         ,
	vPCInput_WriteData       ,
	vIOCMDBUF_WriteData      ,
	vIOKeyBuf_WriteData      ,
	0                        ,
	0                        ,
};

void vIO_Reset( void )
{
	vMeter_Reset( ) ;
}

void vIO_Initial( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < IO_DEVICE_MAX ; slLoop ++ )
	{
		if ( ubIO_ChipInitial[slLoop] )
		{
			(*ubIO_ChipInitial[slLoop])() ;
		}
	}
	
	vKey_Initial( ) ;
	vDipSw_Initial( ) ;
	vMeter_Initial( ) ;
	vSSR_Initial( ) ;
	vLamp_Initial( ) ;
}

void vIO_Write( UBYTE ubDevice , UBYTE ubPort , UBYTE ubBit  , UBYTE ubInputData )
{
    UBYTE ubData , ubTempData ;

    if ( ubDevice >= IO_DEVICE_MAX )
    {
        //ASSERT1(0)
    }
    else
    {
    	if ( vIO_WriteData[ubDevice] )
    	{
        	ubData = ubInputData & ubBit ;
        	ubTempData = (*ubIO_ReadSaveData[ubDevice])(ubPort) & ~ubBit ;
        	ubData |= ubTempData ;

   			(*vIO_WriteData[ubDevice])(ubPort , ubData) ;
   		}
    }
}


UBYTE ubIO_Read( UBYTE ubDevice , UBYTE ubPort , UBYTE ubBit )
{
    UBYTE ubData ;

    ubData = 0x00 ;

    if ( ubDevice >= IO_DEVICE_MAX )
    {
        //ASSERT1(0)
    }
    else
    {
    	if ( ubIO_ReadData[ubDevice] )
    	{
   			ubData = (~(*ubIO_ReadData[ubDevice])(ubPort)) & ubBit ;
   		}
    }

    return ( ubData ) ;
}

