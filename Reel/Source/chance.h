

#ifndef DEF_INCLUDE_CHANCE_H
	#define DEF_INCLUDE_CHANCE_H

	#ifdef DEF_CHANCE_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	
	enum {
		DEF_CHANCE_BUF_MAIN ,
		DEF_CHANCE_BUF_SPEC ,	
		DEF_CHANCE_BUF_BONUS ,	
		DEF_CHANCE_BUF_FEVER ,	
		DEF_CHANCE_BUF_FREE ,			
		DEF_CHANCE_BUFMAX  
	} ; 
	
	enum {
		DEF_CHANCE_MBUF_ALL_A ,
		DEF_CHANCE_MBUF_ALL_B ,
		DEF_CHANCE_MBUF_ALL_C ,
		DEF_CHANCE_MBUF_ALL_D ,
		DEF_CHANCE_MBUF_ALL_E ,
		DEF_CHANCE_MBUF_MAX 				
	} ;
	typedef struct __CHANCE_MBUFF__ {
		ULONG	ulValue ;
		ULONG	ulAsnTop ;
		//UWORD	uwOdds ;
		DLONG	dlRecIn ;		
		DLONG	dlRecWin ;	
		DLONG	dlRecRet ;
		ULONG 	ulAsnTimes ;
	} CHANCEMBUF ;	 

	typedef struct __VIRTUAL_INFO__ {
		ULONG ulAsnGift        ;
		ULONG ulTopValue       ;
		ULONG ulGate           ;
	}VIRTUALINFO ;

	typedef struct __BONUS_INFO__ {
		ULONG ulAsnNum        ;		
		ULONG ulGate          ;
	}BONUSINFO ;
	
	typedef struct __FEVER_INFO__ {
		ULONG ulAsnNum        ;		
		ULONG ulGate          ;
		ULONG ulMinOdds       ;
		ULONG ulMaxOdds       ;
	}FEVERINFO ;
		
	typedef struct 
	{
		BUFFER Buffer[DEF_CHANCE_BUFMAX];
		ULONG ulRate[ DEF_CHANCE_BUFMAX ] ;	
		ULONG ulBase;                        //基数设定	
		ULONG ulMainRetakeTime;              //自然机率重取计数 
		SLONG slFeverOdds;                   //FEVER游戏倍数
		BUFFER VirtualBuffer[8];           //8组虚拟BUF 
		ULONG ulVirtualRate[8];                 //8组虚拟Rate // REX
		ULONG ulVirtualBufGate[8];           //8组虚拟Gate 
		
		BUFFER SpecBuffer[8];                //8组Spec BUF 
		ULONG ulSpecRate[8];                 //8组Spec Rate 
		ULONG ulSpecValue[8];                 //8组Spec送出的值
		
		SLONG slVirtualBufTopValue[8];       //8组虚拟触顶值
		ULONG ulVirtualBufAsnGift[8];        //8组强制奖项
		SLONG slReturnBufValue;              //回灌Buffer
		ULONG slReturnBetValue;              //回灌累加押分
		ULONG ulReturnMainValue;             //回灌Main分数
		BUFFER ReturnSpec;                   //回灌Spec分数
		
		ULONG ulWinTimes[DEF_CHANCE_BUFMAX]; // 各BUF 赢总玩次数					
		ULONG ulPlayTimes    ; // Chance 总玩次数	
		SLONG slAvgBet 		 ; //当时的平均押注 
		SLONG slAvgBetTotal  ; //计算平均押注用的参考总额押注  
		ULONG ulActBuf       ; // 设定本局所使用的 Buffer	
		ULONG ulAsnGift      ; // 设定强制奖项
		
		ULONG ulAsnState ;      //正常本身强制为0,Spec强制为1
		
	
		ULONG ulFreeTotalWin , ulFreeType ;
		ULONG ulFeverTotalWin , ulFeverType ;
		
		ULONG ulBufferGate[DEF_CHANCE_BUFMAX] ;
		ULONG ulRecSpecValue[3] ;	//统计?制給FREE,FEVER,BONUS的分數
		ULONG ulRecFever[2] ;	
		ULONG ulRecMainAsn[3] ;	
		ULONG ulRecVirAsnTimes[8][3] ;	
		ULONG ulRecReelSymTimes[13] ;
		ULONG ulRecBetArray[5][11] ;//统计紀?押注分佈狀態分數
		ULONG ulRecBufArray[5][51] ;//统计各組Buffer分佈狀態
		ULONG ulRecFreeArray[20] ;//统计送FREE次数
		ULONG ulRecFreeTimes;
		ULONG ulRecReturnIn[5] ;
		
		#ifdef DEF_CHANCE_FOR_UART_SLAVE
		UBYTE ubMAsnItemReturn ;	
		UBYTE ubMAsnItem ;	
		CHANCEMBUF MBuf[DEF_CHANCE_MBUF_MAX] ;
        ULONG ulNoPlayTime ;
        DLONG dlMBufRecInTotal ;
        DLONG dlMBufRecRetTotal ;
    	#endif
		
	} MAINCHANCE_BUF ;
	

	typedef struct 	
	{
		UBYTE	ubData;
		ULONG	ulWin;	
		ULONG	ulPlayTimes;
		UBYTE	ubLoseTimes;
	}FEVERCHANCE_BUF ; 

	typedef struct 	
	{
		ULONG	ulCredit ;
		ULONG	ulBet ;
		ULONG	ulWin ;
		//UBYTE	ubFstCard[DEF_HANDCARD_MAX];
		//UBYTE	ubSecCard[DEF_HANDCARD_MAX];
		ULONG	ulGameMode ;
		ULONG	ulGameOdds ;
	}RECORD_INFO_MAIN ;//本轮的游戏记录 
	
	typedef struct 	
	{	
		ULONG   ulWupWin[11];
		UBYTE	ulWupMode[11];
		UBYTE	ulWupCard[11];
		UBYTE   ulWupGuess[11];
		ULONG   ulWupGameMode;
		ULONG   ulWupGameWin;
	}RECORD_INFO_WUP ;//本轮的游戏记录 
	
	
	/*
	typedef struct 	
	{
		ULONG	ulCredit ;
		ULONG	ulBet ;
		ULONG	ulWin ;
		//UBYTE	ubFstCard[DEF_HANDCARD_MAX];
		//UBYTE	ubSecCard[DEF_HANDCARD_MAX];
		ULONG	ulGameMode ;
		ULONG	ulGameOdds ;
		ULONG   ulWupWin[11];
		UBYTE	ulWupMode[11];
		UBYTE	ulWupCard[11];
		ULONG   ulWupGameMode;
		ULONG   ulWupGameWin;
	}RECORD_INFO ;//本轮的游戏记录 
	EXTERN RECORD_INFO stcrecord[11] ;    //没用占时查账程序有调用到,
	*/
	
	#define DEF_RECLAST_MAX					20
	
	
	EXTERN RECORD_INFO_MAIN stcRecordMain[DEF_RECLAST_MAX+1] ;
	EXTERN RECORD_INFO_WUP  stcRecordWup[DEF_RECLAST_MAX+1] ;
	
	EXTERN FEVERCHANCE_BUF stcFeverChance ;

	EXTERN ULONG const ulFeverGameWinOdds[5] ;//= { 5,4,3,2,1 }

	EXTERN MAINCHANCE_BUF stcChance;
	
	EXTERN UBYTE ubAutoPlay2_isRun ;



	EXTERN void  vChance_AddBet(ULONG ulBet );
	EXTERN void  vChance_BufProcess( void );
	EXTERN void  vChance_AsnBufProcess( void );
	
	EXTERN void  vChance_GameRateSet( void ) ;
	EXTERN void  vChance_Reset( void ) ;
	EXTERN void  vChance_Update( ULONG ulMode ) ;	

	EXTERN void vChance_WinProcess( ULONG ulWin ) ;

	EXTERN SLONG slChance_LmpAdd( SLONG slLmpBet );//求强制出奖的触顶押分

	EXTERN void  vChance_AllRecordUpdate( ULONG mode );	
	
	EXTERN void vChance_GameProcess( void );
	EXTERN void vChance_FeverProcess( void );
	EXTERN void vChance_WinBonusProcess( void );
	EXTERN void vChance_WinFeverProcess( void );
	EXTERN void vChance_WinFreeProcess( void ) ;
	EXTERN void vChance_VirtualAllTopValue( void );
	EXTERN void vChance_RecBetArrayReset(void );
	EXTERN void vChance_RecordFreeUpdate( void );
	EXTERN void vChance_DemoWinBig(void);
	
	#undef EXTERN 
#endif
