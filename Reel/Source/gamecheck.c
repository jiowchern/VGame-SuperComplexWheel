#define DEF_GAMECHECK_C
#include "common.h"
#define FILE_NAME "GAMECHECK.C"


// 连线排列
UBYTE const ubGameCheckLineLocInformation[9][5] = 
{
	{  5 ,  6 ,  7 ,  8 ,  9 } ,
	{  0 ,  1 ,  2 ,  3 ,  4 } ,
	{ 10 , 11 , 12 , 13 , 14 } ,     
	{  0 ,  6 , 12 ,  8 ,  4 } ,
	{ 10 ,  6 ,  2 ,  8 , 14 } ,
	{  0 ,  1 ,  7 ,  3 ,  4 } , 
	{ 10 , 11 ,  7 , 13 , 14 } ,	
	{  5 , 11 , 12 , 13 ,  9 } ,
	{  5 ,  1 ,  2 ,  3 ,  9 } ,
} ;

// 连线奖
ULONG const ulGameCheckOddsTable[6][DEF_SYMBOL_MAX] = {
//   SYM00  SYM01  SYM02  SYM03  SYM04  SYM05  SYM06  SYM07  SYM08  SYM09  WILD   FEVER  FREE
	{   0 ,    0 ,   0 ,   0 ,    0 ,    0 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,    0 } ,// 0 Link
	{   0 ,    0 ,   0 ,   0 ,    0 ,    0 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,    0 } ,// 1 Link
	{   0 ,    0 ,   0 ,   0 ,    0 ,    0 ,    0 ,   0 ,    0 ,    0 ,    0 ,    0 ,    0 } ,// 2 Link
	{  50 ,   30 ,  20 ,  15 ,   10 ,    8 ,    5 ,   4 ,    3 ,    2 ,    0 ,    0 ,    0 } ,// 3 Link
	{ 200 ,  120 , 100 ,  50 ,   30 ,   20 ,   15 ,  10 ,    8 ,    5 ,    0 ,    0 ,    0 } ,// 4 Link
	{1500 , 1000 , 800 , 500 ,  200 ,  100 ,   80 ,  50 ,   40 ,   30 ,    0 ,    0 ,    0 } ,// 5 Link
} ;

// All Same 全盘奖
ULONG const ulGameCheckAllSameOddsTable[DEF_SYMBOL_MAX] = 
{
	3000 , 2000 , 1600 , 1000 , 400 , 200 , 160 ,  100 , 80 ,60 , 0 , 0 , 0
} ;

ULONG const ulGameCheckOtherOddsTable[6] = 
{// Build , ET , BNS(S) , BNS1(L) , BNS2(L) , BNS3(L) ,
	 0 ,  0 ,   0 , 200 , 300 , 500
} ;


/*
void vGameInfo_Last( void )
{
	SLONG slLine ;
	SLONG slReel ;
	
	vMemory_Set( (UBYTE *)&stcGameInfoLast , 0x00 , sizeof( GAMEINFOLAST ) ) ;
//	stcGameInfoLast.slCredit = slCredit_Read( ) ;
//	stcGameInfoLast.slBet    = slBet_Read() ;
//	stcGameInfoLast.slWin    = slWin_Read( ) ;
//
//	stcGameInfoLast.slLine   = slSlave_ReadLine() ;
//	stcGameInfoLast.slLineBet= slBet_ReadBet() ;

	for ( slLine = 0 ; slLine < 9 ; slLine ++ )
	{
        if ( stcGameInfo.stcLine[slLine].ubAct[0] || stcGameInfo.stcLine[slLine].ubAct[4] )
		{
			stcGameInfoLast.ubWinFlag[slLine] = 1 ;
		}
	}
	for ( slReel = 0 ; slReel < 15 ; slReel ++ )
	{
		stcGameInfoLast.ubReel[slReel] = ubReel_GetData( slReel ) ;
	}
	if ( stcGameInfo.ulAllSameOdds )
	{
		stcGameInfoLast.ubAllSame = 1 ;
	}
}
*/
// 获取线的 Symbol
// input :
//     ulLine -> 
// output :
//     ubPutData -> 
void vGameCheck_GetLineData( UBYTE *ubPutData , ULONG ulLine )
{
    SLONG slLoop ;
    
    if ( ulLine >= 9 )
    {
        return ;
    }
    for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
    {
        ubPutData[slLoop] = ubScroll_GetData( ubGameCheckLineLocInformation[ulLine][slLoop] ) ;
    }
}

