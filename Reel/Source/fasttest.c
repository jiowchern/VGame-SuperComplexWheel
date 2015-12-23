#define DEF_FASTTEST_C
#include "common.h"
#define FILE_NAME  "FASTTEST.C"

const char *Buffer[DEF_CHANCE_BUFMAX] = 
	{
		"MAIN" ,
		"SPEC" ,	
		"BONUS" ,	
		"FEVER" ,	
		"FREE" ,			
	};	

#ifdef DEF_OPEN_FAST_TEST
	
//#include <stdio.h>
  	#define DEF_TEST_SYMBOL_MAX       13

	//DLONG slLoopTimes , slLoop ;
	//SLONG slBet ;
	//SLONG slMaxBet ;
	//SLONG slMinBet;
	//SLONG slFstWinGift ;
	//SLONG slWinGift ; 
	//SLONG slWin ;	
	SLONG slFeverWin ;	
	SLONG slFreeWin ;
	ULONG ulPlayTimes ;
	ULONG ulWinTimes  ;
	DLONG dlPlayTotal ;
	DLONG dlWinTotal  ;
    DLONG dlRunTime;
    //ULONG ulFstGiftTimes[DEF_ITEM_MAX];
    //ULONG ulGiftTimes[DEF_ITEM_MAX];
    ULONG ulSwitch;
    ULONG ulRecCycle;
    //ULONG ulFillClass;
    //ULONG ulFillTimes;
    //ULONG ulLoseTimes;
    //ULONG ulAsnFillTimes;
    SLONG slWupBet; 
    ULONG ulWupTime;
    ULONG ulWupPlayTimes;
    //ULONG ulWupSavemoney;
    ULONG ulWupCondi1;  //0不比倍、1比一关 ,2比二关,3比三关,4比四关,5比到爆机为止
    ULONG ulWupCondi2;  //0双比倍、1比倍、2半比倍


    
    //ULONG ulBigAwardsGate[6];
    //UWORD uwGameRandom[DEF_TEST_SYMBOL_MAX];
   
    //ULONG ulFstNormalGate[DEF_ITEM_MAX];
    //ULONG ulSecNormalGate[DEF_ITEM_MAX];
    //ULONG ulRate[DEF_CHANCE_BUFMAX];  
    //ULONG ulWupRate;
	//ULONG ulSymbolData[128];

/*	
void vFastTest_RandomNum(void)
{
	SLONG slLoop ,slLoop1 , slJK ;
	UBYTE ubPutIndex[128] ;
	ULONG ulCount; 
	vGameAssign_LocSwap(ubPutIndex,128);
	ulCount = 0;
	for( slLoop = 0 ; slLoop < DEF_TEST_SYMBOL_MAX ; slLoop ++ )
	{
		for( slLoop1 = 0 ; slLoop1 < uwGameRandom[slLoop] ; slLoop1 ++ )
		{
			ulSymbolData[ubPutIndex[ulCount]]= slLoop;				
			ulCount++;			
		}	
	}
	
}	
*/

void vFastTest_AssertOut( ULONG ulLine )
{
	FILE *ofp ;

	ofp = fopen( "txt/assert.txt" , "a+" ) ;
	if ( ofp )
	{
		fprintf( ofp , "ASSERT %d \t" , ulLine ) ;					
		
        fclose( ofp ) ;
	}
}
    
