#define DEF_MASTER_C
#include "../../h/common.h"
#define FILE_NAME "MASTER.C"

UBYTE p_ubVersionMemString[32] ;
ULONG p_ulVersionValue ;
// 押注加快
ULONG ulMainGameBetTouch ;
ULONG ulMainGameBetAddSpeed ;
UBYTE ubMainGameBetFlag;
ULONG ubMainGameBetNoTouch;
UBYTE ubGameShowState ;
ULONG ulMainGameBetCount ;
ULONG ulMainGameBetDelay ;
UBYTE ubMasterHelpState; //帮助状态
UBYTE ubMasterLineState; //选线状态
ULONG ulMasterHelpCount ;//帮助计数
ULONG ulMasterLineCount ;//选线计数
UBYTE ubMainStopFlag[5];//保一到保五
ULONG ulMainDemoCount;//统计进入DEMO数据

#define mSetMasterState(mState)	{stcMaster.ulState=mState;stcMaster.ulIndex=0;stcMaster.ulCount=0;}

 void vMaster_Reset( void )
{
    vMemory_Set((UBYTE *)&stcMaster , 0x00 , sizeof(stcMaster)) ;
    mMainGame_NeedReflashScr();
	mSetMasterState( PROC_MASTER_GAME_INIT );
    
}



void vMaster_Run( void ) { stcMaster.ubRunFlag = 1 ; }
void vMaster_Stop( void ) { stcMaster.ubRunFlag = 0 ; }
ULONG ulMaster_IsRun( void ) { return( stcMaster.ubRunFlag ) ; }
ULONG ulMaster_GetStage( void ) { return( stcMaster.ulState ) ; }

 void vMaster_ShowState( void )
{
	ULONG	animno ;
    char  cStr[128] ;

	// 显示一些需要及时更新的测试数据
	
	animno = DEF_ANIMNO_DEBUG ;
    vSprint( cStr , STR" %l %l %l %l " , stcMaster.ulState , stcMaster.ulIndex , stcMaster.ulCount , ulTimer_Read( DEF_GAMETIMER_REC_GAMETIME ) ) ;
    vPcVideo2D_Img_ShowString( animno , mMacro_Img( DEF_FONT_ASCII_000 ) , 900 , 0 , DEF_PCVIDEO2D_ZOBASE+animno , DEF_RED , 16 , cStr ) ;
     	  
#ifdef DEF_USE_IOPCI    
    //animno ++ ;
    //vSprint( cStr , STR" %l %l " , ulKey_ReadAccessTime( KEY_PCI_START ) , ulKey_ReadAccessTime( KEY_PCI_BET )  ) ;
    //vPcVideo2D_Img_ShowString( animno , mMacro_Img( DEF_FONT_ASCII_000 ) , 900 , 30 , DEF_PCVIDEO2D_ZOBASE+animno , DEF_RED , 16 , cStr ) ;
#endif
    
}


ULONG ulMaster_GetWupKey( void )
{
	ULONG ulRetKey ;
	ULONG ulValue;	

	ulRetKey = 0 ;	
	if( mGame_ReadWupLimitTop( ) )
	{
		if(stcMaster.ulSceneState==3)
		{
			ulValue =slSlave_WupWinRead();	
		}	
		else
		{
			ulValue = slSlave_WinRead( );		
		}	
		
		if (( ulRetKey == 0 )&&( ulKey_Touch( KEY_PCI_DWUP) ) )
		//if (( ulRetKey == 0 )&&( ulKey_PushRange( KEY_PCI_DWUP, 3 , 8 ) ) )
		{
			if(ulValue <  (mGame_ReadWupLimitTop( )/2))
			{
				if( ulCredit_Read( DEF_GAME_ONLY_PLAY ) >= ulValue )
				{
					ulRetKey = KEY_PCI_DWUP ;	
				}	
				else
				{
					vShow_MessAlarm(DEF_MASTERSHOW_MSG_036);
				}									
			}	
			else
			{
				vShow_MessAlarm(DEF_MASTERSHOW_MSG_039);
			}	
				
		}
		if (( ulRetKey == 0 )&&( ulKey_Touch( KEY_PCI_WUP ) ) )
		//if (( ulRetKey == 0 )&&( ulKey_PushRange( KEY_PCI_WUP , 3 , 8 ) ) )
		{
			if( ulValue < mGame_ReadWupLimitTop( ) )
			{
				ulRetKey = KEY_PCI_WUP ;	
			}
			else
			{
				vShow_MessAlarm(DEF_MASTERSHOW_MSG_038);
			}	
		}
		if (( ulRetKey == 0 )&&( ulKey_Touch(KEY_PCI_HWUP) ) )
		//if (( ulRetKey == 0 )&&( ulKey_PushRange( KEY_PCI_HWUP, 3 , 8 ) ) )
		{
			if(ulValue <  (mGame_ReadWupLimitTop( )*2))
			{
				ulRetKey = KEY_PCI_HWUP ;							
			}
			else
			{
				vShow_MessAlarm(DEF_MASTERSHOW_MSG_038);
			}	
			
		}
	}	
	if (( ulRetKey == 0 )&&(( ulKey_Touch( KEY_PCI_TAKE ) )||( ulKey_Touch( KEY_PCI_START ) )) )
	{
		ulRetKey = KEY_PCI_TAKE ;	
	}
	
	#ifdef DEF_TEST_AUTOPLAY
	if( ulRetKey == 0 )
	{
		#ifdef DEF_TEST_AUTOPLAY_WUP
		if ( ulKey_Touch( KEY_PCI_97_TEST ) )
		{
			
			if( mGame_ReadWupLimitTop( ) )
			{	// 没有开启比倍游戏
				ulRetKey = KEY_PCI_WUP ;
			}
			else
			{
				ulRetKey = KEY_PCI_TAKE ;	
			}	
		}	
		#else
		#ifdef DEF_TEST_ALWAYS_AUTO_2
		if ( ubAutoPlay2_isRun )
		#else
		if ( ulKey_Touch( KEY_PCI_97_TEST ) )
		#endif	
		{
			ulRetKey = KEY_PCI_TAKE ;
		}			
		#endif
	}
	#endif
	
	return ulRetKey ;
}


void vMaster_GameInitial( void )
{	
	mSetMasterState( PROC_MASTER_GAME_INIT );
}



ULONG ulMaster_CheckOffLine( void )
{
	#ifdef DEF_USE_VGAME_UART_SLAVE
	if( !ubUartCmdSlaveOnLine[0] )
	{
		// 未连上线的情况下，不能进入后台
		// 可以设置机台号
		vShowRec_ShowWaitLink( 1 ) ;
		
		#ifdef DEF_USE_DIPSW_SET_SLAVEID
		{
			vDipSw_Initial( ) ;
			vUart0_SetMyselfID(DEF_UARTCMD_SLAVE_ID+mGame_ReadLinkSlaveID()-1) ;
		}
		#else
		{
			ULONG 	ulKey ;
			
			ulKey = 0 ;
			if ((ulKey_Push(KEY_PCI_STOP1))||(ulKey_Push(KEY_1))) 		ulKey = 1 ;
			if ((ulKey_Push(KEY_PCI_STOP2))||(ulKey_Push(KEY_2))) 		ulKey = 2 ;
			if ((ulKey_Push(KEY_PCI_BIG))||(ulKey_Push(KEY_ADD))) 		ulKey = 1 ;
			if ((ulKey_Push(KEY_PCI_SMALL))||(ulKey_Push(KEY_SUB)))		ulKey = 2 ;
			
			if( ulKey )
			{
				vAdjustSlaveIDSel_Setup( ) ;
				if( ulKey == 1 )
				{
					vAdjustSlaveIDSel_IncLoop( ) ;	
				}
				else
				{
					vAdjustSlaveIDSel_DecLoop( ) ;	
				}
				vAdjustSlaveIDSel_UpDate( ) ;
				vUart0_SetMyselfID(DEF_UARTCMD_SLAVE_ID+mGame_ReadLinkSlaveID()-1) ;
			}
		}
		#endif
		
		return 1 ;
	}
	else
	{
		vShowRec_ShowWaitLink( 0 ) ;
	}
	#endif
	
	return 0 ;
}


// [流程] 游戏变数初始
void vMaster_Game_Init( void )
{
	ulMainDemoCount = 0;
	ulShowLibDWupCount = 0;//清除双比倍计数
	vPlaySound_Clean();
	if(stcGameInfo.ulFreeNowLife==0)  
    {
    	vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);
    }	
    else
    {
    	vPlaySound_BG(DEF_WAV_MUSIC_FREEGAME_03,DEF_SOUND_VOL_TINY,DEF_SOUND_CH_BG);	    	
    }	
    mSetMasterState( PROC_MASTER_GAME_SCR) ;
   
}

// [流程] 游戏画面
void vMaster_Game_Scr( void )
{
	if(stcMaster.ulCount==0)
	{
		if(slSlave_ReadLastLine()==0)
	    {
	    	vSlave_SetLastLine(9);
	    	vSlave_SetLine(9);    	
	    }
		if(stcGameInfo.ulFreeNowLife==0)  
	    {    	
	    	vSlave_WinSet( 0 ) ;
	    	vSlave_BetSet(slSlave_ReadLastBet());
	    }		
	    if ( ulMainGameReflashScreen == 0 )
	    {
	    	if(stcGameInfo.ulFreeNowLife)
	    	{
	    		vMasterShow_FreeGame( );
	    	}
	    	else
	    	{
	    		vMasterShow_BaseGame();   
	    	}		 
	    	   
	    	
	    	vScroll_LoadData( );  
	        vScroll_RefreshShowScr( ) ;        
	        ulMainGameReflashScreen = 1 ;
	    }
		ubMasterHelpState = 0;
		if(slSlave_ReadBet()>mGame_ReadMaxBet( )) //防止修改最大押分后,押分超过
    	{
    		vSlave_BetSet(mGame_ReadMaxBet( ));
    		vSlave_UpDateLastBet( );
    	}
    	else if(slSlave_ReadBet()< mGame_ReadMinBet( ))
		{
			vSlave_BetSet(mGame_ReadMinBet( )) ;
			vSlave_UpDateLastBet( );
		}
		
	}	
	if( ulCredit_Read( DEF_GAME_ONLY_PLAY ) < mGame_ReadSystemLimit( ) )
	{		
		mSetMasterState( PROC_MASTER_GAME_BET) ;  			
		return ;  		
	}		   
	stcMaster.ulCount++;	
	

}

#ifdef DEF_DEFINE_AUTO_PLAY
extern ULONG ulCreditInForNet ;
#endif





