#define DEF_WUPCHANCE_C
#include "common.h"
#define FILE_NAME "WUPCHANCE.C"



ULONG const ulWupChanceInfoData[4][6] = {
	{ 32359,4400,26754,1258,640,125},	 
	{ 32523,4400,26590,1258,640,125},	 
	{ 32687,4400,26426,1258,640,125},	 
	{ 32850,4400,26263,1258,640,125},	 				
};


ULONG const ulWupChanceAsnGift[6] = {
	DEF_CHANCE_WUP_LOSE,    //猜错
	DEF_CHANCE_WUP_NULL,    //重猜 	
	DEF_CHANCE_WUP_WIN_X1,  //中1次
	DEF_CHANCE_WUP_WIN_X2,
	DEF_CHANCE_WUP_WIN_X3,
	DEF_CHANCE_WUP_WIN_X4				
};

ULONG const ulWupChanceOdds[6] = {
	0,    //猜错
	0,    //重猜 	
	2,    //中1次
	3,
	4,
	5				
};


void vWupChance_SetRate( void )
{
	stcWupChance.ulRate = 990-(mGame_ReadWupRateLevel()%4)*5;
}

// 连输补牌，强制赢
void vWupChance_ResetAsnLose( ULONG ulWin )
{
	if( ulWin )
	{
		// 有赢就重新算
		switch( mGame_ReadWupAsnLose( ) )
		{
		case 2 :
	 		stcWupChance.ulAsnLose = ulRand_ReadMod(3)+2;
	 		break ;
		case 3 :
	 		stcWupChance.ulAsnLose = ulRand_ReadMod(4)+2;
	 		break ;
	 	case 4 :
		default :
	 		stcWupChance.ulAsnLose = ulRand_ReadMod(3)+3;
	 		break ;	 		
		}
	}
	else
	{
		// 输一次扣一，直到为零，会强制赢一次
		if( stcWupChance.ulAsnLose ) stcWupChance.ulAsnLose -- ;					
	}
}

// 周期砍牌，强制输
void vWupChance_ResetAsnKill( void )
{
	if( stcWupChance.ulAsnKill )
	{
		// 不管输赢，每局都扣一	
		stcWupChance.ulAsnKill -- ;
	}	
	else
	{
		// 直到为零，会强制输一次
		switch( mGame_ReadWupAsnKill( ) )
		{
		case 2 :
	 		stcWupChance.ulAsnKill = ulRand_ReadMod(5)+4;
	 		break ;
		case 3 :
	 		stcWupChance.ulAsnKill = ulRand_ReadMod(5)+5;
	 		break ;
		case 4 :
	 		stcWupChance.ulAsnKill = ulRand_ReadMod(5)+6;
	 		break ;	 		
		case 5 :
	 		stcWupChance.ulAsnKill = ulRand_ReadMod(5)+7;
	 		break ;
		case 6 :
	 		stcWupChance.ulAsnKill = ulRand_ReadMod(5)+8;
	 		break ;	
	 	case 7 :	 		
		default :
	 		stcWupChance.ulAsnKill = ulRand_ReadMod(5)+9;
	 		break ;
		}
	}
}


void vWupChance_Reset( void )
{
	//UBYTE i ; //ubFl , ubNum,i ;
    vMemory_Set((UBYTE *)&stcWupChance , 0x00 , sizeof(stcWupChance)) ;
    /*
    for(i=0;i<6;i++)
	{
		stcWupChance.ubHistory[i] = ubWupChanceDefaultLastCard[i];
		stcWupChance.ubDemoHistory[i] = ubWupChanceDefaultLastCard[i];
		
	}
*/
	vWupChance_ResetAsnLose( 1 ) ;
	vWupChance_ResetAsnKill( ) ;
    
}