void vFastTest_OpenInputInfo( void )
{
	FILE *ofp ;
	SLONG	temp ;
	UBYTE	cStr[10] ;
	SLONG	slLoop ;
	temp = 0 ;
	ofp = fopen( "txt/info.txt" , "r" ) ;
	if ( ofp )
	{ 	

		fscanf( ofp ,"%s", cStr ); ulSwitch = atol( cStr );
		if(ulSwitch)
		{
			vAdjustValue_Setup( );
			
			fscanf( ofp ,"%s", cStr ); dlRunTime = atol( cStr );			
  				
			fscanf( ofp ,"%s", cStr ); temp = atol( cStr );			
			vSlave_BetSet(temp) ; //vSlave_SetBet(DEF_GAME_ONLY_PLAY,temp);		
			
			fscanf( ofp ,"%s", cStr ); temp = atol( cStr );
	   		vAdjustValue_Set( DEF_ADJUSTVALUE_MIN_BET , temp ) ;
	   		
			fscanf( ofp ,"%s", cStr ); temp = atol( cStr );
	   		vAdjustValue_Set( DEF_ADJUSTVALUE_MAX_BET , temp ) ;

	   		fscanf( ofp ,"%s", cStr ); temp = atol( cStr );
	   		vSlave_SetLine(temp);

			fscanf( ofp ,"%s", cStr ); temp = atol( cStr );
	   		vAdjustValue_Set( DEF_ADJUSTVALUE_GAME_RATE , temp ) ;

			fscanf( ofp ,"%s", cStr ); temp = atol( cStr );
	   		vAdjustValue_Set( DEF_ADJUSTVALUE_GAME_UNDULATE , temp ) ;

			fscanf( ofp ,"%s", cStr ); temp = atol( cStr );
	   		vAdjustValue_Set( DEF_ADJUSTVALUE_WUP_RATE , temp ) ;
	   			   		
	   		// 各种Symbol在每个轮上出现率
	   		/*
			for( slLoop = 0 ; slLoop < DEF_TEST_SYMBOL_MAX ; slLoop ++ )
			{
				fscanf( ofp ,"%s", cStr ); uwGameRandom[slLoop] = atoi( cStr );				
			} 
			*/
			
	   		fscanf( ofp ,"%s", cStr ); ulRecCycle = atol( cStr );		   				
			fscanf( ofp ,"%s", cStr ); ulWupCondi1 = atol( cStr );
			fscanf( ofp ,"%s", cStr ); ulWupCondi2 = atol( cStr );
	    	vAdjustValue_UpDate( ) ;
		}	
		
		fclose( ofp ) ;
	}
	else
	{
		mDebug_Out( "Open Info.txt error \n", 0 ) ;
	}
	
}


void  vFastTest_OutInfo( void )
{
	FILE *ofp ;
	SLONG	slLoop ;
	//vFastTest_RandomNum();
    ofp = fopen( "txt/outinfo.txt" , "wb" ) ;
    if( ofp )
    {
        fprintf( ofp , "%d\n" ,ulSwitch ) ;
        fprintf( ofp , "%d\n" , dlRunTime) ;
        fprintf( ofp , "%d\n" , slSlave_ReadBet( )) ;
        fprintf( ofp , "%d\n" , mGame_ReadMinBet( )) ;
        fprintf( ofp , "%d\n" , mGame_ReadMaxBet( )) ; 
        fprintf( ofp , "%d\n" , slSlave_ReadLine( )) ;            
        fprintf( ofp , "%d\n" , mGame_ReadGameRateLevel( )) ;
        fprintf( ofp , "%d\n" , mGame_ReadRateModeLevel( )) ;
        fprintf( ofp , "%d\n" , mGame_ReadWupRateLevel( )) ;
        fprintf( ofp , "%d\n" , ulRecCycle) ;       
        fprintf( ofp , "%d\n" , ulWupCondi1) ; 
        fprintf( ofp , "%d\n" , ulWupCondi2) ; 
        /*
		for( slLoop = 0 ; slLoop < DEF_TEST_SYMBOL_MAX ; slLoop ++ )
		{
        	fprintf( ofp , "%d\t" , uwGameRandom[slLoop] ) ;
        }
        */
        fprintf( ofp , "\n" ) ;    
        fclose( ofp ) ;    
    }
	

	/*    
    ofp = fopen( "txt/Datainfo.txt" , "wb" ) ;
    if( ofp )
    {           
       
		for( slLoop = 0 ; slLoop < 128 ; slLoop ++ )
		{
			fprintf( ofp ,"%d\t," , ulSymbolData[slLoop] ) ;	
        }
        fprintf( ofp , "\n" ) ;
        fclose( ofp ) ;
    }    
    ofp = fopen( "txt/Symbolinfo.txt" , "wb" ) ;
    if( ofp )
    {    
     
		for( slLoop = 0 ; slLoop < 128 ; slLoop ++ )
		{
			fprintf( ofp ,"%s," , Symbol[ulSymbolData[slLoop]] ) ;
				
        }
        fprintf( ofp , "\n" ) ;
        fclose( ofp ) ;
    }
    */
}

			



