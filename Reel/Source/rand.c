#define DEF_RAND_C
#include "common.h"
#define FILE_NAME "RAND.C"
#include "credit.h"
#ifndef __ARM__
	#include	"stdio.h"
	#include	"stdlib.h"
	#include 	"time.h"
#endif

ULONG const ulRandSeedTableA[] = {
	1021L, 9301L, 3613L, 4561L, 8121L,36261L,84589L, 17221L, 7141L, 3877L 
} ;

ULONG const ulRandSeedTableB[] = {
	41L  ,49297L,45289L,51349L,28411L,66037L,45989L,107839L,54773L,29573L 
} ;

UBYTE l_ubVersionMemString[32] ;
ULONG l_ulVersionValue ;

ULONG ulRandSeed[10] ;
ULONG ulRandSelect ;
ULONG ulRandIndex ;

ULONG ulCreditValue_2[ DEF_CREDIT_USER_MAX ] ;

void vRand_Reset( void )
{
	#ifndef __ARM__
		SLONG slLoop ;
		
		srand( time(NULL) ) ;
		for ( slLoop = 0 ; slLoop < 10 ; slLoop ++ )
		{
			ulRandSeed[slLoop] = rand() ;
		}
	#endif

	ulRandIndex = 0 ;
}
    
void vRand_Initial( void )
{
	ulRandIndex = 0 ;
}

ULONG ulRand_ReadTemp( void )
{
	ulRandSelect ++ ;
	if ( ulRandSelect >= 10 )
	{
		ulRandSelect = 0 ;
	}
	
	ulRandIndex ++ ;
	if ( ulRandIndex >= 2 )
	{
		ulRandSeed[ulRandSelect] = ulRandSeed[ulRandIndex] * ulRandSeedTableA[ulRandIndex] + ulRandSeedTableB[ulRandIndex] ;

		ulRandIndex = 0 ;
	}

	ulRandSeed[ulRandSelect] = ulRandSeed[ulRandSelect] * ulRandSeedTableA[ulRandSelect] + ulRandSeedTableB[ulRandSelect] ;
	
 	return ( ulRandSeed[ulRandSelect] ) ;
}

ULONG ulRand_ReadMod( ULONG mod )	// 0 ~ mod-1
{
	ULONG	ulTemp , ulMax ;
	
	ulTemp = ulRand_ReadTemp( ) ; 
	
	if( mod == 0 )
	{
		ulTemp = (( ulTemp & 0x7 ) << 29 ) + ( ulTemp >> 3 ) ;
		
		return ulTemp ;
	}
	else if( mod == 1 )
	{
		return 0 ;
	}	
	else if( mod > 0x10000000 )
	{	// ULONG size
		ulMax = mod ;
		while( 1 )
		{
			ulTemp = (( ulTemp & 0x7 ) << 29 ) + ( ulTemp >> 3 ) ;
			if( ulTemp < ulMax ) break ;
				
			ulTemp = ulRand_ReadTemp( ) ; 
		}
	}	
	else if( mod > 0x10000 )
	{	// ULONG size
		ulMax = 0x10000000 / mod ;
		ulMax = ulMax * mod ;
		while( 1 )
		{
			ulTemp = ( (( ulTemp & 0x7 ) << 29 ) + ( ulTemp >> 3 ) ) & 0xFFFFFFF ;
			if( ulTemp < ulMax ) break ;
				
			ulTemp = ulRand_ReadTemp( ) ; 
		}
	}
	else if( mod > 0x100 )
	{	// UWORD size
		ulMax = 0x10000 / mod ;
		ulMax = ulMax * mod ;
		while( 1 )
		{
			ulTemp = (( ulTemp >> 8 ) & 0xFFFF ) ;
			if( ulTemp < ulMax ) break ;
				
			ulTemp = ulRand_ReadTemp( ) ; 
		}
	}
	else
	{	// UBYTE size
		ulMax = 0x100 / mod ;
		ulMax = ulMax * mod ;
		while( 1 )
		{
			ulTemp = (( ulTemp >> 16 ) & 0xFF ) ;
			if( ulTemp < ulMax ) break ;
				
			ulTemp = ulRand_ReadTemp( ) ; 
		}
	}
	
	return ( ulTemp % mod ) ;
}

void vRand_ChgSeed( void )
{
    ULONG ulSeedIdx , ulRandMax , ulRandCnt ;
    for( ulSeedIdx = 0 ; ulSeedIdx < 9 ; ulSeedIdx++ )
    {
        ulRandMax = ulRand_ReadMod( 7 ) ;
        for( ulRandCnt = 0 ; ulRandCnt < ulRandMax ; ulRandCnt++ )
        { 
            ulRandSeed[ ulSeedIdx ] = ulRand_ReadMod( 0 ) ; 
        }
    }
    ulRandSelect = ulRand_ReadMod( 9 ) ;  
}
