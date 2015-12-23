

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
		ULONG ulBase;                        //�����趨	
		ULONG ulMainRetakeTime;              //��Ȼ������ȡ���� 
		SLONG slFeverOdds;                   //FEVER��Ϸ����
		BUFFER VirtualBuffer[8];           //8������BUF 
		ULONG ulVirtualRate[8];                 //8������Rate // REX
		ULONG ulVirtualBufGate[8];           //8������Gate 
		
		BUFFER SpecBuffer[8];                //8��Spec BUF 
		ULONG ulSpecRate[8];                 //8��Spec Rate 
		ULONG ulSpecValue[8];                 //8��Spec�ͳ���ֵ
		
		SLONG slVirtualBufTopValue[8];       //8�����ⴥ��ֵ
		ULONG ulVirtualBufAsnGift[8];        //8��ǿ�ƽ���
		SLONG slReturnBufValue;              //�ع�Buffer
		ULONG slReturnBetValue;              //�ع��ۼ�Ѻ��
		ULONG ulReturnMainValue;             //�ع�Main����
		BUFFER ReturnSpec;                   //�ع�Spec����
		
		ULONG ulWinTimes[DEF_CHANCE_BUFMAX]; // ��BUF Ӯ�������					
		ULONG ulPlayTimes    ; // Chance �������	
		SLONG slAvgBet 		 ; //��ʱ��ƽ��Ѻע 
		SLONG slAvgBetTotal  ; //����ƽ��Ѻע�õĲο��ܶ�Ѻע  
		ULONG ulActBuf       ; // �趨������ʹ�õ� Buffer	
		ULONG ulAsnGift      ; // �趨ǿ�ƽ���
		
		ULONG ulAsnState ;      //��������ǿ��Ϊ0,Specǿ��Ϊ1
		
	
		ULONG ulFreeTotalWin , ulFreeType ;
		ULONG ulFeverTotalWin , ulFeverType ;
		
		ULONG ulBufferGate[DEF_CHANCE_BUFMAX] ;
		ULONG ulRecSpecValue[3] ;	//ͳ��?�ƽoFREE,FEVER,BONUS�ķ֔�
		ULONG ulRecFever[2] ;	
		ULONG ulRecMainAsn[3] ;	
		ULONG ulRecVirAsnTimes[8][3] ;	
		ULONG ulRecReelSymTimes[13] ;
		ULONG ulRecBetArray[5][11] ;//ͳ�Ƽo?Ѻע�ցѠ�B�֔�
		ULONG ulRecBufArray[5][51] ;//ͳ�Ƹ��MBuffer�ցѠ�B
		ULONG ulRecFreeArray[20] ;//ͳ����FREE����
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
	}RECORD_INFO_MAIN ;//���ֵ���Ϸ��¼ 
	
	typedef struct 	
	{	
		ULONG   ulWupWin[11];
		UBYTE	ulWupMode[11];
		UBYTE	ulWupCard[11];
		UBYTE   ulWupGuess[11];
		ULONG   ulWupGameMode;
		ULONG   ulWupGameWin;
	}RECORD_INFO_WUP ;//���ֵ���Ϸ��¼ 
	
	
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
	}RECORD_INFO ;//���ֵ���Ϸ��¼ 
	EXTERN RECORD_INFO stcrecord[11] ;    //û��ռʱ���˳����е��õ�,
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

	EXTERN SLONG slChance_LmpAdd( SLONG slLmpBet );//��ǿ�Ƴ����Ĵ���Ѻ��

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
