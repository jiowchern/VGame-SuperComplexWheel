
#ifndef DEF_INCLUDE_FLASHROM_H
	#define DEF_INCLUDE_FLASHROM_H

	enum 
	{
		// 已经改用Set的方式保存，所以顺序没有差别了
		DEF_ADJUSTVALUE_COIN_A_RATE ,	// 00
		DEF_ADJUSTVALUE_MONEY_RATE ,	// 01
		DEF_ADJUSTVALUE_OPTION_TYPE ,	// 02
		DEF_ADJUSTVALUE_REPORT_DAY ,	// 03
		DEF_ADJUSTVALUE_REPORT_HOUR ,	// 04 
		DEF_ADJUSTVALUE_REPORT_COIN ,	// 05		
		DEF_ADJUSTVALUE_SYS_TIME ,		// 06 (这只是占一个空栏位)
		DEF_ADJUSTVALUE_HOT_MODE ,		// 07
		DEF_ADJUSTVALUE_HOT_ASSIGN ,	// 08		
		
		// 以下的可以自行定义顺序及功能
		DEF_ADJUSTVALUE_COIN_C_RATE ,	// 09
		DEF_ADJUSTVALUE_KEYIN_B_RATE , 	// 0A
		DEF_ADJUSTVALUE_KEYIN_D_RATE , 	// 0B
		DEF_ADJUSTVALUE_KEYOUT_RATE , 	// 0C
		DEF_ADJUSTVALUE_PAYOUT_MODE ,	// 0D
		DEF_ADJUSTVALUE_TICKET_RATE ,	// 0E
		DEF_ADJUSTVALUE_GAME_UNDULATE ,	// 0F
		DEF_ADJUSTVALUE_GAME_RATE ,		// 10
		DEF_ADJUSTVALUE_WUP_RATE ,		// 11
		DEF_ADJUSTVALUE_MIN_BET ,		// 12 
		DEF_ADJUSTVALUE_MAX_BET ,		// 13 
		DEF_ADJUSTVALUE_BETADD ,		// 14
		DEF_ADJUSTVALUE_GIFT_BET ,		// 15
		
		DEF_ADJUSTVALUE_CREDIT_LIMIT ,	// 16
		DEF_ADJUSTVALUE_SYS_LIMIT ,		// 17
		DEF_ADJUSTVALUE_WUP_LIMIT ,		// 18 
		DEF_ADJUSTVALUE_WUP_LOSE ,		// 19
		DEF_ADJUSTVALUE_WUP_KILL ,		// 1A				
		
		DEF_ADJUSTVALUE_GAME_MUSIC ,	// 1B
		DEF_ADJUSTVALUE_MUSIC_VOLUME ,	// 1C
		DEF_ADJUSTVALUE_DEMOMUSIC ,		// 1D
		DEF_ADJUSTVALUE_SYMBOL ,		// 1E   
		DEF_ADJUSTVALUE_FONT_TYPE ,
        DEF_ADJUSTVALUE_ACTIV_LIMIT , 	// DEF_M100CHP_ACTIVATE_LIMIT
		   
		DEF_ADJUSTVALUE_DEF_MAX ,		

		// 特别的，不会被归零的
        #ifdef DEF_ENABLE_MULTI_SELECT
        DEF_ADJUSTVALUE_GAME_SEL = 0xA0 ,
        #endif		
		#ifdef __NO_UART__
		#else        
		DEF_ADJUSTVALUE_SLAVEID ,
		#endif
		
		// 暂时没用上的
	} ;

	
	// key.
	extern ULONG const ulKeyDefineInformation[KEY_MAX] ;

	// adjust.
	extern ADJUSTVALUE const stcAdjustValueInformationForSW[DEF_ADJUSTVALUE_MAX] ;
	
	// IO.
	extern IO const stcLampOutputInformation[DEF_LAMP_MAX] ;
	extern IO const stcMeterOutputInformation[DEF_METER_MAX] ;
	extern IO const stcSSROutputInformation[DEF_SSR_MAX] ;
	extern IO const stcMJKeyScanLineOutInformation[DEF_MJKEY_SCANLINEOUT_MAX] ;

	// password.
	extern UBYTE const ubPasswordDefault[DEF_PASSWORD_ID_MAX][8] ;
		
	#undef EXTERN 
#endif