// [流程] 等待押注
void vMaster_Game_Bet( void )
{	
	ULONG ulTime1,ulTime2,ulTime3,ulTime4;

	#ifdef DEF_USE_VGAME_UART_SLAVE
	if( ulMaster_CheckOffLine( ) )	{ return ; }
	#endif
	
    // 盚钵盽篈 產ぃ祇甮
    #ifdef DEF_GTRULE_GTHS
    if( ulGTHS_GetMode() )
    {
        if( ulGTHS_GetStatus() != DEF_GTHS_STATUS_ISOK )    { return ; }
    }
    else
    { 
        if( ulGTHS_GetStatus() == DEF_GTHS_STATUS_ZERO )    { return ; }
    }
    #endif
    #ifdef DEF_GTRULE_GTVG
    if( ulGTVG_GetMode() )
    {
        if( ulGTVG_GetStatus() != DEF_GTVG_STATUS_ISOK )    { return ; }
    }
    else
    { 
        if( ulGTVG_GetStatus() == DEF_GTVG_STATUS_ZERO )    { return ; }
    }
    #endif
    
    #ifdef DEF_M100XX_ENABLE_SHUTDOWN
    if( ulShutDown_IsHalt() )	{ return ; }
	#endif
	#ifdef DEF_TEST_ALWAYS_AUTO_2
	if ( ubAutoPlay2_isRun )
	{
		if( stcMaster.ulAutoKeyState == 0 )
		{
			stcMaster.ulAutoKeyState = 2 ;
		}
	}
	#endif
	
	stcMaster.ulCount++;	
	vShowLib_RandomExtraMoney(stcMaster.ulCount);
	if(stcMaster.ulSceneState)
	{
		#ifdef DEF_TEST_AUTOPLAY
		if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(stcMaster.ulAutoKeyState&&(stcMaster.ulCount>=10))||ulKey_Touch( KEY_PCI_START))
		#else
		if((stcMaster.ulAutoKeyState &&(stcMaster.ulCount>=10))||ulKey_Touch( KEY_PCI_START)) //自动
		#endif	
		{
			mSetMasterState( PROC_MASTER_GAME_START) ;
	    	return ;
		}
		
	}
	else
	{
		#ifdef DEF_TEST_AUTOPLAY
		if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(stcMaster.ulAutoKeyState&&(stcMaster.ulCount>=10)))
		#else
		if(stcMaster.ulAutoKeyState &&(stcMaster.ulCount>=10)) //自动
		#endif	
		{
			#ifdef DEF_TEST_AUTOPLAY_LINE
			#ifdef DEF_TEST_ALWAYS_AUTO_2
			if ( ubAutoPlay2_isRun )
			#else
			if ( ulKey_Touch( KEY_PCI_97_TEST ) )
			#endif	
			{
				if( slSlave_ReadLine( ) != 9 )
				{
					vSlave_SetLine( 9 ) ;
				}
			}
			#endif
			
			if( slSlave_BetStartGame() )
	        {
	        	vSlave_UpDateLastBet() ;
	            mSetMasterState( PROC_MASTER_GAME_START) ;
	            return ;
	        }			
		}	
		if(stcMaster.ulAutoKeyState==0)
		{
			ulTime1 = 15;  
			ulTime2 = 5;
			ulTime3 = 1;
			ulTime4 = 1;
			if ( ulKey_Touch( KEY_PCI_BET ) )
	    	{
	    		ulMainGameBetTouch ++ ;
	    		ulMainGameBetAddSpeed = 1;	
	    		if( ulMainGameBetTouch == 1)
	    		{
	    			ubMainGameBetFlag = 1;	    			
	    		}	
	    		else if(ulMainGameBetTouch >= (ulTime1 + ulTime2*20 + ulTime3*180+ulTime4))
	    		{
	    			ubMainGameBetFlag = 1;	 
	    			ulMainGameBetTouch = ulTime1 + ulTime2*20 + ulTime3*180;
	    			ulMainGameBetAddSpeed = 2;		
	    			    				
	    			
	    		}    		
	    		else if(ulMainGameBetTouch >= (ulTime1 + ulTime2*20 + ulTime3))
	    		{
	    			ubMainGameBetFlag = 1;	     			  			
	    			
	    		}	
	    		else if(ulMainGameBetTouch >= ulTime1)
	    		{
	    			if(((ulMainGameBetTouch-ulTime1) % ulTime2) ==0)
	    			{
	    				ubMainGameBetFlag = 1;	    					
	    			}	
	    			else
	    			{
	    				ubMainGameBetFlag = 0;			
	    			}	
	    		}	
	    		else
	    		{
	    			ubMainGameBetFlag = 0;		
	    		}	   		
	    		
	    	}
	    	else
	    	{
	    		ubMainGameBetNoTouch++;
				if(ubMainGameBetNoTouch>=3)
				{
					ulMainGameBetTouch = 0 ;	
					
				}	 
				ubMainGameBetFlag = 0;	
				
	    	}		
			if (ubMainGameBetFlag)
			{
				ubMainGameBetFlag = 0;
				ubMainGameBetNoTouch = 0;	
				switch (slSlave_AddBetProcess( ulMainGameBetAddSpeed,ulMainGameBetTouch))
				{				
					case 1  :								
	//					vSlave_UpDateLastBet() ;
	//					mSetMasterState( PROC_MASTER_GAME_START) ;    
	//					return ;
					case -1 :
					break ;
					default :	
						vPlaySound_Play(DEF_WAV_SOUND_SCORE,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);	
						//while ( ulKey_RePush( KEY_PCI_START , 10 , 3 ) == 0 );			
					break ;	
				}	
		
			}	
			if( ulKey_Push(KEY_PCI_LINE ) )
		    {
		    	vPlaySound_Play( DEF_WAV_SOUND_70,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_4);	
		    	ulMasterLineCount=0;
		    	ubMasterLineState++;
		    	if(ubMasterLineState>1)
		    	{
		    		vSlave_LineProcess() ;
		    		//vSlave_UpDateLastBet() ;      
		    	}		        
		        vShow_DisLine(slSlave_ReadLine());	         
		    }
		    if(ubMasterLineState)
		    {
		    	ulMasterLineCount++;
		    	if(ulMasterLineCount>=300)
		    	{
		    		ubMasterLineState = 0;
		    		ulMasterLineCount=0;	
		    		vShow_CleanLineNum(); 
		    	}	
		    }	
		    
		    if( ulKey_Push(KEY_PCI_HELP) )
		    {
		    	ulMasterHelpCount=0;
		    	ubMasterHelpState++;
		    	ubMasterHelpState %= 6;
		        vShow_HelpUiDis(ubMasterHelpState);       
		    }
		    if(ubMasterHelpState)
		    {
		    	ulMasterHelpCount++;
		    	if(ulMasterHelpCount>=1200)
		    	{
		    		ubMasterHelpState = 0;
		    		ulMasterHelpCount=0;	
		    		vShow_CleanHelpDis( );
		    	}	
		    }	
		    if((ubMasterHelpState||ulMasterHelpCount)==0)
		    {
		    	if ( ulKey_Touch( KEY_PCI_STOP3)&&ulCredit_Read(DEF_GAME_ONLY_PLAY) )
		    	{
		    		mSetMasterState(PROC_MASTER_GAME_LASTDIS) ;	
					return;
		    		
		    	}	
		    	
		    }	
		    if( ulKey_Push(KEY_PCI_MAXBET) )
		    { 
		        if( slBet_MaxBetStartGame() )
		        {
		            vSlave_UpDateLastBet() ;
		            mSetMasterState( PROC_MASTER_GAME_START) ;           
		            return ;
		        }
		    }	    
		    if(stcMaster.ulCount>20)
		    {
		    	if (ulKey_Touch( KEY_PCI_START) )
			    {    	
			        if( slSlave_BetStartGame() )
			        {
			        	vSlave_UpDateLastBet() ;
			            mSetMasterState( PROC_MASTER_GAME_START) ;
			            return ;
			        }
			    }	
		    	
		    }		
			
		}		   	
	}	
}	
//演示程序
void vMaster_Game_Act(void)
{
	ULONG ulTemp;
	if(stcMaster.ulCount==0)
	{
		vPlaySound_BG(DEF_WAV_MUSIC_DEMO_09,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);
	}	
	ulTemp = 0;
	if ( ulCredit_Read( DEF_GAME_ONLY_PLAY) )
	{
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_ACT3_BG16 ,DEF_ANIMNO_ACT3_END) ;
		ulTemp = 1;

	}	
	if( ulKey_Push(KEY_PCI_HELP)&&(ulTemp==0))
    {
    	ulMasterHelpCount=0;
    	ubMasterHelpState++;
    	ubMasterHelpState %= 6;
        vShow_HelpUiDis(ubMasterHelpState);  
        ulTemp = 1;         
     
    }	
    if(ulTemp==0)
    {
    	if(slShowLib_ActEffect(stcMaster.ulCount))
		{
			ulTemp = 1;				
		}
    	
    }	
	
	if(ulTemp)
	{
		vSlave_SetLastLine(9);
	    vSlave_SetLine(9);
	    vSlave_BetSet(mGame_ReadMaxBet( ));
	    vSlave_UpDateLastBet( );
	    vShow_CleanLineNum(); 
	    vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);
		mSetMasterState( PROC_MASTER_GAME_BET) ;	
	}	
	else
	{
		stcMaster.ulCount++;		
	}		
	

}

void vMaster_Game_LastDis(void)
{
	if(stcMaster.ulIndex == 0)
	{
		vShow_CleanLineNum(); 
		vShow_DisWinLine();
		vShow_AllSymbolsHK();
		vSlaveShow_ShowExtraMoney( stcGameInfo.ulBonusValue);  
		stcMaster.ulIndex++; 	
	}	
	if( ulKey_Touch( KEY_PCI_STOP3 )==0 )
	{
		vShow_CleanLineNum();
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_REEL_HK+0 , DEF_ANIMNO_BG_REEL_HK+14 ) ;	
		mSetMasterState( PROC_MASTER_GAME_BET) ;
		return ;
	}		
	
}

// [流程] 开始游戏
void vMaster_Game_Start( void )
{
    // 开始转轮
	ULONG	ulValue ;	
	SLONG slLoop ;
	ubMasterHelpState = 0;	
	ulMasterHelpCount = 0;	
    ubMasterLineState = 0;
    ulMasterLineCount=0;
    vShow_CleanHelpDis( );
    vShow_CleanLineNum(); 
   // vShow_DisNoLineNum();   
    vPlaySound_Play( DEF_WAV_SOUND_01,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_1); 
    ulValue = slSlave_ReadTotalBet();
    stcGameInfo.ulBonusValue =80*ulValue + ulRand_ReadMod(220*ulValue);	
    vSlaveShow_ShowExtraMoney( stcGameInfo.ulBonusValue);    
    vScroll_StartAllRun() ;	
    stcMaster.ulAutoKeyGameState = stcMaster.ulAutoKeyState ;//保存自动状态
    vPlaySound_LoopPlay( DEF_WAV_SOUND_02,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_2);	
	vReel_CloseSound( );
	for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
	{
		ubMainStopFlag[slLoop] = 0;
	}   
    mSetMasterState( PROC_MASTER_GAME_CHANCE) ;
}

// [流程] Chance 运算
void vMaster_Game_Chance( void )
{	
    vChance_GameProcess( );    
    mSetMasterState( PROC_MASTER_GAME_RUN) ;
}
#ifdef DEF_USE_IOPCI

ULONG const ulPlayerHoldKeyTable[DEF_HANDCARD_MAX] = { KEY_PCI_STOP1 , KEY_PCI_STOP2 , KEY_PCI_STOP3 , KEY_PCI_STOP4 , KEY_PCI_STOP5 } ;

#endif
// [流程] 跑动转轮
void vMaster_Game_Run( void )
{
	SLONG slLoop ;	
    #ifdef DEF_TEST_AUTOPLAY
    if ( ulKey_Touch( KEY_PCI_97_TEST ) )
    {    	
    	vReel_AllNowStopRun();
    	vShow_SymbolsBase( );
        mSetMasterState( PROC_MASTER_GAME_STOP) ;
        return ;
    }	    
    #endif	
	if( stcMaster.ulCount > 30 )
	{
		for ( slLoop = 0 ; slLoop < 5 ; slLoop ++ )
	    {    				
	        if ( ulKey_Push( ulPlayerHoldKeyTable[slLoop])&& (ubMainStopFlag[slLoop]==0) )
	        {                
				vPlaySound_Play( DEF_WAV_SOUND_03,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_3);	
	            vScroll_StopOneRow( slLoop ) ;   
	            ubMainStopFlag[slLoop] = 1;         
	        }
	    } 
	}	
       
    vShowLib_JPStar(stcMaster.ulCount);     
	if(stcMaster.ulSceneState)
	{
		#ifdef DEF_TEST_AUTOPLAY
		if ( ulKey_Touch( KEY_PCI_97_TEST ) )
		{
			stcMaster.ulCount=14;
		}
		#endif	
		vShowLib_FreeSpinEffect(stcMaster.ulCount);
		if(stcMaster.ulCount==0)
		{
			vPlaySound_Play( DEF_WAV_SOUND_71,DEF_SOUND_VOL_MID,DEF_SOUND_CH_NONE_4);					
		}			
		if(ulKey_Touch( KEY_PCI_START )||(stcMaster.ulAutoKeyGameState==2))
		{
			if( stcMaster.ulCount >= 20 )
			{
				vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_004),161,664);
				vPcVideo2D_Img_Clean(DEF_ANIMNO_PLAYER_MESS+1 ) ;						
	            vScroll_AllStop() ;
	            vReel_OpenSound( );//打开全停声音
	            mSetMasterState( PROC_MASTER_GAME_STOP) ;
	            return ;
			}	
								
		}					
						
	}	
	else
	{
		
		//if(ulKey_PushRange( KEY_PCI_START , 3 , 8 )||(stcMaster.ulAutoKeyGameState==2))
		if(ulKey_Touch( KEY_PCI_START )||(stcMaster.ulAutoKeyGameState==2))
        {
        	if( stcMaster.ulCount >= 20 )
        	{        		 
	        	vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_004),161,664);
	        	vPcVideo2D_Img_Clean(DEF_ANIMNO_PLAYER_MESS+1 ) ;		
	            vScroll_AllStop() ;
	            vReel_OpenSound( );//打开全停声音
	            mSetMasterState( PROC_MASTER_GAME_STOP) ;
	            return ;	
        		
        	}		        	
        }	
	}	
    if( stcMaster.ulCount > 120 )
    {
        mSetMasterState( PROC_MASTER_GAME_STOP) ;
        return ;
    }
    if( !ulScroll_CheckIsRun() )   
    {
    	vSound_StopChannel(DEF_SOUND_CH_NONE_2);		
		vScroll_SaveStopData( ) ;	
		mSetMasterState( PROC_MASTER_GAME_CHECK) ;      
        
    }  
	stcMaster.ulCount ++ ;

}

UBYTE const ubMaster_StopStep[7][3] = {
    {  0,255,255},
    {  1,  5,255},
    {  2,  6, 10},
    {  3,  7, 11},
    {  4,  8, 12},
    {255,  9, 13},
    {255,255, 14},
} ;

void vMaster_Game_Stop( void )
{
    UBYTE ubStopStep ;
    UBYTE ubLoop ;
    if(stcMaster.ulCount==0)
    {
    	vPcVideo2D_Img_Clean( DEF_ANIMNO_BG_STAR+1) ;
    	vPcVideo2D_Img_Clean( DEF_ANIMNO_BG_REEL_SPIN) ;
    }
    if( ( stcMaster.ulCount % 12 ) == 0 )
    {
        ubStopStep = stcMaster.ulCount / 12 ;
        if( ubStopStep < 7 )
        {
            for( ubLoop = 0 ; ubLoop < 3 ; ubLoop ++ )
            {
                if(( ubMaster_StopStep[ubStopStep][ubLoop] != 255  )&&( ulReel_CheckIsRun( ubMaster_StopStep[ubStopStep][ubLoop] ) ))
                {
                    vReel_StopRun( ubMaster_StopStep[ubStopStep][ubLoop] ) ;
                }
            }
        }
    }
    stcMaster.ulCount ++ ;
    #ifdef DEF_TEST_AUTOPLAY
	if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(!ulScroll_CheckIsRun()))
	#else
	if( !ulScroll_CheckIsRun() )
	#endif	    
    {
    	vSound_StopChannel(DEF_SOUND_CH_NONE_2);		
		vScroll_SaveStopData( ) ;	
		mSetMasterState( PROC_MASTER_GAME_CHECK) ;      
        
    }
}

// [流程] 检查奖项
void vMaster_Game_Check( void )
{

	SLONG slLine,slWin;
	vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
	slWin = slGameCheck_GameWinRule( (GAMEINFO*)&stcGameInfo );
	vSlave_WinAdd(slWin) ;  
	vChance_WinProcess(slWin);
	if(stcGameInfo.ulFreeNowLife)
    {
    	stcGameInfo.ulFreeNowLife--;
    }	
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
    
    if( stcGameInfo.ulAllSameOdds )
    {        
		mSetMasterState( PROC_MASTER_GAME_OVERALEFT) ;	
		return ;
    }
	for ( slLine = 0 ; slLine < 9 ; slLine ++ )
	{
		if(slWin)
		{
			vShowLib_SetCount(0);
			stcMaster.ulTemp = 0;
			mSetMasterState( PROC_MASTER_GAME_EFT) ;	
			return ;
		}	
	}	
	if(stcGameInfo.ulBonusType)
    { 	      	   		    	
    	mSetMasterState( PROC_MASTER_GAME_BONUSEFT) ;	
		return ;
    }	
	if( stcGameInfo.ulFeverSetLife )
    {    	
    	mSetMasterState( PROC_MASTER_GAME_FEVEREFT) ;	
		return ;	
    }	
    if(stcGameInfo.ulFreeSetLife)
    {     	
    	mSetMasterState( PROC_MASTER_GAME_FREEEFT) ;	
		return ;
    }	
	    
	if(stcMaster.ulSceneState)
	{
		if(stcGameInfo.ulFreeNowLife==0)
		{
			if(slSlave_WinRead( ))
			{
				mSetMasterState( PROC_MASTER_GAME_EXITFREE );
				return ;		
			}				
		}		
	}	
	mSetMasterState( PROC_MASTER_GAME_EXIT ) ;		
	
}