void vFastTest_OpenOutputRecord_all( void )
{
	FILE *ofp ;
	SLONG slLoop ;
	DLONG dlPlay,dlWin; 
	ofp = fopen( "txt/all.txt" , "wb" ) ;
	if ( ofp )
	{ 	
		fprintf( ofp , "总玩次数:\t" ) ;		
		fprintf( ofp , "%ld\t" , ulPlayTimes  ) ;
		fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTIMES ) ) ;
		fprintf( ofp , "%ld\n" , stcChance.ulPlayTimes ) ;
		
		fprintf( ofp , "总赢次数:\t" ) ;		
		fprintf( ofp , "%ld\t" ,  ulWinTimes ) ;
		fprintf( ofp , "%I64d\n" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTIMES ) ) ;
		
		fprintf( ofp , "总押分:\t" ) ;	
		fprintf( ofp , "%I64d\t" , dlPlayTotal) ;
		dlPlay = dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTOTAL );
		
		fprintf( ofp , "%I64d\n" , dlPlay ) ;
		
		fprintf( ofp , "总赢分:\t" ) ;	
		fprintf( ofp , "%I64d\t" , dlWinTotal) ;
		dlWin = dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL );
		fprintf( ofp , "%I64d\n" , dlWin ) ;
		
		fprintf( ofp , "千分率:\t" ) ;	
		if(dlWin&&dlPlay)
		{
			fprintf( ofp , "%ld\n" ,(ULONG)(dlWin*1000/dlPlay)) ;
		}	
		else
		{
			fprintf( ofp , "%ld\n" ,0) ;
		}			
						
		fprintf( ofp , "主游戏Buffer\n" ) ; 
		for ( slLoop = 0 ; slLoop < DEF_CHANCE_BUFMAX ; slLoop ++ )
		{
			fprintf( ofp ,"%s:\t" , Buffer[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.Buffer[slLoop].slValue ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulRate[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulWinTimes[slLoop] ) ;
			fprintf( ofp ,"%ld\n" , stcChance.ulBufferGate[slLoop] ) ;
		}
		fprintf( ofp ,"%ld\n" , stcChance.slReturnBufValue ) ;

		for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
		{
			fprintf( ofp ,"%ld\t" , stcChance.VirtualBuffer[slLoop].slValue ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulVirtualBufGate[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulVirtualBufTopValue[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.SpecBuffer[slLoop].slValue ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulSpecValue[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulRecVirAsnTimes[slLoop][0] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulRecVirAsnTimes[slLoop][1] ) ;
			fprintf( ofp ,"%ld\n" , stcChance.ulRecVirAsnTimes[slLoop][2] ) ;
		}

		for ( slLoop = 0 ; slLoop < 10 ; slLoop ++ )
		{
			fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_X3+slLoop ) ) ;
			fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_X4+slLoop ) ) ;
			fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_X5+slLoop ) ) ;
			fprintf( ofp , "%I64d\n" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM00_ALL+slLoop ) ) ;
		}
		for ( slLoop = 0 ; slLoop < 3 ; slLoop ++ )
		{
			fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM_WILD_X3+slLoop*3 ) ) ;
			fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM_WILD_X4+slLoop*3 ) ) ;
			fprintf( ofp , "%I64d\n" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_REC_SYM_WILD_X5+slLoop*3 ) ) ;
		}
		for ( slLoop = 0 ; slLoop < DEF_SYMBOL_MAX ; slLoop ++ )
		{
			fprintf( ofp , "%ld\t" , stcChance.ulRecReelSymTimes[slLoop] ) ;
		}
		fprintf( ofp ,"\n" , 0 ) ;
		fprintf( ofp ,"%ld\t%ld\t%ld\t" , stcChance.ulRecMainAsn[0] , stcChance.ulRecMainAsn[1],stcChance.ulRecMainAsn[2] ) ;		
		fprintf( ofp ,"\n" , 0  ) ;
		fprintf( ofp , "%ld\n" , stcChance.ulReturnMainValue ) ;			
	/*
		fprintf( ofp , "第一次开牌奖项次数纪录\n" ) ;
		for ( slLoop = 0 ; slLoop < DEF_ITEM_MAX ; slLoop ++ )
		{
			fprintf( ofp ,"%s:\t" , Awards[slLoop] ) ;			
			fprintf( ofp ,"%ld\n   " , stcChance.ulRecFstGiftTimes[slLoop] ) ;
		}

		fprintf( ofp , "第二次开牌奖项次数纪录\n" ) ;
		for ( slLoop = 0 ; slLoop < DEF_ITEM_MAX ; slLoop ++ )
		{
			fprintf( ofp ,"%s:\t" , Awards[slLoop] ) ;			
			fprintf( ofp ,"%ld\n" , stcChance.ulRecGiftTimes[slLoop] ) ;			
		}
		fprintf( ofp , "强制补一对次数记录:\t" ) ;	
		fprintf( ofp , "%ld \n" ,ulAsnFillTimes) ;
	*/			

		

	fclose( ofp ) ;		
	}
	
}

