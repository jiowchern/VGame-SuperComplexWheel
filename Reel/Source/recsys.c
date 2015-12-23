#define DEF_RECSYS_C
#include "../../h/common.h"
#define FILE_NAME  "RECSYS.C"

#define DEF_BUFSHOW_PAGE_MAX    11

UBYTE h_ubVersionMemString[32] ;
ULONG h_ulVersionValue ;
ULONG ulRecordSysState ;
ULONG ulRecordSysCount ;
UBYTE ubRecordSysPage ;
ULONG ulRecordSysPassID ;
ULONG ulRecSys_BlinkMsg_Img , ulRecSys_BlinkMsg_AnimNo , ulRecSys_BlinkMsg_Flag , ulRecSys_BlinkMsg_Count ;
UBYTE ubRecordGetDipsw ;

#ifdef DEF_USE_IPCKEY_RECORD
#define DEF_IPCRECKEY_UP		KEY_PCI_GIP03
#define DEF_IPCRECKEY_DOWN		KEY_PCI_GIP04
#define DEF_IPCRECKEY_LEFT		KEY_PCI_GIP05
#define DEF_IPCRECKEY_RIGHT		KEY_PCI_GIP06
#define DEF_IPCRECKEY_ENTER		KEY_PCI_GIP07
#define DEF_IPCRECKEY_CHECK		KEY_PCI_GIP17
#endif

UBYTE ubRecSys_GetNumberKey(ULONG mode)
{
	if (ulKey_Push(KEY_0))	return 0 ;
	if (ulKey_Push(KEY_1))	return 1 ;
	if (ulKey_Push(KEY_2))	return 2 ;
	if (ulKey_Push(KEY_3))	return 3 ;
	if (ulKey_Push(KEY_4))	return 4 ;
	if (ulKey_Push(KEY_5))	return 5 ;
	if (ulKey_Push(KEY_6))	return 6 ;
	if (ulKey_Push(KEY_7))	return 7 ;
	if (ulKey_Push(KEY_8))	return 8 ;
	if (ulKey_Push(KEY_9))	return 9 ;

	#ifdef DEF_USE_IOPCI
	if( mode )
	{
		#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(KEY_PCI_GIP07))	return 0 ;
		if (ulKey_Push(KEY_PCI_GIP03))	return 1 ;
		if (ulKey_Push(KEY_PCI_GIP04))	return 2 ;
		if (ulKey_Push(KEY_PCI_GIP05))	return 3 ;
		if (ulKey_Push(KEY_PCI_GIP06))	return 4 ;
		if (ulKey_Push(KEY_PCI_GIP18))	return 5 ;
		if (ulKey_Push(KEY_PCI_GIP08))	return 6 ;
		if (ulKey_Push(KEY_PCI_GIP17))	return 7 ;
		if (ulKey_Push(KEY_PCI_GIP19))	return 8 ;
		if (ulKey_Push(KEY_PCI_GIP27))	return 9 ;
		#else
		if (ulKey_Push(KEY_PCI_STOP1))	return 1 ;
		if (ulKey_Push(KEY_PCI_STOP2))	return 2 ;
		if (ulKey_Push(KEY_PCI_STOP3))	return 3 ;
		if (ulKey_Push(KEY_PCI_STOP4))	return 4 ;
		if (ulKey_Push(KEY_PCI_STOP5))	return 5 ;
		if (ulKey_Push(KEY_PCI_TAKE))	return 6 ;
		if (ulKey_Push(KEY_PCI_HELP))	return 7 ;
		if (ulKey_Push(KEY_PCI_AUTO))	return 8 ;
		if (ulKey_Push(KEY_PCI_START))	return 9 ;
		if (ulKey_Push(KEY_PCI_MAXBET))	return 0 ;
		#endif	
	}
	#endif		
	
	return 10 ;
}

extern UBYTE ubPasswordInputKey[8] ;
extern ULONG ulPasswordInputIndex ;

SLONG slRecSys_Password_Input( void )
{
	ULONG ulKeyInput ;
	
	ulKeyInput = ubRecSys_GetNumberKey( 1 ) ;
	if ( ulKeyInput < 10 )
	{
		ubPasswordInputKey[ulPasswordInputIndex] = ulKeyInput ;
		ulPasswordInputIndex ++ ;
		if ( ulPasswordInputIndex >= 8 )
		{
			return ( 2 ) ;
		}
		return ( 1 ) ;
	}
	return ( 0 ) ;
}

void vRecSys_SetState(ULONG ulState)
{
    if( ulState >= E_RECSYS_STATE_MAX ) return ;

    ulRecordSysState = ulState ;
    ulRecordSysCount = 0 ;
    ubRecordSysPage = 0 ;
}