// [流程] 播放 SYMBOL 动画
void vMaster_Game_Effect( void )
{
	ULONG  ulValue;
	if(slShowLib_SymbolsWin(stcMaster.ulCount ))
	{
		if(stcGameInfo.ulBonusType)
	    {  	      		    	
	    	mSetMasterState( PROC_MASTER_GAME_BONUSEFT) ;	
			return ;
	    }	
		if( stcGameInfo.ulFeverSetLife )
	    {    	
	    	mSetMasterState( PROC_MASTER_GAME_FEVEREFT) ;	
			return ;	
	    }	
	    if(stcGameInfo.ulFreeSetLife)
	    {     	
	    	mSetMasterState( PROC_MASTER_GAME_FREEEFT) ;	
			return ;
	    }	
	    if(stcMaster.ulSceneState)
	    {
	    	vShow_SymbolsBase( );	
			if(stcGameInfo.ulFreeNowLife==0)
			{
				mSetMasterState( PROC_MASTER_GAME_EXITFREE );
				return ;
			}
			else
			{									 	
				mSetMasterState( PROC_MASTER_GAME_EXIT);
				return ;	
			}	
	    	
	    }		    

		ulValue = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo );
		if(ulValue>=100)
		{
			mSetMasterState( PROC_MASTER_GAME_BIGODDSEFT) ;	
			return ;			
		}	
		if((stcMaster.ulAutoKeyGameState)||ulKey_Touch( KEY_PCI_START )) //自动		
		{		 			 	
			vShow_CleanDeputySymbols();			
		 	vShow_SymbolsBase( );	
			vSlave_WinTakeInitial( slSlave_WinRead( )/130 ) ;
			mSetMasterState( PROC_MASTER_GAME_TAKE );
			return ;		
		}

		
		#ifdef DEF_TEST_AUTOPLAY_WUP	
		if(ulKey_Touch( KEY_PCI_97_TEST )) 		
		{
			if(mGame_ReadWupLimitTop())
			{	
				ulValue = slSlave_WinRead( );		 			 	
				vPlaySound_Clean();			
				vSlave_WupWinSet(ulValue);	
				vSlave_WinSet(0);	
				mSetMasterState( PROC_MASTER_WUP_INIT );				
				return ;	
			}
			else
			{
				vShow_CleanDeputySymbols();			
			 	vShow_SymbolsBase( );	
				vSlave_WinTakeInitial( slSlave_WinRead( )/130 ) ;
				mSetMasterState( PROC_MASTER_GAME_TAKE );
				return ;
				
			}	
			
		}	
		
		#endif	
	}	
	else
	{		
		if(ulKey_Touch( KEY_PCI_START ))
		{
			vPlaySound_Clean();			
			vShow_CleanDeputySymbols();
			//vShow_CleanLine();		
			vShow_SymbolsBase( );	
		    if(stcGameInfo.ulBonusType)
		    { 	       		    	
		    	mSetMasterState( PROC_MASTER_GAME_BONUSEFT) ;	
				return ;
		    }	
		    if( stcGameInfo.ulFeverSetLife )
		    {    	
		    	mSetMasterState( PROC_MASTER_GAME_FEVEREFT) ;	
				return ;	
		    }				    
		    if(stcGameInfo.ulFreeSetLife)
		    {      	
		    	mSetMasterState( PROC_MASTER_GAME_FREEEFT) ;	
				return ;
		    }
		    if(stcMaster.ulSceneState)
		    {
		    	if(stcGameInfo.ulFreeNowLife)
		    	{
		    		mSetMasterState( PROC_MASTER_GAME_EXIT);
		    	}	
		    	else
		    	{
		    		mSetMasterState( PROC_MASTER_GAME_EXITFREE );	
		    	}		
		    	return ;
		    }	
	
			ulValue = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo );
			if(ulValue>=100)
			{
				mSetMasterState( PROC_MASTER_GAME_BIGODDSEFT) ;	
				return ;			
			}	
		}

	}	
	if((stcGameInfo.ulFreeNowLife==0)&&(stcGameInfo.ulFeverSetLife==0)
		&&(stcGameInfo.ulFreeSetLife==0)&&(stcGameInfo.ulBonusType==0))
	{
		ulValue = slSlave_WinRead( );	
		if( ulValue )
		{
			#ifdef DEF_USE_IOPCI	
			if(mGame_ReadWupLimitTop())
			{
				
				ULONG ulRetKey ;
	
				ulRetKey = ulMaster_GetWupKey( ) ;				
				
				if( ulRetKey == KEY_PCI_HWUP )
				{	// 半比倍
									
					vPlaySound_Clean();					
					ulValue /= 2 ;				
					vSlave_WinSet(0);	
					ulCredit_Add( DEF_GAME_ONLY_PLAY , ulValue ) ;	
					vSlave_WupWinSet(ulValue);		
					mSetMasterState( PROC_MASTER_WUP_INIT );				
					return ;	
											
				}	
				if( ulRetKey == KEY_PCI_WUP )
				{	// 比倍					
					
					vPlaySound_Clean();
					vSlave_WinSet(0);
					vSlave_WupWinSet(ulValue);		
					mSetMasterState( PROC_MASTER_WUP_INIT );				
					return ;											
				}			
	
				if( ulRetKey == KEY_PCI_DWUP )
				{	// 双比倍						
					vPlaySound_Clean();
					vSlave_WinSet(0);
					vSlave_WupWinSet(ulValue*2);						
					ulCredit_Sub( DEF_GAME_ONLY_PLAY , ulValue ) ;									
					mSetMasterState( PROC_MASTER_WUP_INIT );				
					return ;	
				}	
				if( ulRetKey == KEY_PCI_TAKE )
				{	// 得分
					vPlaySound_Clean();				 	
					vShow_CleanDeputySymbols();
					//vShow_CleanLine();		
					vShow_SymbolsBase( );				 	
					vSlave_WinTakeInitial( ulValue/130 ) ;
					mSetMasterState( PROC_MASTER_GAME_TAKE );
					return ;
				}			
								
			}
			else
			{		
	
				#ifdef DEF_TEST_AUTOPLAY
				if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
				#else
				if (( ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
				#endif					
				{	// 得分	
					vPlaySound_Clean();					
					vShow_CleanDeputySymbols();						
					vShow_SymbolsBase( );				 										
					vSlave_WinTakeInitial( ulValue/130 ) ;
					mSetMasterState( PROC_MASTER_GAME_TAKE );
					return ;
				}	
			}
		#endif			
		}
		else
		{
			mSetMasterState( PROC_MASTER_GAME_EXIT);
			return ;
		}
		
		
		
	}	
		
	 stcMaster.ulCount++ ;	
}


//有得分效果时的按键判断
void vMaster_EffectChooseKey(ULONG ulState)
{
	ULONG ulValue;	
	if(stcMaster.ulIndex == 1)	
	{
		ulValue = slSlave_WinRead( );	
		if( ulValue )
		{
			#ifdef DEF_USE_IOPCI	
			if(mGame_ReadWupLimitTop())
			{
				
				ULONG ulRetKey ;
				ulRetKey = ulMaster_GetWupKey( ) ;
				
				// 得分放外面，这样在 FreeGame 里面中 Bonus 才能自动得分
				if( ulRetKey == KEY_PCI_TAKE )
				{	// 得分
							
					stcMaster.ulIndex++;					
					vSlave_WinTakeInitial( ulValue/130 ) ;					
					return ;
				}	
				if((stcGameInfo.ulFreeNowLife==0)||(stcMaster.ulSceneState==2))
				{
					if( ulRetKey == KEY_PCI_HWUP )
					{	// 半比倍
						vPlaySound_Clean();				
						//ulValue /= 2 ;				
						vSlave_WinSet(0);	
						ulCredit_Add( DEF_GAME_ONLY_PLAY , ulValue-ulValue/2 ) ;	
						vSlave_WupWinSet(ulValue/2);		
						mSetMasterState( PROC_MASTER_WUP_INIT );				
						return ;
					}			
		
					if( ulRetKey == KEY_PCI_WUP )
					{	// 比倍
						vPlaySound_Clean();
						vSlave_WinSet(0);
						vSlave_WupWinSet(ulValue);		
						mSetMasterState( PROC_MASTER_WUP_INIT );				
						return ;
					}			
		
					if( ulRetKey == KEY_PCI_DWUP )
					{	// 双比倍		
						
						vPlaySound_Clean();
						vSlave_WinSet(0);
						vSlave_WupWinSet(ulValue*2);						
						ulCredit_Sub( DEF_GAME_ONLY_PLAY , ulValue ) ;									
						mSetMasterState( PROC_MASTER_WUP_INIT );				
						return ;	
					}	
					
				}	
			}
			else
			{		
	
				#ifdef DEF_TEST_AUTOPLAY
				if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
				#else
				if (( ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
				#endif					
				{	// 得分	
					vSlave_WinTakeInitial( ulValue/130 ) ;
					stcMaster.ulIndex++;					
				}	
			}
		#endif			
		}
		else
		{			
			mSetMasterState( ulState) ;		
			return ;
		}		
	}	
}

// [流程] 玩家进 FeverGame 效果
void vMaster_Game_FeverEffect( void )
{
	ULONG ulCount,ulLoc; 
	if(stcMaster.ulCount==0)
	{		
		vShow_CleanLine();	
		vPlaySound_LoopPlay(DEF_WAV_SOUND_58,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);		
		stcChance.ulFeverType = stcGameInfo.ulFeverSetLife ;
	}
	ulLoc = stcMaster.ulCount;
	ulCount = 0;
	#ifdef DEF_TEST_AUTOPLAY_x
	if ( ulKey_Touch( KEY_PCI_97_TEST ))
	{
		ulLoc = stcMaster.ulCount/2;	
		ulCount = stcMaster.ulCount%2;
	}	
	#endif	
	if(ulCount==0)
	{
		if(slShowLib_FeverEffect(ulLoc))
		{
			#ifdef DEF_TEST_AUTOPLAY
			if( (stcMaster.ulCount>460)&&(stcMaster.ulCount<460*10) )
			{
				vMasterShow_FeverGame();
				vScroll_FeverReset();		
				vScroll_FeverLoadData();
				vScroll_FeverRefreshShowScr( ) ;
			}
			#endif		
			vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_REEL_WILD , DEF_ANIMNO_BG_REEL_HZ+14 ) ;	
			vPcVideo2D_Img_CleanAry(DEF_ANIMNO_FEVER_CB ,DEF_ANIMNO_FREER_END ) ;	
			mSetMasterState( PROC_MASTER_FEVER_INIT) ;  
			return;
		}	
	}		
	stcMaster.ulCount++ ;		
    
    
}

// [流程] 玩家拉 Bonus 效果
void vMaster_Game_BonusEffect( void )
{
	ULONG  ulCount,ulLoc; 	
	if(stcMaster.ulCount==0)
	{
		vSlave_WinAdd(stcGameInfo.ulBonusWin) ; 
    	vChance_WinBonusProcess();	// Rex		
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_REEL_HK+0 , DEF_ANIMNO_BG_REEL_HK+14 ) ;			
		vShow_CleanLine();			
		if(stcGameInfo.ulBonusType==3)
		{
			vPlaySound_LoopPlay(DEF_WAV_SOUND_52,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_BG);
		}
		else
		{			
			vPlaySound_LoopPlay(DEF_WAV_SOUND_53,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_BG);
		}	
	}			   
	ulLoc = stcMaster.ulCount;
	ulCount = 0;
	#ifdef DEF_TEST_AUTOPLAY_x
	if ( ulKey_Touch( KEY_PCI_97_TEST ))
	{
		ulLoc = stcMaster.ulCount/2;	
		ulCount = stcMaster.ulCount%2;	
	}	
	#endif		
    if(ulCount==0)
    {
    	if(slShowLib_BonusEffect(ulLoc))
		{
			vShow_CleanDeputySymbols();
			vShow_SymbolsBase( );	
			vPlaySound_Clean();			
			if(mGame_ReadMusicMode()==DEF_MUSIC_MODE_ON)
			{
				if(stcMaster.ulSceneState)  
			    {
			    	vPlaySound_BG(DEF_WAV_MUSIC_FREEGAME_03,DEF_SOUND_VOL_TINY,DEF_SOUND_CH_BG);
			    }	
			    else
			    {
			    	vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);	    	
			    }
				
			}			
			
			
			if(stcMaster.ulSceneState)
			{
				if(stcGameInfo.ulFreeNowLife==0)
				{
					mSetMasterState( PROC_MASTER_GAME_EXITFREE );
					return ;					
				}					
			}					
			mSetMasterState( PROC_MASTER_GAME_EXIT ) ;	
			return;
			
		}
		vMaster_EffectChooseKey(PROC_MASTER_GAME_EXIT);
	
    }			
	stcMaster.ulCount++;	

}

// [流程] 玩家拉 Free 效果
void vMaster_Game_FreeEffect( void )
{
	ULONG  ulCount,ulLoc; 
	
	if(stcMaster.ulCount==0)
	{
		stcGameInfo.ulFreeNowLife  += stcGameInfo.ulFreeSetLife ; 	
		vChance_WinFreeProcess( ) ;  
		vShow_CleanLine();			
		//vPlaySound_LoopPlay(DEF_WAV_SOUND_58,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);		
		vPlaySound_Play( DEF_WAV_SOUND_63,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);	
		
	}
	ulLoc = stcMaster.ulCount;
	ulCount = 0;
	#ifdef DEF_TEST_AUTOPLAY_x
	if ( ulKey_Touch( KEY_PCI_97_TEST ))
	{
		ulLoc = stcMaster.ulCount/2;	
		ulCount = stcMaster.ulCount%2;	
	}	
	#endif		
    if(ulCount==0)
    {
    	if(slShowLib_FreeEffect(ulLoc))
		{	
			#ifdef DEF_OPEN_PCFILEOUT
			vFastTest_OpenOutputRecord_one( ) ;
			#endif

			#ifdef DEF_TEST_AUTOPLAY
			if( (stcMaster.ulCount>472)&&(stcMaster.ulCount<472*10) )
			{
				UWORD uwAnimID;
				vShow_CleanEffect();
				uwAnimID = DEF_ANIMNO_BG_FREE_NUM;							
				vPcVideo2D_Img_ShowNumDef( uwAnimID , mMacro_Img(DEF_NUMBER_NUM_Z03) ,173-22-18 , 82-23, DEF_PCVIDEO2D_ZOBASE+uwAnimID , 36 , 2 , stcGameInfo.ulFreeNowLife , (char *)"%2d" ) ;	
				vPcVideo2D_Img_SetZoomCenter(uwAnimID,171,76,600);	
				vShow_GameMap(uwAnimID+1,DEF_NUMBER_NUM_Z03_X,117-22,82-23);			
				vPcVideo2D_Img_SetZoomCenter(uwAnimID+1,171,76,600);
				uwAnimID = DEF_ANIMNO_BG_FREE_SPIN;	
				vShow_GameMap(uwAnimID,DEF_EFFECT_Z03_SPIN,171-77,76-42);					
				vPcVideo2D_Img_SetZoomCenter(uwAnimID,171,76,1000);								
				vMasterShow_FreeGame( );	
				vPcVideo2D_Img_CleanAry(DEF_ANIMNO_BG_FREE,DEF_ANIMNO_BG_FREE+4 ) ;
			}
			#endif	
			stcMaster.ulSaveAutoKeyState = stcMaster.ulAutoKeyState;
			if(stcMaster.ulAutoKeyState == 0)
			{
				stcMaster.ulAutoKeyState = 1;
				ulUiAutoCount = 0;	    
			}				
			vShow_CleanDeputySymbols();	
			vShow_SymbolsBase( );	
			vPlaySound_Clean();
			vPlaySound_BG(DEF_WAV_MUSIC_FREEGAME_03,DEF_SOUND_VOL_TINY,DEF_SOUND_CH_BG);
			vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_REEL_WILD , DEF_ANIMNO_BG_REEL_HZ+14 ) ;			
			mSetMasterState( PROC_MASTER_GAME_SCR) ;  
			return; 
			
		}
    	
    }		
	
	stcMaster.ulCount++ ;	
}