void vFastWup_Test( ULONG ulWin )	
{
	ulWupPlayTimes = 0;//
	switch( ulWupCondi2 )
	{
		case 0:
			vSlave_WupWinSet(ulWin*2);
			break ;	
		case 2:
			vSlave_WupWinSet(ulWin/2);
			break ;		
		default :	
			vSlave_WupWinSet(ulWin);	
			break ;	
	}
	if(ulWupCondi1) //是否是要比倍
	{
		while(1)
		{
			slWupBet = slSlave_WupWinRead();
			ulWupPlayTimes++;
			if(ulRand_ReadMod(2))
			{
				stcWupChance.ubGuess = DEF_WUP_GUESS_BIG ;	
			}	
			else
			{
				stcWupChance.ubGuess = DEF_WUP_GUESS_SMALL ;	
			}				
			vWupChance_DealProcess();
			if(stcWupChance.ubData != DEF_CHANCE_WUP_NULL)
			{
				vWupChance_BetProcess();//不需要把该局押注纳入计算	
				vGameCheck_WupWinRule();
				vWupChance_WinProcess(slSlave_WupWinRead());//不需要把该局押注纳入计算	
			}	
			if((ulPlayTimes%ulRecCycle)==0)
			{
				#ifdef DEF_OPEN_PCFILEOUT
				vFastWupTest_OpenOutputRecord_one( );
				#endif			
			}
			
			if(slSlave_WupWinRead())
			{
				if( slSlave_WupWinRead() >= mGame_ReadWupLimitTop( ) )	
				{			
					break ;	
				}
				if(ulWupCondi1==1)
				{
					break ;		
				}	
				else if(ulWupCondi1==2)
				{
					if(ulWupPlayTimes>=2)
					{
						break ;		
					}						
				}	
				else if(ulWupCondi1==3)
				{
					if(ulWupPlayTimes>=3)
					{
						break ;		
					}						
				}
				else if(ulWupCondi1==4)
				{
					if(ulWupPlayTimes>=4)
					{
						break ;		
					}						
				}
				
			}	
			else
			{
				break ;					
			}				
			
			ulWin = slSlave_WupWinRead();
			switch ( stcWupChance.ubData )
			{
				case DEF_CHANCE_WUP_WIN_X1:
				case DEF_CHANCE_WUP_WIN_X2:
				case DEF_CHANCE_WUP_WIN_X3:
				case DEF_CHANCE_WUP_WIN_X4:
					switch( ulWupCondi2 )
					{
						case 0:
							vSlave_WupWinSet(ulWin*2);
							break ;	
						case 2:
							vSlave_WupWinSet(ulWin/2);
							break ;	
					}					
					break ;			
			}
			
			
		}	
	}	
	
		
	
}
	