// 第一次進到查賬畫面，就會被執行的第一個流程
// 所以做一些相關數據的初始化動作
void vRecSys_Init(void) // E_RECSYS_STATE_INIT
{
    switch (ulRecordSysCount)
    {
        case 0 :
			// 婃礿翋蚔牁雄釬
			vMaster_Stop() ;
            vShareData_Write( DEF_SHAREDATA_ARM_SYSHALT , 1 ) ;

            vShowRec_Init() ;
            vSound_StopAll() ;
            vSSR_AllOff() ;

            ulRecordSysCount = 1 ;
            break ;

        case 1 :
            ulRecordSysPassID = 0 ;
            vRecSys_SetState(E_RECSYS_STATE_MAIN_MENU) ;
            break ;
    }
}

// 離開查賬畫面前，會被執行的最後一個流程
// 所以做一些，返回主遊戲前的一些設定
void vRecSys_Exit(void)
{
    switch (ulRecordSysCount)
    {
        case 0 :
            vShowRec_Exit() ;
			//vMaster_ReCover() ;
			//vSlave_ReCover() ;

            ulRecordSysCount = 1 ;
            break ;

        case 1 :
			// 笭陔ゐ雄翋蚔牁霜最
			//vMaster_Initial( ) ; // 祥夔植芛羲宎ㄛ斛剕植輛�賮蒱昐�
			//vMaster_RecReCover() ;
			vMaster_Run( ) ;
    		vShareData_Write( DEF_SHAREDATA_ARM_SYSHALT , 0 ) ;
    		vShow_GameCleanAll() ;
    		//vShow_Init( ) ;
    		vPlaySound_RecSys( );    		
    		vReel_AllNowStopRun();	
    		stcSlave[DEF_GAME_ONLY_PLAY].ulError = 0 ; //ь壺渣昫陓洘
    		stcSlave[DEF_GAME_ONLY_PLAY].ubPayoutChoose = 0 ;
    		stcSlaveShow[DEF_GAME_ONLY_PLAY].ulPayoutErrorCount=0;
    		stcSlaveShow[DEF_GAME_ONLY_PLAY].ulCoinErrorCount=0;
    		stcSlaveShow[DEF_GAME_ONLY_PLAY].ulErrorCount = 0; 
			ulMainOtherState   = 0 ;
			ulMainOtherCount   = 0 ;
			if( stcMaster.ubDemoFlag)	
			{
				stcGameInfo.ulFreeNowLife = 0;	
				vSlave_WinSet(0);	
				vSlave_WupWinSet(0);	
				vShow_SymbolsBase( );							
        		ulMainPowerOnState = PROC_MAIN_POWERON_DEMO ;	
				mSetMasterState( PROC_MASTER_GAME_BET );
			}
			else
			{
				//vMasterShow_RecSysScreen( ) ;
				vMasterShow_PowerOnScreen( );
				ulMainPowerOnState = PROC_MAIN_POWERON_RUN ;	
			}
            break ;
    }
}

ULONG ulRecSys_MasterOPKey( ULONG ulMaxPage , ULONG ulLastStage )
{
	ULONG	ulKey ;
	
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI		
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_DOWN)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_STOP2)) ulKey = 1 ;
#endif    	
#endif    	
    if ((ulKey_Push(KEY_ADD))||(ulKey_Push(KEY_2))) ulKey = 1 ;
    if( ulKey )
	{
		ubRecordSysPage ++ ;
		if( ubRecordSysPage >= ulMaxPage ) ubRecordSysPage = 0 ;
		ulRecordSysCount = 0 ;
		return 1 ;
	}
		
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI		
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_UP)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_STOP1)) ulKey = 1 ;
#endif    	
#endif    	
    if ((ulKey_Push(KEY_SUB))||(ulKey_Push(KEY_8))) ulKey = 1 ;
    if( ulKey )
	{
		if( ubRecordSysPage ) ubRecordSysPage -- ;
		else ubRecordSysPage = ulMaxPage-1 ;
		ulRecordSysCount = 0 ;
		return 1 ;   				
	}

	if( ulLastStage )
	{
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_ENTER)) ulKey = 1 ;
	#else	
	    if ((ulKey_Push(KEY_PCI_START))||(ulKey_Push(KEY_PCI_97_RECORD))) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if (ulKey_Push(KEY_RTN)) ulKey = 1 ;
	    if( ulKey )
	    {
	        vRecSys_SetState(ulLastStage) ;
	        return 1 ;
	    }
    }
    
    return 0 ;
}

void vRecSys_Main(void) // E_RECSYS_STATE_MAIN_MENU // 第一頁主選單
{
	ULONG	ulKey ;
	
    if( ulRecordSysCount == 0 )
    {
        vShowRec_MainMenu() ;
        vShowRec_MainPage( ubRecordSysPage ) ;

        ulRecordSysCount ++ ;
    }

    #ifdef DEF_DEFINE_DEBUG_ENABLE
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(KEY_PCI_97_TEST)) ulKey = 1 ;
#endif
#endif		
	if (ulKey_Push(KEY_DOT)) ulKey = 1 ;
 	if ( ulKey )
    {
        vRecSys_SetState(E_RECSYS_STATE_BUFSHOW) ; // 進入測試用的查內部數據畫面
        return ;
    }
    #endif
   
   	if( ulRecSys_MasterOPKey( 7 , 0 ) )
   	{
   		return ;
   	}
   	     
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_ENTER)) ulKey = 1 ;
#else	
    if ((ulKey_Push(KEY_PCI_START))||(ulKey_Push(KEY_PCI_97_RECORD))) ulKey = 1 ;