void vMaster_Game_BigOddsEffect(void)
{
	if(stcMaster.ulCount==0)
	{
		vShow_DisWinLine();		
		vShow_AllSymbolsHK();
		//vPlaySound_LoopPlay(DEF_WAV_MUSIC_BIGGAME_06,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);		
		//vPlaySound_Play(DEF_WAV_MUSIC_BIGGAME_A06,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);
		vPlaySound_BG(DEF_WAV_MUSIC_BIGGAME_B06,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);		
	}
//	if((stcMaster.ulCount==320)&&(stcMaster.ulIndex<2))
//	{
//		vPlaySound_LoopPlay(DEF_WAV_MUSIC_BIGGAME_B06,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);		
//	}		
	if(slShowLib_BigOddsEffect(stcMaster.ulCount))
	{
		
		if(mGame_ReadMusicMode()==DEF_MUSIC_MODE_ON)
		{
			if(stcMaster.ulSceneState)  
		    {
		    	vPlaySound_BG(DEF_WAV_MUSIC_FREEGAME_03,DEF_SOUND_VOL_TINY,DEF_SOUND_CH_BG);
		    }	
		    else
		    {
		    	vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);	    	
		    }			
		}			
		mSetMasterState( PROC_MASTER_GAME_EXIT) ;	
		return ;		
	}	
	//if(stcMaster.ulCount>=30)
	{
		vMaster_EffectChooseKey(PROC_MASTER_GAME_EXIT);
	}		
	stcMaster.ulCount++;		
	
}
//全盘奖显示效果
void vMaster_Game_OverallEffect(void )
{
	if(stcMaster.ulCount==0)
	{		
		vPlaySound_BigPlay(DEF_WAV_MUSIC_OVERALL_A08,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);
	}
	if((stcMaster.ulCount==320)&&(stcMaster.ulIndex<2))
	{
		vPlaySound_BigLoopPlay(DEF_WAV_MUSIC_OVERALL_B08,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);		
	}	
	if(slShowLib_AllSymbolsEffect(stcMaster.ulCount))
	{
		//ULONG i;
		vPlaySound_Clean();	
		if(mGame_ReadMusicMode()==DEF_MUSIC_MODE_ON)
		{
			if(stcMaster.ulSceneState)  
		    {
		    	vPlaySound_BG(DEF_WAV_MUSIC_FREEGAME_03,DEF_SOUND_VOL_TINY,DEF_SOUND_CH_BG);
		    }	
		    else
		    {
		    	vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);	    	
		    }			
		}						
		vShow_CleanDeputySymbols();						
		vShow_SymbolsBase( );
		mSetMasterState( PROC_MASTER_GAME_EXIT) ;	
		return ;		
	}	
	vMaster_EffectChooseKey(PROC_MASTER_GAME_EXIT );
//	if(stcMaster.ulIndex)
//	{
//		if(stcMaster.ulCount<350)
//		{
//		 	stcMaster.ulIndex = 0;
//		}	
//	}	

	stcMaster.ulCount++;	
	
}


//免费游戏退出流程
void vMaster_Game_ExitFree(void)
{

	if(stcMaster.ulCount==0)
	{
		vChance_RecordFreeUpdate();//更新历史次数
		vShow_CleanLineNum( );
		vShowLib_SymbolsHKC(0,0);
		vPlaySound_BG(DEF_WAV_MUSIC_FREEGAMESCORE_07,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);
	}
	if(slShowLib_ExitFreeEffect(stcMaster.ulCount))
	{		
		stcMaster.ulAutoKeyState = stcMaster.ulSaveAutoKeyState;
		if(ulKey_Touch( KEY_PCI_START )==0)
		{
			stcMaster.ulAutoKeyState = 0;
			ulUiAutoCount = 0;	
		}	
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_UI , DEF_ANIMNO_BG_UI+14 ) ;	
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_FREE_SPIN , DEF_ANIMNO_BG_FREE_NUM+1 ) ;	
		vPcVideo2D_Img_Clean(DEF_ANIMNO_BG_FREE_UI) ;	
		vPcVideo2D_Img_CleanAry(DEF_ANIMNO_BG_BASE,DEF_ANIMNO_BG_BASE+4 ) ;
		vMasterShow_BaseGame(); 
		vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);      
		vShow_CleanLineNum(); 
		vPlaySound_Clean();		
		mSetMasterState( PROC_MASTER_GAME_EXIT) ;	
		return ;		
	}	
	vMaster_EffectChooseKey(PROC_MASTER_GAME_EXIT );	
	stcMaster.ulCount++;		
	
}

// 等待玩家选择比倍或得分
void vMaster_Game_Choose( void )
{
	ULONG ulValue;	
	ulValue = slSlave_WinRead( );	
	if( ulValue )
	{
		if(stcMaster.ulCount>= 20)
		{
			#ifdef DEF_USE_IOPCI	
			if(mGame_ReadWupLimitTop())
			{				
				ULONG ulRetKey ;
				ulRetKey = ulMaster_GetWupKey( ) ;					
				if( ulRetKey == KEY_PCI_HWUP )
				{	// 半比倍
					vPlaySound_Clean();				
					//ulValue /= 2 ;				
					vSlave_WinSet(0);	
					ulCredit_Add( DEF_GAME_ONLY_PLAY , ulValue-ulValue/2 ) ;	
					vSlave_WupWinSet(ulValue/2);		
					mSetMasterState( PROC_MASTER_WUP_INIT );				
					return ;
				}			
	
				if( ulRetKey == KEY_PCI_WUP )
				{	// 比倍
					vPlaySound_Clean();
					vSlave_WinSet(0);
					vSlave_WupWinSet(ulValue);		
					mSetMasterState( PROC_MASTER_WUP_INIT );				
					return ;
				}			
	
				if( ulRetKey == KEY_PCI_DWUP )
				{	// 双比倍	
					
					vPlaySound_Clean();
					vSlave_WinSet(0);
					vSlave_WupWinSet(ulValue*2);						
					ulCredit_Sub( DEF_GAME_ONLY_PLAY , ulValue ) ;									
					mSetMasterState( PROC_MASTER_WUP_INIT );				
					return ;							
					
				}	
				if( ulRetKey == KEY_PCI_TAKE )
				{	// 得分
				 		
					vSlave_WinTakeInitial( ulValue/130 ) ;
					mSetMasterState( PROC_MASTER_GAME_TAKE );
					return ;
				}	
								
			}
			else
			{	
				#ifdef DEF_TEST_AUTOPLAY
				if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
				#else
				if (( ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
				#endif					
				{	// 得分	
				 										
					vSlave_WinTakeInitial( ulValue/130 ) ;
					mSetMasterState( PROC_MASTER_GAME_TAKE );
					return ;
				}	
			}		
			#endif	
		}			
	}
	else
	{		
		mSetMasterState( PROC_MASTER_GAME_EXIT);
		return ;
	}
	stcMaster.ulCount++;
}



// [流程] 得分
void vMaster_Game_Take( void )
{	

	if(stcMaster.ulAutoKeyGameState==2) //自动
	{
		vSlave_SetWinTakeValueMax( );		
	}	
	if(stcMaster.ulCount==0)
	{
		vShow_DisWinLine();
		vShow_AllSymbolsHK();
	}	
	if(stcMaster.ulCount>= 20)
	{
		if(ulKey_RePush( KEY_PCI_START , 20 , 5 ))
		{
			vSlave_SetWinTakeValueMax( );	
		}			
	}		
	if ( (stcMaster.ulCount % 30) == 29 )	
	{
		// 加速     
		vSlave_WinTakeAddSpeed( ) ;
	}
	if(!slSlave_TakeToCredit( stcMaster.ulCount )) 
	{	
		vPlaySound_Play(DEF_WAV_SOUND_49,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);				
		vShow_SymbolsBase( );
		mSetMasterState( PROC_MASTER_GAME_EXIT ) ;
	}	
	stcMaster.ulCount ++ ;	
}



// 游戏结束处理
void vMaster_Game_Exit( void ) 
{
//	DLONG dlVal[2] ;
//	SLONG slValue[2];
	#ifdef DEF_OPEN_PCFILEOUT
	vFastTest_OpenOutputRecord_one( ) ;
	#endif	
	if(stcMaster.ulSceneState&&(stcGameInfo.ulFreeNowLife==0))
	{		
		if(ulKey_Touch( KEY_PCI_START )==0)
		{
			stcMaster.ulAutoKeyState = 0;
			ulUiAutoCount = 0;	
		}	
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_UI , DEF_ANIMNO_BG_UI+14 ) ;	
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_FREE_SPIN , DEF_ANIMNO_BG_FREE_NUM+1 ) ;	
		vPcVideo2D_Img_Clean(DEF_ANIMNO_BG_FREE_UI) ;	
		vPcVideo2D_Img_CleanAry(DEF_ANIMNO_BG_BASE,DEF_ANIMNO_BG_BASE+4 ) ;
		vMasterShow_BaseGame(); 
		vPlaySound_BG(DEF_WAV_MUSIC_MAINGAME_01,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);     
			
		
	}	
	/*
	if(stcMaster.ulSceneState==0)
	{
		DLONG dlVal[2] ;
		SLONG slValue[2];
		dlVal[0] = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALPLAY);
        dlVal[1] = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN);      
		slValue[0] =  dlVal[0] - dlVal[1];
		slMainRveValue[6]=dlVal[0];
		slMainRveValue[7]=dlVal[1];
		dlVal[0] = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_COIN)+dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_KEYIN); 
        dlVal[1] =dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_PAYOUT ) + dlRecord_ReadCurrTotal( DEF_GAME_ONLY_PLAY, DEF_RECORD_DATA_KEYOUT ) ;
		slValue[1] =  dlVal[0] - dlVal[1]-ulCredit_Read(DEF_GAME_ONLY_PLAY)-slSlave_WinRead();
		if(slValue[0] != slValue[1])
		{
			vShowRec_ClsPage() ;
			vShowrec_Value(slValue[0],334,1*40);	
			vShowrec_Value(slValue[1],334,2*40);
			vShowrec_Value(slMainRveValue[0],334,3*40);
			vShowrec_Value(slMainRveValue[1],334,4*40);
			vShowrec_Value(slMainRveValue[2],334,5*40);
			vShowrec_Value(slMainRveValue[3],334,6*40);
			vShowrec_Value(slMainRveValue[4],334,7*40);
			vShowrec_Value(slMainRveValue[5],334,8*40);
        	vShowrec_Value(slMainRveValue[6],334,9*40);
			vShowrec_Value(slMainRveValue[7],334,10*40);
			while ( ulKey_RePush( KEY_1, 10 , 3 ) == 0 );	
			while ( ulKey_RePush( KEY_2, 10 , 3 ) == 0 );	
		}			
	}
	*/
	ulShowLibDWupCount = 0;//清除双比倍计数
	ulMainDemoCount = 0;	
	vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_REEL_HK+0 , DEF_ANIMNO_BG_REEL_HK+14 ) ;	
	vShow_CleanDeputySymbols();
	vShow_CleanLineNum(); 
	vPlaySound_Clean();
	vPcVideo2D_Img_Clean( DEF_ANIMNO_SYSTEM_TEST ) ;	
	mSetMasterState( PROC_MASTER_GAME_SCR) ; 	
}



void vMaster_Fever_Init(void)
{	

	ulShowLibDWupCount = 0;//清除双比倍计数
	#ifdef DEF_DEFINE_SHOW_STATE_x
	vPcVideo2D_Debug_OutMsg( "FEVERODDS : ", stcChance.slFeverOdds );		
	#endif			
	vPlaySound_Clean();
	vPlaySound_BG(DEF_WAV_MUSIC_FEVERGAME_04,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_BG);	
	mSetMasterState(PROC_MASTER_FEVER_START) ;
}

void vMaster_Fever_Start(void)
{		
	if(stcMaster.ulIndex == 0)
	{
		vPcVideo2D_Img_Clean(DEF_ANIMNO_FEVER_BG_ALLSYMBOL) ;	
		stcMaster.ulIndex++;		  
	}	
	#ifdef DEF_TEST_AUTOPLAY
	#ifdef DEF_TEST_ALWAYS_AUTO_2
	if ( ubAutoPlay2_isRun )
	#else
	if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_START)))
	#endif	
	#else
	if(ulKey_Touch( KEY_PCI_START))
	#endif	
	{	
		mSetMasterState( PROC_MASTER_FEVER_CHANCE) ;
		return ;		
	}	
	stcMaster.ulCount++;
}

void vMaster_Fever_Chance(void)
{	
	vChance_FeverProcess( );  
	vScroll_FeverStartAllRun();
	mSetMasterState( PROC_MASTER_FEVER_RUN) ;	
}


void vMaster_Fever_Run(void)
{
    #ifdef DEF_TEST_AUTOPLAY
    if ( ulKey_Touch( KEY_PCI_97_TEST ) )
    {
    	vReel_FeverAllNowStopRun();
    	//vShow_FeverSymbolsBase();
    	vShow_FeverSymbol(stcFeverChance.ubData-1);
        mSetMasterState( PROC_MASTER_FEVER_STOP) ;
        return ;
    }
    #endif
	vShowLib_FeverGameUILGStart(stcMaster.ulCount);
	if( stcMaster.ulCount > 60 )
    {
    	vScroll_FeverAllStop();
        mSetMasterState( PROC_MASTER_FEVER_STOP) ;
    }
    else
    {
    	stcMaster.ulCount++;	
    }	
}

