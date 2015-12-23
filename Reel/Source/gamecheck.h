#ifndef DEF_INCLUDE_GAMECHECK_H
	#define DEF_INCLUDE_GAMECHECK_H

	#ifdef DEF_GAMECHECK_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
		typedef struct __GAMEINFOLINE__ 
    {
		ULONG ulOdds[2]     ;
		ULONG ulWinSym[2]   ;
		ULONG ulWinNum[2]   ;
		UBYTE ubSym[5]   ;
		UBYTE ubAct[2][5]   ;
		

	} GAMEINFOLINE ;

	typedef struct __GAMEINFO__ 
    {
		GAMEINFOLINE stcLine[9] ; // 線的中獎資訊  // <--
		ULONG ulAllSameOdds     ;
		ULONG ulAllSameSym      ;
		ULONG ulFeverSetLife    ;
		ULONG ulFeverNowLife    ;
		ULONG ulFeverType       ;
		ULONG ulFever1Odds      ;
		ULONG ulFever2Odds      ;
		ULONG ulFever3Odds      ;
		ULONG ulFreeSetLife     ;
		ULONG ulFreeNowLife     ;
		ULONG ulFreeType       ;
		ULONG ulBonusType       ;
		ULONG ulBonusWin        ;
		ULONG ulBonusValue   ;
	} GAMEINFO ;
	
	typedef struct __GAMEINFO_LAST__ 
    {
		SLONG slCredit      ;
		SLONG slBet         ;
		SLONG slWin         ;
		UBYTE ubAllSame     ;
		SLONG slLine        ;
		SLONG slLineBet     ;
		UBYTE ubWinFlag[9]  ;
		UBYTE ubReel[15]    ;
	} GAMEINFOLAST ;
	
	EXTERN GAMEINFO     stcGameInfo ;
	EXTERN GAMEINFOLAST stcGameInfoLast ;
	EXTERN UBYTE const ubGameCheckLineLocInformation[9][5];
	EXTERN ULONG const ulGameCheckAllSameOddsTable[13];
	EXTERN ULONG const ulGameCheckOddsTable[6][13];
	EXTERN void  vGameCheck_CheckOdds( GAMEINFO *stcGame ) ;

	EXTERN SLONG slGameCheck_LineWildValue( UBYTE ubLine);
	EXTERN UWORD uwGameCheck_MessLine( UBYTE ubLine );


	EXTERN SLONG slGameCheck_ReadAllOdds( GAMEINFO *stcGame );	
	EXTERN SLONG slGameCheck_FeverValue( void );
	EXTERN SLONG slGameCheck_IsSpecial( UBYTE ubSymID );	
	EXTERN void vGameCheck_WupWinRule( void );
	EXTERN SLONG slGameCheck_MaxGameWinRule( GAMEINFO *stcGame );    
	EXTERN SLONG slGameCheck_GameWinRule( GAMEINFO *stcGame );
	EXTERN void vGameCheck_SaveWinRule( GAMEINFO *stcGame );
	
	#ifdef DEF_FIX_CHANCE_20150212
	EXTERN void vGameCheck_CheckAllLineOdds( GAMEINFO *stcGame );
	#endif
	
	#undef EXTERN 
#endif