// 由左至右检查奖项
// Input :
//     ubLineData 
// Output :
//     (return) 
//          15~8 Bits -> 个数
//          7~0  Bits -> Symbol ID
ULONG ulGameCheck_LeftType( UBYTE *ubLineData )
{
    SLONG slLoop ;
    UBYTE ubFstSym , ubCal ;
    UBYTE ubWildCal ;
    ULONG ulWildOdds , ulOdds ;
    
    ubFstSym   = ubLineData[0] ;
    ubCal      = 1 ;
    ubWildCal  = 0 ;
    ulWildOdds = 0 ;
    ulOdds     = 0 ;
    
    // 如果第一个 Symbol 是 Fever Symbol 表示无法连线
    if ( ubFstSym == DEF_SYMBOL_FEVER )
    {
        return ( 0 ) ;
    }
    // 如果第一个 Symbol 是 Free Symbol 表示无法连线
    if ( ubFstSym == DEF_SYMBOL_FREE )
    {
        return ( 0 ) ;
    }
    // 果第一个 Symbol 是 Wild Symbol
    if ( ubFstSym == DEF_SYMBOL_WILD )
    {
        //计算 Wild 连续个数
        ubWildCal = 1 ;
        for ( slLoop = 1 ; slLoop < 5 ; slLoop ++ )
        {
            if ( ubLineData[slLoop] == DEF_SYMBOL_WILD )
            {
                ubWildCal ++ ;
            }
            else
            {
                break ;
            }
        }
    }
    
    // 计算正常 Symbol 连续个数 , 包含 Wild
    for ( slLoop = 1 ; slLoop < 5 ; slLoop ++ )
    {
        //Symbol 是 Wild 直接计算
        if ( ubLineData[slLoop] == DEF_SYMBOL_WILD )
        {
            ubCal ++ ;
            continue ;
        }
        
        // 如果第一个 Symbol 是 Wild , 则将新的 Symbol 取代 FstSym
        if ( ubFstSym == DEF_SYMBOL_WILD )
        {
            ubFstSym = ubLineData[slLoop] ;
            ubCal ++ ;
        }
        else
        {
            if ( ubFstSym == ubLineData[slLoop] )
            {
                ubCal ++ ;
            }
            else
            {
                break ;
            }
        }
    }
    
    // 获取正常连线奖
    ulOdds = ulGameCheckOddsTable[ubCal][ubFstSym] ;
    
    // 如果有 Wild 连线
    if ( ubWildCal )
    {
        // 获取 Wild 连线奖
        ulWildOdds = ulGameCheckOddsTable[ubWildCal][DEF_SYMBOL_WILD] ;
        
        // 比较哪个倍数比较大
        if ( ulWildOdds > ulOdds )
        {
            return ( (((ULONG)ubWildCal) << 8) | ((ULONG)DEF_SYMBOL_WILD) ) ;
        }
    }
    return ( (((ULONG)ubCal) << 8) | ((ULONG)ubFstSym) ) ;  
}

