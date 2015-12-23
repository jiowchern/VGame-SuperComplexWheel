#ifndef DEF_INCLUDE_MASTER_H
	#define DEF_INCLUDE_MASTER_H

	#ifdef DEF_MASTER_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

    typedef struct __MASTERINFO__
    {
        UBYTE 	ubRunFlag ;
        UBYTE 	ubDemoFlag ;        
        ULONG 	ulState ;
        ULONG 	ulIndex ;
        ULONG 	ulCount ;
        ULONG 	ulEftCnt ;
        ULONG 	ulMapTime ;
        ULONG   ulTestCount;
        ULONG   ulSceneState; //场景状态，0主游戏，1 Free游戏
        ULONG   ulTemp;   //暂存
        ULONG 	ulAllCount; //
        ULONG   ulAutoKeyState;//0正常玩，1，第一段开始与得分，2第二段开始+全停+得分+加速    
        ULONG   ulAutoKeyGameState; //启动时的自动状态
		ULONG   ulSaveAutoKeyState;//自动FREE游戏时保存状态 
		ULONG   ulBackUp[3];
    } MASTERINFO ;

    enum
    {
        
        PROC_MASTER_REPORT_ERROR	,  
		PROC_MASTER_ERROR       ,
		PROC_MASTER_PAY_OUT     ,       //退币中状态
		
        PROC_MASTER_GAME_INIT        ,		// 3
        PROC_MASTER_GAME_SCR         ,          
        PROC_MASTER_GAME_BET   ,
        PROC_MASTER_GAME_LASTDIS   ,    //显示上轮中奖结果
        //PROC_MASTER_GAME_ACT   ,
        PROC_MASTER_GAME_START ,
        PROC_MASTER_GAME_CHANCE ,
        PROC_MASTER_GAME_RUN  ,    //10
        PROC_MASTER_GAME_STOP   ,
        PROC_MASTER_GAME_CHECK     ,                                                                                                                                                                                    
        PROC_MASTER_GAME_EFT    ,
        PROC_MASTER_GAME_OVERALEFT  ,
        PROC_MASTER_GAME_BIGODDSEFT ,
        PROC_MASTER_GAME_FEVEREFT  ,
        PROC_MASTER_GAME_BONUSEFT  ,
        PROC_MASTER_GAME_FREEEFT   ,
        PROC_MASTER_GAME_EXITFREE  ,
        PROC_MASTER_GAME_CHOOSE    ,//20
        PROC_MASTER_GAME_TAKE,
		PROC_MASTER_GAME_EXIT	    ,

        
        PROC_MASTER_FEVER_INIT,
        PROC_MASTER_FEVER_START , 
        PROC_MASTER_FEVER_CHANCE ,
 		PROC_MASTER_FEVER_RUN  ,
 		PROC_MASTER_FEVER_STOP   ,	 
 		PROC_MASTER_FEVER_WIN , 
 		PROC_MASTER_FEVER_LOSE  ,
 		PROC_MASTER_FEVER_EFT	,
 		PROC_MASTER_FEVER_CHOOSE	,	//30
 		PROC_MASTER_FEVER_TAKE,
 		PROC_MASTER_FEVER_EXIT, 		

 		
 		PROC_MASTER_WUP_INIT	,
 		PROC_MASTER_WUP_READY 	,
 		PROC_MASTER_WUP_GUESS	,	
 		PROC_MASTER_WUP_GTAKE	,
 		PROC_MASTER_WUP_CHANCE	,	
 		PROC_MASTER_WUP_EFT  	,	
 		PROC_MASTER_WUP_CHOOSE	,		
 		PROC_MASTER_WUP_LIMIT	, 
 		PROC_MASTER_WUP_TAKE	, 			
 		PROC_MASTER_WUP_EXIT  	,		        


        PROC_MASTER_MAX
    } ;
	EXTERN MASTERINFO stcMaster ;
	#define mSetMasterState(mState)	{stcMaster.ulState=mState;stcMaster.ulIndex=0;stcMaster.ulCount=0;}
	EXTERN void vMaster_Reset( void ) ;
	EXTERN void vMaster_Run( void ) ;
	EXTERN void vMaster_Stop( void ) ;
	EXTERN ULONG ulMaster_IsRun( void ) ;
	EXTERN ULONG ulMaster_GetStage( void ) ;
	EXTERN void vMaster_LampProcessInitial( void );
	EXTERN void vMaster_Process( void ) ;
	EXTERN void vMaster_GameInitial( void );
	EXTERN void vMaster_RunTimeProcess( void );	
	EXTERN void vMaster_LampProcess( void );
	EXTERN ULONG ulMainGameReflashScreen;
    #define mMainGame_NeedReflashScr() { ulMainGameReflashScreen = 0 ; }	

	EXTERN ULONG ulMaster_CheckOffLine( void ) ;
		
	#undef EXTERN
#endif
