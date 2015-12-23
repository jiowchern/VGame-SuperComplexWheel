#ifndef DEF_INCLUDE_SLAVE_H
	#define DEF_INCLUDE_SLAVE_H

	#ifdef DEF_SLAVE_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	    enum
    {
        DEF_BET_NOW ,
        DEF_BET_LST ,
        DEF_BET_MAXID    
    } ;

    typedef struct __BETLINE__
    {
        SLONG slLine ;
        SLONG slBet ;
    } BETLINE ;



	typedef struct
	{		
		// poker
		//ULONG	ulPrize;		// 牌型大小		

		//UBYTE	ubDeal[DEF_HANDCARD_MAX];	// 手上的牌(第一次发的牌)
		//UBYTE	ubCard[DEF_HANDCARD_MAX];	// 手上的牌
		//UBYTE	ubHold[DEF_HANDCARD_MAX];
		
		//UBYTE ubHoldCount[DEF_HANDCARD_MAX]; //保留牌显示次数
		//UBYTE ubJKCount[DEF_HANDCARD_MAX];  //鬼牌动态显示次数
		//UBYTE ubOpenCard[DEF_HANDCARD_MAX];  //已显示出的牌
		//UBYTE ubOddsWinCount;   //倍率宽显示次数   
		//ULONG	ulOdds;		// 倍数
		
		// game
		ULONG	ulBet ;
		ULONG	ulWin ;
		ULONG ulLastBet;   //上轮押注	
		
			
		// chance
		ULONG ulContribution[2] ;		// 贡献度		
		SLONG	slInOut ;				// 贡献度
		
		// other
		UBYTE 	ubState ;		
		UBYTE	ubPayoutChoose ;
		UBYTE	ubTicketOut ;		
		ULONG	ulError ;
		ULONG	ulPayoutEmptyCnt ;
		ULONG	ulPayoutChooseTimer ;
		ULONG	ulPayoutRefresh ;
		ULONG	ulPayoutLast ;
		//ULONG	ulCoinErrorShowTimer ;	
		
		ULONG 	ulShowKeyinValueCnt ;
		SLONG	slShowKeyinValue ;
		ULONG	ulCoinLimitTimer ;	//上分或投币进分上限显示时间
												
	} SLAVE_INFO ;
	
	#define DEF_SLAVE_ERROR_COIN		0x01
	#define DEF_SLAVE_ERROR_PAYOUT		0x02
	#define DEF_SLAVE_ERROR_SYSLIMIT	0x04

	// +1 是因为 DEF_GAME_PLAYER_MAX 这个栏位代表的是所有副机的总和
	EXTERN SLAVE_INFO stcSlave[DEF_GAME_PLAYER_MAX+1] ;	
	//EXTERN ULONG ulPKRecGift[DEF_ITEM_MAX];	//统计奖项数量
	EXTERN void vSlave_Reset( void ) ;
	EXTERN void vSlave_Initial( void ) ;
	EXTERN void vSlave_WinTakeInitial( SLONG slMaxValue );
	EXTERN void vSlave_WinTakeAddSpeed( void );
	EXTERN SLONG slSlave_TakeToCredit( ULONG ulCount );
	EXTERN void vSlave_RefreshInitial( void );
	
	EXTERN void vSlave_SetWinTakeValueMax( void );

	EXTERN void vSlave_UpDateLastBet(void );
	EXTERN SLONG slSlave_AddBetProcess(SLONG slAddValue,ULONG ulCount );
	EXTERN SLONG slSlave_BetStartGame( void );
	EXTERN void vSlave_GameInitial( UBYTE ubSlaveID ) ;

	
	EXTERN void vSlave_PayoutInterruptProcess( void ) ;
	EXTERN void vSlave_Process( void ) ;
	EXTERN void vSlave_WinJPTakeInitial( void );	
	EXTERN SLONG slSlave_WupWinIsRefresh( void );
	EXTERN SLONG slSlave_WupWinRead( void );
	EXTERN void vSlave_WupWinSet( SLONG slValue );
	EXTERN void vSlave_WupWinSub( SLONG slValue );
	EXTERN void vSlave_WupWinAdd( SLONG slValue );	
	EXTERN void vSlave_WinSet( SLONG slValue );  
	EXTERN SLONG slSlave_WinRead( void ); 
	EXTERN void vSlave_WinAdd( SLONG slValue );  	
	EXTERN SLONG slSlave_WinIsRefresh( void ); 
	EXTERN ULONG ulSlave_WinJPTakeAddSpeed( ULONG ulValue );
	EXTERN SLONG slSlave_WupTakeToCredit( ULONG ulCount );
	
	EXTERN void vSlave_SetLine( SLONG slLine );
	EXTERN SLONG slSlave_ReadTotalBet( void );
	EXTERN SLONG slSlave_ReadLine( void );
	EXTERN SLONG slSlave_ReadBet( void );
	EXTERN void vSlave_BetSet( SLONG slValue );
	EXTERN void vSlave_SetLastLine( SLONG slLine );
	EXTERN SLONG slSlave_ReadLastLine( void );
	EXTERN SLONG slSlave_ReadLastBet( void );
	EXTERN void vSlave_UiIsRefresh( void );
	EXTERN void vSlave_WinSub( SLONG slValue );
	EXTERN void vSlave_LineProcess( void );
	EXTERN SLONG slBet_MaxBetStartGame( void );
	EXTERN SLONG slSlave_BetIsRefresh( void );
	#undef EXTERN
#endif