// 由右至左检查奖项
// Input :
//     ubLineData 
// Output :
//     (return) 
//          15~8 Bits -> 个数
//          7~0  Bits -> Symbol ID
ULONG ulGameCheck_RightType( UBYTE *ubLineData )
{
    SLONG slLoop ;
    UBYTE ubFstSym , ubCal ;
    UBYTE ubWildCal ;
    ULONG ulWildOdds , ulOdds ;
    
    ubFstSym   = ubLineData[4] ;
    ubCal      = 1 ;
    ubWildCal  = 0 ;
    ulWildOdds = 0 ;
    ulOdds     = 0 ;
    
    // 如果第一个 Symbol 是 Fever Symbol 表示无法连线
    if ( ubFstSym == DEF_SYMBOL_FEVER )
    {
        return ( 0 ) ;
    }
     // 如果第一个 Symbol 是 Free Symbol 表示无法连线
    if ( ubFstSym == DEF_SYMBOL_FREE )
    {
        return ( 0 ) ;
    }
    // 如果第一个 Symbol 是 Wild Symbol
    if ( ubFstSym == DEF_SYMBOL_WILD )
    {
        // 计算 Wild 连续个数
        ubWildCal = 1 ;
        for ( slLoop = 3 ; slLoop >= 0 ; slLoop -- )
        {
            if ( ubLineData[slLoop] == DEF_SYMBOL_WILD )
            {
                ubWildCal ++ ;
            }
            else
            {
                break ;
            }
        }
    }
    
    // 计算正常 Symbol 连续个数 , 包含 Wild
    for ( slLoop = 3 ; slLoop >= 0 ; slLoop -- )
    {
        // Symbol 是 Wild 直接计算
        if ( ubLineData[slLoop] == DEF_SYMBOL_WILD )
        {
            ubCal ++ ;
            continue ;
        }
        
        // 如果第一个 Symbol 是 Wild , 则将新的 Symbol 取代 FstSym
        if ( ubFstSym == DEF_SYMBOL_WILD )
        {
            ubFstSym = ubLineData[slLoop] ;
            ubCal ++ ;
        }
        else
        {
            if ( ubFstSym == ubLineData[slLoop] )
            {
                ubCal ++ ;
            }
            else
            {
                break ;
            }
        }
    }
    
    // 获取正常连线奖
    ulOdds = ulGameCheckOddsTable[ubCal][ubFstSym] ;
    
    // 如果有 Wild 连线
    if ( ubWildCal )
    {
        // 获取 Wild 连线奖
        ulWildOdds = ulGameCheckOddsTable[ubWildCal][DEF_SYMBOL_WILD] ;
        
        // 比较哪个倍数比较大
        if ( ulWildOdds > ulOdds )
        {
            return ( (((ULONG)ubWildCal) << 8) | ((ULONG)DEF_SYMBOL_WILD) ) ;
        }
    }
    return ( (((ULONG)ubCal) << 8) | ((ULONG)ubFstSym) ) ;  
}

/*
//检查连线型态
// Input :
//     ubLineData
// Output :
//     (return)
//          15~8 Bits -> 个数
//          7~0  Bits -> Symbol ID
//          19 Bits   -> 左或右中奖
 ULONG ulGameCheck_CheckType( SLONG slLine )
{
    ULONG ulLeftType  , ulLeftOdds  ;
    ULONG ulRightType , ulRightOdds ;
    ULONG ulSym , ulCal ;
    
    ulLeftOdds  = 0 ;
    ulRightOdds = 0 ;
    ulLeftType  = ulGameCheck_LeftType( stcGameInfo.stcLine[slLine].ubSym ) ;
    ulRightType = ulGameCheck_RightType( stcGameInfo.stcLine[slLine].ubSym ) ;
    
    ulSym  = (ulLeftType & 0xFF) ;
    ulCal  = ( ( ulLeftType >> 8 ) & 0xFF ) ;
    
    if ( (ulCal <= 5) && (ulSym < DEF_SYMBOL_MAX) )
    {
        ulLeftOdds = ulGameCheckOddsTable[ulCal][ulSym] ;
    }
    
    ulSym  = (ulRightType & 0xFF) ;
    ulCal  = ( ( ulRightType >> 8 ) & 0xFF ) ;
    
    if ( (ulCal <= 5) && (ulSym < DEF_SYMBOL_MAX) )
    {
        ulRightOdds = ulGameCheckOddsTable[ulCal][ulSym] ;
    }
    if ( ulLeftOdds >= ulRightOdds )
    {
        return ( ulLeftType | 0x80000) ;
    }
    return ( ulRightType ) ;
}

*/
// 检查是否是 All Same
UBYTE ubGameCheck_CheckAllSame( UBYTE *ubAllSymbol )
{
    SLONG slLoop ;
    UBYTE ubFstSym ;

    ubFstSym = ubAllSymbol[0] ;
    
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
        if ( ubAllSymbol[slLoop] == DEF_SYMBOL_WILD )
        {
            continue ;
        }
        if ( ubAllSymbol[slLoop] == ubFstSym )
        {
        }
        else
        {
            return ( DEF_SYMBOL_MAX ) ;
        }
    }
    return ( ubFstSym ) ;
}