// 初始化变数，每次比倍前都会执行一次
void vWupChance_Initial( void )
{
	//stcWupChance.ubMovePassTime=0;
	//stcWupChance.ubPassTime = 0;
	//stcWupChance.ubCard = DEF_POKER_BK ;
	//stcWupChance.ulLoseBet = 0;	
	//stcWupChance.ulInTimes ++ ;
}
//更新查账历史记录
void vWupChance_RecordUpdate( void )
{
	/*
	SLONG slLoop ;    
    for ( slLoop = 10 ; slLoop >= 1 ; slLoop -- )
    {
        stcRecordWup[0].ulWupWin[slLoop] = stcRecordWup[0].ulWupWin[slLoop-1] ;	
        stcRecordWup[0].ulWupMode[slLoop] = stcRecordWup[0].ulWupMode[slLoop-1] ;
        stcRecordWup[0].ulWupCard[slLoop] = stcRecordWup[0].ulWupCard[slLoop-1] ; 
        stcRecordWup[0].ulWupGuess[slLoop] = stcRecordWup[0].ulWupGuess[slLoop-1] ; 
    }
    stcRecordWup[0].ulWupWin[0] = 0;
    stcRecordWup[0].ulWupCard[0] = DEF_POKER_BK;
	*/
}

// 更新前局记录
void vWupChance_Update( void )
{
	
	SLONG slLoop ;
    
    for ( slLoop = 5 ; slLoop >= 1 ; slLoop -- )
    {
        stcWupChance.ubHistory[slLoop] = stcWupChance.ubHistory[slLoop-1] ;	
    }
    //stcWupChance.ubHistory[0] = stcWupChance.ubCard ;
    //stcWupChance.ubCard = DEF_POKER_BK ;
}


// 更新演示前局记录
void vWupChance_DemoUpdate( void )
{
	
	SLONG slLoop ;
    
    for ( slLoop = 5 ; slLoop >= 1 ; slLoop -- )
    {
        stcWupChance.ubDemoHistory[slLoop] = stcWupChance.ubDemoHistory[slLoop-1] ;	
    }
    //stcWupChance.ubDemoHistory[0] = stcWupChance.ubCard ;
    //stcWupChance.ubCard = DEF_POKER_BK ;
}

// 比倍发牌前的几率处理
void vWupChance_BetProcess( void )
{
	ULONG	ulBet ;
	
	ulBet = slSlave_WupWinRead( );
	slBuffer_AddRate( &stcWupChance.Buffer , ulBet , stcWupChance.ulRate ) ;	
	
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALPLAY , ulBet ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_PLAYTOTAL , ulBet ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_PLAYTIMES , 1 ) ;
	#ifdef DEF_USE_VGAME_UART_SLAVE
	ulUartCmdRec[DEF_RECORD_DATA_TOTALPLAY][0] += ulBet ;
	ulUartCmdRec[DEF_RECORD_WUP_PLAYTOTAL][0] += ulBet ;
	ulUartCmdRec[DEF_RECORD_WUP_PLAYTIMES][0] += 1 ;
	#endif
}


// 比倍演示发牌处理
void vWupChance_DemoDealProcess( void )
{
	if(stcWupChance.ubDemoTime == 1)
	{
		stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
	}	
	else if(stcWupChance.ubDemoTime == 2)
	{
		stcWupChance.ubData = DEF_REC_WUP_NULL;
	}
	else if(stcWupChance.ubDemoTime == 3)
	{
		stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X4;
	}	
	else
	{
		stcWupChance.ubData = DEF_CHANCE_WUP_LOSE;
	}	
	stcWupChance.ubDemoTime++;
}



//求表格的那组数据
ULONG ulWupChance_TakeValueNum( ULONG const *ulData,ULONG ulValue,ULONG ulSize )
{
	ULONG	i ;	
	if ( ulSize >= 100 )
	{
		return 0;
	}
	for(i=0;i<ulSize;i++)
	{
		if( ulValue < ulData[i] ) break ;
		ulValue -= ulData[i] ;
	}	
	if(i>=ulSize)
	{
		i = ulSize-1;	
	}
	return 	i;
}

