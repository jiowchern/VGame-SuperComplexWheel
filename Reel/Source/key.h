#ifndef DEF_INCLUDE_KEY_H
	#define DEF_INCLUDE_KEY_H

	#ifdef DEF_KEY_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	enum __KEY_DEVICE__
    {
		DEF_KEY_DEVICE_CPU_A ,  // ARM Ext Input
		DEF_KEY_DEVICE_CPU_H ,  // ARM Ext Input
		DEF_KEY_DEVICE_MAP_C ,  // PCI Ext Input
		DEF_KEY_DEVICE_MAP_D ,  // PCI Ext Input

        DEF_KEY_DEVICE_PCI_A ,  // PCI Input NumPad   A
        DEF_KEY_DEVICE_PCI_B ,  // PCI Input NumPad   A

    #ifdef DEF_DEFINE_DEBUG_PCKEY
    
        DEF_KEY_DEVICE_PCI_C ,  // PCI Input KeyBoard A
        DEF_KEY_DEVICE_PCI_D ,  // PCI Input KeyBoard A
        DEF_KEY_DEVICE_PCI_E ,  // PCI Input KeyBoard B
        DEF_KEY_DEVICE_PCI_F ,  // PCI Input KeyBoard B
        DEF_KEY_DEVICE_PCI_G ,  // PCI Input KeyBoard B
        DEF_KEY_DEVICE_PCI_H ,  // PCI Input KeyBoard B
        DEF_KEY_DEVICE_PCI_I ,  // PCI Input KeyBoard C
        DEF_KEY_DEVICE_PCI_J ,  // PCI Input KeyBoard C
        DEF_KEY_DEVICE_PCI_K ,  // PCI Input KeyBoard C
        DEF_KEY_DEVICE_PCI_L ,  // PCI Input KeyBoard C
        DEF_KEY_DEVICE_PCI_M ,  // PCI Input KeyBoard D
        DEF_KEY_DEVICE_PCI_N ,  // PCI Input Mouse    A
        
    #else
	        
        DEF_KEY_DEVICE_USR_A ,  // PL1 KEY0
        DEF_KEY_DEVICE_USR_B ,  // PL1 KEY1
        DEF_KEY_DEVICE_USR_C ,  // PL2 KEY0
        DEF_KEY_DEVICE_USR_D ,  // PL2 KEY1
        DEF_KEY_DEVICE_USR_E ,  // PL3 KEY0
        DEF_KEY_DEVICE_USR_F ,  // PL3 KEY1
        DEF_KEY_DEVICE_USR_G ,  // PL4 KEY0
        DEF_KEY_DEVICE_USR_H ,  // PL4 KEY1
        DEF_KEY_DEVICE_USR_I ,  // PL5 KEY0
        DEF_KEY_DEVICE_USR_J ,  // PL5 KEY1
        DEF_KEY_DEVICE_USR_K ,  // PL6 KEY0
        DEF_KEY_DEVICE_USR_L ,  // PL6 KEY1
        DEF_KEY_DEVICE_USR_M ,  // PL7 KEY0
        DEF_KEY_DEVICE_USR_N ,  // PL7 KEY1
        DEF_KEY_DEVICE_USR_O ,  // PL8 KEY0
        DEF_KEY_DEVICE_USR_P ,  // PL8 KEY1        
        DEF_KEY_DEVICE_USR_Q ,  // PL9 KEY0
        DEF_KEY_DEVICE_USR_R ,  // PL9 KEY1
        DEF_KEY_DEVICE_USR_S ,  // PL10 KEY0
        DEF_KEY_DEVICE_USR_T ,  // PL10 KEY1
        
   	#endif

		DEF_KEY_DEVICE_MAX
	} ;

	enum __KEY_DEVICE_BIT__
    {
		DEF_KEY_DEVICE_BIT_0 ,
		DEF_KEY_DEVICE_BIT_1 ,
		DEF_KEY_DEVICE_BIT_2 ,
		DEF_KEY_DEVICE_BIT_3 ,
		DEF_KEY_DEVICE_BIT_4 ,
		DEF_KEY_DEVICE_BIT_5 ,
		DEF_KEY_DEVICE_BIT_6 ,
		DEF_KEY_DEVICE_BIT_7 
	} ;

	enum __KEY_ACTION__ {
		DEF_KEY_DISABLE ,
		DEF_KEY_ENABLE  ,
		DEF_KEY_NORMAL 	= DEF_KEY_ENABLE ,
		DEF_KEY_ACTION  ,
		DEF_KEY_ACTION_10  ,
		DEF_KEY_ERROR  
	} ;

	enum __KEY__ {
		
        KEY_0                       ,
        KEY_1                       ,
        KEY_2                       ,
        KEY_3                       ,
        KEY_4                       ,
        KEY_5                       ,
        KEY_6                       ,
        KEY_7                       ,
        KEY_8                       ,
        KEY_9                       ,
        KEY_DOT                     ,
        KEY_DIV                     ,
        KEY_MUL                     ,
        KEY_SUB                     ,
        KEY_ADD                     ,
        KEY_RTN                     ,
        
	#ifdef DEF_USE_IOBOARD

    #ifdef DEF_DEFINE_DEBUG_PCKEY
    
        KEY_SEL_1P                  ,
        KEY_SEL_2P                  ,
        KEY_SEL_3P                  ,
        KEY_SEL_4P                  ,
        KEY_SEL_5P                  ,
        KEY_SEL_6P                  ,
        KEY_SEL_7P                  ,
        KEY_SEL_8P                  ,
        KEY_SEL_9P                  ,
        KEY_SEL_10P                 ,
        
    #endif
	
        KEY_1P_KEYIN                ,
        KEY_1P_KEYOUT               ,
        KEY_1P_COIN                 ,
        KEY_1P_PAYOUT               ,
        KEY_1P_UP                   ,
        KEY_1P_DN                   ,
        KEY_1P_LF                   ,
        KEY_1P_RT                   ,
        KEY_1P_FIRE                 ,
        KEY_1P_BETUP                ,
        KEY_1P_BETDN                ,

        KEY_2P_KEYIN                ,
        KEY_2P_KEYOUT               ,
        KEY_2P_COIN                 ,
        KEY_2P_PAYOUT               ,
        KEY_2P_UP                   ,
        KEY_2P_DN                   ,
        KEY_2P_LF                   ,
        KEY_2P_RT                   ,
        KEY_2P_FIRE                 ,
        KEY_2P_BETUP                ,
        KEY_2P_BETDN                ,

        KEY_3P_KEYIN                ,
        KEY_3P_KEYOUT               ,
        KEY_3P_COIN                 ,
        KEY_3P_PAYOUT               ,
        KEY_3P_UP                   ,
        KEY_3P_DN                   ,
        KEY_3P_LF                   ,
        KEY_3P_RT                   ,
        KEY_3P_FIRE                 ,
        KEY_3P_BETUP                ,
        KEY_3P_BETDN                ,

        KEY_4P_KEYIN                ,
        KEY_4P_KEYOUT               ,
        KEY_4P_COIN                 ,
        KEY_4P_PAYOUT               ,
        KEY_4P_UP                   ,
        KEY_4P_DN                   ,
        KEY_4P_LF                   ,
        KEY_4P_RT                   ,
        KEY_4P_FIRE                 ,
        KEY_4P_BETUP                ,
        KEY_4P_BETDN                ,

        KEY_5P_KEYIN                ,
        KEY_5P_KEYOUT               ,
        KEY_5P_COIN                 ,
        KEY_5P_PAYOUT               ,
        KEY_5P_UP                   ,
        KEY_5P_DN                   ,
        KEY_5P_LF                   ,
        KEY_5P_RT                   ,
        KEY_5P_FIRE                 ,
        KEY_5P_BETUP                ,
        KEY_5P_BETDN                ,

        KEY_6P_KEYIN                ,
        KEY_6P_KEYOUT               ,
        KEY_6P_COIN                 ,
        KEY_6P_PAYOUT               ,
        KEY_6P_UP                   ,
        KEY_6P_DN                   ,
        KEY_6P_LF                   ,
        KEY_6P_RT                   ,
        KEY_6P_FIRE                 ,
        KEY_6P_BETUP                ,
        KEY_6P_BETDN                ,

        KEY_7P_KEYIN                ,
        KEY_7P_KEYOUT               ,
        KEY_7P_COIN                 ,
        KEY_7P_PAYOUT               ,
        KEY_7P_UP                   ,
        KEY_7P_DN                   ,
        KEY_7P_LF                   ,
        KEY_7P_RT                   ,
        KEY_7P_FIRE                 ,
        KEY_7P_BETUP                ,
        KEY_7P_BETDN                ,

        KEY_8P_KEYIN                ,
        KEY_8P_KEYOUT               ,
        KEY_8P_COIN                 ,
        KEY_8P_PAYOUT               ,
        KEY_8P_UP                   ,
        KEY_8P_DN                   ,
        KEY_8P_LF                   ,
        KEY_8P_RT                   ,
        KEY_8P_FIRE                 ,
        KEY_8P_BETUP                ,
        KEY_8P_BETDN                ,

        KEY_9P_KEYIN                ,
        KEY_9P_KEYOUT               ,
        KEY_9P_COIN                 ,
        KEY_9P_PAYOUT               ,
        KEY_9P_UP                   ,
        KEY_9P_DN                   ,
        KEY_9P_LF                   ,
        KEY_9P_RT                   ,
        KEY_9P_FIRE                 ,
        KEY_9P_BETUP                ,
        KEY_9P_BETDN                ,

        KEY_10P_KEYIN                ,
        KEY_10P_KEYOUT               ,
        KEY_10P_COIN                 ,
        KEY_10P_PAYOUT               ,
        KEY_10P_UP                   ,
        KEY_10P_DN                   ,
        KEY_10P_LF                   ,
        KEY_10P_RT                   ,
        KEY_10P_FIRE                 ,
        KEY_10P_BETUP                ,
        KEY_10P_BETDN                ,
        
	#endif // DEF_USE_IOBOARD
	
	#ifdef DEF_USE_IOPCI
	
        KEY_PCI_GIP01				,
        KEY_PCI_GIP02				,
        KEY_PCI_GIP03				,
        KEY_PCI_GIP04				,
        KEY_PCI_GIP05				,
        KEY_PCI_GIP06				,
        KEY_PCI_GIP07				,
        KEY_PCI_GIP08				,

        KEY_PCI_GIP17				,
        KEY_PCI_GIP18				,
        KEY_PCI_GIP19				,
        KEY_PCI_GIP20				,
        KEY_PCI_GIP21				,
        KEY_PCI_GIP22				,
        KEY_PCI_GIP23				,
        KEY_PCI_GIP24				,

        KEY_PCI_GIP25				,
        KEY_PCI_GIP26				,
        KEY_PCI_GIP27 				,
        KEY_PCI_GIP28				,
        KEY_PCI_GIP29				,
        KEY_PCI_GIP30				,
        KEY_PCI_GIP31				,
        KEY_PCI_GIP32				,
        
	#endif // DEF_USE_IOPCI

    	KEY_MAX                     ,
    } ;

	// 97's key define 
	
	#define KEY_PCI_OB_TEST 	KEY_PCI_GIP01
	#define KEY_PCI_OB_RECORD 	KEY_PCI_GIP02

	#define KEY_PCI_STOP1 		KEY_PCI_GIP03
	#define KEY_PCI_STOP2 		KEY_PCI_GIP04
	#define KEY_PCI_STOP3 		KEY_PCI_GIP05
	#define KEY_PCI_STOP4 		KEY_PCI_GIP06
	#define KEY_PCI_STOP5 		KEY_PCI_GIP18
	#define KEY_PCI_START 		KEY_PCI_GIP07
	
	#define KEY_PCI_HELP 		KEY_PCI_GIP19			// 说明键
	#define KEY_PCI_LINE 		KEY_PCI_STOP2			// 选线键
	#define KEY_PCI_AUTO 		KEY_PCI_GIP08			// 自动键
	#define KEY_PCI_MAXBET		KEY_PCI_GIP17			// 最大押注键
	#define KEY_PCI_BET   		KEY_PCI_STOP1			// 押注

	#define KEY_PCI_BIG   		KEY_PCI_STOP2			// 猜右
	#define KEY_PCI_SMALL 		KEY_PCI_STOP1			// 猜左
	#define KEY_PCI_HWUP  		KEY_PCI_STOP3			// 半比倍
	#define KEY_PCI_WUP   		KEY_PCI_STOP4			// 比倍
	#define KEY_PCI_DWUP  		KEY_PCI_STOP5			// 双比倍
	
	#define KEY_PCI_TAKE  		KEY_PCI_GIP30			// 独立的得分键
	#define KEY_PCI_RES   		KEY_PCI_GIP27			// 保留键

	#define KEY_PCI_COIN_A 		KEY_PCI_GIP20
	#define KEY_PCI_KEYIN_B		KEY_PCI_GIP21
	#define KEY_PCI_PAYOUT		KEY_PCI_GIP24
	#define KEY_PCI_KEYOUT		KEY_PCI_GIP25
	#define KEY_PCI_97_RECORD   KEY_PCI_GIP22
	#define KEY_PCI_97_TEST		KEY_PCI_GIP23
	#define KEY_PCI_HPSW  		KEY_PCI_GIP26
	#define KEY_PCI_TKSW  		KEY_PCI_GIP29
	
	#define KEY_PCI_COIN_C 		KEY_PCI_GIP28
	#define KEY_PCI_KEYIN_D 	KEY_PCI_GIP31

	#define KEY_PCI_POBOX_FULL	KEY_PCI_GIP32
		
	#define DEF_MJKEY_SCANLINEOUT_MAX	5
		
	typedef struct __KEYTEST__ {
		ULONG ulKeyID   ;
		UBYTE *ubString ;
		ULONG ulAnimNum ;
		ULONG ulBit     ;
	} KEYTEST ;

	#define mKey_PadIndex( mDevice , mBit )        ( mDevice * 8 + mBit )

    #define DEF_USER_KEY                           ( KEY_2P_KEYIN-KEY_1P_KEYIN )
    #define mKey_GetUserKey( mBaseKey , mUserID )  ( mBaseKey + ( mUserID * DEF_USER_KEY ) )

	#define DEF_KEY_COIN_ERROR_TIME_MAX	 	125			//  500ms
	#define DEF_KEY_HPSW_ERROR_TIME_MAX 	50  		// 200ms
	#define DEF_KEY_KEYIN_ACTION_TIME		375			// 1500ms
	
	EXTERN void vKey_SetActionErrorTime( ULONG mode , UWORD value ) ;
	EXTERN void vKey_MJKeyScan( ULONG id , ULONG mode ) ;
	
	EXTERN void  vKey_Initial( void ) ; // poweron initial
	EXTERN void  vKey_ReadIOAndSetAccessProcess( void ) ; // interrupt timer0 or timer1
	
	EXTERN ULONG ulKey_ReadAccessTime( ULONG ulKeyID ) ;
	EXTERN void  vKey_SetAccessTime( ULONG ulKeyID , ULONG ulTimeValue ) ;

    EXTERN ULONG ulKey_Push( ULONG ulKeyID ) ; // 检查按键是否被按下(单次)
	EXTERN ULONG ulKey_PushRange( ULONG ulKeyID , ULONG ulMin , ULONG ulMax ) ; // 检查按键是否被按下(比较严谨的检查范围)
	EXTERN ULONG ulKey_RePush( ULONG ulKeyID , ULONG ulFstDelay , ULONG ulSecDelay ) ; // 检查按键是否被按下(可以一直按着)
	EXTERN ULONG ulKey_Gear( ULONG ulKeyID , ULONG ulG1Tim , ULONG ulG1Dly , ULONG ulG2Tim , ULONG ulG2Dly , ULONG ulG3Tim , ULONG ulG3Dly ) ;
	EXTERN ULONG ulKey_Touch( ULONG ulKeyID ) ; // 检查按键是否被按下(按住)
	EXTERN ULONG ulKey_Get( void ) ; // 检查有那个按键被按下(依序)
	EXTERN ULONG ulKey_CheckIsSame( ULONG ulKey1 , ULONG ulKey2 ) ; // 检查二个按键是否相同

	EXTERN void  vKey_EnableActionFlag( ULONG ulKeyID ) ; // 开启ActionKey
	EXTERN void  vKey_DisableActionFlag( ULONG ulKeyID ) ; // 关闭ActionKey
	EXTERN void  vKey_CleanActionFlag( ULONG ulKeyID ) ;
	EXTERN ULONG ulKey_ReadActionFlag( ULONG ulKeyID ) ; // 读取ActionKey
	EXTERN ULONG ulKey_ActionIsError( ULONG ulKeyID ) ; // 检查ActionKey是否错误
	EXTERN UBYTE ubKey_GetActionStatus( ULONG ulKeyID ) ;
    
 	#undef EXTERN
#endif