// 检查是3个及以上Symbol
SLONG slGameCheck_CheckWinSpecial( UBYTE *ubAllSymbol,UBYTE ubSymID)
{
    SLONG slLoop , slCal ;

    slCal = 0 ;
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
        if ( ubAllSymbol[slLoop] == ubSymID )
        {
            slCal ++ ;
        }
    }
    
    if ( slCal >= 3 )
    {
        return ( slCal ) ;
    }
    return ( 0 ) ;
}




// 检查倍数
void vGameCheck_CheckOdds( GAMEINFO *stcGame )
{
    SLONG slLine ,slLoop,slLoop1 ;
    ULONG ulType , ulSym , ulCal ;
    UBYTE ubAllSymbol[15] ;
    
    // 初始资讯
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
        ubAllSymbol[slLoop] = ubScroll_GetData( slLoop ) ;
    }

    stcGame->ulAllSameOdds     = 0 ;
    stcGame->ulAllSameSym      = 0 ;
    stcGame->ulFeverSetLife    = 0 ;
    stcGame->ulFeverNowLife    = 0 ;

    stcGame->ulBonusType       = 0 ;
    stcGame->ulBonusWin        = 0 ;
    stcGame->ulFreeSetLife     = 0 ;    
	stcGame->ulFreeType 	   = 0 ;
    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
    	 for ( slLoop1 = 0 ; slLoop1 < 2 ; slLoop1 ++ )
    	 {
    	 	stcGame->stcLine[slLine].ulWinSym[slLoop1]   = 0 ;
        	stcGame->stcLine[slLine].ulWinNum[slLoop1]   = 0 ;
        	stcGame->stcLine[slLine].ulOdds[slLoop1]     = 0 ;
        	for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
	        {
	            stcGame->stcLine[slLine].ubAct[slLoop1][slLoop] = 0 ;           
	        }
    	 	
    	 }
        vGameCheck_GetLineData( stcGame->stcLine[slLine].ubSym , slLine ) ;        
    }
    
    // 检查 AllSame 奖
    ulSym = ubGameCheck_CheckAllSame( ubAllSymbol );
    if( ulSym < DEF_SYMBOL_MAX )
    {
        stcGame->ulAllSameSym  = ulSym ;
        stcGame->ulAllSameOdds = ulGameCheckAllSameOddsTable[ulSym] ;
        return ;
    }

    // 检查 Fever Game
    ulCal = slGameCheck_CheckWinSpecial( ubAllSymbol,DEF_SYMBOL_FEVER );
    if( ulCal>=3 )
    {
    	if(ulCal==3)
    	{
    		stcGame->ulFeverSetLife    = 1 ;
            stcGame->ulFeverNowLife    = 1 ;	
    	}	
    	else if(ulCal==4)
    	{
    		stcGame->ulFeverSetLife    = 2 ;
            stcGame->ulFeverNowLife    = 2 ;	
    	}	
    	else
    	{
    		stcGame->ulFeverSetLife    = 3 ;
            stcGame->ulFeverNowLife    = 3 ;	
    	}	    	
    }
    
    // 检查 Free Game
    ulCal = slGameCheck_CheckWinSpecial( ubAllSymbol,DEF_SYMBOL_FREE );
    if( ulCal>=3 )
    {
    	if(ulCal==3)
    	{
    		stcGame->ulFreeSetLife    = 10 ;
    		stcGame->ulFreeType = 1 ;
           
    	}	
    	else if(ulCal==4)
    	{
    		stcGame->ulFreeSetLife    = 20 ;
            stcGame->ulFreeType = 2 ;
    	}	
    	else
    	{
    		stcGame->ulFreeSetLife    = 30 ;
            stcGame->ulFreeType = 3 ;
    	}	    	
    }
    ulCal = slGameCheck_CheckWinSpecial( ubAllSymbol,DEF_SYMBOL_WILD );
    if( ulCal>=3 )
    {
    	if(ulCal==3)
    	{
    		stcGame->ulBonusType = 1 ;
    	}	
    	else if(ulCal==4)
    	{
    		stcGame->ulBonusType = 2 ;
    	}	
    	else
    	{
    		stcGame->ulBonusType = 3 ;	
    	}	
    	
    }
    // 检查 Link 奖
    ulSym = 0 ;
    ulCal = 0 ;

    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
        if( slLine < slSlave_ReadLine() )	// 从这里避开未押注的线       
        {
        	for ( slLoop = 0 ; slLoop < 2 ; slLoop ++ )
        	{
        		if(slLoop)	
        		{
        			ulType = ulGameCheck_RightType( stcGame->stcLine[slLine].ubSym ); 
        		}	
        		else
        		{
        			ulType = ulGameCheck_LeftType( stcGame->stcLine[slLine].ubSym ); 
        		}	
        		ulSym  = (ulType & 0xFF) ;
	            ulCal  = ( ( ulType >> 8 ) & 0xFF ) ;
	            
	            if (( ulCal >= 6 )||( ulSym >= DEF_SYMBOL_MAX ))
	            {
	                continue ;
	            }            
	            stcGame->stcLine[slLine].ulWinSym[slLoop]   = ulSym ;
	            stcGame->stcLine[slLine].ulWinNum[slLoop]   = ulCal ;
	            stcGame->stcLine[slLine].ulOdds[slLoop]     = ulGameCheckOddsTable[ulCal][ulSym] ;
	            if ( stcGame->stcLine[slLine].ulOdds[slLoop] )
	            { 
	            	if(slLoop)	
	            	{
	            		for ( slLoop1 = 4 ; slLoop1 >= (5-ulCal) ; slLoop1 -- )
		                {
		                    stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1 ;
		                } 
	            	}
	            	else
	            	{
	            		for ( slLoop1 = 0 ; slLoop1 < ulCal ; slLoop1 ++ )
		                {
		                    stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1 ;
		                }
	            	
	            	}		               
	                if(ulCal>=4)
	                {
	                	break;	//防止5连线时重复计算
	                }	               
	            }
        		
        	}
        }
    }
}
#ifdef DEF_FIX_CHANCE_20150212
// 检查全部线倍数
void vGameCheck_CheckAllLineOdds( GAMEINFO *stcGame )
{
    SLONG slLine ,slLoop,slLoop1 ;
    ULONG ulType , ulSym , ulCal ;
    UBYTE ubAllSymbol[15] ;
    
    // 初始资讯
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
        ubAllSymbol[slLoop] = ubScroll_GetData( slLoop ) ;
    }

    stcGame->ulAllSameOdds     = 0 ;
    stcGame->ulAllSameSym      = 0 ;
    stcGame->ulFeverSetLife    = 0 ;
    stcGame->ulFeverNowLife    = 0 ;

    stcGame->ulBonusType       = 0 ;
    stcGame->ulBonusWin        = 0 ;
    stcGame->ulFreeSetLife     = 0 ;    
	stcGame->ulFreeType 	   = 0 ;
    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
    	 for ( slLoop1 = 0 ; slLoop1 < 2 ; slLoop1 ++ )
    	 {
    	 	stcGame->stcLine[slLine].ulWinSym[slLoop1]   = 0 ;
        	stcGame->stcLine[slLine].ulWinNum[slLoop1]   = 0 ;
        	stcGame->stcLine[slLine].ulOdds[slLoop1]     = 0 ;
        	for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
	        {
	            stcGame->stcLine[slLine].ubAct[slLoop1][slLoop] = 0 ;           
	        }
    	 	
    	 }
        vGameCheck_GetLineData( stcGame->stcLine[slLine].ubSym , slLine ) ;        
    }
    
    // 检查 AllSame 奖
    ulSym = ubGameCheck_CheckAllSame( ubAllSymbol );
    if( ulSym < DEF_SYMBOL_MAX )
    {
        stcGame->ulAllSameSym  = ulSym ;
        stcGame->ulAllSameOdds = ulGameCheckAllSameOddsTable[ulSym] ;
        return ;
    }

    // 检查 Fever Game
    ulCal = slGameCheck_CheckWinSpecial( ubAllSymbol,DEF_SYMBOL_FEVER );
    if( ulCal>=3 )
    {
    	if(ulCal==3)
    	{
    		stcGame->ulFeverSetLife    = 1 ;
            stcGame->ulFeverNowLife    = 1 ;	
    	}	
    	else if(ulCal==4)
    	{
    		stcGame->ulFeverSetLife    = 2 ;
            stcGame->ulFeverNowLife    = 2 ;	
    	}	
    	else
    	{
    		stcGame->ulFeverSetLife    = 3 ;
            stcGame->ulFeverNowLife    = 3 ;	
    	}	    	
    }
    
    // 检查 Free Game
    ulCal = slGameCheck_CheckWinSpecial( ubAllSymbol,DEF_SYMBOL_FREE );
    if( ulCal>=3 )
    {
    	if(ulCal==3)
    	{
    		stcGame->ulFreeSetLife    = 10 ;
    		stcGame->ulFreeType = 1 ;
           
    	}	
    	else if(ulCal==4)
    	{
    		stcGame->ulFreeSetLife    = 20 ;
            stcGame->ulFreeType = 2 ;
    	}	
    	else
    	{
    		stcGame->ulFreeSetLife    = 30 ;
            stcGame->ulFreeType = 3 ;
    	}	    	
    }
    ulCal = slGameCheck_CheckWinSpecial( ubAllSymbol,DEF_SYMBOL_WILD );
    if( ulCal>=3 )
    {
    	if(ulCal==3)
    	{
    		stcGame->ulBonusType = 1 ;
    	}	
    	else if(ulCal==4)
    	{
    		stcGame->ulBonusType = 2 ;
    	}	
    	else
    	{
    		stcGame->ulBonusType = 3 ;	
    	}	
    	
    }
    // 检查 Link 奖
    ulSym = 0 ;
    ulCal = 0 ;

    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
        //if( slLine < slSlave_ReadLine() )	// 从这里避开未押注的线       
        {
        	for ( slLoop = 0 ; slLoop < 2 ; slLoop ++ )
        	{
        		if(slLoop)	
        		{
        			ulType = ulGameCheck_RightType( stcGame->stcLine[slLine].ubSym ); 
        		}	
        		else
        		{
        			ulType = ulGameCheck_LeftType( stcGame->stcLine[slLine].ubSym ); 
        		}	
        		ulSym  = (ulType & 0xFF) ;
	            ulCal  = ( ( ulType >> 8 ) & 0xFF ) ;
	            
	            if (( ulCal >= 6 )||( ulSym >= DEF_SYMBOL_MAX ))
	            {
	                continue ;
	            }            
	            stcGame->stcLine[slLine].ulWinSym[slLoop]   = ulSym ;
	            stcGame->stcLine[slLine].ulWinNum[slLoop]   = ulCal ;
	            stcGame->stcLine[slLine].ulOdds[slLoop]     = ulGameCheckOddsTable[ulCal][ulSym] ;
	            if ( stcGame->stcLine[slLine].ulOdds[slLoop] )
	            { 
	            	if(slLoop)	
	            	{
	            		for ( slLoop1 = 4 ; slLoop1 >= (5-ulCal) ; slLoop1 -- )
		                {
		                    stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1 ;
		                } 
	            	}
	            	else
	            	{
	            		for ( slLoop1 = 0 ; slLoop1 < ulCal ; slLoop1 ++ )
		                {
		                    stcGame->stcLine[slLine].ubAct[slLoop][slLoop1] = 1 ;
		                }
	            	
	            	}		               
	                if(ulCal>=4)
	                {
	                	break;	//防止5连线时重复计算
	                }	               
	            }
        		
        	}
        }
    }
}
#endif
// 检查倍数
SLONG slGameCheck_ReadAllOdds( GAMEINFO *stcGame )
{
	ULONG ulOdds;
	SLONG slLine;
	ulOdds = stcGame->ulAllSameOdds;
	for ( slLine = 0 ; slLine < 9 ; slLine ++ )
	{
		ulOdds += stcGame->stcLine[slLine].ulOdds[0];
		ulOdds += stcGame->stcLine[slLine].ulOdds[1];
	}
	
	return ( ulOdds ) ;
	
	
}