void vMaster_Fever_Stop(void)
{

	#ifdef DEF_TEST_AUTOPLAY
	if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(!ulScroll_FeverCheckIsRun()))
	#else
	if( !ulScroll_FeverCheckIsRun() )
	#endif		
    {
    	vSound_StopChannel(DEF_SOUND_CH_NONE_2);
		vPlaySound_Play( DEF_WAV_SOUND_04,DEF_SOUND_VOL_BIG,DEF_SOUND_CH_NONE_1);
    	stcFeverChance.ubData = slGameCheck_FeverValue();
    	if(stcFeverChance.ubData< 7)
    	{
    		if(stcFeverChance.ubData)
    		{
    			vShow_FeverSymbol(stcFeverChance.ubData-1);
    		}	
	    	if(stcFeverChance.ubData==6)
	    	{
	    		vPlaySound_Play( DEF_WAV_SOUND_30,DEF_SOUND_VOL_BIG,DEF_SOUND_CH_EFT);
	    		stcGameInfo.ulFeverNowLife--;
	    		if(stcGameInfo.ulFeverNowLife==0)	
				{
					vPlaySound_Play( DEF_WAV_SOUND_28,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_4);
					vPlaySound_Play( DEF_WAV_SOUND_28,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_5);
				}	
	    		mSetMasterState(PROC_MASTER_FEVER_LOSE) ;		
	    	}	
	    	else
	    	{	    		
	    		stcFeverChance.ulWin = ulFeverGameWinOdds[stcFeverChance.ubData-1]*slSlave_ReadTotalBet();
				stcChance.ulFeverTotalWin += stcFeverChance.ulWin ;	// Rex
	    		mSetMasterState(PROC_MASTER_FEVER_WIN) ;	
	    		
	    	}		
    		
    	}	
    	else
    	{
    		
    		mSetMasterState(PROC_MASTER_FEVER_START) ;		
    	}	
    		       
    }	
//	}
}


void vMaster_Fever_Win(void)
{
	if(slShowLib_FeverGameWinEffect(stcMaster.ulCount))
	{
		vSlaveShow_FeverGameWin();
		mSetMasterState(PROC_MASTER_FEVER_START) ;	
		
	}	
	else
	{
		stcMaster.ulCount++;	
	}	
	
}
void vMaster_Fever_Lose(void)
{	
	SLONG slWin;
	if(slShowLib_FeverGameLoseEffect(stcMaster.ulCount))
	{
		if(stcGameInfo.ulFeverNowLife==0)	
		{	
			vChance_WinFeverProcess(); // Rex
			slWin = slSlave_WinRead();		
			if(slWin)
			{
				mSetMasterState(PROC_MASTER_FEVER_EFT) ;	
			}
			else
			{
				mSetMasterState(PROC_MASTER_FEVER_EXIT) ;		
			}		
				
		}
		else
		{
			mSetMasterState(PROC_MASTER_FEVER_START) ;		
		}			
		
		
	}	
	else
	{
		stcMaster.ulCount++;	
	}	
	
}


// 等待玩家选择比倍或得分花样效果
void vMaster_Fever_Effect( void )
{
	if(stcMaster.ulCount==0)
	{
		vPlaySound_BG(DEF_WAV_MUSIC_FEVERGAMESCORE_05,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_BG);
	}		
	if(slShowLib_FeverEffectEnd(stcMaster.ulCount))
	{
		mSetMasterState(PROC_MASTER_FEVER_EXIT) ;	
		return ;		
	}	
	vMaster_EffectChooseKey(PROC_MASTER_FEVER_EXIT);	
	stcMaster.ulCount++;
}

// 等待玩家选择比倍或得分
void vMaster_Fever_Choose( void )
{
	
	ULONG ulValue;	
	ulValue = slSlave_WinRead( );	
	if( ulValue )
	{		
		#ifdef DEF_USE_IOPCI	
		if(mGame_ReadWupLimitTop())
		{
			
			ULONG ulRetKey ;
			ulRetKey = ulMaster_GetWupKey( ) ;					
			if( ulRetKey == KEY_PCI_HWUP )
			{	// 半比倍
				vPlaySound_Clean();				
				//ulValue /= 2 ;				
				vSlave_WinSet(0);	
				ulCredit_Add( DEF_GAME_ONLY_PLAY , ulValue-ulValue/2 ) ;	
				vSlave_WupWinSet(ulValue/2);		
				mSetMasterState( PROC_MASTER_WUP_INIT );				
				return ;
			}			

			if( ulRetKey == KEY_PCI_WUP )
			{	// 比倍
				vPlaySound_Clean();
				vSlave_WinSet(0);
				vSlave_WupWinSet(ulValue);		
				mSetMasterState( PROC_MASTER_WUP_INIT );				
				return ;
			}			

			if( ulRetKey == KEY_PCI_DWUP )
			{	// 双比倍				
				vPlaySound_Clean();
				vSlave_WinSet(0);
				vSlave_WupWinSet(ulValue*2);						
				ulCredit_Sub( DEF_GAME_ONLY_PLAY , ulValue ) ;									
				mSetMasterState( PROC_MASTER_WUP_INIT );
			}	
			if( ulRetKey == KEY_PCI_TAKE )
			{	// 得分			 	
				vSlave_WinTakeInitial( ulValue/130 ) ;
				mSetMasterState( PROC_MASTER_FEVER_TAKE );
				return ;
			}			
							
		}
		else
		{		

			#ifdef DEF_TEST_AUTOPLAY
			if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
			#else
			if (( ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
			#endif					
			{	// 得分				 											
				vSlave_WinTakeInitial( ulValue/130 ) ;
				mSetMasterState( PROC_MASTER_FEVER_TAKE );
				return ;
			}	
		}		
		#endif	
					
	}
	else
	{		
		mSetMasterState( PROC_MASTER_FEVER_EXIT);		
	}
	
	
	
}



void vMaster_Fever_Take(void)
{
	
	if(stcMaster.ulCount>= 20)
	{
		if(ulKey_RePush( KEY_PCI_START , 20 , 5 ))
		{
			vSlave_SetWinTakeValueMax( );	
		}			
	}		
	if ( (stcMaster.ulCount % 30) == 29 )	
	{
		// 加速     
		vSlave_WinTakeAddSpeed( ) ;
	}
	if(!slSlave_TakeToCredit( stcMaster.ulCount )) 
	{
		vPlaySound_Play(DEF_WAV_SOUND_49,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);				
		mSetMasterState(PROC_MASTER_FEVER_EXIT) ;	
		return ;
		
	}
	stcMaster.ulCount ++ ;	
	
}

void vMaster_Fever_Exit(void)
{
	//UWORD uwAnimID;

	#ifdef DEF_OPEN_PCFILEOUT
	vFastTest_OpenOutputRecord_one( ) ;
	#endif

	vPcVideo2D_Img_CleanAry( 0 , DEF_ANIMNO_FEVER_BG_END  ) ;
	vPcVideo2D_Img_CleanAry( DEF_ANIMNO_FEVER_CB , DEF_ANIMNO_FREER_END ) ;	
	//while ( ulKey_RePush( KEY_PCI_START , 10 , 3 ) == 0 );
    mMainGame_NeedReflashScr();  	    	
  	vPlaySound_Clean();
	mSetMasterState( PROC_MASTER_GAME_INIT) ; 	
}





// 比倍游戏初始化
void vMaster_Wup_Init( void ) // PROC_MASTER_WUP_INIT
{
	if(stcMaster.ulSceneState==1)
	{	
		stcMaster.ulAutoKeyState = 0;;	
		ulUiAutoCount = 0;	    
	}
	vPlaySound_Clean();
	vPlaySound_BG(DEF_WAV_MUSIC_DOUBLEUP_02,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_BG);	
	vMasterShow_WupGame( );	
	ubUiRefreshFlag[DEF_UI_WIN] = 1;
	ulUiRefreshCount[DEF_UI_WIN] = 0;
	mSetMasterState( PROC_MASTER_WUP_GUESS) ; 
}


//重新进行比倍
void vMaster_Wup_Ready( void ) // PROC_MASTER_WUP_INIT
{
 
	if(slShowLib_WupWitchReady(stcMaster.ulCount))
	{
		mSetMasterState( PROC_MASTER_WUP_GUESS) ;		
	}	
	else
	{
		stcMaster.ulCount++;	
	}	
		
}

// 等待玩家决定大小
void vMaster_Wup_Guess( void ) // PROC_MASTER_WUP_GUESS
{	
	ULONG ulValue;
	#ifdef DEF_TEST_AUTOPLAY_WUP
	if ( ulKey_Touch( KEY_PCI_97_TEST ) )
	{
		if(ulRand_ReadMod(2))
		{
			stcWupChance.ubGuess = DEF_WUP_GUESS_BIG ;	
		}	
		else
		{
			stcWupChance.ubGuess = DEF_WUP_GUESS_SMALL ;	
		}	
		mSetMasterState( PROC_MASTER_WUP_CHANCE );
		return ;	
	}	
	#endif	
	
	vShowLib_WupGuessEffect(stcMaster.ulCount);
	if ( ulKey_PushRange( KEY_PCI_BIG,3,8 ) )
	{	// 猜大
		
		stcWupChance.ubGuess = DEF_WUP_GUESS_BIG ;		
		mSetMasterState( PROC_MASTER_WUP_CHANCE );
		return ;
	}	
	if ( ulKey_PushRange( KEY_PCI_SMALL,3,8 ) )
	{	// 猜小
		
		stcWupChance.ubGuess = DEF_WUP_GUESS_SMALL ;			
		mSetMasterState( PROC_MASTER_WUP_CHANCE );
		return ;
	}
	if ( ulKey_Push( KEY_PCI_TAKE )||ulKey_Push( KEY_PCI_START) )
	{	// 得分		
		ulValue =slSlave_WupWinRead();	
		if( ulValue )
		{			
			vSlave_WinTakeInitial( ulValue/130 ) ;	
			mSetMasterState( PROC_MASTER_WUP_GTAKE );
		}	
	}
	stcMaster.ulCount++;
}
//猜时得分
void vMaster_Wup_GTake(void)
{
	vShowLib_WupFairyWait(stcMaster.ulCount);
	vShowLib_WupWitchWait(stcMaster.ulCount);
	if(stcMaster.ulIndex == 0)
	{
		if(stcMaster.ulCount>= 20)
		{
			if(ulKey_RePush( KEY_PCI_START , 20 , 5 ))
			{
				vSlave_SetWinTakeValueMax( );	
			}	
		}	
		if ( (stcMaster.ulCount % 30) == 29 )	
		{
			// 加速     
			vSlave_WinTakeAddSpeed( ) ;
		}
		if(!slSlave_WupTakeToCredit( stcMaster.ulCount )) 
		{	
			vPlaySound_Play(DEF_WAV_SOUND_49,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);		
			stcMaster.ulIndex++;	
			stcMaster.ulTemp = stcMaster.ulCount;
					
		}	
	}
	else
	{
		#ifdef DEF_TEST_AUTOPLAY_WUP
		if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(stcMaster.ulCount>=(stcMaster.ulTemp+120))|| ulKey_Push(KEY_PCI_START ))
		#else
		if((stcMaster.ulCount>=(stcMaster.ulTemp+120))|| ulKey_Push(KEY_PCI_START ))		
		#endif			
		{
			mSetMasterState( PROC_MASTER_WUP_EXIT) ;		
			return ;	
		}				
	}		
	stcMaster.ulCount ++ ;		
	
}


void vMaster_Wup_Chance( void ) // PROC_MASTER_WUP_CHANCE
{	
	vWupChance_DealProcess();
	if(stcWupChance.ubData != DEF_CHANCE_WUP_NULL)
	{
		vWupChance_BetProcess();//不需要把该局押注纳入计算	
	}		
	vShow_WupGuessKeyDis();	
	mSetMasterState( PROC_MASTER_WUP_EFT) ;		
}

void vMaster_Wup_Effect( void ) // PROC_MASTER_WUP_EFFECT
{
	if(slShowLib_WupAttackEffect(stcMaster.ulCount))
	{
		if(stcWupChance.ubData != DEF_CHANCE_WUP_NULL)
		{
			vGameCheck_WupWinRule();
			vWupChance_WinProcess(slSlave_WupWinRead());//不需要把该局押注纳入计算	
		}	
		else
		{
   			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_WUP_NULL , 1 ) ;			
		}
		
		switch ( stcWupChance.ubData )
		{
			case DEF_CHANCE_WUP_WIN_X1:
			case DEF_CHANCE_WUP_WIN_X2:
			case DEF_CHANCE_WUP_WIN_X3:
			case DEF_CHANCE_WUP_WIN_X4:
			if(mGame_ReadWupLimitTop( ))
			{
				if( slSlave_WupWinRead() >= mGame_ReadWupLimitTop( ) )	
				{			
					vWupChance_RecWupLimit( slSlave_WupWinRead( ) ) ; // 20141219 REX
					
					mSetMasterState( PROC_MASTER_WUP_LIMIT) ;	
				}
				else
				{
					mSetMasterState( PROC_MASTER_WUP_CHOOSE) ;			
				}	
			
			}	
			else
			{
				mSetMasterState( PROC_MASTER_WUP_CHOOSE) ;			
			}									
			break ;		
			case DEF_CHANCE_WUP_LOSE:
			mSetMasterState( PROC_MASTER_WUP_EXIT) ;					
			break ;	
			case DEF_CHANCE_WUP_NULL:
			default :  	
			mSetMasterState( PROC_MASTER_WUP_GUESS) ;					
			break ;				
		}
		
	}
	else
	{
		stcMaster.ulCount++;	
	}	
	
}




