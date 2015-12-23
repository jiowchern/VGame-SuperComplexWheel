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
	DEF_CHANCE_WUP_LOSE,    //�´�
	DEF_CHANCE_WUP_NULL,    //�ز�
	DEF_CHANCE_WUP_WIN_X1,  //��1��
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
		UBYTE	ubDemoTime ;//Dome�����
		//ULONG 	ulPassMoner;//���زʽ�
		//ULONG 	ulInsureMoney; //���ղʽ�
		//ULONG 	ulBlastMoney; //�����ʽ�
		//ULONG 	ulLoseBet;
		//UBYTE	ubMovePassTime ;//�ƹ��ƹ��ش���
		
		//SLONG 	slAvgBet ;       // ��ʱ��ƽ��Ѻע 
		//SLONG 	slAvgBetTotal ;  // ����ƽ��Ѻע�õĲο��ܶ�Ѻע  
		ULONG 	ulPlayTimes    ; // �������	  
		//ULONG 	ulInTimes    ;  
				
		ULONG	ulAsnLose ;		// ���䲹�� DEF_ADJUSTVALUE_WUP_LOSE
		ULONG	ulAsnKill ;		// �������� DEF_ADJUSTVALUE_WUP_KILL
		ULONG 	ulRecAsnValue[7] ;	//ͳ��?��X2,LOSE����
		ULONG 	ulRecAsnTimes[7] ;	//ͳ��?��X2,LOSE����
		ULONG 	ulRecTimes[DEF_CHANCE_WUP_MAX] ;	//ͳ�ƽ������
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