SLONG slGameCheck_GameWinRule( GAMEINFO *stcGame )
{
    SLONG slValue ;
    SLONG slLine ;   
    slValue = stcGame->ulAllSameOdds *  slSlave_ReadTotalBet() ;
    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
        slValue += stcGame->stcLine[slLine].ulOdds[0] * slSlave_ReadBet() ;
        slValue += stcGame->stcLine[slLine].ulOdds[1] * slSlave_ReadBet() ;
    }   
    return ( slValue ) ;
}

void vGameCheck_SaveWinRule( GAMEINFO *stcGame )
{
//    SLONG slValue ;
    SLONG slLine,slLoop ;   
    //slValue = stcGame->ulAllSameOdds *  slSlave_ReadTotalBet() ;
    SLONG slGiftBet ;
    SLONG slInFree ;
    
    slGiftBet = 0 ;
    if( slSlave_ReadTotalBet( ) >= mGame_ReadBetForGift( ) ) slGiftBet = 1 ;

	slInFree = 0 ;
	if( stcGame->ulFreeNowLife ) slInFree = 8 ;
    	    
    if( stcGame->ulAllSameOdds )
    {    
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_ALL+stcGame->ulAllSameSym , 1 ) ;
		if( slGiftBet )
		{
			vRecord_Add_GiftBet( DEF_REC_SYM00_ALL+stcGame->ulAllSameSym , 1 ) ;
		}		
		vRecord_Save_WinEvent( ( stcGame->ulAllSameOdds * slSlave_ReadTotalBet( ) ) , 2+slInFree , stcGame->ulAllSameSym ) ;
    }
    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
    	for ( slLoop = 0 ; slLoop < 2 ; slLoop ++ )
    	{
	    	if( stcGame->stcLine[slLine].ulOdds[slLoop] )
	    	{
	            if( stcGame->stcLine[slLine].ulWinNum[slLoop] == 3 )
	            {
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_X3+stcGame->stcLine[slLine].ulWinSym[slLoop] , 1 ) ;
					if( slGiftBet )
					{
						vRecord_Add_GiftBet( DEF_REC_SYM00_X3+stcGame->stcLine[slLine].ulWinSym[slLoop] , 1 ) ;
					}
					if( stcGame->stcLine[slLine].ulOdds[slLoop] >= 100 )
					{
						vRecord_Save_WinEvent( ( stcGame->stcLine[slLine].ulOdds[slLoop] * slSlave_ReadBet( ) ) , 3+slInFree , stcGame->stcLine[slLine].ulWinSym[slLoop] ) ;
					}
				}
	            else if( stcGame->stcLine[slLine].ulWinNum[slLoop] == 4 )
	            {
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_X4+stcGame->stcLine[slLine].ulWinSym[slLoop] , 1 ) ;
					if( slGiftBet )
					{
						vRecord_Add_GiftBet( DEF_REC_SYM00_X4+stcGame->stcLine[slLine].ulWinSym[slLoop] , 1 ) ;
					}
					if( stcGame->stcLine[slLine].ulOdds[slLoop] >= 100 )
					{
						vRecord_Save_WinEvent( ( stcGame->stcLine[slLine].ulOdds[slLoop] * slSlave_ReadBet( ) ) , 4+slInFree , stcGame->stcLine[slLine].ulWinSym[slLoop] ) ;
					}
				}
	            else if( stcGame->stcLine[slLine].ulWinNum[slLoop] == 5 )
	            {
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_X5+stcGame->stcLine[slLine].ulWinSym[slLoop] , 1 ) ;
					if( slGiftBet )
					{
						vRecord_Add_GiftBet( DEF_REC_SYM00_X5+stcGame->stcLine[slLine].ulWinSym[slLoop] , 1 ) ;
					}
					if( stcGame->stcLine[slLine].ulOdds[slLoop] >= 100 )
					{
						vRecord_Save_WinEvent( ( stcGame->stcLine[slLine].ulOdds[slLoop] * slSlave_ReadBet( ) ) , 5+slInFree , stcGame->stcLine[slLine].ulWinSym[slLoop] ) ;
					}
				}			
	    	}	
    		
    	}
    	
    }   
}