#endif    	
#endif    	
    if ((ulKey_Push(KEY_RTN))||(ulKey_Push(KEY_4))||(ulKey_Push(KEY_6))) ulKey = 1 ;
    if( ulKey )
    {
        switch( ubRecordSysPage )
        {
			case 0 : 
				{
					ulRecordSysPassID = 0 ;
	                vRecSys_SetState(E_RECSYS_STATE_MASTER_CUR) ; // 當期記錄
				}
				break ;
	        case 1 :
	            {
	                vRecSys_SetState(E_RECSYS_STATE_MASTER_LAST) ; // 當期記錄
	            }
	            break ;
	        case 2 :
	            {
	                ulRecordSysPassID  = DEF_PASSWORD_ID_00 ;
	                ulRecSys_LastState = E_RECSYS_STATE_MAIN_MENU ;
	                ulRecSys_NextState = E_RECSYS_STATE_MASTER_TOL ;
	                vRecSys_SetState(E_RECSYS_STATE_PASSWORD) ; // 進入總額記錄前，必須先輸入密碼
	            }
	            break ;
            case 3 : // 參數調整
            	{
	                vAdjustValue_Setup( ) ;
				    #ifdef DEF_ENABLE_MULTI_SELECT
				    vAdjustGameSel_Setup() ;
				    #endif
					#ifdef DEF_USE_VGAME_UART_SLAVE
				    vAdjustSlaveIDSel_Setup() ; 
				    #endif
	                vShowRec_SaveBackupTime( ) ; // NowTime to BackupStr
	                vPassword_IDToFix( DEF_PASSWORD_ID_00 ) ;

	                ulRecordSysPassID = DEF_PASSWORD_ID_00 ;
	                ulRecSys_LastState = E_RECSYS_STATE_MAIN_MENU ;	
	                ulRecSys_NextState = E_RECSYS_STATE_ADJUST_DIRECT ;	               
	                vRecSys_SetState(E_RECSYS_STATE_PASSWORD) ; // 進入參數調整前，必須先輸入密碼 
	            }
                break ;                
            case 4 : // 歸零
            	{
	                ulRecordSysPassID = DEF_PASSWORD_ID_00 ;
	                ulRecSys_LastState = E_RECSYS_STATE_MAIN_MENU ;
	                ulRecSys_NextState = E_RECSYS_STATE_REPORT_RESET ;
	                vRecSys_SetState(E_RECSYS_STATE_PASSWORD) ; 
	            }
                break ;
            case 5 : // 測試
            	ulKey = 0 ;
			#ifdef DEF_USE_IOPCI	
			#ifdef DEF_USE_IPCKEY_RECORD
				if (ulKey_Touch(KEY_PCI_GIP23)) ulKey = 1 ;
			#endif
			#endif					
                if( ulKey_Touch( KEY_MUL ) ) ulKey = 1 ;
                if( ulKey )
                {
                    vRecSys_SetState(E_RECSYS_STATE_TESTQC) ; 
                }
                else
                {
                    vRecSys_SetState(E_RECSYS_STATE_TEST) ; 
                }
                break ;
            case 6 : // 離開
                {
                    vRecSys_SetState(E_RECSYS_STATE_EXIT) ;
                }
                break ;
        }
    }
}

void vRecSys_MasterCur(void) // E_RECSYS_STATE_MASTER_CUR // 當期記錄
{
	ULONG	ulKey ;
	
    if( ulRecordSysCount == 0 )
    {
        vShowRec_MasterCurPage(ulRecordSysState,ubRecordSysPage,ulRecordSysPassID) ;

        ulRecordSysCount++ ;
    }
    
    if( ulRecSys_MasterOPKey( 5 , E_RECSYS_STATE_MAIN_MENU ) )
    {
    	return ;
    }

	if( ubRecordSysPage == 2 )
	{
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI	
	#ifdef DEF_USE_IPCKEY_RECORD
		if ((ulKey_Push(KEY_PCI_GIP19))&&(ulKey_Touch(DEF_IPCRECKEY_ENTER))) ulKey = 1 ;
	#endif
	#endif	
		if ((ulKey_Push(KEY_DOT))&&(ulKey_Touch(KEY_0))) ulKey = 1 ;
		if ( ulKey )
	    {
	        vRecSys_SetState(E_RECSYS_STATE_BUFSHOW) ; // 進入測試用的查內部數據畫面
	        return ;
	    }
	}
       
	if( ubRecordSysPage == 0 )
	{
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI	
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_CHECK)) ulKey = 1 ;
	#else	
	    if (ulKey_Push(KEY_PCI_MAXBET)) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if (ulKey_Push(KEY_MUL)) ulKey = 1 ;
	    if( ulKey )
	    {
	        if(!ubRecord_IsSame( DEF_RECORD_PLR_ALL , DEF_RECORD_MAIN_PLAYTIMES ))
	        {   // 如果遊戲次數不是相同的就可以更新（交班）
	            // 防止連續更新後，當期上期都變成零
	            vRecord_UpDate() ;
	            ulRecordSysCount = 0 ;
	        }
	        return ;
	    }
	}
	
	if(( ubRecordSysPage == 3 )||( ubRecordSysPage == 4 ))
	{		 
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_RIGHT)) ulKey = 1 ;
	#else	
	    if ((ulKey_Push(KEY_PCI_STOP4))||(ulKey_Push(KEY_PCI_START))) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if ((ulKey_Push(KEY_6))||(ulKey_Push(KEY_RTN))) ulKey = 1 ;
	    if( ulKey )
	    {
	        ulRecordSysPassID += 10 ;
	        if( ulRecordSysPassID > 90 ) ulRecordSysPassID = 0 ;
	        ulRecordSysCount = 0 ;	
	    }
	    
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_LEFT)) ulKey = 1 ;
	#else	
	    if (ulKey_Push(KEY_PCI_STOP3)) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if (ulKey_Push(KEY_4)) ulKey = 1 ;
	    if( ulKey )
	    {
	        if( ulRecordSysPassID >= 10 ) ulRecordSysPassID -= 10 ;
	        else ulRecordSysPassID = 90 ;	
	        ulRecordSysCount = 0 ;		
	    }
	}
}