void vMaster_Wup_Choose( void ) // PROC_MASTER_WUP_CHOOSE
{
	ULONG ulValue;	
	vShowLib_WupWinSelectEffect(stcMaster.ulCount);	
	stcMaster.ulCount++;	
	ulValue =slSlave_WupWinRead();	
	if( ulValue )
	{
		#ifdef DEF_USE_IOPCI	
		if(mGame_ReadWupLimitTop())
		{			
			ULONG ulRetKey ;
			ulRetKey = ulMaster_GetWupKey( ) ;					
			if( ulRetKey == KEY_PCI_HWUP )
			{	// 半比倍
					
				//ulValue /= 2 ;	
				ulCredit_Add( DEF_GAME_ONLY_PLAY , ulValue-ulValue/2 ) ;	
				vSlave_WupWinSet(ulValue/2);	
				vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_EFF_MESS , DEF_ANIMNO_WUP_EFF_MESS+1 ) ;	
				mSetMasterState( PROC_MASTER_WUP_READY) ;			
				return ;
			}			

			if( ulRetKey == KEY_PCI_WUP )
			{	// 比倍	
				vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_EFF_MESS , DEF_ANIMNO_WUP_EFF_MESS+1 ) ;		
				mSetMasterState( PROC_MASTER_WUP_READY) ;				
				return ;
			}			

			if( ulRetKey == KEY_PCI_DWUP )
			{	// 双比倍
				
				vSlave_WupWinSet(ulValue*2);						
				ulCredit_Sub( DEF_GAME_ONLY_PLAY , ulValue ) ;	
				vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_EFF_MESS , DEF_ANIMNO_WUP_EFF_MESS+1 ) ;									
				mSetMasterState( PROC_MASTER_WUP_READY) ;		
				return ;						
			
			}				

			if( ulRetKey == KEY_PCI_TAKE )
			{	// 得分
				vSlave_WinTakeInitial( ulValue/130 ) ;	
				//vShow_WupMessageDis(2);		
				//vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_EFF_MESS , DEF_ANIMNO_WUP_EFF_MESS+1 ) ;	
				mSetMasterState( PROC_MASTER_WUP_TAKE ) ;
				return ;
			}			
							
		}
		else
		{		

			#ifdef DEF_TEST_AUTOPLAY
			if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
			#else
			if (( ulKey_Touch( KEY_PCI_TAKE ))||(ulKey_Touch( KEY_PCI_START )))
			#endif					
			{	// 得分	
				vSlave_WinTakeInitial( slSlave_WupWinRead()/130 ) ;	
				//vShow_WupMessageDis(2);	
				//vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_EFF_MESS , DEF_ANIMNO_WUP_EFF_MESS+1 ) ;		
				mSetMasterState( PROC_MASTER_WUP_TAKE ) ;
				return ;
			}	
		}
	#endif			
	}
	else
	{	
		vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_EFF_MESS , DEF_ANIMNO_WUP_EFF_MESS+1 ) ;		
		mSetMasterState( PROC_MASTER_WUP_EXIT) ;		
		return ;
	}
	
	
}

// 得分效果处理
void vMaster_Wup_Take( void ) // PROC_MASTER_WUP_TAKE
{
	vShowLib_WupWinSelectEffect(stcMaster.ulCount);
	if(stcMaster.ulIndex == 0)
	{
		if(stcMaster.ulCount>= 20)
		{
			if(ulKey_RePush( KEY_PCI_START , 20 , 5 ))
			{
				vSlave_SetWinTakeValueMax( );	
			}	
		}	
		if ( (stcMaster.ulCount % 30) == 29 )	
		{
			// 加速     
			vSlave_WinTakeAddSpeed( ) ;
		}
		if(!slSlave_WupTakeToCredit( stcMaster.ulCount )) 
		{
			vPlaySound_Play(DEF_WAV_SOUND_49,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);
			stcMaster.ulIndex++;	
			stcMaster.ulTemp = stcMaster.ulCount;					
		}	
		//while ( ulKey_RePush( KEY_PCI_START , 10 , 3 ) == 0 );
	}
	else
	{
		#ifdef DEF_TEST_AUTOPLAY_WUP
		if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(stcMaster.ulCount>=(stcMaster.ulTemp+120))|| ulKey_Push(KEY_PCI_START ))
		#else
		if((stcMaster.ulCount>=(stcMaster.ulTemp+120))|| ulKey_Push(KEY_PCI_START ))		
		#endif			
		{
			mSetMasterState( PROC_MASTER_WUP_EXIT) ;		
			return ;	
		}	
			
	}		
	stcMaster.ulCount ++ ;	
}

void vMaster_Wup_Limit( void ) // PROC_MASTER_WUP_LIMIT
{
	vShowLib_WupWinSelectEffect(stcMaster.ulCount);
	#ifdef DEF_TEST_AUTOPLAY
	if (( ulKey_Touch( KEY_PCI_97_TEST ) )||(ulKey_Touch( KEY_PCI_START)))
	#else
	if(ulKey_Touch( KEY_PCI_START))
	#endif	
	{
		vSlave_WinTakeInitial( slSlave_WupWinRead()/130 ) ;		
		mSetMasterState( PROC_MASTER_WUP_TAKE ) ;
		return ;
	}
	stcMaster.ulCount++;
	
}

// 比倍游戏结束处理
void vMaster_Wup_Exit( void ) // PROC_MASTER_WUP_END
{
	//UWORD uwAnimID;
	#ifdef DEF_OPEN_PCFILEOUT
    vFastTest_OpenOutputRecord_one( ) ;
    #endif
	ulShowLibDWupCount = 0;//清除双比倍计数
	vPcVideo2D_Img_Clean(DEF_ANIMNO_PLAYER_WUP_WIN) ;	
	vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_BG , DEF_ANIMNO_WUP_EFF_END) ;
	mMainGame_NeedReflashScr();  			
	mSetMasterState( PROC_MASTER_GAME_INIT) ;
}


















void vMaster_Stage_PayOut( void ) // PROC_MASTER_PAY_OUT
{	
	if(( stcSlave[DEF_GAME_ONLY_PLAY].ulError & DEF_SLAVE_ERROR_PAYOUT )||
	(stcSlave[DEF_GAME_ONLY_PLAY].ubPayoutChoose != 1 ) )   
	{	
		//vMasterShow_Message(DEF_MASTERSHOW_MSG_NO);
		//mSetMasterState( PROC_MASTER_GAME__READY );	
		mSetMasterState( PROC_MASTER_GAME_SCR );				
	}		
}

void vMaster_Stage_Error( void ) // PROC_MASTER_ERROR
{
	// 能够进入查账做归零动作

    //vPcVideo2D_Img_Show( DEF_ANIMNO_SYSTEM_MESSAGE , mHSRecord_GetImg( mGame_ReadFontType() , DEF_HSRIMG_J_003 ) , DEF_PCVIDEO2D_SCREEN_W/2 , DEF_PCVIDEO2D_SCREEN_H/2 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_SYSTEM_MESSAGE ) ;
	//vPcVideo2D_Img_SetColorIdx(DEF_ANIMNO_SYSTEM_MESSAGE , DEF_RED ) ;
	vShowRec_ShowRecordLimitMessage( ) ;
}

void vMaster_Stage_ReportError( void ) // PROC_MASTER_REPORT_ERROR
{
#ifdef DEF_DEFINE_ENABLE_GTRULE
	{
		// 检查管理系统是否当机需要报账解码
		#ifdef DEF_GTRULE_GTHS
		if( ulGTHS_GetStatus( ) == DEF_GTHS_STATUS_ISOK )
		{
			vShowRec_ShowReportErrClean( ) ;
			//vShow_CleanAllEffect( ) ;	
			//mSetMasterState( PROC_MASTER_GAME_READY );
			mSetMasterState( PROC_MASTER_GAME_INIT );
		}
		#endif
		#ifdef DEF_GTRULE_GTVG
		if( ulGTVG_GetStatus( ) == DEF_GTVG_STATUS_ISOK )
		{
			vShowRec_ShowReportErrClean( ) ;
			//vShow_CleanAllEffect( ) ;	
			mSetMasterState( PROC_MASTER_GAME_INIT );
		}
		#endif
		else
		{
			vShowRec_ShowReportError( ) ;
			
			ulMainOtherCount ++ ;
		}	
	}
#else
	{
		//vShow_CleanAllEffect( ) ;	
		//mSetMasterState( PROC_MASTER_GAME_READY );
		ASSERT(0);
	}	
#endif		
			
}


ULONG ulMaster_IsCanRecsys(void )
{
	if( ulMainPowerOnState ==  PROC_MAIN_POWERON_DEMO)	
	{
		return 1;	
	}
	if((stcMaster.ulSceneState==1)&&stcGameInfo.ulFreeNowLife)  
	{
		return 0;	
	}
	if( ulMainPowerOnState ==  PROC_MAIN_POWERON_RUN)	
	{
		switch ( stcMaster.ulState )	
		{	
			case  PROC_MASTER_GAME_EFT:	
			{
				if(stcMaster.ulSceneState)
				{
					return 0;	
				}	
				else
				{
					return 1;	
				}			
			}
			case  PROC_MASTER_GAME_BIGODDSEFT:
			case  PROC_MASTER_GAME_OVERALEFT:	
			case  PROC_MASTER_GAME_BONUSEFT:
			if(stcMaster.ulSceneState)
			{
				return 0;	
			}	
			case  	PROC_MASTER_GAME_EXITFREE:		
			case  	PROC_MASTER_FEVER_EFT:	
			if(stcMaster.ulIndex == 1)
			{
				return 1;	
			}
			else
			{
				return 0;		
			}				
			case 	PROC_MASTER_GAME_SCR:		
			case 	PROC_MASTER_GAME_BET :
			//case    PROC_MASTER_GAME_ACT :
				
			case    PROC_MASTER_GAME_CHOOSE :
			case    PROC_MASTER_FEVER_START :	
			//case 	PROC_MASTER_FEVER_WAITGO :
			case 	PROC_MASTER_FEVER_CHOOSE :			
			case    PROC_MASTER_WUP_GUESS :				
			case    PROC_MASTER_WUP_CHOOSE :
			case    PROC_MASTER_WUP_LIMIT:
			case 	PROC_MASTER_ERROR :   
			case 	PROC_MASTER_REPORT_ERROR :
			{
				return 1;		
			}	
			default : 	
			{
				return 0;		
			}		
		}
		
		
	}	
	return 0;
	
}

ULONG ulLastLampState ;
ULONG ulLampStatus_PAYOUT ;
ULONG ulLampStatus_DWUP ;
ULONG ulLampCount_PAYOUT ;//按键计时