//用最大押分算出的值
SLONG slGameCheck_MaxGameWinRule( GAMEINFO *stcGame )
{
    SLONG slValue,slLine ,slBet ;
	slBet = mGame_ReadMaxBet();
    slValue = stcGame->ulAllSameOdds * slBet * slSlave_ReadLine() ;
    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
    {
        slValue += stcGame->stcLine[slLine].ulOdds[0] * slBet ;
        slValue += stcGame->stcLine[slLine].ulOdds[1] * slBet ;
    }   
    return ( slValue ) ;
}

//判断线上是否有带WILD
SLONG slGameCheck_LineWildValue( UBYTE ubLine )
{
	SLONG slLoop;
	ULONG ulLoc,ulWinSym;
	UBYTE   ubType;
	ubType = ubLine%2; 
	ubLine /= 2;
	
	if(stcGameInfo.stcLine[ubLine].ulWinSym[ubType] != DEF_SYMBOL_WILD)
	{
		for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
		{
			if(stcGameInfo.stcLine[ubLine].ubAct[ubType][slLoop])
			{
				ulLoc = ubGameCheckLineLocInformation[ ubLine][slLoop];
				ulWinSym = ubScroll_GetData(ulLoc);	
				if(ulWinSym==DEF_SYMBOL_WILD)	
				{
					return ( 1 ) ;	
				}		
			}		
		}	
		
	}	
	return ( 0 ) ;	
}