void vRecSys_MasterLast(void) // E_RECSYS_STATE_MASTER_LAST // 當期記錄
{	
    if( ulRecordSysCount == 0 )
    {
        vShowRec_MasterCurPage(ulRecordSysState,ubRecordSysPage,ulRecordSysPassID) ;

        ulRecordSysCount++ ;
    }
    
    if( ulRecSys_MasterOPKey( 2 , E_RECSYS_STATE_MAIN_MENU ) )
    {
    	return ;
    }
       
}

void vRecSys_MasterTol(void) // E_RECSYS_STATE_MASTER_TOL // 總額記錄
{	
    if( ulRecordSysCount == 0 )
    {
        vShowRec_MasterCurPage(ulRecordSysState,ubRecordSysPage,ulRecordSysPassID) ;

        ulRecordSysCount++ ;
    }

    if( ulRecSys_MasterOPKey( 2 , E_RECSYS_STATE_MAIN_MENU ) )
    {
    	return ;
    }
       
}

void vRecSys_AdjDirect(void) // E_RECSYS_STATE_ADJUST_DIRECT // 直接調整
{
    ULONG   ulRecordEnter ;
    ULONG	ulKey ;

    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 0 ;

        vShowRec_DirAdjMenu() ;
        vShowRec_DirAdjPage( ubRecordSysPage ) ;
        
        #ifdef DEF_USE_DIPSW_SET_SLAVEID_x	
        ubRecordGetDipsw = ~ubDipSw_Read( ) ;
		#endif
		
        ulRecordSysCount ++ ;
    }
    if( ubShowRec_UpdateAdjTime( ) )
    {
        vShowRec_DirAdjPage_ByTime( ) ;
    }

	{	    
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_DOWN)) ulKey = 1 ;
	#else	
	    if (ulKey_Push(KEY_PCI_STOP2)) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if ((ulKey_Push(KEY_ADD))||(ulKey_Push(KEY_2))) ulKey = 1 ;
	    if( ulKey )
	    {
	        ubRecordSysPage ++ ;
	        if( ubRecordSysPage > (ulShowRec_GetDirAdjPageItemMax( )-1) ) ubRecordSysPage = 0 ;
	
	        vShowRec_DirAdjPage( ubRecordSysPage ) ;
	    }
	    	    
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_UP)) ulKey = 1 ;
	#else	
	    if (ulKey_Push(KEY_PCI_STOP1)) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if ((ulKey_Push(KEY_SUB))||(ulKey_Push(KEY_8))) ulKey = 1 ;
	    if( ulKey )
	    {
	        if( ubRecordSysPage ) ubRecordSysPage -- ;
	        else ubRecordSysPage = (ulShowRec_GetDirAdjPageItemMax( )-1) ;
	
	        vShowRec_DirAdjPage( ubRecordSysPage ) ;
	    }

	    ulRecordEnter = 0 ;
	    
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if ((ulKey_Push(DEF_IPCRECKEY_RIGHT))||(ulKey_Push(DEF_IPCRECKEY_ENTER))) ulKey = 1 ;
	#else	
	    if ((ulKey_Push(KEY_PCI_STOP4))||(ulKey_Push(KEY_PCI_START))) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if ((ulKey_Push(KEY_6))||(ulKey_Push(KEY_RTN))) ulKey = 1 ;
	    if( ulKey )
	    {
	        ulRecordEnter = 1 ;
	    }
	    
		ulKey = 0 ;
	#ifdef DEF_USE_IOPCI		
	#ifdef DEF_USE_IPCKEY_RECORD
		if (ulKey_Push(DEF_IPCRECKEY_LEFT)) ulKey = 1 ;
	#else	
	    if (ulKey_Push(KEY_PCI_STOP3)) ulKey = 1 ;
	#endif	    	
	#endif    	
	    if (ulKey_Push(KEY_4)) ulKey = 1 ;
	    if( ulKey )
	    {
	        ulRecordEnter = 2 ;
	    }
	}
	
	#ifdef DEF_USE_DIPSW_SET_SLAVEID_x
	if( ubRecordGetDipsw != ubDipSw_Read( ) )
	{
		vDipSw_Initial( ) ;
		ubRecordGetDipsw = ubDipSw_ReadSaveData( ) ;
		
        vShowRec_DirAdjPage_ByDipsw( ) ;
	}
	#endif
	
    if ( ulRecordEnter )
    {
        switch( ulShowRec_GetAdjValueID( E_RECSYS_STATE_ADJUST_DIRECT , ubRecordSysPage ) )
        {
            case DEF_ADJUSTVALUE_SYS_TIME :
                // 調整系統時間
                vRecSys_SetState(E_RECSYS_STATE_ADJUST_TIME) ; 
                break ;

            case DEF_ADJUSTVALUE_DEF_MAX+1 :
                // 修改密碼（總額密碼）
                vRecSys_SetState(E_RECSYS_STATE_FIX_PASSWORD) ; 
                break ;

            case DEF_ADJUSTVALUE_DEF_MAX+2 :
                // 恢復默認值
                vShowRec_ResetAdjValue( E_RECSYS_STATE_ADJUST_DIRECT ) ;
                ulRecordSysCount = 0 ;
                break ;
            case DEF_ADJUSTVALUE_DEF_MAX+3 :
                // 保存並離開
                if(ulAdjustValue_ReadBitValue(DEF_ADJUSTVALUE_MAX_BET)!=ulAdjustValue_ReadTempBits(DEF_ADJUSTVALUE_MAX_BET))//党蜊善郔湮挹煦載陔剞攜
                {
                	vAdjustValue_UpDate( ) ;
                	vChance_VirtualAllTopValue( );
                	vChance_RecBetArrayReset( );
                }
                else
                {
                	vAdjustValue_UpDate( ) ;
                }	
                
                vPCGame_AdjustValue( ) ;

                vShowRec_SaveBackupTimeToRTC( ) ; // BackupStr to GTHS_SetSysDate time
                //vGTHS_UpdateSysTime() ; // 140822
                slPassword_CheckFix( DEF_PASSWORD_ID_00 ) ;

				#ifdef DEF_USE_VGAME_UART_SLAVE
				ubUartCmdSetAdjust = 1 ;
				vAdjustValue_ValueToLink( ) ;
				#endif
                #ifdef DEF_ENABLE_MULTI_SELECT
                if( ulAdjustGameSel_Read() != ulAdjustGameSel_ReadTemp() )
                {
                    vAdjustGameSel_UpDate() ;
                    vRecSys_SetState( E_RECSYS_STATE_HALT ) ;
                    break ;
                }
                #endif
				#ifdef DEF_USE_VGAME_UART_SLAVE
                if( ulAdjustSlaveIDSel_Read() != ulAdjustSlaveIDSel_ReadTemp() )
                {
                    vAdjustSlaveIDSel_UpDate() ;
                }
                #endif
                
                ulRecSys_BlinkMsg_Img = mHSRecord_GetImg( mGame_ReadFontType() , DEF_HSRIMG_C_040 ) ;
                ulRecSys_BlinkMsg_AnimNo = DEF_ANIMNO_RECORD_MSG ;
                ulRecSys_BlinkMsg_Count = 9999 ;
                ulRecSys_NextState = E_RECSYS_STATE_MAIN_MENU ;
                vRecSys_SetState(E_RECSYS_STATE_BLINK_MSG) ;
                break ;
            case DEF_ADJUSTVALUE_DEF_MAX+4 :
                // 離開
                vRecSys_SetState(E_RECSYS_STATE_MAIN_MENU) ;
                break ;
                
           	#ifdef DEF_USE_VGAME_UART_SLAVE
           	case DEF_ADJUSTVALUE_DEF_MAX+5 :
           		break ;
           	#endif     

            default :
                if( ulRecordEnter == 1 )
                {
                    vShowRec_IncAdjValue( E_RECSYS_STATE_ADJUST_DIRECT , ubRecordSysPage ) ;
                    vShowRec_DirAdjPage( ubRecordSysPage ) ;
                }
                else
                {
                    vShowRec_DecAdjValue( E_RECSYS_STATE_ADJUST_DIRECT , ubRecordSysPage ) ;
                    vShowRec_DirAdjPage( ubRecordSysPage ) ;
                }
                break ;
        }
    }
}

