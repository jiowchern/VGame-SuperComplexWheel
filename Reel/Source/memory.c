#define DEF_MEMORY_C
#include "common.h"
#define FILE_NAME "MEMORY.C"

void vMemory_Set( UBYTE *ubD , UBYTE ubValue , ULONG ulSize )
{
	SLONG slLoop ;
	
	if ( ulSize >= 0x4000 )
	{
		return ;
	}
	for ( slLoop = 0 ; slLoop < ulSize ; slLoop ++ )
	{
		ubD[slLoop] = ubValue ;
	}
}

void vMemory_Copy( UBYTE *ubD , UBYTE *ubS , ULONG ulSize )
{
	SLONG slLoop ;

	if ( ulSize >= 1024 )
	{
		return ;
	}
	for ( slLoop = 0 ; slLoop < ulSize ; slLoop ++ )
	{
		ubD[slLoop] = ubS[slLoop] ;
	}
}

ULONG ulMemory_CompSame( UBYTE *ubD , UBYTE *ubS , ULONG ulSize )
{
	SLONG slLoop ;

	if ( ulSize >= 1024 )
	{
		return ( 0 );
	}
	for ( slLoop = 0 ; slLoop < ulSize ; slLoop ++ )
	{
		if ( ubD[slLoop] != ubS[slLoop] )
		{
			return ( 0 ) ;
		}
	}
	return ( 1 ) ;
}