// 猜左右处理
void vWupChance_DealProcess( void )
{
	SLONG slNextWin,slValue;
    ULONG ulNum,ulMaxBet ;   
     
	ulMaxBet = mGame_ReadMaxBet()*9;
	
    if((stcWupChance.ulPlayTimes==0)&&(stcWupChance.Buffer.slValue==0))
    {
    	stcWupChance.Buffer.slValue = ulMaxBet * 10; //固定灌十倍的 MaxBet
 
    }	
    ulNum = ulWupChance_TakeValueNum(&ulWupChanceInfoData[mGame_ReadWupRateLevel()][0],ulRand_ReadMod(0x10000),6);

    stcWupChance.ubData = ulWupChanceAsnGift[ulNum];
    
    #ifdef DEF_TEST_WUPWIN
    stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1 ;
    return ;
    #endif
    
    slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[ulNum];
        
    slValue = stcWupChance.Buffer.slValue - slNextWin;
    
    if(slValue > 400*(SLONG)ulMaxBet)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(200))&&(stcWupChance.ubData==DEF_CHANCE_WUP_LOSE))
    	{
			slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[2] ;
    		slValue -= slNextWin ;
    		if( slValue > (-100)*(SLONG)ulMaxBet)
    		{
	    		stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
	    		stcWupChance.ulRecAsnValue[0] += slSlave_WupWinRead()*2;
	    		stcWupChance.ulRecAsnTimes[0]++;
	    	}
    	}	
    	
    }	
    else if(slValue > 200*(SLONG)ulMaxBet)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(100))&&(stcWupChance.ubData==DEF_CHANCE_WUP_LOSE))
    	{
			slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[2] ;
    		slValue -= slNextWin ;
    		if( slValue > (-100)*(SLONG)ulMaxBet)
    		{
	    		stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
	    		stcWupChance.ulRecAsnValue[1] += slSlave_WupWinRead()*2;
	    		stcWupChance.ulRecAsnTimes[1]++;
    		}
    	}	    	
    }	
    else if(slValue > 100*(SLONG)ulMaxBet)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(50))&&(stcWupChance.ubData==DEF_CHANCE_WUP_LOSE))
    	{
			slNextWin = slSlave_WupWinRead() * ulWupChanceOdds[2] ;
    		slValue -= slNextWin ;
    		if( slValue > (-100)*(SLONG)ulMaxBet)
    		{
	    		stcWupChance.ubData = DEF_CHANCE_WUP_WIN_X1;
	    		stcWupChance.ulRecAsnValue[2] += slSlave_WupWinRead()*2;
	    		stcWupChance.ulRecAsnTimes[2]++;  
	    	}
    	}	
    	
    }	
    else if(slValue < (-200)*(SLONG)ulMaxBet)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(1000))&&slNextWin)
    	{
    		stcWupChance.ubData=DEF_CHANCE_WUP_LOSE;
    		stcWupChance.ulRecAsnValue[6] += slNextWin;
    		stcWupChance.ulRecAsnTimes[6]++;
    	}	    	
    }	
    else if(slValue < (-100)*(SLONG)ulMaxBet)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(150))&&slNextWin)
    	{
    		stcWupChance.ubData=DEF_CHANCE_WUP_LOSE;
    		stcWupChance.ulRecAsnValue[5] += slNextWin;
    		stcWupChance.ulRecAsnTimes[5]++;
    	}	    	
    }	
    else if(slValue < (-50)*(SLONG)ulMaxBet)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(100))&&slNextWin)
    	{
    		stcWupChance.ubData=DEF_CHANCE_WUP_LOSE;
    		stcWupChance.ulRecAsnValue[4] += slNextWin;
    		stcWupChance.ulRecAsnTimes[4]++;
    	}	    	
    }	
    else if(slValue < 0)
    {
    	if(( ulRand_ReadMod(0x10000) < mMacro_Rate(50))&&slNextWin)
    	{
    		stcWupChance.ubData=DEF_CHANCE_WUP_LOSE;
    		stcWupChance.ulRecAsnValue[3] += slNextWin;
    		stcWupChance.ulRecAsnTimes[3]++;
    	}	    	
    }
    stcWupChance.ulRecTimes[ulNum]++;
	stcWupChance.ulPlayTimes ++ ;
	if( stcWupChance.ulPlayTimes > 100001000 ) stcWupChance.ulPlayTimes -= 100000000 ;
		
   


    	
}