void vMaster_LampProcessInitial( void )
{
	ulLastLampState = PROC_MASTER_MAX ;	
	ulLampStatus_PAYOUT = 0 ;
	ulLampStatus_DWUP = 0 ;
}
void vMaster_LampProcess( void )
{
	SLONG slWin;
	
	if(stcMaster.ulSceneState==3)
	{
		slWin =slSlave_WupWinRead();	
	}	
	else
	{
		slWin = slSlave_WinRead( );		
	}	
	if(stcMaster.ubDemoFlag==0)
	{
		if( ulLastLampState != stcMaster.ulState )
		{
			ulLastLampState = stcMaster.ulState ;
			
			switch( ulLastLampState )
			{
			case PROC_MASTER_GAME_INIT  :
					{
						vLamp_AllOff( ) ;
					}
					break ;	
			case PROC_MASTER_GAME_SCR :
					if( ulCredit_Read( DEF_GAME_ONLY_PLAY ) >= mGame_ReadSystemLimit( ) )
					{
						vLamp_On( LAMP_PCI_KEY_PAYOUT ) ;
					}
					break ;			
								
			case PROC_MASTER_GAME_BET :
					{
						if(stcMaster.ulSceneState==0) //正常游戏时才有这功能
						{
							vLamp_On( LAMP_PCI_KEY_MAXBET ) ;
							vLamp_On( LAMP_PCI_KEY_HELP ) ;	
						}				
						vLamp_On( LAMP_PCI_KEY_STOP3 ) ; //查看上比记录					
						vLamp_On( LAMP_PCI_KEY_STOP2 ) ; //选线
						vLamp_On( LAMP_PCI_KEY_START ) ;
						vLamp_On( LAMP_PCI_KEY_BET ) ;
						vLamp_Off( LAMP_PCI_KEY_PAYOUT ) ;
					}	
					break ;
			case PROC_MASTER_GAME_CHANCE :
					{
						vLamp_Off( LAMP_PCI_KEY_START ) ;
						vLamp_Off( LAMP_PCI_KEY_BET ) ;
						vLamp_Off( LAMP_PCI_KEY_MAXBET ) ;
						vLamp_Off( LAMP_PCI_KEY_HELP ) ;
						vLamp_Off( LAMP_PCI_KEY_STOP2 ) ; //选线
						vLamp_Off( LAMP_PCI_KEY_STOP3 ) ; //查看上比记录
						
					}
					break ;	
						
			case  PROC_MASTER_GAME_RUN :
					{
						vLamp_On( LAMP_PCI_KEY_START ) ;
						vLamp_On( LAMP_PCI_KEY_STOP1 ) ;
						vLamp_On( LAMP_PCI_KEY_STOP2 ) ;
						vLamp_On( LAMP_PCI_KEY_STOP3 ) ;
						vLamp_On( LAMP_PCI_KEY_STOP4 ) ;
						vLamp_On( LAMP_PCI_KEY_STOP5 ) ;
					}	
					break ;
			case PROC_MASTER_GAME_CHECK :
					{
						vLamp_Off( LAMP_PCI_KEY_START ) ;
						vLamp_Off( LAMP_PCI_KEY_STOP1 ) ;
						vLamp_Off( LAMP_PCI_KEY_STOP2 ) ;
						vLamp_Off( LAMP_PCI_KEY_STOP3 ) ;
						vLamp_Off( LAMP_PCI_KEY_STOP4 ) ;
						vLamp_Off( LAMP_PCI_KEY_STOP5 ) ;
					}	
					break ;	
							
			
			case PROC_MASTER_GAME_FREEEFT :			
			case PROC_MASTER_GAME_OVERALEFT :				
			case PROC_MASTER_GAME_BIGODDSEFT :				
			case PROC_MASTER_GAME_FEVEREFT :	
			case PROC_MASTER_GAME_BONUSEFT :	
					vLamp_On( LAMP_PCI_WINBIG  ) ;	
					vLamp_On( LAMP_PCI_WIN ) ;	
					break ;	
			case PROC_MASTER_GAME_EFT :	
					vLamp_On( LAMP_PCI_WIN ) ;	
					if((stcGameInfo.ulFreeNowLife==0)&&(stcGameInfo.ulFeverSetLife==0)
						&&(stcGameInfo.ulFreeSetLife==0)&&(stcGameInfo.ulBonusType==0))	
					{
						vLamp_On( LAMP_PCI_KEY_TAKE ) ;					
						if(mGame_ReadWupLimitTop())
						{							
							if(slWin <  (mGame_ReadWupLimitTop( )*2))
							{
								vLamp_On( LAMP_PCI_KEY_HWUP ) ;
								if(slWin <  mGame_ReadWupLimitTop( ))
								{
									vLamp_On( LAMP_PCI_KEY_WUP ) ;
									if(slWin <  (mGame_ReadWupLimitTop( )/2))
									{										
										if( ulCredit_Read( DEF_GAME_ONLY_PLAY ) >= slWin )
										{
											vLamp_On( LAMP_PCI_KEY_DWUP ) ;
										}
									}	
								}	
							}	
						}		
						
					}				
					break ;	
			case PROC_MASTER_GAME_CHOOSE :
				vLamp_Off( LAMP_PCI_KEY_START ) ;	
			case PROC_MASTER_WUP_CHOOSE :
					{
						vLamp_On( LAMP_PCI_KEY_TAKE ) ;					
						if(mGame_ReadWupLimitTop())
						{							
							if(slWin <  (mGame_ReadWupLimitTop( )*2))
							{
								vLamp_On( LAMP_PCI_KEY_HWUP ) ;
								if(slWin <  mGame_ReadWupLimitTop( ))
								{
									vLamp_On( LAMP_PCI_KEY_WUP ) ;									
								}	
							}	
						}				
						
					}
					break ;	
			case PROC_MASTER_GAME_EXIT:		
			case PROC_MASTER_WUP_INIT :
			case PROC_MASTER_FEVER_EXIT:
					vLamp_Off( LAMP_PCI_WIN ) ;
					if(stcGameInfo.ulFreeNowLife==0)
					{
						vLamp_Off( LAMP_PCI_WINBIG ) ;
					}		
			case PROC_MASTER_GAME_TAKE :		
			case PROC_MASTER_WUP_TAKE :
			case PROC_MASTER_WUP_GTAKE :	
			case PROC_MASTER_WUP_READY :
			case PROC_MASTER_WUP_EXIT :		
					{										
						vLamp_Off( LAMP_PCI_KEY_TAKE ) ;
						vLamp_Off( LAMP_PCI_KEY_WUP ) ;
						vLamp_Off( LAMP_PCI_KEY_HWUP ) ;
						vLamp_Off( LAMP_PCI_KEY_DWUP ) ;
						vLamp_Off( LAMP_PCI_KEY_BIG ) ;
						vLamp_Off( LAMP_PCI_KEY_SALL ) ;
					}
					break ;
			case PROC_MASTER_WUP_GUESS :
					{
						vLamp_On( LAMP_PCI_KEY_TAKE ) ;
						vLamp_On( LAMP_PCI_KEY_BIG ) ;
						vLamp_On( LAMP_PCI_KEY_SALL ) ;
					}
					break ;			
			case PROC_MASTER_WUP_CHANCE :
					{
						vLamp_Off( LAMP_PCI_KEY_TAKE ) ;
						vLamp_Off( LAMP_PCI_KEY_BIG ) ;
						vLamp_Off( LAMP_PCI_KEY_SALL ) ;
					}
					break ;	
			case  PROC_MASTER_WUP_LIMIT:						
			case  PROC_MASTER_FEVER_START :	
					vLamp_On( LAMP_PCI_KEY_START ) ;	
					break ;	
					
			case  PROC_MASTER_FEVER_RUN :	
					vLamp_Off( LAMP_PCI_KEY_START ) ;	
					break ;			
			}
		}		
		switch( ulLastLampState )	
		{
			case PROC_MASTER_GAME_CHOOSE :
			case PROC_MASTER_WUP_CHOOSE :
				{					
					if((slWin <  (mGame_ReadWupLimitTop( )/2))&&(mGame_ReadWupLimitTop())&&( ulCredit_Read( DEF_GAME_ONLY_PLAY ) >= slWin ))
					{										
						vLamp_On( LAMP_PCI_KEY_DWUP ) ;
					}	
					else
					{
						vLamp_Off( LAMP_PCI_KEY_DWUP ) ;
					}
				}
				break ;
		}
		if(stcMaster.ulSceneState<2)
		{
			vLamp_On( LAMP_PCI_KEY_AUTO ) ;
		}	
		else
		{
			vLamp_Off( LAMP_PCI_KEY_AUTO ) ;
		}		
		if( stcSlave[ DEF_GAME_ONLY_PLAY ].ubPayoutChoose )
		{
			if( stcSlave[ DEF_GAME_ONLY_PLAY ].ulError & DEF_SLAVE_ERROR_PAYOUT )
			{
				vLamp_On( LAMP_PCI_KEY_PAYOUT ) ;
			}
			else
			{			
				vLamp_Off( LAMP_PCI_KEY_PAYOUT ) ;
			}
		}
		else 
		{
			if(( ulCredit_Read( DEF_GAME_ONLY_PLAY ) >= mGame_ReadCoinRate( ) )&&
				( stcSlave[ DEF_GAME_ONLY_PLAY ].ulBet == 0 ))
			{
				vLamp_On( LAMP_PCI_KEY_PAYOUT ) ;
			}
			else
			{
				vLamp_Off( LAMP_PCI_KEY_PAYOUT ) ;
			}
		}
		
		if( stcSlave[ DEF_GAME_ONLY_PLAY ].ulError )
		{
			vLamp_On( LAMP_PCI_ERROR ) ;
		}
		else
		{	
			vLamp_Off( LAMP_PCI_ERROR ) ;
		}
		
		switch( stcMaster.ulState )	
		{
			case PROC_MASTER_GAME_OVERALEFT :				
			case PROC_MASTER_GAME_BIGODDSEFT :				
			case PROC_MASTER_FEVER_EFT :	
			case PROC_MASTER_GAME_BONUSEFT :
			case PROC_MASTER_GAME_EXITFREE: 
				 if(stcMaster.ulIndex == 1)
				 {
				 	vLamp_On( LAMP_PCI_KEY_TAKE ) ;					
					if(mGame_ReadWupLimitTop())
					{						
						if(slWin <  (mGame_ReadWupLimitTop( )*2))
						{
							vLamp_On( LAMP_PCI_KEY_HWUP ) ;
							if(slWin <  mGame_ReadWupLimitTop( ))
							{
								vLamp_On( LAMP_PCI_KEY_WUP ) ;
								if(slWin <  (mGame_ReadWupLimitTop( )/2))
								{										
									if( ulCredit_Read( DEF_GAME_ONLY_PLAY ) >= slWin )
									{
										vLamp_On( LAMP_PCI_KEY_DWUP ) ;
									}
								}	
							}	
						}	
					}
					
				 	
				 }		        
				 if(stcMaster.ulIndex == 2)
				 {
				 	vLamp_Off( LAMP_PCI_KEY_TAKE ) ;					
					if(mGame_ReadWupLimitTop())
					{
						vLamp_Off( LAMP_PCI_KEY_WUP ) ;
						vLamp_Off( LAMP_PCI_KEY_HWUP ) ;
				 		vLamp_Off( LAMP_PCI_KEY_DWUP ) ;
				 	}	
				 }		
				 break ;	
		}
		
	}		

	
	#ifdef DEF_OPEN_CHECK_PAYOUT_BOX_FULL
	if ( ulKey_Touch( KEY_PCI_POBOX_FULL ) )
	{
		if(ulLampStatus_PAYOUT==0)
		{
			ulLampCount_PAYOUT++;
			if(ulLampCount_PAYOUT>300)
			{
				ulLampStatus_PAYOUT = 1;
				ulLampCount_PAYOUT = 0;
				vLamp_On( LAMP_PCI_ERROR ) ;
			}		
		}	
		else
		{
			ulLampCount_PAYOUT = 0;
		}	
		
	}
	else
	{	
		if(ulLampStatus_PAYOUT)
		{
			ulLampCount_PAYOUT++;
			if(ulLampCount_PAYOUT>300)
			{
				ulLampStatus_PAYOUT = 1;
				ulLampCount_PAYOUT = 0;
				vLamp_Off( LAMP_PCI_ERROR ) ;
			}		
		}	
		else
		{
			ulLampCount_PAYOUT = 0;
		}		
		
	}		
	#endif

		
}

extern UBYTE ubGTHSZeroFlag ;
extern UBYTE ubGTVGZeroFlag ;

void vMaster_RunTimeProcess( void )
{
	ULONG	ulKey ;

	#ifdef DEF_USE_VGAME_UART_SLAVE
	if( ulUartCmdPollingCount )
	{
		ulUartCmdPollingCount -- ;
	}
	else
	{
		ubUartCmdSlaveOnLine[0] = 0 ;
	}
	
	if( stcChance.ulNoPlayTime )
	{
		stcChance.ulNoPlayTime -- ;
	}
	#endif

    // Every 1 Sec TimeUp
    if( ulInt_TimeUp() )
    {
        #if defined(DEF_FIX_NOGT_RECORD)
    	#else
    	#ifdef DEF_GTRULE_GTHS
        vGTHS_ReportCheck( mGame_ReadCoinRate() ) ;
		#endif
		#ifdef DEF_GTRULE_GTVG
		vGTVG_ReportCheck( mGame_ReadMoneyRate() ) ;
		#endif
		#endif
		// 总玩分数、总利润 超过时，不能继续游戏，强制清零
    	#ifdef DEF_GTRULE_GTHS
		if( ulGTHS_GetStatus( ) == DEF_GTHS_STATUS_ISOK )
		{
			if((dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALPLAY )/100000000)>90000000)
			{
				ubGTHSZeroFlag = 1 ;
			}
			if( slGTHS_GetToalProfit( ) > 90000000 )
			{
				ubGTHSZeroFlag = 1 ;
			}
		}
		#endif
		#ifdef DEF_GTRULE_GTVG
		if( ulGTVG_GetStatus( ) == DEF_GTVG_STATUS_ISOK )
		{
			if((dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALPLAY )/100000000)>90000000)
			{
				ubGTVGZeroFlag = 1 ;
			}
		}
		#endif
		
        #ifdef DEF_M100XX_ENABLE_SHUTDOWN
        vShutDown_HaltCD( ) ; 
        vShutDown_CheckCD( 1 ) ;
        #endif
        
		// Reset Timer
        vInt_TimeRun() ;
	}

	
    // 盚钵盽篈 陪ボ钵盽癟 ぃ瑈祘(э產ぃ祇甮紆)
    #ifdef DEF_GTRULE_GTHS
    if( ulGTHS_GetMode() )
    {
        if( ulGTHS_GetStatus() != DEF_GTHS_STATUS_ISOK )
    	{
            vShowRec_ShowReportError() ;
    	}
	}
	else
	{
        if( ulGTHS_GetStatus() == DEF_GTHS_STATUS_ZERO )
    	{
            vShowRec_ShowReportError() ;
    	}
	}
	#endif
    #ifdef DEF_GTRULE_GTVG
    if( ulGTVG_GetMode() )
    {
        if( ulGTVG_GetStatus() != DEF_GTVG_STATUS_ISOK )
    	{
            vShowRec_ShowReportError() ;
    	}
	}
	else
	{
        if( ulGTVG_GetStatus() == DEF_GTVG_STATUS_ZERO )
    	{
            vShowRec_ShowReportError() ;
    	}
	}
	#endif
	
	
    #ifdef DEF_M100XX_ENABLE_SHUTDOWN
    if( ulShutDown_IsHalt() )
    {
        vPcVideo2D_Img_ShowString( DEF_ANIMNO_SYSTEM_NO_MESSAGE , DEF_FONT_ASCII_000&0xFFFF , 50 , (DEF_PCVIDEO2D_SCREEN_H/2)-32 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_SYSTEM_NO_MESSAGE , DEF_RED , 48 , (char *)pShutDown_GetErrMsg() ) ;
    }
    if( ulMainPowerOnState == PROC_MAIN_POWERON_RUN )
    {
        // Θ块浪琩盞絏
        if( ubShutDown_CheckKey() )
        {
	    	if ( ulMaster_IsCanRecsys( ) )
	    	{	
		        vRecSys_Initial( ) ;
		        vMaster_LampProcessInitial( ) ;
		        vSound_StopAll( );
		        vPlaySound_Clean( );	       
	
				vShutDown_Break() ;
	            vShutDown_Reset() ;
	
		        ulMainPowerOnState = PROC_MAIN_POWERON_RECORD ;
		        ulMainOtherCount   = 0 ;
		        return ;
		    }
        }
    }
    #endif
	
	// 检查是否进入查账画面
	ulKey = 0 ;
	#ifdef DEF_TEST_AUTOPLAY
	if (( ulKey_Touch( KEY_PCI_97_TEST ) )&&( ulKey_Touch( KEY_PCI_97_RECORD ) ) )
	{
		ulKey_Push(KEY_PCI_97_RECORD) ;
		ulKey = 1 ;
	}
	#endif	
	#ifdef DEF_USE_IOPCI
    if (ulKey_Push(KEY_PCI_97_RECORD)) ulKey = 1 ;
	#endif    	
	
	if (ulKey_Push(KEY_RTN)) ulKey = 1 ;
    #ifdef DEF_M100XX_ENABLE_SHUTDOWN
    if( ulShutDown_IsHalt() ) ulKey = 0 ;
    #endif
	if( ulKey )
    {
    	if ( ulMaster_IsCanRecsys( ) )
    	{	
	        vRecSys_Initial( ) ;
	        vMaster_LampProcessInitial( ) ;
	        vSound_StopAll( );
	        vPlaySound_Clean( );	       
	        ulMainPowerOnState = PROC_MAIN_POWERON_RECORD ;
	        ulMainOtherCount   = 0 ;
	        return ;
	    }
	}
	
	// 检查是否离开Demo状态
	if (( stcMaster.ubDemoFlag )&&( ulCredit_Read( DEF_GAME_ONLY_PLAY ) ))
	{
		ulMainDemoCount = 0;
		vReel_AllNowStopRun();
		stcGameInfo.ulBonusValue = ulDemoBonusValue ;
		vSlave_SetLine(stcDemoBet.slLine);
	    vSlave_BetSet(stcDemoBet.slBet);
	    vShow_CleanHelpDis( );
    	vShow_CleanLineNum(); 
		vSlave_WinSet(0);	
		vSlave_WupWinSet(0);			
		stcMaster.ubDemoFlag = 0 ;			
		ulMainPowerOnState = PROC_MAIN_POWERON_RUN ;
		ulMainOtherState   = 0 ;
		ulMainOtherCount   = 0 ;
		
        if(stcMaster.ulState >= PROC_MASTER_WUP_INIT	)
		{
			vPcVideo2D_Img_Clean(DEF_ANIMNO_PLAYER_MESS) ;				
			vPcVideo2D_Img_Clean(DEF_ANIMNO_PLAYER_WUP_WIN) ;	
			vPcVideo2D_Img_CleanAry( DEF_ANIMNO_WUP_BG , DEF_ANIMNO_WUP_EFF_END) ;					
		}
		else if(stcMaster.ulState >= PROC_MASTER_FEVER_INIT	)
		{
			vPcVideo2D_Img_CleanAry( 0 , DEF_ANIMNO_FEVER_BG_END  ) ;
			vPcVideo2D_Img_CleanAry( DEF_ANIMNO_FEVER_CB , DEF_ANIMNO_FREER_END ) ;					
		}	
		else
		{
			vPcVideo2D_Img_CleanAry( DEF_ANIMNO_BG_FREE_SPIN ,DEF_ANIMNO_GAME_MAX ) ;
			vShow_CleanDeputySymbols();			 
			vPcVideo2D_Img_CleanAry( DEF_ANIMNO_ACT3_BG16 ,DEF_ANIMNO_ACT3_END) ;
			
		}	
			
		vScroll_LoadStopData( );  
		vScroll_LoadData();
		vScroll_RefreshShowScr( ) ; 
		vShow_SymbolsBase( );
		vMasterShow_BaseGame( ) ;	
		vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
		stcGameInfo.ulFreeNowLife = 0;	
		//while ( ulKey_RePush( KEY_1, 10 , 3 ) == 0 );	
		mSetMasterState( PROC_MASTER_GAME_INIT );
        return ;
	}
	// 检查是否进入Demo状态
	if (( stcMaster.ubDemoFlag==0 )&&( ulCredit_Read( DEF_GAME_ONLY_PLAY )==0 )&&(stcMaster.ulState < PROC_MASTER_GAME_START))
	{	

	    // 盚钵盽篈 產ぃ祇甮
	    #ifdef DEF_GTRULE_GTHS
	    if( ulGTHS_GetMode() )
	    {
	        if( ulGTHS_GetStatus() != DEF_GTHS_STATUS_ISOK )    { return ; }
	    }
	    else
	    { 
	        if( ulGTHS_GetStatus() == DEF_GTHS_STATUS_ZERO )    { return ; }
	    }
	    #endif
	    #ifdef DEF_GTRULE_GTVG
	    if( ulGTVG_GetMode() )
	    {
	        if( ulGTVG_GetStatus() != DEF_GTVG_STATUS_ISOK )    { return ; }
	    }
	    else
	    { 
	        if( ulGTVG_GetStatus() == DEF_GTVG_STATUS_ZERO )    { return ; }
	    }
	    #endif
		
		ulMainDemoCount++;
		if(ulMainDemoCount>=600)
		{			
			vLamp_AllOff( ) ;			
			vScroll_LoadStopData( );  
			vScroll_LoadData();
			vScroll_RefreshShowScr( ) ; 
			vShow_SymbolsBase( ); 
			vShow_CleanHelpDis( );	
			//vSlave_SetLastLine(9);
			stcDemoBet.slBet = slSlave_ReadBet();
			stcDemoBet.slLine = slSlave_ReadLine();
			ulDemoBonusValue = stcGameInfo.ulBonusValue;
		    vSlave_SetLine(9);
		    vSlave_BetSet(mGame_ReadMaxBet( ));
		    //vSlave_UpDateLastBet( );
		    vShow_CleanHelpDis( );
	    	vShow_CleanLineNum(); 
			ulMainOtherState   = 0 ;
			ulMainOtherCount   = 0 ;
	        ulMainPowerOnState = PROC_MAIN_POWERON_DEMO ;	        
	       	stcMaster.ubDemoFlag = 1 ;	       		
			vPlaySound_BG(DEF_WAV_MUSIC_DEMO_09,DEF_SOUND_VOL_WEAK,DEF_SOUND_CH_BG);
	        mSetMasterState( PROC_MASTER_GAME_LASTDIS );
	        return ;
		}	
		
	}
	
	
}


