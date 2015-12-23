#define DEF_SCROLL_C
#include "common.h"
#define FILE_NAME "SCROLL.C"

void vScroll_Reset( void )
{
	SLONG slLoop,slLoop1 ;
	for ( slLoop1 = 0 ; slLoop1 < 10 ; slLoop1 ++ )
	{
		for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
		{
			vReel_Initial( slLoop , (UBYTE *)&ubScrollSymbolData[0] ) ;		
			vReel_SaveData( slLoop ) ;
			//vReel_SetRandData( slLoop ) ;
			//vReel_StopDataToShowData( slLoop ) ;
		}
		if(slGameCheck_IsSpecial(DEF_SYMBOL_WILD))
		{			
			continue ;	
		}	
		if(slGameCheck_IsSpecial(DEF_SYMBOL_FEVER))
		{
			continue ;	
		}	
		if(slGameCheck_IsSpecial(DEF_SYMBOL_FREE))
		{
			continue ;	
		}
		break ;
		
	}
	
	
}


void vScroll_FeverReset( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		vReel_FeverInitial( slLoop , (UBYTE *)&ubScrollSymbolDataCS[slLoop][0] ) ;
		vReel_FeverSaveData( slLoop ) ;
		//vReel_SetRandData( slLoop ) ;
		//vReel_StopDataToShowData( slLoop ) ;
	}
}

void vScroll_ReSetInfo( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_ReSetReelData( slLoop , (UBYTE *)&ubScrollSymbolData[0] ) ;
	}
}

void vScroll_RefreshShowScr( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_RefreshShowScr( slLoop ) ;
	}
}

void vScroll_FeverRefreshShowScr( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		vReel_FeverRefreshShowScr( slLoop ) ;
	}
}






void vScroll_InitState( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_InitState( slLoop ) ;
	}
}

void vScroll_SaveData( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_SaveData( slLoop ) ;
	}
}

void vScroll_LoadData( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_LoadData( slLoop ) ;
	}
}

void vScroll_SaveStopData( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_SaveStopData( slLoop ) ;
	}
}

void vScroll_LoadStopData( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_LoadStopData( slLoop ) ;
	}
}

void vScroll_FeverStartAllRun( void )
{
	SLONG slLoop ;

	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		vReel_FeverStartRun( slLoop ) ;
	}
}

void vScroll_FeverLoadData( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		vReel_FeverLoadData( slLoop ) ;
	}
}


void vScroll_StartRun( ULONG ulReel )
{
	if ( ulReel>= DEF_REEL_MAX )
	{
		return ;
	}
	vReel_StartRun( ulReel ) ;
}

void vScroll_StartAllRun( void )
{
	SLONG slLoop ;

	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_StartRun( slLoop ) ;
	}
}

void vScroll_SetStopData( ULONG ulReel , UBYTE ubData )
{
	if ( ulReel >= DEF_REEL_MAX )
	{
		return ;
	}
	vReel_SetStopData( ulReel , ubData ) ;
}

void vScroll_SetRandData( ULONG ulReel )
{
	if ( ulReel >= DEF_REEL_MAX )
	{
		return ;
	}
	vReel_SetRandData( ulReel ) ;
}




void vScroll_StopRun( ULONG ulReel )
{
	if ( ulReel >= DEF_REEL_MAX )
	{
		return ;
	}
	vReel_StopRun( ulReel ) ;
}


ULONG ulScroll_CheckOneRow( ULONG ulRow )
{
	SLONG slLoop ;
	if ( ulRow >= 5 )
	{
		return 0 ;
	}
	for ( slLoop = 0 ; slLoop < 3 ; slLoop ++ )
	{
		if (( stcReelData[slLoop*5+ulRow].ubState == DEF_REEL_JUMP)&&(stcReelData[slLoop*5+ulRow].swCount<=1))
		{
			
		}	
		else
		{
			return ( 1 ) ;	
		}		
	}
	return ( 0 ) ;
}

void vScroll_StopOneRow( ULONG ulRow )
{
	SLONG slLoop ;
	
	if ( ulRow >= 5 )
	{
		return ;
	}
	for ( slLoop = 0 ; slLoop < 3 ; slLoop ++ )
	{
		vReel_AsnStopRun( slLoop*5+ulRow ) ;
	}
}

void vScroll_AllStop( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_AsnStopRun( slLoop ) ;
	}
}


void vScroll_FeverAllStop( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		vReel_FeverStopRun( slLoop ) ;
	}
}

void vScroll_StopToShowData( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		vReel_StopDataToShowData( slLoop ) ;
	}
}

UBYTE ubScroll_GetData( ULONG ulReel )
{
	if ( ulReel >= DEF_REEL_MAX )
	{
		return ( 0 ) ;
	}
	return ( ubReel_GetData( ulReel ) ) ;
}

ULONG ulScroll_CheckIsRun( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		if ( ulReel_CheckIsRun( slLoop ) )
		{
			return ( 1 ) ;
		}
	}
	return ( 0 ) ;
}

ULONG ulScroll_FeverCheckIsRun( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		if ( ulReel_FeverCheckIsRun( slLoop ) )
		{
			return ( 1 ) ;
		}
	}
	return ( 0 ) ;
}



//ULONG ulScrollSpeedFlag ;

void vScroll_Process( void )
{
	SLONG slLoop ;
/*
	ulScrollSpeedFlag ++ ;
	if ( ulScrollSpeedFlag < 3 )
    {
        //ulScrollSpeedFlag = 0 ;
        return ;
    }
    else
    {
        ulScrollSpeedFlag = 0 ;
    }
*/
	for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
	{
		vReel_Process( slLoop , slLoop*3) ;
	}
}


void vScroll_FeverProcess( void )
{
	SLONG slLoop ;
/*
	ulScrollSpeedFlag ++ ;
	if ( ulScrollSpeedFlag < 3 )
    {
        //ulScrollSpeedFlag = 0 ;
        return ;
    }
    else
    {
        ulScrollSpeedFlag = 0 ;
    }
*/
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		vReel_FeverProcess( slLoop , slLoop*3) ;
	}
}