// 比倍中奖后的几率处理
void vWupChance_WinProcess( ULONG ulWin )
{

	if( ulWin )
	{
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , ulWin ) ;
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_WINTOTAL , ulWin ) ;
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_WINTIMES , 1 ) ;
		#ifdef DEF_USE_VGAME_UART_SLAVE
		ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += ulWin ;
		ulUartCmdRec[DEF_RECORD_WUP_WINTOTAL][0] += ulWin ;
		ulUartCmdRec[DEF_RECORD_WUP_WINTIMES][0] += 1 ;
		#endif

		stcWupChance.Buffer.slValue -= ulWin;	
	}
   	vWupChance_ResetAsnLose( ulWin ) ;
   	switch ( stcWupChance.ubData )
   	{
   		case DEF_CHANCE_WUP_LOSE:
   		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_LOSE , 1 ) ;	
   		break ;		
   		case DEF_CHANCE_WUP_WIN_X1:
   		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_X2 , 1 ) ;	
   		break ;		
   		case DEF_CHANCE_WUP_WIN_X2:
   		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_X3 , 1 ) ;	
   		break ;		
   		case DEF_CHANCE_WUP_WIN_X3:
   		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_X4 , 1 ) ;	
   		break ;		
   		case DEF_CHANCE_WUP_WIN_X4:	
   		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_X5 , 1 ) ;	
   		break ;			
   		//case DEF_CHANCE_WUP_NULL:	
   		//vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_NULL , 1 ) ;	// 搬到 vMaster_Wup_Effect 来处理		
   		//break ;	
   	}
	
}

void vWupChance_WinBnsProcess( ULONG ulWin , ULONG mode )
{
/*
	//if( ulWin )
	{
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , ulWin ) ;
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_WINTOTAL , ulWin ) ;
		#ifdef DEF_USE_VGAME_UART_SLAVE
		ulUartCmdRecAdd[DEF_RECORD_DATA_TOTALWIN] += ulWin ;
		ulUartCmdRecAdd[DEF_RECORD_WUP_WINTOTAL] += ulWin ;
		#endif

		stcWupChance.Buffer.slValue -= ulWin;		
		
		if( mode == 1 )
		{
			stcWupChance.ulRecInsure[0] ++ ;
			stcWupChance.ulRecInsure[1] += ulWin ;			

			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_SAVE_TIMES , 1 ) ;
			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_SAVE_TOTAL , ulWin ) ;
		}
		else if( mode == 2 )
		{
			stcWupChance.ulRecPass[0] ++ ;
			stcWupChance.ulRecPass[1] += ulWin ;			

			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_BONUS_TIMES , 1 ) ;
			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_BONUS_TOTAL , ulWin ) ;
		}
		else if( mode == 3 )
		{
			stcWupChance.ulRecLimit[0] ++ ;
			stcWupChance.ulRecLimit[1] += ulWin ;			

			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_LIMIT_TIMES , 1 ) ;
			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_LIMIT_TOTAL , ulWin ) ;
		}
					
	}
*/	
}

void vWupChance_RecWupLimit( ULONG ulWin )
{
	stcWupChance.ulRecLimit[0] ++ ;
	stcWupChance.ulRecLimit[1] += ulWin ;			

	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_LIMIT_TIMES , 1 ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_LIMIT_TOTAL , ulWin ) ;
	#ifdef DEF_USE_VGAME_UART_SLAVE
	ulUartCmdRec[DEF_REC_WUP_LIMIT_TOTAL][0] += ulWin ;
	ulUartCmdRec[DEF_REC_WUP_LIMIT_TIMES][0] += 1 ;
	#endif
}