//判断出中奖线条是首或尾，
UWORD uwGameCheck_MessLine( UBYTE ubLine )
{
	SLONG slLoop;
	ULONG ulAllCount,ulLineCount,ulActLoc,ulActCount;
	UWORD uwStart,uwEnd;
	
	ulAllCount = 0;
	ulLineCount = 0;	
	
	for ( slLoop = 0 ; slLoop < 18 ; slLoop ++ )
	{
		ulActLoc = slLoop/2;
		ulActCount = slLoop%2;		
		if(stcGameInfo.stcLine[ulActLoc].ulOdds[ulActCount])	
		{
			ulAllCount++;	
			if(slLoop <= ubLine)
			{
				ulLineCount++;
			}	
		}	
	}		
	uwStart = 0;
	uwEnd = 0;
	if(ulLineCount==1)
	{
		uwStart = 0xFF;	
	}	
	if(ulLineCount==ulAllCount)
	{
		uwEnd = 0xFF00;	
	}	
	return ( uwStart|uwEnd ) ;	
}





//测试是否中3个或以上,
SLONG slGameCheck_IsSpecial( UBYTE ubSymID )
{
    SLONG slLoop ;
    UBYTE ubAllSymbol[15] ;
    
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
        ubAllSymbol[slLoop] = ubScroll_GetData( slLoop ) ;
    }
    return (  slGameCheck_CheckWinSpecial( ubAllSymbol,ubSymID ) ) ;
}