SLONG slFastTest_Test( void )
{

	//ULONG i, ulTemp,slLoop,ulRate,ulValue; 
	ULONG ulValue,ulTemp; 
	ulPlayTimes = 0 ;
	ulWinTimes  = 0 ;
	dlPlayTotal = 0 ;
	dlWinTotal  = 0 ;
	//ulAsnFillTimes = 0;
	//ulLoseTimes = 0;
	ulWupPlayTimes = 0;
	
	slFeverWin = 0 ;
	slFreeWin = 0 ;
	
	// Reset
	{
//		vMaster_Reset( ) ;
//		vSlave_Reset( ) ;
//		vChance_Reset( ) ;
	}
	
	vFastTest_OpenInputInfo( );	
	vFastTest_OutInfo();	
	if(slSlave_ReadBet()< mGame_ReadMinBet( ))
	{
		vSlave_BetSet(mGame_ReadMinBet( )) ;
	}	
	if(slSlave_ReadBet()> mGame_ReadMaxBet( ))
	{
		vSlave_BetSet(mGame_ReadMaxBet( )) ;
	
	}
	if(ulSwitch==0)
	{
		return ( 0 ) ;	
	}		
	// Init
	{
		vScroll_Reset( ) ;
		vChance_Update( 0 ) ;
	}
		
	while( stcChance.ulPlayTimes < dlRunTime )
	{		
		slFeverWin = 0 ;
		slFreeWin = 0 ;

		if(stcGameInfo.ulFreeNowLife)
		{
		}
		else
		{
			ulPlayTimes ++ ;
			dlPlayTotal += slSlave_ReadTotalBet( ) ;
	    	vSlave_WinSet( 0 ) ;
	    	ulTemp = 0;
		}
		
		// vMaster_Game_Chance
		{
		    vChance_GameProcess( );
		    ulValue = slSlave_ReadTotalBet();
		    stcGameInfo.ulBonusValue =80*ulValue + ulRand_ReadMod(220*ulValue);	
		    
    		vScroll_StartAllRun() ;
		}
    	vReel_AllNowStopRun();
		// vMaster_Game_Check
		{
			vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
			ulValue = slGameCheck_GameWinRule( (GAMEINFO*)&stcGameInfo );
			vSlave_WinAdd(ulValue);
			vChance_WinProcess(ulValue);
			stcGameInfo.ulBonusWin = 0;
		    if(stcGameInfo.ulBonusType==3)
			{
				stcGameInfo.ulBonusWin =  stcGameInfo.ulBonusValue;	
			}	
			if(stcGameInfo.ulBonusType==2)
			{
				stcGameInfo.ulBonusWin =  stcGameInfo.ulBonusValue/5;	
			}	
			if(stcGameInfo.ulBonusType==1)
			{
				stcGameInfo.ulBonusWin =  stcGameInfo.ulBonusValue/10;	
			}	
		}
		
		if(stcGameInfo.ulBonusType)
	    {    		    	
	    	if(stcChance.ulActBuf  == DEF_CHANCE_BUF_MAIN)
	    	{
	    		vFastTest_AssertOut( __LINE__ ) ;
	    	}
			vSlave_WinAdd(stcGameInfo.ulBonusWin) ;     
	    	vChance_WinBonusProcess( ) ;
			//vSlave_WinAdd(stcGameInfo.ulBonusWin);
	    }	
		if( stcGameInfo.ulFeverSetLife )
	    {    	
	    	if(stcGameInfo.ulFreeSetLife)
	    	{
	    		vFastTest_AssertOut( __LINE__ ) ;
	    	}
	    	if(stcChance.ulActBuf  == DEF_CHANCE_BUF_MAIN)
	    	{
	    		vFastTest_AssertOut( __LINE__ ) ;
	    	}
	    	
	    	vScroll_FeverReset( ) ;
	    	while(stcGameInfo.ulFeverNowLife)
	    	{
		    	vChance_FeverProcess( );
		    	vScroll_FeverStartAllRun( ) ;
		    	vScroll_FeverAllStop( ) ;
		    	
		    	stcFeverChance.ubData = slGameCheck_FeverValue();
		    	if(stcFeverChance.ubData< 7)
		    	{
			    	if(stcFeverChance.ubData==6)
			    	{
			    		stcGameInfo.ulFeverNowLife--;
			    	}
			    	else
			    	{
			    		stcFeverChance.ulWin = ulFeverGameWinOdds[stcFeverChance.ubData-1]*slSlave_ReadTotalBet();	    		
						stcChance.ulFeverTotalWin += stcFeverChance.ulWin ;
			    		vSlave_WinAdd(stcFeverChance.ulWin);
			    	}			    		
		    	}	
		    }	
		    vChance_WinFeverProcess( ) ;
	    }	
	    if(stcGameInfo.ulFreeSetLife)
	    {      
	    	if(stcChance.ulActBuf  == DEF_CHANCE_BUF_MAIN)
	    	{
	    		vFastTest_AssertOut( __LINE__ ) ;
	    	}

	    	/*	
			if((ulPlayTimes%ulRecCycle)==0)
			{
				vFastTest_OpenOutputRecord_one( );
			}
			*/
			stcGameInfo.ulFreeNowLife  += stcGameInfo.ulFreeSetLife ; 	
		}	
		
		if( slSlave_WinRead( ) )
		{
			ulWinTimes ++ ; 
			dlWinTotal += slSlave_WinRead( ) ;
		}

		if(stcGameInfo.ulFreeNowLife)
		{
			if(stcGameInfo.ulFreeType)
			{
				ulTemp += stcGameInfo.ulFreeType;
			}	
			stcGameInfo.ulFreeNowLife--;	
			if(stcGameInfo.ulFreeNowLife==0)
			{
				stcGameInfo.ulFreeType = ulTemp;
				stcChance.ulActBuf = DEF_CHANCE_BUF_FREE;
				
			}			
		}
		if(stcGameInfo.ulFreeNowLife) continue ;					
		if((ulPlayTimes%ulRecCycle)==0)
		{
			#ifdef DEF_OPEN_PCFILEOUT
			vFastTest_OpenOutputRecord_one( );
			#endif			
		}
		if(slSlave_WinRead( ))
		{
			vFastWup_Test(slSlave_WinRead( ));		
		}
	}
	vFastTest_OpenOutputRecord_all( );
	vFastWupTest_OpenOutputRecord_all( );		
	return ( 1 ) ;	
}