extern void vRecSys_SetPtset_patrandom( void ) ;

void vRecSys_AdjTime(void) // E_RECSYS_STATE_ADJUST_TIME // 調整系統時間
{
    ULONG   ulRecordEnter ;
    ULONG	ulKey ;

    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 2 ;

        vShowRec_TimeAdjMenu() ;
        vShowRec_TimeAdjPage( ubRecordSysPage ) ;

        ulRecordSysCount ++ ;
    }

    ulRecordEnter = ubRecSys_GetNumberKey( 0 ) ;
    if( ulRecordEnter < 10 )
    {
        ubRecSysShowSTR[ubRecordSysPage] = ulRecordEnter+'0' ;
        vShowRec_TimeAdjFixValue( ) ;
    }

	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_RIGHT)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_STOP4)) ulKey = 1 ;
#endif    	
#endif    	
   	if ((ulKey_Push(KEY_ADD))||( ulRecordEnter < 10 )) ulKey = 1 ;
    if( ulKey )	
    {
        ubRecordSysPage ++ ;
        switch( ubRecordSysPage )
        {
        case 4 : case 7 : case 11 : case 14 : case 17 :
            ubRecordSysPage ++ ;
            break ;
        case 10 :
            ubRecordSysPage += 2 ;
            break ;
        case 20 :
            ubRecordSysPage = 0 ;
            break ;
        }
        vShowRec_TimeAdjPage( ubRecordSysPage ) ;
    }

	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_LEFT)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_STOP3)) ulKey = 1 ;
