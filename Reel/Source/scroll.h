#ifndef DEF_INCLUDE_SCROLL_H
	#define DEF_INCLUDE_SCROLL_H
	
	#ifdef DEF_SCROLL_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	EXTERN void  vScroll_Reset( void ) ;
	EXTERN void  vScroll_ReSetInfo( void ) ;
	EXTERN void  vScroll_RefreshShowScr( void ) ;
	EXTERN void  vScroll_InitState( void ) ;
	EXTERN void  vScroll_SaveData( void ) ;
	EXTERN void  vScroll_LoadData( void ) ;
	EXTERN void  vScroll_StartRun( ULONG ulReel ) ;
	EXTERN void  vScroll_StartAllRun( void ) ;
	EXTERN void  vScroll_SetStopData( ULONG ulReel , UBYTE ubData ) ;
	EXTERN void  vScroll_SetRandData( ULONG ulReel ) ;
	EXTERN void  vScroll_StopRun( ULONG ulReel ) ;
	EXTERN void  vScroll_StopOneRow( ULONG ulRow ) ;
	EXTERN void  vScroll_AllStop( void ) ;
	EXTERN void  vScroll_StopToShowData( void ) ;
	EXTERN UBYTE ubScroll_GetData( ULONG ulReel ) ;
	EXTERN ULONG ulScroll_CheckIsRun( void ) ;
	EXTERN void  vScroll_Process(void) ;
	EXTERN void vScroll_NaturalSymbolData( void );
	EXTERN void vScroll_FeverStartAllRun( void );
	EXTERN void vScroll_FeverAllStop( void );
	EXTERN ULONG ulScroll_FeverCheckIsRun( void );
	EXTERN void vScroll_FeverProcess( void );
	EXTERN void vScroll_FeverReset( void );
	EXTERN void vScroll_FeverLoadData( void );
	EXTERN void vScroll_FeverRefreshShowScr( void );
	EXTERN void vScroll_SaveStopData( void );
	EXTERN void vScroll_LoadStopData( void );
	#undef EXTERN
#endif