#endif

#ifdef DEF_OPEN_PCFILEOUT

void vFastTest_FileOut_Iinit( void )
{
	FILE *ofp ;

	ofp = fopen( "txt/one.txt" , "wb" ) ;
	if ( ofp )
	{ 	
        fclose( ofp ) ;
    }
    ofp = fopen( "txt/wupone.txt" , "wb" ) ;
	if ( ofp )
	{ 	
        fclose( ofp ) ;
    }
}

void vFastTest_OpenOutputRecord_one( void )
{
	FILE *ofp ;
	SLONG slLoop ;

	ofp = fopen( "txt/one.txt" , "a+" ) ;
	if ( ofp )
	{ 			
		//fprintf( ofp , "%ld\t" , ulPlayTimes  ) ;
		fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTIMES ) ) ;
		//fprintf( ofp , "%ld\t" , stcGameInfo.ulFreeNowLife ) ;

		//fprintf( ofp , "%ld\t" , slSlave_ReadBet( ) ) ;
		//fprintf( ofp , "%ld\t" , slSlave_ReadLine( ) ) ;
		
	    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
	    {
			fprintf( ofp ,"%d\t" , ubScroll_GetData( slLoop ) ) ;
    	}
    	
   		fprintf( ofp ,"%d\t" , stcGameInfo.ulAllSameOdds ) ;
	    for ( slLoop = 0 ; slLoop < 9 ; slLoop ++ )
	    {
    		fprintf( ofp ,"%d\t" , stcGameInfo.stcLine[slLoop].ulOdds[0]+stcGameInfo.stcLine[slLoop].ulOdds[1] ) ;
    	}
    	
    	fprintf( ofp ,"%d\t" , stcGameInfo.ulBonusType ) ;
    	fprintf( ofp ,"%d\t" , stcGameInfo.ulFeverSetLife ) ;
    	fprintf( ofp ,"%d\t" , stcGameInfo.ulFreeType ) ;

    	fprintf( ofp ,"%ld\t" , stcGameInfo.ulBonusWin ) ;
    	fprintf( ofp ,"%ld\t" , stcChance.ulFeverTotalWin ) ;
    	fprintf( ofp ,"%ld\t" , stcChance.ulFreeTotalWin ) ;
    	
		fprintf( ofp , "XXXX\t" ) ;
    	
		fprintf( ofp , "%ld\t" , slSlave_WinRead( )  ) ;
		fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTOTAL ) ) ;
		fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL ) ) ;
		fprintf( ofp , "%I64d\t" , dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTIMES ) ) ;

		fprintf( ofp , "%s\t" , Buffer[stcChance.ulActBuf] ) ;
		fprintf( ofp , "%ld\t" , stcChance.ulBase ) ;
		
		for ( slLoop = 0 ; slLoop < DEF_CHANCE_BUFMAX ; slLoop ++ )
		{
			fprintf( ofp ,"[\t") ;
			fprintf( ofp ,"%ld\t" , stcChance.Buffer[slLoop].slValue ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulRate[slLoop] ) ;
			fprintf( ofp , "%ld\t" , stcChance.ulBufferGate[slLoop] ) ;
			fprintf( ofp ,"]\t") ;
		}	
		
		fprintf( ofp ,"%ld\t" , stcChance.slReturnBufValue ) ;
		
		for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
		{
			fprintf( ofp ,"[\t") ;

			fprintf( ofp ,"%ld\t" , stcChance.VirtualBuffer[slLoop].slValue ) ;
			fprintf( ofp ,"%lx\t" , stcChance.ulVirtualBufAsnGift[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulVirtualBufTopValue[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulVirtualRate[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulVirtualBufGate[slLoop] ) ;
			
			fprintf( ofp ,"%ld\t" , stcChance.SpecBuffer[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulSpecRate[slLoop] ) ;
			fprintf( ofp ,"%ld\t" , stcChance.ulSpecValue[slLoop] ) ;

			fprintf( ofp ,"]\t") ;
		}
		
		fprintf( ofp ,"%ld\t" , stcChance.ulReturnMainValue ) ;
		fprintf( ofp ,"%ld\t" , stcChance.ReturnSpec.slValue ) ;
		fprintf( ofp ,"%ld\t" , stcChance.ulRecSpecValue[0] ) ;
		fprintf( ofp ,"%ld\t" , stcChance.ulRecSpecValue[1] ) ;
		fprintf( ofp ,"%ld\t" , stcChance.ulRecSpecValue[2] ) ;	
		fprintf( ofp ,"%ld\t" , stcChance.ulRecMainAsn[0] ) ;	
		fprintf( ofp ,"%ld\t" , stcChance.ulRecMainAsn[1] ) ;	
		fprintf( ofp ,"%ld\t" , stcChance.ulRecMainAsn[2] ) ;	
//		for ( slLoop = 0 ; slLoop < 51 ; slLoop ++ )
//		{
//			fprintf( ofp ,"%ld\t" , stcChance.ulRecBufArray[1][slLoop] ) ;
//			
//		}
		fprintf( ofp , "\n" ) ;	
		fclose( ofp ) ; 
		
	}
	
}



void vFastWupTest_OpenOutputRecord_one( void )
{
	FILE *ofp ;

	ofp = fopen( "txt/wupone.txt" , "a+" ) ;
	if ( ofp )
	{ 			
		
		fprintf( ofp , "%ld\t" , ulPlayTimes  ) ;
		fprintf( ofp , "%10ld\t" , stcWupChance.ulPlayTimes  ) ;	
		fprintf( ofp , "%ld\t" , ulWupPlayTimes	 ) ;
		
		fprintf( ofp ,"%10ld\t"  , slWupBet ) ;	
		fprintf( ofp ,"%10ld\t"  , slSlave_WupWinRead()) ;	
		
		fprintf( ofp , "%10I64d\t" , dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_PLAYTOTAL)) ;	
		
		fprintf( ofp , "%10I64d\t" , dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_WINTOTAL)) ;
		fprintf( ofp , "%ld\t" , stcChance.ulBase ) ;
		fprintf( ofp ,"%10ld\t" , stcWupChance.Buffer.slValue ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecAsnValue[0] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecAsnTimes[0] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecAsnValue[1] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecAsnTimes[1] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecTimes[0] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecTimes[1] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecTimes[2] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecTimes[3] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecTimes[4] ) ;
		fprintf( ofp , "%ld\t" , stcWupChance.ulRecTimes[5] ) ;
		fprintf( ofp , "\n" ) ;		
		fclose( ofp ) ;	
	}
	 
}