#endif    	
#endif    	
    if (ulKey_Push(KEY_SUB)) ulKey = 1 ;
    if( ulKey )	
    {
        if( ubRecordSysPage ) ubRecordSysPage -- ;
        else ubRecordSysPage = 19 ;
        switch( ubRecordSysPage )
        {
        case 4 : case 7 : case 10 : case 14 : case 17 :
            ubRecordSysPage -- ;
            break ;
        case 11 :
            ubRecordSysPage -= 2 ;
            break ;
        }
        vShowRec_TimeAdjPage( ubRecordSysPage ) ;
    }

#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_UP))
#else	
	if(ulKey_Push(KEY_PCI_STOP1))
#endif		
	{	// -
		ubRecSysShowSTR[ubRecordSysPage] -- ;
		if( ubRecSysShowSTR[ubRecordSysPage] < '0' ) ubRecSysShowSTR[ubRecordSysPage] = '9' ;
		
		vShowRec_TimeAdjFixValue( ) ;
		vShowRec_TimeAdjPage( ubRecordSysPage ) ;
	}
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_DOWN))
#else	
	if(ulKey_Push(KEY_PCI_STOP2))
#endif		
	{	// +
		ubRecSysShowSTR[ubRecordSysPage] ++ ;
		if( ubRecSysShowSTR[ubRecordSysPage] > '9' ) ubRecSysShowSTR[ubRecordSysPage] = '0' ;		
			
		vShowRec_TimeAdjFixValue( ) ;	
		vShowRec_TimeAdjPage( ubRecordSysPage ) ;	
	}	
#endif

	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_CHECK)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_MAXBET)) ulKey = 1 ;
#endif    	
#endif    	
    if (ulKey_Push(KEY_MUL)) ulKey = 1 ;
    if( ulKey )	
    {   // 確認修改
        vShowRec_TimeAdjUpdata( ) ; // str to BackupStr

        vRecSys_SetState(E_RECSYS_STATE_ADJUST_DIRECT) ; // 回 直接調整
        return ;
    }

	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_ENTER)) ulKey = 1 ;
#else	
	if ((ulKey_Push(KEY_PCI_START))||(ulKey_Push(KEY_PCI_97_RECORD))) ulKey = 1 ;
#endif		
#endif    	
	if (ulKey_Push(KEY_RTN)) ulKey = 1 ;
	if( ulKey )
    {
        vRecSys_SetState(E_RECSYS_STATE_ADJUST_DIRECT) ; // 回 直接調整
        return ;
    }
}

void vRecSys_ReportReset(void) // E_RECSYS_STATE_REPORT_RESET // 歸零打碼
{
	ULONG	ulKey ;
	
    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 0 ;
        vShowRec_ReportResetMenu() ;
    }

    if( (ulRecordSysCount % 60) ==  0 )
    {
        vShowRec_ReportPasswordPage( 0 ) ;
    }
    if( (ulRecordSysCount % 60) == 30 )
    {
        vShowRec_ReportPasswordPage( 1 ) ;
    }
    ulRecordSysCount ++ ;
    
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI	
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_CHECK)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_MAXBET)) ulKey = 1 ;
#endif    	
#endif    	
    if( ulKey_Push(KEY_MUL) ) ulKey = 1 ;
    if( ulKey )
    {
    	vVersion_Break( ) ;
	#ifdef DEF_NO_GTRULE	
		vRecord_Reset( ) ;
	#endif
    	
        vRecSys_SetState(E_RECSYS_STATE_RESET) ;
        return ;
    }
    
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI	
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_ENTER)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_START)) ulKey = 1 ;
#endif    	
#endif    	
    if( ulKey_Push(KEY_RTN) ) ulKey = 1 ;
    if( ulKey )
    {
        vRecSys_SetState(E_RECSYS_STATE_MAIN_MENU) ;
        return ;
    }
}

#define DEF_SHOWREC_MSG_X   512
#define DEF_SHOWREC_MSG_Y   600

