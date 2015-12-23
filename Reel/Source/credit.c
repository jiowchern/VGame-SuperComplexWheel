#define DEF_CREDIT_C
#include "common.h"
#include "credit.h"
#define FILE_NAME "CREDIT.C"

// ================================================= //
// 內部變數區
// ================================================= //
UBYTE D_ubVersionMemString[32] ;
ULONG D_ulVersionValue ;

ULONG ulCreditValue_0[ DEF_CREDIT_USER_MAX ] ;
ULONG ulCreditValue_backup[ DEF_CREDIT_USER_MAX ] ;
ULONG ulCreditRefresh ;

extern ULONG ulCreditValue_1[ DEF_CREDIT_USER_MAX ] ;
extern ULONG ulCreditValue_2[ DEF_CREDIT_USER_MAX ] ;

// ================================================= //
// 外部函式區
// ================================================= //
void vCredit_Reset( void )
{
    ULONG ulPlrID ;

    for( ulPlrID = 0 ; ulPlrID < DEF_CREDIT_USER_MAX ; ulPlrID++ )
    {
    	ulCreditValue_backup[ ulPlrID ] = ulCreditValue_0[ ulPlrID ] ;
    	
       	ulCreditValue_0[ ulPlrID ] = 0 ;
       	ulCreditValue_1[ ulPlrID ] = 0 ;
       	ulCreditValue_2[ ulPlrID ] = 0 ;
    }
}

void vCredit_Initial( void )
{
    ulCreditRefresh = 0xFFFFFFFF ;
}

ULONG ulCredit_Set( ULONG ulPlrID , ULONG ulSet )
{
    if( ulPlrID >= DEF_CREDIT_USER_MAX )     { return 0 ; }

    ulCreditValue_0[ ulPlrID ] = ulSet ;
    ulCreditValue_1[ ulPlrID ] = ulSet ;
    ulCreditValue_2[ ulPlrID ] = ulSet ;
    ulCreditRefresh |= (0x01 << ulPlrID) ;
    
    return ulCreditValue_0[ ulPlrID ] ;
}
ULONG ulCredit_Add( ULONG ulPlrID , ULONG ulAdd )
{
    if( ulPlrID >= DEF_CREDIT_USER_MAX )     { return 0 ; }

    ulCreditValue_0[ ulPlrID ] += ulAdd ;
    ulCreditValue_1[ ulPlrID ] += ulAdd ;
    ulCreditValue_2[ ulPlrID ] += ulAdd ;
    ulCreditRefresh |= (0x01 << ulPlrID) ;

    return ulCreditValue_0[ ulPlrID ] ;
}
ULONG ulCredit_Sub( ULONG ulPlrID , ULONG ulSub )
{
    if( ulPlrID >= DEF_CREDIT_USER_MAX )     { return 0 ; }

    if( ulCreditValue_0[ ulPlrID ] >= ulSub )
    {
        ulCreditValue_0[ ulPlrID ] -= ulSub ;
        ulCreditValue_1[ ulPlrID ] -= ulSub ;
        ulCreditValue_2[ ulPlrID ] -= ulSub ;
        ulCreditRefresh |= (0x01 << ulPlrID) ;
    }

    return ulCreditValue_0[ ulPlrID ] ;
}

ULONG ulCredit_Read( ULONG ulPlrID )
{
    if( ulPlrID >= DEF_CREDIT_USER_MAX )     { return ( 0 ) ; }

	if( ulCreditValue_0[ ulPlrID ] > 200000000L )
	{
		ulCreditValue_0[ ulPlrID ] = 0 ;
		ulCreditValue_1[ ulPlrID ] = 0 ;
		ulCreditValue_2[ ulPlrID ] = 0 ;
	}
	/*
	if(( ( ulCreditValue_0[ ulPlrID ]+5000 ) > ulCreditValue_1[ ulPlrID ] )||
		( ulCreditValue_0[ ulPlrID ] < ( ulCreditValue_1[ ulPlrID ]+5000 ) ))
	{
		if( ulCreditValue_1[ ulPlrID ] == ulCreditValue_2[ ulPlrID ] )
		{
			ulCreditValue_0[ ulPlrID ] = ulCreditValue_1[ ulPlrID ] ;
		}
	}
    */
    		
    return ulCreditValue_0[ ulPlrID ] ;
}

ULONG ulCredit_IsRefresh( ULONG ulPlrID )
{
    ULONG ulChkBit ;

    ulChkBit = (0x01 << ulPlrID) ;
    if( ulCreditRefresh & ulChkBit )
    {
        ulCreditRefresh ^= ulChkBit ;
        return ( 1 ) ;
    }
    return ( 0 ) ;
}