void vFastWupTest_OpenOutputRecord_all( void )
{
	FILE *ofp ;
    DLONG dlPlay,dlWin; 
	

	ofp = fopen( "txt/wupall.txt" , "wb" ) ;
	if ( ofp )
	{ 	
		fprintf( ofp , "总玩次数:\t" ) ;		
		fprintf( ofp , "%ld\n" , stcWupChance.ulPlayTimes  ) ;

		dlPlay = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_PLAYTOTAL);
		fprintf( ofp , "总押分:\t" ) ;	
		fprintf( ofp , "%I64d\n" , dlPlay) ;
		dlWin = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_WUP_WINTOTAL);
		
		fprintf( ofp , "总赢分:\t" ) ;	
		fprintf( ofp , "%I64d\n" , dlWin) ;
		
		fprintf( ofp , "千分率:\t" ) ;	
		if(dlWin)
		{
			fprintf( ofp , "%ld\n" ,(ULONG)(dlWin*1000/dlPlay)) ;	
		}	
		else
		{
			fprintf( ofp , "%ld\n" ,0 ) ;		
		}			
				
		fprintf( ofp , "Buffer\n" ) ; 
		fprintf( ofp ,"%10ld\t" , stcWupChance.Buffer.slValue ) ;
		fprintf( ofp , "\n" ) ;	
		fclose( ofp ) ;
		
	}
	
}	



#endif
