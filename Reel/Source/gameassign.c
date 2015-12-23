#define DEF_GAMEASSIGN_C
#include "common.h"
#define FILE_NAME "GAMEASSIGN.C"

// 设定互换位置
void vGameAssign_LocSwap( UBYTE *ubLoc,ULONG ulCount )
{
	SLONG slLoop , slSwapIndex ;
	UBYTE ubSwapData ;

    // 设定正常位置 0 1 2 3 4 
	for ( slLoop = 0 ; slLoop < ulCount ; slLoop ++ )
	{
		ubLoc[slLoop] = slLoop ;
	}
	
	// 搅乱位置 
	for ( slLoop = 0 ; slLoop < ulCount ; slLoop ++ )
	{
		slSwapIndex = ulRand_ReadMod(ulCount) ;
		mMacro_Swap( ubLoc[slLoop] , ubLoc[slSwapIndex] , ubSwapData ) ;
	}	
}

// Assign All Same 奖项
void vGameAssign_AllSame( UBYTE ubSymID )
{
    SLONG slLoop ;
    
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
        vScroll_SetStopData( slLoop , ubSymID ) ;
    }
}

// Assign 5 连线
void vGameAssign_5Line( UBYTE ubSymID )
{
    UBYTE ubAllSymID[3][5] ;
    SLONG slLine , slX , slY ;
    SLONG slLoop , slLoop1 , slTimes ;
    ULONG ulValue; 
    for( slTimes = 0 ; slTimes < 10 ; slTimes++ )
    {
        for ( slLoop = 0 ; slLoop < 3 ; slLoop ++ )
        {
            for ( slLoop1 = 0 ; slLoop1 < 5 ; slLoop1 ++ )
            {
                ubAllSymID[slLoop][slLoop1] = 0xFF ;
            }
        }    
        #ifdef DEF_FIX_CHANCE_20150212
        slLine = ulRand_ReadMod(9) ;  //wcm 150212 随机的（9选1）        
        #else
        slLine = ulRand_ReadMod(slSlave_ReadLine()) ;  //防止强制时没押到线
        #endif
        for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
        {
            slY = ubGameCheckLineLocInformation[slLine][slLoop] / 5 ;
            slX = ubGameCheckLineLocInformation[slLine][slLoop] % 5 ;
            ubAllSymID[slY][slX] = ubSymID ;
        }
        for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
        {
            slY = slLoop / 5 ;
            slX = slLoop % 5 ;
            ulValue = ulRand_ReadMod(32768);
            if ( ubAllSymID[slY][slX] != 0xFF )
            {            	
            	if(ulValue<6553)
            	{
            		vScroll_SetStopData( slLoop ,  DEF_SYMBOL_WILD ) ;	
            	}	
            	else
            	{
            		vScroll_SetStopData( slLoop , ubAllSymID[slY][slX] ) ;	
            	}	                
            }
            else
            {
            	if(ulValue<3276)
            	{
            		vScroll_SetStopData( slLoop , DEF_SYMBOL_WILD ) ;	
            	}
            	else if(ulValue<3276+6553)
            	{
            		vScroll_SetStopData( slLoop , ubAllSymID[slY][slX] ) ;	
            	}
            	else
            	{
            		vScroll_SetRandData( slLoop ) ;	
            	}	
            	
                
            }
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



// Assign Spec5 连线
void vGameAssign_Spec5Line(UBYTE ubSymID,ULONG ulLoc )
{
	SLONG slLoop,slOdds,slValue;
	vGameAssign_5Line(ubSymID);	
	#ifdef DEF_FIX_CHANCE_20150212
	vGameCheck_CheckAllLineOdds( (GAMEINFO*)&stcGameInfo ) ;
	#else
	vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
	#endif
	vScroll_SaveStopData( );
	#ifdef DEF_FIX_CHANCE_20150212
	slOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo )* mGame_ReadMaxBet();
	#else
	slOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
	#endif
	for ( slLoop = 0 ; slLoop < 9 ; slLoop ++ ) //取十次，取「最接近、又不超過觸?值」的一局給?
	{
		vGameAssign_5Line(ubSymID);	
		#ifdef DEF_FIX_CHANCE_20150212
		vGameCheck_CheckAllLineOdds( (GAMEINFO*)&stcGameInfo ) ;
		#else
		vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
		#endif
		slValue = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo )*mGame_ReadMaxBet();	
		if(slValue<stcChance.slVirtualBufTopValue[ulLoc])
		{
			if(slValue>slOdds)	
			{
				slOdds = slValue;	
				vScroll_SaveStopData( );			
			}	
		}	
	}
	vScroll_LoadStopData( );  
	
}


#define DEF_GameAssign_Natural_case_1
//Assign 自然
void vGameAssign_Natural( void )
{	
	SLONG slLoop ;
	#ifdef DEF_GameAssign_Natural_case_1
	{
		while(1)//for ( slLoop1 = 0 ; slLoop1 < 10 ; slLoop1 ++ )
		{
			for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
			{
				vReel_SetRandData( slLoop ) ;			
				
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
	#endif
	
	#ifdef DEF_GameAssign_Natural_case_2
	{
		SLONG slBonus , slFever , slFree ;
		UBYTE ubSym ;
		
		slBonus = 0 ; slFever = 0 ; slFree = 0 ;
		for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
		{
			while(1)
			{
				vReel_SetRandData( slLoop ) ;
						
				ubSym = ubReel_GetData( slLoop ) ;
				
				if(( ubSym == DEF_SYMBOL_10 )&&( slBonus >= 2 )) continue ;
				if(( ubSym == DEF_SYMBOL_11 )&&( slFever >= 2 )) continue ;
				if(( ubSym == DEF_SYMBOL_12 )&&( slFree  >= 2 )) continue ;
					
				break ;	
			}			
			if( ubSym == DEF_SYMBOL_10 ) slBonus ++ ;
			if( ubSym == DEF_SYMBOL_11 ) slFever ++ ;
			if( ubSym == DEF_SYMBOL_12 ) slFree ++ ;
		}
		
		for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
		{
			slLoop1 = ulRand_ReadMod(DEF_REEL_MAX) ;
			if( slLoop1 == slLoop ) continue ;
				
			vReel_LocSwap( slLoop , slLoop1 ) ;		
		}
	}
	#endif
	
}

// Assign  连线
void vGameAssign_Line(UBYTE ubSymID,UBYTE ubLoc )
{
    UBYTE ubAllSymID[3][5] ;
    SLONG slLine , slX , slY ;
    SLONG slLoop , slLoop1 , slTimes ;
    if( (ubLoc>=3)&&(ubLoc<=5))
    {
    	
    	//return ;	
    }	
    
    for( slTimes = 0 ; slTimes < 10 ; slTimes++ )
    {
        for ( slLoop = 0 ; slLoop < 3 ; slLoop ++ )
        {
            for ( slLoop1 = 0 ; slLoop1 < 5 ; slLoop1 ++ )
            {
                ubAllSymID[slLoop][slLoop1] = 0xFF ;
            }
        }
        
        slLine = ulRand_ReadMod(slSlave_ReadLine()) ;
        for ( slLoop = 0 ; slLoop < ubLoc ; slLoop ++ )
        {
            slY = ubGameCheckLineLocInformation[slLine][slLoop] / 5 ;
            slX = ubGameCheckLineLocInformation[slLine][slLoop] % 5 ;
            ubAllSymID[slY][slX] = ubSymID ;
        }
        for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
        {
            slY = slLoop / 5 ;
            slX = slLoop % 5 ;
            if ( ubAllSymID[slY][slX] != 0xFF )
            {
                vScroll_SetStopData( slLoop , ubAllSymID[slY][slX] ) ;
            }
            else
            {
                vScroll_SetRandData( slLoop ) ;
            }
        }

       // if( !slGameCheck_IsSpecial(DEF_SYMBOL_WILD) )    break ;
    }
}








// Assign Special Symbol
void vGameAssign_SpecialSymbol( UBYTE ubSymID,UBYTE ubLoc )
{
    UBYTE ubAllSymID[3][5] ;
    SLONG slLoc , slX , slY ;
    SLONG slLoop , slLoop1 , slTimes ;
    if((ubLoc==0)||(ubLoc>15))
    {
    	return;	
    }	    
    for( slTimes = 0 ; slTimes < 10 ; slTimes++ )
    {
        for ( slLoop = 0 ; slLoop < 3 ; slLoop ++ )
        {
            for ( slLoop1 = 0 ; slLoop1 < 5 ; slLoop1 ++ )
            {
                ubAllSymID[slLoop][slLoop1] = 0xFF ;
            }
        }        
        for ( slLoop = 0 ; slLoop < ubLoc ; slLoop ++ )
        {
            slLoc = ulRand_ReadMod(15) ;        	
            slY = slLoc / 5 ;
            slX = slLoc % 5 ;
            if ( ubAllSymID[slY][slX] == 0xFF )
            {
                ubAllSymID[slY][slX] = ubSymID ;
            }
        }
        for ( slLoop1 = 0 ; slLoop1 < 10 ; slLoop1 ++ )
        {
            for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
            {
                slY = slLoop / 5 ;
                slX = slLoop % 5 ;
                if ( ubAllSymID[slY][slX] != 0xFF )
                {
                    vScroll_SetStopData( slLoop , ubAllSymID[slY][slX] ) ;
                }
                else
                {
                    vScroll_SetRandData( slLoop ) ;
                }
            }
            if ( slGameCheck_IsSpecial(ubSymID) == ubLoc )
            {            	
            	if(ubSymID==DEF_SYMBOL_WILD)
		        {
		        	if(slGameCheck_IsSpecial(DEF_SYMBOL_FEVER)==0)
		        	{
		        		if(slGameCheck_IsSpecial(DEF_SYMBOL_FREE)==0)
		        		{
		        			 return;	
		        		}			
		        	}	
		        }	
		        if(ubSymID==DEF_SYMBOL_FEVER)
		        {
		        	if(slGameCheck_IsSpecial(DEF_SYMBOL_WILD)==0)
		        	{
		        		if(slGameCheck_IsSpecial(DEF_SYMBOL_FREE)==0)
		        		{
		        			 return;	
		        		}			
		        	}	
		        }
		        if(ubSymID==DEF_SYMBOL_FREE)
		        {
		        	if(slGameCheck_IsSpecial(DEF_SYMBOL_WILD)==0)
		        	{
		        		if(slGameCheck_IsSpecial(DEF_SYMBOL_FEVER)==0)
		        		{
		        			return;		
		        		}			
		        	}	
		        }            	
               
            }
        }

        
    }
	
}

// Assign 5次最小倍率 Special Symbol
void vGameAssign_MinSpecialSymbol( UBYTE ubSymID,UBYTE ubLoc )
{
	SLONG slLoop;
	ULONG ulOdds,ulValue;
	vGameAssign_SpecialSymbol(ubSymID,ubLoc);	
	vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
	vScroll_SaveStopData( );
	ulOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
	for ( slLoop = 0 ; slLoop < 4 ; slLoop ++ ) //取5次，取最小給?
	{
		vGameAssign_SpecialSymbol(ubSymID,ubLoc);	
		vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
		ulValue = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
		if(ulValue<ulOdds)	
		{
			ulOdds = ulValue;	
			vScroll_SaveStopData( );			
		}		
	}
	vScroll_LoadStopData( );  	
	
}

// Assign  FEVER Symbol
void vGameAssign_FeverSymbol(UBYTE ubSymID)
{
    SLONG slLoop ;
    if((ubSymID>=DEF_SYMBOL_01)&&(ubSymID<=DEF_SYMBOL_06))
    {
    	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
    	{
    		vReel_FeverSetStopData( slLoop ,ubSymID) ;	
    	}	
    	
    }	
}


// Assign  FEVER Null
void vGameAssign_FeverNull(void)
{
    SLONG slLoop,slLoop1 ;
    ULONG ulValue;
	for ( slLoop1 = 0 ; slLoop1 < 100 ; slLoop1 ++ )
	{
    	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
    	{
    		vReel_FeverSetRandData( slLoop ) ;	
    	}	
    	ulValue = slGameCheck_FeverValue();
    	if(ulValue==7)
    	{
    		break ;	
    	}	
    }	
} 