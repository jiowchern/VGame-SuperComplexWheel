#ifndef DEF_INCLUDE_WUPCHANCE_H
	#define DEF_INCLUDE_WUPCHANCE_H

	#ifdef DEF_WUPCHANCE_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	enum {
		DEF_WUP_GUESS_BIG 	,
		DEF_WUP_GUESS_SMALL ,
		DEF_WUP_GUESS_TAKE ,
		
	} ;
	
	enum {
	DEF_CHANCE_WUP_LOSE,    //猜错
	DEF_CHANCE_WUP_NULL,    //重猜
	DEF_CHANCE_WUP_WIN_X1,  //中1次
	DEF_CHANCE_WUP_WIN_X2,
	DEF_CHANCE_WUP_WIN_X3,
	DEF_CHANCE_WUP_WIN_X4, 	
	DEF_CHANCE_WUP_MAX
	
};
	
	typedef struct 
	{
		BUFFER	Buffer ;	
		ULONG	ulRate ;
		UBYTE	ubData ;
		UBYTE	ubGuess ;
		//UBYTE	ubCard ;
		UBYTE	ubHistory[10] ;
		UBYTE	ubDemoHistory[10] ;
		UBYTE	ubDemoTime ;//Dome玩次数
		//ULONG 	ulPassMoner;//过关彩金
		//ULONG 	ulInsureMoney; //保险彩金
		//ULONG 	ulBlastMoney; //爆机彩金
		//ULONG 	ulLoseBet;
		//UBYTE	ubMovePassTime ;//移过牌过关次数
		
		//SLONG 	slAvgBet ;       // 当时的平均押注 
		//SLONG 	slAvgBetTotal ;  // 计算平均押注用的参考总额押注  
		ULONG 	ulPlayTimes    ; // 总玩次数	  
		//ULONG 	ulInTimes    ;  
				
		ULONG	ulAsnLose ;		// 连输补牌 DEF_ADJUSTVALUE_WUP_LOSE
		ULONG	ulAsnKill ;		// 砍牌周期 DEF_ADJUSTVALUE_WUP_KILL
		ULONG 	ulRecAsnValue[7] ;	//统计?制X2,LOSE分数
		ULONG 	ulRecAsnTimes[7] ;	//统计?制X2,LOSE次数
		ULONG 	ulRecTimes[DEF_CHANCE_WUP_MAX] ;	//统计结果次数
		ULONG	ulRecPass[2] ;		// 
		ULONG	ulRecInsure[2] ;	// 
		ULONG	ulRecLimit[2] ;		// 		
		ULONG	ulRecLose[2] ;		// 
		ULONG	ulRecKill[2] ;		// 
		ULONG	ulRecOver[2][2] ;	// 
		ULONG	ulJKTimes[4] ;
		
	} WUPCHANCE_BUF ;
	
	EXTERN WUPCHANCE_BUF stcWupChance ;	
	
	EXTERN void  vWupChance_SetRate( void ) ;
	EXTERN void  vWupChance_Reset( void ) ;

	EXTERN void  vWupChance_Initial( void ) ;
	EXTERN void  vWupChance_Update( void ) ;

	EXTERN void  vWupChance_BetProcess( void ) ;
	EXTERN void  vWupChance_DealProcess( void ) ;
	EXTERN void  vWupChance_WinProcess( ULONG ulWin ) ;
	EXTERN void  vWupChance_DemoUpdate( void );
	EXTERN void  vWupChance_DemoDealProcess( void );
	EXTERN void vWupChance_RecordUpdate( void );
	EXTERN void vWupChance_WinBnsProcess( ULONG ulWin , ULONG mode );
	EXTERN void vWupChance_RecWupLimit( ULONG ulWin ) ;
	
	#undef EXTERN
#endif
