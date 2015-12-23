#ifndef DEF_INCLUDE_DEFINE_H
    #define DEF_INCLUDE_DEFINE_H

    // ********** System **********

	#define __IOUART__
//	#define __GTVG__
//	#define __GTHS__

	#ifdef __HY__
		#define __GTHS__
	#endif
    
	#define DEF_HANDCARD_MAX			5		// �����Ƶ�����
	#define DEF_GAME_PLAYER_MAX			8		// ���������8Ҳ��ׯ�ҡ�Ҳ���ܺ�
	#define DEF_GAME_ONLY_PLAY			0		// �����˿ˣ�ֻʹ��һ�����
        
    //#define DEF_DEFINE_ENABLE_GTRULE				//������̨���빦��
    //#ifdef __RELEASE__
    //#define DEF_DEFINE_ROMTEST
    //#endif

	#ifdef __GTHS__
		#define DEF_GTRULE_GTHS
		#define DEF_GTHS_II
    	#define DEF_M106CH_FIX_GTHS_II                  // M106CH �W�[ ?�{�[?���O��?[?������??,����X?]
        #define DEF_M107CH_FIX_GTHS_II                  // M107CH �ץ�M106CH????,??�x?�s?�A?�J�K???
	    //#define DEF_M100CHP_ACTIVATE_LIMIT              //  M112CHP �W�[�E  (CPU����s�ɡA�h��s)   
	    #define DEF_FIX_GTHS_GETCHECKCODE               // ��������k�s������X���~���D(CPU����s�ɡA�h��s)          
    	#define DEF_M304CH_FIX_GTDISDEFPWD              // M304CH �ק� �H�x�t�ζR��x�w�]�ѽX�K�X ADJ:[��6] RST:[��7]
    
    	#ifdef __HY__	
    		#define DEF_GTHS_II_HY
    	#endif	
	#else
	#ifdef __GTVG__
		#define DEF_GTRULE_GTVG
		#define DEF_GTVG_5PK
	#else
		#define DEF_NO_GTRULE
	#endif
	#endif	
		
    // ****************************
    
    // �ⶨ����Flash�ں˳�ʽ�йأ�����������
    #ifdef __IOPCI__
    	#define DEF_USE_IOPCI
    #endif	
    #ifdef __IOBOARD__
    	#define DEF_USE_IOBOARD			// ���û�� DEF_USE_UART_1 �������� CmdPort �ķ�ʽ
    	#define DEF_USE_UART_1  		// ����RS232��ͬʱҪ���� DEF_USE_IOBOARD
    #endif	
    #ifdef __IOUART__
    	#define DEF_USE_IOPCI
	#endif
	
	#define	DEF_OPEN_SLAVE_PROCESS			// �������ڸ��������̣�����ƽ����������̵Ĳ�Ʒ
	//#define DEF_CHANGE_LF_RT_KEY			// �������Ҽ��෴���⣬Ϊ����������汾ͬ�����������޸�
	#define DEF_M100XX_ENABLE_SHUTDOWN
	
    // ********** Update **********
	#define DEF_FIX_RepoCoinBug
	
	#ifdef __HY__
		#define DEF_USE_CHS_SHOWREC
		#define DEF_ADD_GAMERATE_ADJ
	#endif
	   
    // ****************************
	//#define DEF_OPEN_CHECK_PAYOUT_BOX_FULL
	#define DEF_USE_IPCKEY_RECORD				// M104HY
	   
    #if defined(__TW__)
    	#define DEF_USE_UART_0					// ���û�� DEF_USE_VGAME_UART ����ֻ�п�UART û������
    	#define DEF_USE_VGAME_UART_SLAVE		// ����VGAME UART���̣�ͬʱҪ���� DEF_USE_UART_0
    	#define DEF_USE_DIPSW_SET_SLAVEID
    	#define DEF_CHANCE_FOR_UART_SLAVE		
		//#define DEF_SHOWTMP_KEYIN
	    //#define DEF_CHANCE_TW_EXAMINE                // ForTest
    #endif  
	#ifdef DEF_CHANCE_TW_EXAMINE
		#undef DEF_USE_UART_0
		#undef DEF_USE_VGAME_UART_SLAVE
		#define DEF_TEST_KEYWINBIG      		// ���԰��̶������� 
		//#define DEF_TEST_WUPWIN
	#endif
	
    // ********** Chance ********** 
    #define DEF_FIX_CHANCE_BUG_20150126 
    #define DEF_FIX_CHANCE_20150212			// ǿ�������ߣ���һ������Ѻע���߲Ÿ��������

   	// ****************************    

	#define DEF_DEFINE_FOR_QCTEST
	#ifdef __DEBUG__
		#define DEF_DEFINE_DEBUG_ENABLE
	#endif
		
    #ifdef DEF_DEFINE_DEBUG_ENABLE
    	#ifdef __PCSIM__
        	#define DEF_DEFINE_DEBUG_PCKEY          // �}�Ұƾ�IO��PC��L���� (���ե�)(����CPU)
        	#define DEF_SYSTEM_CMD_GAMEEXIT
			#define DEF_DEFINE_DISBLE_GTRULE		// Ĭ��Ϊ������̨��
        	//#define DEF_OPEN_FAST_TEST
        	//#define DEF_OPEN_PCFILEOUT 
        	//#define DEF_TEST_ONLY_NATURE       	
		#endif

		//#define DEF_DEFINE_SHOW_STATE        
        
        // For Debug Game
        #define DEF_DEFINE_PAUSE_KEY            // �� [/] �i�Ȱ�/�~��
       	//#define DEF_DEFINE_SHOW_FPS

		#ifdef DEF_DEFINE_ENABLE_GTRULE
			//#define DEF_DEFINE_DISBLE_GTRULE		// Ĭ��Ϊ������̨��
			#define DEF_DEFINE_SHOW_HUAHAI_CODE		// ��ʾ��������ֵ
		#endif
		
		//#define DEF_DEFINE_DEBUG_PCKEY	
		//#define DEF_TEST_AUTOPLAY_ALWAYS
		//#define DEF_TEST_AUTOPLAY
		//#define DEF_TEST_KEYWINBIG      // ���԰��̶�������   
		
		#ifdef DEF_TEST_AUTOPLAY
			//#define DEF_TEST_AUTOPLAY_COIN             //��������Զ����·� 
			//#define DEF_TEST_AUTOPLAY_LINE             //��������Զ������9��
			//#define DEF_TEST_AUTOPLAY_WUP              //��������Զ��ȱ�
			//#ifdef DEF_USE_VGAME_UART_SLAVE
				//#define DEF_TEST_ALWAYS_AUTO_2
				//#undef DEF_TEST_AUTOPLAY_WUP
			//#endif
		#endif
		
    #endif

    #define DEF_FONT_SIZE           24		//32
    
    #define BIT00 0x00000001
    #define BIT01 0x00000002
    #define BIT02 0x00000004
    #define BIT03 0x00000008
    #define BIT04 0x00000010
    #define BIT05 0x00000020
    #define BIT06 0x00000040
    #define BIT07 0x00000080
    #define BIT08 0x00000100
    #define BIT09 0x00000200
    #define BIT10 0x00000400
    #define BIT11 0x00000800
    #define BIT12 0x00001000
    #define BIT13 0x00002000
    #define BIT14 0x00004000
    #define BIT15 0x00008000
    #define BIT16 0x00010000
    #define BIT17 0x00020000
    #define BIT18 0x00040000
    #define BIT19 0x00080000
    #define BIT20 0x00100000
    #define BIT21 0x00200000
    #define BIT22 0x00400000
    #define BIT23 0x00800000
    #define BIT24 0x01000000
    #define BIT25 0x02000000
    #define BIT26 0x04000000
    #define BIT27 0x08000000
    #define BIT28 0x10000000
    #define BIT29 0x20000000
    #define BIT30 0x40000000
    #define BIT31 0x80000000

    typedef union __BIT8__ {
        struct {
            unsigned d00:1 ;
            unsigned d01:1 ;
            unsigned d02:1 ;
            unsigned d03:1 ;
            unsigned d04:1 ;
            unsigned d05:1 ;
            unsigned d06:1 ;
            unsigned d07:1 ;
        } of ;
        UBYTE ubValue ;
    } STCBIT8 ;

    typedef union __BIT16__ {
        struct {
            unsigned d00:1 ;
            unsigned d01:1 ;
            unsigned d02:1 ;
            unsigned d03:1 ;
            unsigned d04:1 ;
            unsigned d05:1 ;
            unsigned d06:1 ;
            unsigned d07:1 ;
            unsigned d08:1 ;
            unsigned d09:1 ;
            unsigned d10:1 ;
            unsigned d11:1 ;
            unsigned d12:1 ;
            unsigned d13:1 ;
            unsigned d14:1 ;
            unsigned d15:1 ;
        } of ;
        UWORD uwValue ;
    } STCBIT16 ;

    typedef union __BIT32__ {
        struct {
            unsigned d00:1 ;
            unsigned d01:1 ;
            unsigned d02:1 ;
            unsigned d03:1 ;
            unsigned d04:1 ;
            unsigned d05:1 ;
            unsigned d06:1 ;
            unsigned d07:1 ;
            unsigned d08:1 ;
            unsigned d09:1 ;
            unsigned d10:1 ;
            unsigned d11:1 ;
            unsigned d12:1 ;
            unsigned d13:1 ;
            unsigned d14:1 ;
            unsigned d15:1 ;
            unsigned d16:1 ;
            unsigned d17:1 ;
            unsigned d18:1 ;
            unsigned d19:1 ;
            unsigned d20:1 ;
            unsigned d21:1 ;
            unsigned d22:1 ;
            unsigned d23:1 ;
            unsigned d24:1 ;
            unsigned d25:1 ;
            unsigned d26:1 ;
            unsigned d27:1 ;
            unsigned d28:1 ;
            unsigned d29:1 ;
            unsigned d30:1 ;
            unsigned d31:1 ;
        } of ;
        ULONG ulValue ;
    } STCBIT32 ;    
#endif
