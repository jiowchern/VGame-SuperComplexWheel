#ifndef DEF_INCLUDE_REEL_H
	#define DEF_INCLUDE_REEL_H
	
	#ifdef DEF_REEL_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	#define DEF_REEL_MAX              15
	#define DEF_REEL_MAX_SHOW 		   5	
	#define DEF_REEL_MAX_SYM         128
	#define DEF_FEVER_REEL_MAX         1
	#define DEF_FEVER_SYMBOL_MAX       6
	#define DEF_FEVER_REEL_SLOW_NEAR  60
	typedef struct __REEL_INFO__ {
		ULONG ulMaxData        ;
		ULONG ulMaxRun         ;
		SLONG slLocX           ;
		SLONG slLocY           ;
		SLONG slViewStartY     ;
		SLONG slViewEndY       ;
		SLONG slIntervalHeight ;
	} REELINFO ;
	
	// 单一转轮的资料结构
	typedef struct __REEL__ {
		UBYTE ubShowID[DEF_REEL_MAX_SHOW] ;  	// 秀的资料
		UBYTE ubStopID[DEF_REEL_MAX_SHOW] ;  	// 停止的资料
		UBYTE ubSaveID[DEF_REEL_MAX_SHOW] ;     // 存放转轮资料
		UBYTE ubState		   ;  				// 转轮目前的状态
		UBYTE ubAsnState	   ;  				// 是否强制停止 1是
		UBYTE ubAdjustIndex    ;  				// 
		SWORD swMoveY		   ;  				//  
		SWORD swSpeed          ;
	    SWORD swCount          ;
		UWORD uwGetIndex	   ;
		UBYTE *ubReelData      ;
	} REEL ;
	

    typedef struct __ANIM_IMAGE__
    {
		UWORD uwW   ;
		UWORD uwH   ;
		ULONG ulAdr ;
		UWORD uwOW  ;
		UWORD uwOH  ;
    } ANIM_IMAGE ;
    
	enum __SYMBOL__ 
    {
        DEF_SYMBOL_00   ,	// 桃乐斯
        DEF_SYMBOL_01   ,	// 女巫
        DEF_SYMBOL_02   ,	// 稻草人
        DEF_SYMBOL_03   ,	// 铁人
        DEF_SYMBOL_04   ,	// 狮子
        DEF_SYMBOL_05   ,	// 狗
        DEF_SYMBOL_06   ,	// 猴子
        DEF_SYMBOL_07   ,	// 红鞋
        DEF_SYMBOL_08   ,	// 龙卷风
        DEF_SYMBOL_09   ,	// 热气球
        DEF_SYMBOL_10   ,	// Wild（Bonus）
        DEF_SYMBOL_11   ,	// Fever
        DEF_SYMBOL_12   ,	// Free
		DEF_SYMBOL_MAX  ,
	} ;
	#define DEF_SYMBOL_WILD   DEF_SYMBOL_10 
	#define DEF_SYMBOL_FEVER  DEF_SYMBOL_11
	#define DEF_SYMBOL_FREE   DEF_SYMBOL_12
	enum __REEL_STATE__
{
	DEF_REEL_STOP   ,
	DEF_REEL_SHOW   ,
	DEF_REEL_START  ,
	DEF_REEL_ADD	,
	DEF_REEL_RUN	,
	DEF_REEL_WIN	,
	DEF_REEL_ADJUST ,
	DEF_REEL_SUB	,
	DEF_REEL_JUMP
} ;
	EXTERN REELINFO const stcReelInfoData[DEF_REEL_MAX];
	EXTERN REEL stcReelData[DEF_REEL_MAX];
	EXTERN REEL stcReelFeverData[DEF_FEVER_REEL_MAX];
	//EXTERN void  vReel_Initial( SLONG slReel , UBYTE *ubReelData ) ;
	EXTERN void vReel_Initial( SLONG slReel , UBYTE *ubReelData ) ;
	EXTERN void  vReel_OpenSound( void ) ;
	EXTERN void  vReel_CloseSound( void ) ;
	EXTERN void  vReel_ReSetReelData( SLONG slReel , UBYTE *ubReelData ) ;
	EXTERN void  vReel_RefreshShowScr( SLONG slReel ) ;
	EXTERN void  vReel_InitState( SLONG slReel ) ;
	EXTERN UBYTE ubReel_GetData( SLONG slReel ) ;
	EXTERN void  vReel_SaveData( SLONG slReel ) ;
	EXTERN void  vReel_LoadData( SLONG slReel ) ;
	EXTERN void  vReel_StartRun( SLONG slReel ) ;
	EXTERN void  vReel_SetStopData( SLONG slReel , UBYTE ubData ) ;
	EXTERN void  vReel_SetRandData( SLONG slReel ) ;
	EXTERN void  vReel_StopDataToShowData( SLONG slReel ) ;
	EXTERN void  vReel_StopRun( SLONG slReel ) ;
	EXTERN ULONG ulReel_CheckIsRun( SLONG slReel ) ;
	EXTERN void  vReel_Process( SLONG slReel , ULONG ulAnim ) ;
	//EXTERN SLONG const slReelAddSpeedData[];
	//EXTERN SLONG const slReelSubSpeedData[];
	EXTERN UBYTE const ubScrollSymbolData[DEF_REEL_MAX_SYM];	
	EXTERN UBYTE const ubScrollSymbolDataCS[3][DEF_REEL_MAX_SYM];
	EXTERN void vReel_AllNowStopRun(void );
	
	EXTERN void vReel_FeverInitial( SLONG slReel , UBYTE *ubReelData );
	EXTERN void vReel_FeverLoadData( SLONG slReel );
	EXTERN void vReel_FeverProcess( SLONG slReel , ULONG ulAnim );
	EXTERN void vReel_FeverRefreshShowScr( SLONG slReel );
	EXTERN void vReel_FeverSaveData( SLONG slReel );
	EXTERN void vReel_FeverSetRandData( SLONG slReel );
	EXTERN void vReel_FeverSetStopData( SLONG slReel , UBYTE ubData );
	EXTERN void vReel_FeverStartRun( SLONG slReel );
	EXTERN void vReel_FeverStopRun( SLONG slReel );
	EXTERN ULONG ulReel_FeverCheckIsRun( SLONG slReel );
	EXTERN void vReel_FeverAllNowStopRun(void);
	EXTERN void vReel_SaveStopData( SLONG slReel );
	EXTERN void vReel_LoadStopData( SLONG slReel );
	EXTERN void vReel_AsnStopRun( SLONG slReel );
	#undef EXTERN
#endif