void vMaster_Process( void )
{
	UBYTE ubFlag;//界面刷新标志
	
	if ( !stcMaster.ubRunFlag )      return ;
    switch ( stcMaster.ulState )
    {   	
	    case PROC_MASTER_GAME_INIT 			:	vMaster_Game_Init( ) ;	   					break ;
	    case PROC_MASTER_GAME_SCR  			:	vMaster_Game_Scr( ) ;	   					break ;
	    case PROC_MASTER_GAME_BET   		:   vMaster_Game_Bet( ) ;						break ;
	    //case PROC_MASTER_GAME_ACT   		:   vMaster_Game_Act( ) ;						break ;
	    case PROC_MASTER_GAME_LASTDIS       :	vMaster_Game_LastDis( ) ;					break ;
        case PROC_MASTER_GAME_START 		:   vMaster_Game_Start( ) ; 					break ;
        case PROC_MASTER_GAME_CHANCE 		:   vMaster_Game_Chance( ) ; 					break ;
        case PROC_MASTER_GAME_RUN  			:   vMaster_Game_Run( ) ;  						break ;
        case PROC_MASTER_GAME_STOP   		:   vMaster_Game_Stop( ) ;   					break ;
        case PROC_MASTER_GAME_CHECK     	:   vMaster_Game_Check( ) ;     				break ;
        case PROC_MASTER_GAME_EFT    		:   vMaster_Game_Effect( ) ; 					break ;
        case PROC_MASTER_GAME_OVERALEFT		:   vMaster_Game_OverallEffect( ) ; 			break ;
        case PROC_MASTER_GAME_BIGODDSEFT	:   vMaster_Game_BigOddsEffect( ) ; 			break ;        	
        case PROC_MASTER_GAME_FEVEREFT  	:   vMaster_Game_FeverEffect(); 				break ;
        case PROC_MASTER_GAME_BONUSEFT  	:   vMaster_Game_BonusEffect(); 				break ;
        case PROC_MASTER_GAME_FREEEFT   	:   vMaster_Game_FreeEffect( ); 				break ;
        case PROC_MASTER_GAME_EXITFREE   	:   vMaster_Game_ExitFree( ); 					break ;	        
        case PROC_MASTER_GAME_CHOOSE	   	:   vMaster_Game_Choose( ); 					break ;        	
        case PROC_MASTER_GAME_TAKE      	:   vMaster_Game_Take( ) ;      				break ;
        case PROC_MASTER_GAME_EXIT      	:   vMaster_Game_Exit( ) ;      				break ;	                 
        	                                                                       	
        case PROC_MASTER_FEVER_INIT      	:   vMaster_Fever_Init( ) ;      				break ;
        case PROC_MASTER_FEVER_START		:   vMaster_Fever_Start( ) ;					break ;
        case PROC_MASTER_FEVER_CHANCE       :   vMaster_Fever_Chance( ) ; 	      			break ;
        case PROC_MASTER_FEVER_RUN			:   vMaster_Fever_Run( ) ;       				break ;
        case PROC_MASTER_FEVER_STOP      	:   vMaster_Fever_Stop( ) ;       				break ;
        case PROC_MASTER_FEVER_WIN			:   vMaster_Fever_Win( ) ;      				break ;
        case PROC_MASTER_FEVER_LOSE      	:   vMaster_Fever_Lose( ) ;       				break ;	
        case PROC_MASTER_FEVER_EFT  		:   vMaster_Fever_Effect( ) ;  					break ;
        case PROC_MASTER_FEVER_CHOOSE	   	:   vMaster_Fever_Choose( ); 					break ; 
        case PROC_MASTER_FEVER_TAKE  	   	:   vMaster_Fever_Take( ); 					    break ;         	       	
        case PROC_MASTER_FEVER_EXIT  		:   vMaster_Fever_Exit( ) ;  					break ;
        	
	    case PROC_MASTER_WUP_INIT			: 	vMaster_Wup_Init( ) ;						break ;
	    case PROC_MASTER_WUP_READY			: 	vMaster_Wup_Ready( ) ;						break ;	
	    case PROC_MASTER_WUP_GUESS			: 	vMaster_Wup_Guess( ) ;						break ;
	    case PROC_MASTER_WUP_GTAKE          :	vMaster_Wup_GTake( ) ;						break ;
	    case PROC_MASTER_WUP_CHANCE			: 	vMaster_Wup_Chance( ) ;						break ;
		case PROC_MASTER_WUP_EFT			: 	vMaster_Wup_Effect( ) ;						break ;
	    case PROC_MASTER_WUP_CHOOSE			: 	vMaster_Wup_Choose( ) ;						break ;
	    case PROC_MASTER_WUP_TAKE			: 	vMaster_Wup_Take( ) ;						break ;	
	    case PROC_MASTER_WUP_LIMIT			: 	vMaster_Wup_Limit( ) ;						break ;
	    case PROC_MASTER_WUP_EXIT  			: 	vMaster_Wup_Exit( ) ;						break ;    
	    	
	    case PROC_MASTER_REPORT_ERROR		:	vMaster_Stage_ReportError( ) ;				break ;
		case PROC_MASTER_PAY_OUT			:	vMaster_Stage_PayOut( );					break ;          
	    default :                   		                                           	
	    case PROC_MASTER_ERROR				:	vMaster_Stage_Error( ) ;					break ;    	
    }
    //while (ulKey_Touch( KEY_0 ) == 0 );
    vSlave_UiIsRefresh();    
    vSlaveShow_ShowWin();
    vSlaveShow_ShowBet();

	#ifdef DEF_TEST_ALWAYS_AUTO_2
	//#ifdef DEF_CHANCE_FOR_UART_SLAVE
    {
    	if( ulKey_Push( KEY_7 ) )
    	{
    		if( ubAutoPlay2_isRun )
    		{
    			ubAutoPlay2_isRun = 0 ;
   				stcMaster.ulAutoKeyState = 0 ;
    		}		
    		else
    		{
    			ubAutoPlay2_isRun = 1 ;
   				stcMaster.ulAutoKeyState = 2 ;
    		}
    	}
	}
	//#endif
	#endif
	
    #ifdef DEF_TEST_AUTOPLAY
	if ( ulKey_Touch( KEY_PCI_97_TEST ) )
	{
		if(stcMaster.ulTestCount==0)
		{
			vSound_StopAll( );
			vPlaySound_Clean( );//关闭声音
		}	
		stcMaster.ulTestCount++;
		vShow_GamePlayTimes( );   //快测时显示局数					
	}	 
	else	 
	#endif 
	{
		if(stcMaster.ulTestCount)
		{
			vPlaySound_RecSys( );
			stcMaster.ulTestCount=0;	
		}	
		vShowLib_GameMessage(stcMaster.ulCount,stcMaster.ulState);
		vShowLib_UiMessDis();
	    if(stcMaster.ulSceneState<2)
	    {
	    	if(stcMaster.ulSceneState)
	    	{
	    		if(ulKey_Push( KEY_PCI_AUTO))
		    	{
		    		stcMaster.ulAutoKeyState++;
		    		if(stcMaster.ulAutoKeyState>2)
		    		{
		    			stcMaster.ulAutoKeyState = 1;	       //自动功能
		    		}	    		
		    		ulUiAutoCount = 0;	
		    		stcMaster.ulSaveAutoKeyState = stcMaster.ulAutoKeyState;	    			
		    	}	
		    	#ifdef DEF_TEST_ALWAYS_AUTO_2
		    	/*
		    	if ( ubAutoPlay2_isRun )
		    	{
		    		stcMaster.ulAutoKeyState = 2 ;
		    	}
		    	*/
		    	#endif
	    		ubFlag = stcMaster.ulAutoKeyState;	
	    	}	
	    	else
	    	{
	    		if((ulCredit_Read(DEF_GAME_ONLY_PLAY)==0)&&(slSlave_WinRead()==0)&&(stcMaster.ulState<PROC_MASTER_GAME_BET))
		    	{
		    		if(stcMaster.ulAutoKeyState)
		    		{
		    			stcMaster.ulAutoKeyState = 0;	
		    			ubFlag = 0;
		    			ulUiAutoCount = 0;	    	
		    		}	
		    		
		    	}	
		    	else if(ulKey_Push( KEY_PCI_AUTO))
		    	{
		    		stcMaster.ulAutoKeyState++;
		    		if(stcMaster.ulAutoKeyState>2)
		    		{
		    			stcMaster.ulAutoKeyState = 0;	       //自动功能
		    		}	    		
		    		ulUiAutoCount = 0;	    			
		    	}	
		    	#ifdef DEF_TEST_ALWAYS_AUTO_2
		    	/*
		    	if ( ubAutoPlay2_isRun )
		    	{
		    		stcMaster.ulAutoKeyState = 2 ;
		    	}
		    	*/
		    	#endif
	    		ubFlag = stcMaster.ulAutoKeyState;	
	    		
	    	}	   	
	    	
	    	//vShow_DisUiAuto(ubFlag);	
	    	vShowLib_DisUiAuto(ubFlag);
	    	vScroll_Process(  ) ;
	    	vShowLib_UiBG(stcMaster.ulAllCount);
	    	vShowLib_GameMessage(stcMaster.ulCount,stcMaster.ulState);
	    }	
	    if(stcMaster.ulSceneState==0)
	    {
	    	vShowLib_UiBaseGame(stcMaster.ulAllCount);		
	    }	    
	    if(stcMaster.ulSceneState==1)
	    {
	    	vShowLib_UiFreeGame(stcMaster.ulAllCount);				    	
	    }		    
	    if(stcMaster.ulSceneState==3)
	    {
	    	vShowLib_WupMessage(stcMaster.ulCount,stcMaster.ulState);
	    	vShowLib_WupUi(stcMaster.ulAllCount);	
	    	vSlaveShow_ShowWupWin();	    	
	    }
	    if(stcMaster.ulSceneState==2)
	    {   
	    	if(stcMaster.ulState>=PROC_MASTER_GAME_FEVEREFT)//防止刚到主游戏还在刷新问题
	    	{
	    		vShowLib_FeverGameUIEffect(stcMaster.ulAllCount);	
		    	vScroll_FeverProcess();	
		    	vShowLib_FeverMessage(stcMaster.ulCount,stcMaster.ulState);
	    	}	 	
	    	
	    }
	} 	
    	
    stcMaster.ulAllCount++;	
    vMaster_LampProcess( ) ; 
    vSound_Proc( ) ;  
    vMaster_RunTimeProcess( ) ;  
    if( stcMaster.ulCount > 1010000000 ) stcMaster.ulCount -= 1000000000 ;
    if( stcMaster.ulAllCount > 1010000000 ) stcMaster.ulAllCount -= 1000000000 ;	
#ifdef DEF_DEFINE_SHOW_STATE
    if (ulKey_Push(KEY_SUB))
    {
    	if (ubGameShowState)
    	{
    		ubGameShowState = 0 ;
    	}
    	else
    	{
    		ubGameShowState = 1 ;
    	}
    	if (!ubGameShowState) vPcVideo2D_Img_CleanAry(DEF_ANIMNO_DEBUG , DEF_ANIMNO_DEBUG+36) ;
    }
#endif
	
    if ( ulTimer_IsActive( DEF_GAMETIMER_REC_GAMETIME ) )
    {
    	vRecord_GameSecAdd( 1 ) ;

    	#ifdef DEF_DEFINE_SHOW_STATE
	    	if (ubGameShowState) vMaster_ShowState( ) ;
		#endif
	}
//	vShowRec_ClsPage() ;
//	vShowrec_Value(stcMaster.ulSceneState,300,50);
//	vShowrec_Value(stcGameInfo.ulFreeNowLife,300,90);
	//vShowrec_Value(stcGameInfo.ulFreeNowLife,300,130);
    
}
