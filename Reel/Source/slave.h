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
		//ULONG	ulPrize;		// ���ʹ�С		

		//UBYTE	ubDeal[DEF_HANDCARD_MAX];	// ���ϵ���(��һ�η�����)
		//UBYTE	ubCard[DEF_HANDCARD_MAX];	// ���ϵ���
		//UBYTE	ubHold[DEF_HANDCARD_MAX];
		
		//UBYTE ubHoldCount[DEF_HANDCARD_MAX]; //��������ʾ����
		//UBYTE ubJKCount[DEF_HANDCARD_MAX];  //���ƶ�̬��ʾ����
		//UBYTE ubOpenCard[DEF_HANDCARD_MAX];  //����ʾ������
		//UBYTE ubOddsWinCount;   //���ʿ���ʾ����   
		//ULONG	ulOdds;		// ����
		
		// game
		ULONG	ulBet ;
		ULONG	ulWin ;
		ULONG ulLastBet;   //����Ѻע	
		
			
		// chance
		ULONG ulContribution[2] ;		// ���׶�		
		SLONG	slInOut ;				// ���׶�
		
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
		ULONG	ulCoinLimitTimer ;	//�Ϸֻ�Ͷ�ҽ���������ʾʱ��
												
	} SLAVE_INFO ;
	
	#define DEF_SLAVE_ERROR_COIN		0x01
	#define DEF_SLAVE_ERROR_PAYOUT		0x02
	#define DEF_SLAVE_ERROR_SYSLIMIT	0x04

	// +1 ����Ϊ DEF_GAME_PLAYER_MAX �����λ����������и������ܺ�
	EXTERN SLAVE_INFO stcSlave[DEF_GAME_PLAYER_MAX+1] ;	
	//EXTERN ULONG ulPKRecGift[DEF_ITEM_MAX];	//ͳ�ƽ�������
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