void vRecSys_Password(void) // E_RECSYS_STATE_PASSWORD
{
    ULONG   ulRecordEnter ;

    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 0 ;

        vShowRec_RecordPasswordMenu() ;
        vShowRec_RecordPasswordPage( ubRecordSysPage ) ;

        ulRecordSysCount ++ ;
    }

    ulRecordEnter = slRecSys_Password_Input() ;

    if( ulRecordEnter )
    {
        if( slPassword_ReadInputIndex( ) > ubRecordSysPage )
        {
            ubRecSysShowSTR[ubRecordSysPage] = '*' ;
            ubRecordSysPage = slPassword_ReadInputIndex( ) ;

            vShowRec_RecordPasswordPage( ubRecordSysPage ) ;
        }

        // finish.
        if( ulRecordEnter == 2 )
        {
            if( slPassword_Check( ulRecordSysPassID ) )
            {
            	ubRecordSysPage = 0 ;
            	
                vRecSys_SetState( ulRecSys_NextState ) ;
            }
            else
            {
                ulRecSys_BlinkMsg_Img = mHSRecord_GetImg( mGame_ReadFontType() , DEF_HSRIMG_C_042 ) ;
                ulRecSys_BlinkMsg_AnimNo = DEF_ANIMNO_RECORD_MSG ;
                ulRecSys_BlinkMsg_Count = 9999 ;
                ulRecSys_NextState = ulRecSys_LastState ;
                vRecSys_SetState(E_RECSYS_STATE_BLINK_MSG) ;
            }
            return ;
        }
    }
}

void vRecSys_FixPassword(void) // E_RECSYS_STATE_FIX_PASSWORD
{
    ULONG   ulRecordEnter ;

    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 0 ;

        vShowRec_FixPassword1Menu() ;
        vShowRec_RecordPasswordPage( ubRecordSysPage ) ;

        ulRecordSysCount ++ ;
    }

    ulRecordEnter = slRecSys_Password_Input( ) ;

    if( ulRecordEnter )
    {
        if( slPassword_ReadInputIndex( ) > ubRecordSysPage )
        {
            ubRecSysShowSTR[ubRecordSysPage] = '*' ;
            ubRecordSysPage = slPassword_ReadInputIndex( ) ;

            vShowRec_RecordPasswordPage( ubRecordSysPage ) ;
        }

        // finish.
        if( ulRecordEnter == 2 )
        {
            vPassword_InputToFix(  ) ;
            vRecSys_SetState(E_RECSYS_STATE_ADJUST_DIRECT) ;
            return ;
        }
    }
}

void vRecSys_BlinkMessage(void) // E_RECSYS_STATE_BLINK_MSG
{
    ulRecSys_BlinkMsg_Count ++ ;
    if( ulRecSys_BlinkMsg_Count > 30 )
    {
        ulRecSys_BlinkMsg_Count = 0 ;

        if( ulRecSys_BlinkMsg_Flag )
        {
            ulRecSys_BlinkMsg_Flag = 0 ;

            vPcVideo2D_Img_Clean( ulRecSys_BlinkMsg_AnimNo ) ;
        }
        else
        {
            ulRecSys_BlinkMsg_Flag = 1 ;

            vPcVideo2D_Img_Show(ulRecSys_BlinkMsg_AnimNo , ulRecSys_BlinkMsg_Img , DEF_SHOWREC_MSG_X , DEF_SHOWREC_MSG_Y , DEF_PCVIDEO2D_ZOBASE+ulRecSys_BlinkMsg_AnimNo) ;
            vPcVideo2D_Img_SetColorIdx(ulRecSys_BlinkMsg_AnimNo , DEF_YEL) ;
        }
    }

    ulRecordSysCount ++ ;
    if( ulRecordSysCount > 120 )
    {
        vPcVideo2D_Img_Clean( ulRecSys_BlinkMsg_AnimNo ) ;
        vRecSys_SetState(ulRecSys_NextState) ;
        return ;
    }
}

void vRecSys_Test(void) // E_RECSYS_STATE_TEST
{
    if( ulRecordSysCount == 0)
    {
        vUserIO_EnableIsTest() ;
        
        ulMainOtherState = 0 ;
        ulMainOtherCount = 0 ;
            
        ulRecordSysCount ++ ;
    }
    
    if ( ulTest_Key( 0 ) )      // REX 20130321
    {
        vUserIO_Enable( ) ;
        
        vRecSys_SetState(E_RECSYS_STATE_MAIN_MENU) ;
    }
}

void vRecSys_TestQC(void) // E_RECSYS_STATE_TESTQC      // REX 20130321
{
    if( ulRecordSysCount == 0)
    {
        vUserIO_EnableIsTest() ;
        
        ulMainOtherState = 0 ;
        ulMainOtherCount = 0 ;
            
        ulRecordSysCount ++ ;
    }
    
    if ( ulTest_Key( 1 ) )
    {
        vUserIO_Enable( ) ;

        vRecSys_SetState(E_RECSYS_STATE_MAIN_MENU) ;
    }
}