SLONG slGameCheck_FeverValue( void )
{
    SLONG slLine , slLoop ;    
    UBYTE ubAllSymbol[3] ;
    
    // 初始资讯
    for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
    {
        ubAllSymbol[slLoop] = stcReelFeverData[slLoop].ubStopID[2];
    }	
    for ( slLine = 0 ; slLine < 7 ; slLine ++ )
    {
    	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
    	{
    		if(ubAllSymbol[slLoop] != slLine)
    		{
    			break;	
    		}		
    	}
    	if(slLoop == DEF_FEVER_REEL_MAX)
    	{
    		return(slLine); 	
    	}	
    		
    }
    
	return(7); 	
	
}

void vGameCheck_WupWinRule( void )
{	
	SLONG slValue;
	slValue = slSlave_WupWinRead();
	switch ( stcWupChance.ubData )
	{
		case DEF_CHANCE_WUP_WIN_X1:			
			vSlave_WupWinSet(slValue*2);			
			 break ;	
		case DEF_CHANCE_WUP_WIN_X2:
			 vSlave_WupWinSet(slValue*3);
			 break ;	
		case DEF_CHANCE_WUP_WIN_X3:
			 vSlave_WupWinSet(slValue*4);
			 break ;	
		case DEF_CHANCE_WUP_WIN_X4:
			 vSlave_WupWinSet(slValue*5);
			 break ;	
			
		case DEF_CHANCE_WUP_LOSE:
			 vSlave_WupWinSet(0);					
			 break ;			
	}
}