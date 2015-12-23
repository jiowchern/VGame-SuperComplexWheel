
    #ifdef DEF_ENABLE_MULTI_SELECT
    #define mGame_ReadGameSelect()      ulAdjustGameSel_Read()
    #endif
	#ifdef DEF_USE_VGAME_UART_SLAVE
	#ifdef DEF_USE_DIPSW_SET_SLAVEID
    #define mGame_ReadLinkSlaveID()		(ubDipSw_ReadSaveData()&0x1F)			// 连线编号
	#else
    #define mGame_ReadLinkSlaveID()		ulAdjustSlaveIDSel_Read()				// 连线编号
    #endif
    #endif
	
	// system.
    #define mGame_ReadCoinRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_COIN_A_RATE)
    #define mGame_ReadCoinARate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_COIN_A_RATE)
    #define mGame_ReadCoinCRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_COIN_C_RATE)
    //#define mGame_ReadMoneyRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_MONEY_RATE)
    
    #ifdef DEF_GTRULE_GTHS
    #define mGame_ReadOptionType() 		ulAdjustValue_Read(DEF_ADJUSTVALUE_OPTION_TYPE)
    #define mGame_ReadReportDay()		ulAdjustValue_Read(DEF_ADJUSTVALUE_REPORT_DAY)
    //#define mGame_ReadReportHour()		ulAdjustValue_Read(DEF_ADJUSTVALUE_REPORT_HOUR)
    #define mGame_ReadReportCoin()		ulAdjustValue_Read(DEF_ADJUSTVALUE_REPORT_COIN)
    #define mGame_ReadHotMode()			ulAdjustValue_Read(DEF_ADJUSTVALUE_HOT_MODE)
    #define mGame_ReadHotValue()		ulAdjustValue_Read(DEF_ADJUSTVALUE_HOT_ASSIGN)
    #ifdef DEF_M100CHP_ACTIVATE_LIMIT
    #define mGame_ReadActivLimit()      ulAdjustValue_Read(DEF_ADJUSTVALUE_ACTIV_LIMIT)
    #endif
    #endif
    
    #define mGame_ReadKeyInRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_KEYIN_B_RATE)
    #define mGame_ReadKeyInBRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_KEYIN_B_RATE)
    #define mGame_ReadKeyInDRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_KEYIN_D_RATE)
    #define mGame_ReadKeyOutRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_KEYOUT_RATE)    
    #define mGame_ReadTicketRate()		ulAdjustValue_Read(DEF_ADJUSTVALUE_TICKET_RATE)

    #define mGame_ReadGameRateLevel()	ulAdjustValue_Read(DEF_ADJUSTVALUE_GAME_RATE)
    #define mGame_ReadRateModeLevel()	ulAdjustValue_Read(DEF_ADJUSTVALUE_GAME_UNDULATE)	
    #define mGame_ReadWupRateLevel()	ulAdjustValue_Read(DEF_ADJUSTVALUE_WUP_RATE)
    
    #define mGame_ReadMinBet()			ulAdjustValue_Read(DEF_ADJUSTVALUE_MIN_BET)
    #define mGame_ReadMaxBet()			ulAdjustValue_Read(DEF_ADJUSTVALUE_MAX_BET)
    #define mGame_ReadBetAdd()			ulAdjustValue_Read(DEF_ADJUSTVALUE_BETADD)
    #define mGame_ReadBetForGift()		ulAdjustValue_Read(DEF_ADJUSTVALUE_GIFT_BET)

    #define mGame_ReadCreditLimit()		ulAdjustValue_Read(DEF_ADJUSTVALUE_CREDIT_LIMIT)
    #define mGame_ReadSystemLimit()		ulAdjustValue_Read(DEF_ADJUSTVALUE_SYS_LIMIT)
    
    // 比倍爆机分数：如果为0，表示没有比倍游戏，中奖只能得分
    #define mGame_ReadWupLimitTop()		ulAdjustValue_Read(DEF_ADJUSTVALUE_WUP_LIMIT)
	
    #define mGame_ReadWupAsnKill()		ulAdjustValue_Read(DEF_ADJUSTVALUE_WUP_KILL) 				// 周期砍牌
    #define mGame_ReadWupAsnLose()		ulAdjustValue_Read(DEF_ADJUSTVALUE_WUP_LOSE) 				// 连输补牌
             
    #define mGame_ReadMusicMode() 		ulAdjustValue_Read(DEF_ADJUSTVALUE_GAME_MUSIC)
    
        #define DEF_MUSIC_MODE_OFF 0
        #define DEF_MUSIC_MODE_ON  1
        #define DEF_MUSIC_MODE_SND 2
        #define DEF_MUSIC_MODE_MUS 3

    #define mGame_ReadMusicVol() 		ulAdjustValue_Read(DEF_ADJUSTVALUE_MUSIC_VOLUME)
            
    #define mGame_ReadDemoMusic()		ulAdjustValue_Read(DEF_ADJUSTVALUE_DEMOMUSIC)
        
    //#define mGame_ReadFontType() 		ulAdjustValue_Read(DEF_ADJUSTVALUE_FONT_TYPE)
   // #define mGame_ReadFontType()		0
    	#define DEF_FONTTYPE_CN 0
    	#define DEF_FONTTYPE_TW 1
    	#define DEF_FONTTYPE_EN 2
    	#define DEF_FONTTYPE_JP 3
    	//#define DEF_FONTTYPE_IT 4
    	
    #ifdef __CN__
    #define mGame_ReadFontType()		DEF_FONTTYPE_CN
    #endif
    #ifdef __TW__
    #define mGame_ReadFontType()		DEF_FONTTYPE_TW
    #endif
    #ifdef __FA__
    #define mGame_ReadFontType()		DEF_FONTTYPE_EN
    #endif	
    #ifdef __HY__
    #define mGame_ReadFontType()		DEF_FONTTYPE_EN
    #endif	
    
    #define mGame_ReadPayMode()			ulAdjustValue_Read(DEF_ADJUSTVALUE_PAYOUT_MODE)
		#define DEF_PAYOUT_MODE_HPOUT 0
		#define DEF_PAYOUT_MODE_TKOUT 1
		#define DEF_PAYOUT_MODE_DIRHP 2
		#define DEF_PAYOUT_MODE_DIRTK 3
		#define DEF_PAYOUT_MODE_FASKO 4
		#define mGamePayISHPMode()		((mGame_ReadPayMode()&1)==DEF_PAYOUT_MODE_HPOUT)
    
	#define mGame_ReadMaxLink()			1		// DEF_GAME_PLAYER_MAX
	#define mGame_ReadSymbolMode()		ulAdjustValue_Read(DEF_ADJUSTVALUE_SYMBOL)			// 动物 或 数字	