void vRecSys_BuffShow(void) // E_RECSYS_STATE_BUFSHOW
{
    ULONG ulRecordReDraw ;
    ULONG ulKey ;

    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 0 ;

        vShowRec_ClsMenu( ) ;
        vShowRec_ClsPage( ) ;
        vShowRec_ShowChanceRec( ubRecordSysPage ) ;

        ulRecordSysCount++ ;
    }

    ulRecordReDraw = 0 ;
    
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_DOWN)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_STOP2)) ulKey = 1 ;
#endif    	
#endif    	
    if( ulKey_Push(KEY_2) || ulKey_Push(KEY_ADD) ) ulKey = 1 ;
    if( ulKey )
    {
        ubRecordSysPage ++ ;
        if( ubRecordSysPage > (DEF_BUFSHOW_PAGE_MAX-1) ) ubRecordSysPage = 0 ;
        ulRecordReDraw = 1 ;
    }
    
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_UP)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_STOP1)) ulKey = 1 ;
#endif    	
#endif    	
    if( ulKey_Push(KEY_8) || ulKey_Push(KEY_SUB) ) ulKey = 1 ;
    if( ulKey )
    {
        if( ubRecordSysPage ) ubRecordSysPage -- ;
        else ubRecordSysPage = (DEF_BUFSHOW_PAGE_MAX-1) ;
        ulRecordReDraw = 1 ;
    }
    if( ulRecordReDraw )
    {
        vShowRec_ClsPage() ;
        vShowRec_ShowChanceRec( ubRecordSysPage ) ;
    }
  
	ulKey = 0 ;
#ifdef DEF_USE_IOPCI
#ifdef DEF_USE_IPCKEY_RECORD
	if (ulKey_Push(DEF_IPCRECKEY_ENTER)) ulKey = 1 ;
#else	
    if (ulKey_Push(KEY_PCI_START)) ulKey = 1 ;
#endif    	
#endif    	
    if (ulKey_Push(KEY_RTN)) ulKey = 1 ;
    if( ulKey )
    {
        vRecSys_SetState(E_RECSYS_STATE_MAIN_MENU) ;
        return ;
    }
}

void vRecSys_Reset(void)
{
    ulMainPowerOnState = PROC_MAIN_POWERON_RESET ;
    ulMainOtherCount = 0 ;
}

#ifdef DEF_ENABLE_MULTI_SELECT
void vRecSys_Halt( void )
{
    if( ulRecordSysCount == 0 )
    {
        ubRecordSysPage = 0 ;
        vShowRec_HaltMenu() ;
		ulRecordSysCount ++ ;
    }
}
#endif


// ====================================== EXTERN =========================================.
void vRecSys_Initial(void)
{
    ulRecordSysState = E_RECSYS_STATE_INIT ;
    ulRecordSysCount = 0 ;
}

void vRecSys_Process(void)
{
    switch( ulRecordSysState )
    {
        case E_RECSYS_STATE_INIT :              vRecSys_Init() ;            break ;
        case E_RECSYS_STATE_MAIN_MENU :         vRecSys_Main() ;            break ;
        case E_RECSYS_STATE_MASTER_CUR :        vRecSys_MasterCur() ;       break ;
        case E_RECSYS_STATE_MASTER_LAST:        vRecSys_MasterLast() ;      break ;
        case E_RECSYS_STATE_MASTER_TOL :        vRecSys_MasterTol() ;       break ;
        case E_RECSYS_STATE_ADJUST_DIRECT :     vRecSys_AdjDirect() ;       break ;
        case E_RECSYS_STATE_ADJUST_TIME :       vRecSys_AdjTime() ;         break ;
        case E_RECSYS_STATE_REPORT_RESET :      vRecSys_ReportReset() ;     break ;
        case E_RECSYS_STATE_PASSWORD :          vRecSys_Password() ;        break ;
        case E_RECSYS_STATE_FIX_PASSWORD :      vRecSys_FixPassword() ;     break ;
        case E_RECSYS_STATE_BLINK_MSG :         vRecSys_BlinkMessage() ;    break ;
        case E_RECSYS_STATE_TEST :              vRecSys_Test() ;            break ;
        case E_RECSYS_STATE_TESTQC :            vRecSys_TestQC() ;          break ;     // REX 20130321
        case E_RECSYS_STATE_BUFSHOW :           vRecSys_BuffShow() ;        break ;
        case E_RECSYS_STATE_RESET :             vRecSys_Reset() ;           break ;
        #ifdef DEF_ENABLE_MULTI_SELECT
        case E_RECSYS_STATE_HALT :              vRecSys_Halt() ;            break ;
        #endif
        default :
        case E_RECSYS_STATE_EXIT :              vRecSys_Exit() ;            break ;
    }
    switch( ulRecordSysState )
   	{
   	case E_RECSYS_STATE_INIT :
   	case E_RECSYS_STATE_EXIT :
   	case E_RECSYS_STATE_RESET :
   			vPcVideo2D_Img_Clean( DEF_ANIMNO_RECORD_TIME ) ;
   			break ;
   	default :
	        vShowRec_ShowTime() ;
	        break ;
    }
}



