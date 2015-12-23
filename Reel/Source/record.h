#ifndef DEF_INCLUDE_RECORD_H
    #define DEF_INCLUDE_RECORD_H

    #ifdef DEF_RECORD_C
        #define EXTERN
    #else
        #define EXTERN extern
    #endif

    typedef struct __RECORD__
    {
        DLONG dlCurTotal ;
        DLONG dlLasTotal ;
        DLONG dlHisTotal ;
    } RECORD ;

	#define DEF_RECORD_EVENT_STR_LEN	16
	
    typedef struct __RECORD_EVENT_IN__
    {
    	SLONG slValue ;
    	UBYTE ubStr[DEF_RECORD_EVENT_STR_LEN] ;
    } RECORD_EVENT_IN ;

    typedef struct __RECORD_EVENT_WIN__
    {
    	ULONG ulWin ;
    	UBYTE ubStr[DEF_RECORD_EVENT_STR_LEN] ;
    } RECORD_EVENT_WIN ;

    #define DEF_VGAME_RCT_USER_1P       0x0001  // ( 查詢 玩家1P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_2P       0x0002  // ( 查詢 玩家2P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_3P       0x0003  // ( 查詢 玩家3P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_4P       0x0004  // ( 查詢 玩家4P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_5P       0x0005  // ( 查詢 玩家5P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_6P       0x0006  // ( 查詢 玩家6P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_7P       0x0007  // ( 查詢 玩家7P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_8P       0x0008  // ( 查詢 玩家8P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_9P       0x0009  // ( 查詢 玩家9P   查帳資訊 )
    #define DEF_VGAME_RCT_USER_10P      0x000A  // ( 查詢 玩家10P  查帳資訊 )
    #define DEF_VGAME_RCT_USER_ALL      0x000B  // ( 查詢 全體加總 查帳資訊 )
    
    #define DEF_VGAME_RCT_TOAL          0x0010  // ( 查詢 總額     查帳項目 )
    #define DEF_VGAME_RCT_CURR          0x0020  // ( 查詢 當期     查帳項目 )
    #define DEF_VGAME_RCT_LAST          0x0030  // ( 查詢 上期     查帳項目 )
    
    #define DEF_VGAME_RCT_GT_CHEK_REPO  0x0100  // ( 查詢 機台報帳用 檢查碼 )
    #define DEF_VGAME_RCT_GT_CHEK_ZERO  0x0200  // ( 查詢 機台歸零用 檢查碼 )
    #define DEF_VGAME_RCT_GT_CHEK_SADJ  0x0300  // ( 查詢 系統調整用 檢查碼 )
    #define DEF_VGAME_RCT_GT_CHEK_SMID  0x0400  // ( 查詢 設機器號用 檢查碼 )

    enum __RECORD_PLR__
    {
        DEF_RECORD_PLR_1P   ,
        /*
        DEF_RECORD_PLR_2P   ,
        DEF_RECORD_PLR_3P   ,
        DEF_RECORD_PLR_4P   ,
        DEF_RECORD_PLR_5P   ,
        DEF_RECORD_PLR_6P   ,
        DEF_RECORD_PLR_7P   ,
        DEF_RECORD_PLR_8P   ,
        DEF_RECORD_PLR_9P   ,
        DEF_RECORD_PLR_10P  ,
        */
        DEF_RECORD_PLR_ALL  ,
        DEF_RECORD_PLR_MAX
    } ;
    enum __RECORD_DATA__
    {										// 涴窒煦腔隅砱斛剕迵翋儂傷 slave.h 腔隅砱眈肮
        DEF_RECORD_DATA_COIN            , // ( 投幣[分] 累加:分 )
        DEF_RECORD_DATA_PAYOUT          , // ( 退幣[分] 累加:分 )
        DEF_RECORD_DATA_KEYIN           , // ( 上分[分] 累加:分 )
        DEF_RECORD_DATA_KEYOUT          , // ( 下分[分] 累加:分 )
        DEF_RECORD_DATA_TOTALPLAY       , // ( 總玩[分] 累加:分 )
        DEF_RECORD_DATA_TOTALWIN        , // ( 總贏[分] 累加:分 )
        DEF_RECORD_DATA_COIN_A          ,
        DEF_RECORD_DATA_COIN_C          ,
		DEF_RECORD_DATA_KEYIN_B			,
		DEF_RECORD_DATA_KEYIN_D			,
        DEF_RECORD_MAIN_WINTIMES		,
        DEF_RECORD_MAIN_PLAYTIMES		,
        DEF_RECORD_MAIN_WINTOTAL		,
        DEF_RECORD_MAIN_PLAYTOTAL		,
        DEF_RECORD_WUP_WINTIMES			,
        DEF_RECORD_WUP_PLAYTIMES		,
        DEF_RECORD_WUP_WINTOTAL			,
        DEF_RECORD_WUP_PLAYTOTAL		,                       
        
        DEF_RECORD_DATA_USER_01			,
        DEF_RECORD_DATA_USER_02			,
        DEF_RECORD_DATA_USER_03			,
        DEF_RECORD_DATA_USER_04			,
        DEF_RECORD_DATA_USER_05			,
        DEF_RECORD_DATA_USER_06			,
        DEF_RECORD_DATA_USER_07			,
        DEF_RECORD_DATA_USER_08			,
        DEF_RECORD_DATA_USER_09			,
        DEF_RECORD_DATA_USER_10			,
        DEF_RECORD_DATA_USER_11			,
        DEF_RECORD_DATA_USER_12			,
        DEF_RECORD_DATA_USER_13			,
        DEF_RECORD_DATA_USER_14			,
        DEF_RECORD_DATA_USER_15			,
        DEF_RECORD_DATA_USER_16			,
        DEF_RECORD_DATA_USER_17			,
        DEF_RECORD_DATA_USER_18			,
        DEF_RECORD_DATA_USER_19			,
        DEF_RECORD_DATA_USER_20			,
        DEF_RECORD_DATA_USER_21			,
        DEF_RECORD_DATA_USER_22			,
        DEF_RECORD_DATA_USER_23			,
        DEF_RECORD_DATA_USER_24			,
        DEF_RECORD_DATA_USER_25			,
        DEF_RECORD_DATA_USER_26			,
        DEF_RECORD_DATA_USER_27			,
        DEF_RECORD_DATA_USER_28			,
        DEF_RECORD_DATA_USER_29			,
        DEF_RECORD_DATA_USER_30			,
        DEF_RECORD_DATA_USER_31			,
        DEF_RECORD_DATA_USER_32			,
        DEF_RECORD_DATA_USER_33			,
        DEF_RECORD_DATA_USER_34			,
        DEF_RECORD_DATA_USER_35			,
        DEF_RECORD_DATA_USER_36			,
        DEF_RECORD_DATA_USER_37			,
        DEF_RECORD_DATA_USER_38			,
        DEF_RECORD_DATA_USER_39			,
        DEF_RECORD_DATA_USER_40			,
        DEF_RECORD_DATA_USER_41			,
        DEF_RECORD_DATA_USER_42			,
        DEF_RECORD_DATA_USER_43			,
        DEF_RECORD_DATA_USER_44			,
        DEF_RECORD_DATA_USER_45			,
        DEF_RECORD_DATA_USER_46			,
        DEF_RECORD_DATA_USER_47			,
        DEF_RECORD_DATA_USER_48			,
        DEF_RECORD_DATA_USER_49			,
        DEF_RECORD_DATA_USER_50			,
        DEF_RECORD_DATA_USER_51			,
        DEF_RECORD_DATA_USER_52			,
        DEF_RECORD_DATA_USER_53			,
        DEF_RECORD_DATA_USER_54			,
        DEF_RECORD_DATA_USER_55			,
        DEF_RECORD_DATA_USER_56			,
        DEF_RECORD_DATA_USER_57			,
        DEF_RECORD_DATA_USER_58			,
        DEF_RECORD_DATA_USER_59			,
        DEF_RECORD_DATA_USER_60			,
        DEF_RECORD_DATA_USER_61			,
        DEF_RECORD_DATA_USER_62			,
        DEF_RECORD_DATA_USER_63			,
        DEF_RECORD_DATA_USER_64			,
        DEF_RECORD_DATA_USER_65			,
        DEF_RECORD_DATA_USER_66			,
        DEF_RECORD_DATA_USER_67			,
        DEF_RECORD_DATA_USER_68			,
        DEF_RECORD_DATA_USER_69			,
        DEF_RECORD_DATA_USER_70			,

        DEF_RECORD_INFO_PROFIT_SCOR     , // ( 盈利分數[分]   (TotalIn - TotalOut)            累加:不可 )
        DEF_RECORD_INFO_PROFIT_COIN     , // ( 營收幣數[幣]   (TotalIn - TotalOut)/CoinRate   累加:不可 )
        DEF_RECORD_INFO_BOOT_DAYS       , // ( 開機天數[日時] 8'BCD[DDDDDDhh] Ex: 00078923    累加:不可 )
        DEF_RECORD_INFO_GAME_DAYS       , // ( 遊戲天數[日時] 8'BCD[DDDDDDhh] Ex: 00078923    累加:不可 )

        DEF_RECORD_MAX                  ,
        DEF_RECORD_DATA_MAX             = DEF_RECORD_INFO_PROFIT_SCOR ,
    } ;

	
	EXTERN RECORD stcRecordSymbolGift[ DEF_RECORD_DATA_MAX ] ;
	EXTERN RECORD_EVENT_IN 	stcRecordEvent_InOut[100] ;
	EXTERN RECORD_EVENT_WIN stcRecordEvent_Win[100] ;
	
    EXTERN void  vRecord_Reset( void ) ;

    EXTERN void  vRecord_Add( UBYTE ubPlr , UBYTE ubDataID , ULONG ulAdd ) ; // dlCurTotal += ulAdd
    EXTERN void  vRecord_Set( UBYTE ubPlr , UBYTE ubDataID , ULONG ulSet ) ; // dlCurTotal = ulSet , dlLasTotal=dlHisTotal=0
    EXTERN DLONG dlRecord_ReadCurr( UBYTE ubPlr , UBYTE ubDataID ) ; // dlCurTotal-dlLasTotal
    EXTERN DLONG dlRecord_ReadLast( UBYTE ubPlr , UBYTE ubDataID ) ; // dlLasTotal-dlHisTotal
    EXTERN DLONG dlRecord_ReadCurrTotal( UBYTE ubPlr , UBYTE ubDataID ) ; // dlCurTotal
    EXTERN DLONG dlRecord_ReadLastTotal( UBYTE ubPlr , UBYTE ubDataID ) ; // dlLasTotal
	EXTERN UBYTE ubRecord_IsSame( UBYTE ubPlr , UBYTE ubDataID ) ; // dlCurTotal==dlLasTotal
    EXTERN void  vRecord_UpDate( void ) ; // dlHisTotal=dlLasTotal , dlLasTotal=dlCurTotal

    EXTERN void  vRecord_BootSecAdd( ULONG ulAddSec ) ;
    EXTERN void  vRecord_GameSecAdd( ULONG ulAddSec ) ;
    EXTERN DLONG dlRecord_ReadBootSec( void ) ;
    EXTERN DLONG dlRecord_ReadGameSec( void ) ;

    EXTERN void  vRecord_Process( void ) ;

	EXTERN void vRecord_Add_GiftBet( UBYTE ubDataID , ULONG ulAdd ) ;
	EXTERN DLONG dlRecord_ReadCurr_GitfBet( UBYTE ubDataID ) ;
	
	EXTERN void vRecord_Save_InOutEvent( SLONG ulValue ) ;
	EXTERN void vRecord_Save_WinEvent( ULONG ulWin , ULONG ulMode , ULONG ulSymbol ) ;

    #undef EXTERN
#endif
