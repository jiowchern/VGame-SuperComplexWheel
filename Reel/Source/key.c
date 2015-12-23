#define DEF_KEY_C
#include "../../h/common.h"
#define FILE_NAME "KEY.C"

#ifdef __PCSIM__
	#define DEF_KEY_PUSH_ACCESS_TIME	6
#else
#ifdef DEF_USE_IOBOARD        
	#define DEF_KEY_PUSH_ACCESS_TIME	6
#endif
#ifdef DEF_USE_IOPCI
	#define DEF_KEY_PUSH_ACCESS_TIME	24
#endif
#endif

#define IO_P1_K0    mUserIO_IndexToPort( 0 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P1_K1    mUserIO_IndexToPort( 0 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P2_K0    mUserIO_IndexToPort( 1 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P2_K1    mUserIO_IndexToPort( 1 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P3_K0    mUserIO_IndexToPort( 2 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P3_K1    mUserIO_IndexToPort( 2 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P4_K0    mUserIO_IndexToPort( 3 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P4_K1    mUserIO_IndexToPort( 3 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P5_K0    mUserIO_IndexToPort( 4 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P5_K1    mUserIO_IndexToPort( 4 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P6_K0    mUserIO_IndexToPort( 5 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P6_K1    mUserIO_IndexToPort( 5 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P7_K0    mUserIO_IndexToPort( 6 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P7_K1    mUserIO_IndexToPort( 6 , DEF_PCI_WR_KEY_L , 1 )
#define IO_P8_K0    mUserIO_IndexToPort( 7 , DEF_PCI_WR_KEY_L , 0 )
#define IO_P8_K1    mUserIO_IndexToPort( 7 , DEF_PCI_WR_KEY_L , 1 )

// Key Device
IO const stcKeyDeviceInfo[DEF_KEY_DEVICE_MAX] = {
	// 
	{ IO_CPU   , IO_PORTA , IO_BIT0|IO_BIT1                                         , 0xFF , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	{ IO_CPU   , IO_PORTH , IO_BIT2|IO_BIT3|IO_BIT4|IO_BIT5|IO_BIT6|IO_BIT7         , 0xFF , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	{ IO_MAP   , IO_PORTC , IO_BIT_FULL                                             , 0xFF , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	{ IO_MAP   , IO_PORTD , IO_BIT_FULL                                             , 0xFF , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,

	{ IO_PCI   , IO_PORTA , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	{ IO_PCI   , IO_PORTB , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,

    #ifdef DEF_DEFINE_DEBUG_PCKEY
    
		{ IO_PCI   , IO_PORTC , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
		{ IO_PCI   , IO_PORTD , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTE , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTF , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTG , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTH , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTI , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTJ , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTK , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTL , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTM , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
		{ IO_PCI   , IO_PORTN , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } , 
    
    #else
    
    #ifdef DEF_USE_UART_1

	    { IO_KEYBUF   , IO_PORTA , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTB , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTC , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTD , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTE , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTF , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTG , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTH , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTI , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTJ , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTK , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTL , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTM , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTN , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTO , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTP , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTQ , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTR , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTS , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_KEYBUF   , IO_PORTT , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,

    #else
    	
	    { IO_CMDBUF   , IO_P1_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P1_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P2_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P2_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P3_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P3_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P4_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P4_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P5_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P5_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P6_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P6_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P7_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P7_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P8_K0 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
	    { IO_CMDBUF   , IO_P8_K1 , IO_BIT_FULL                                             , 0x00 , {  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
    
    #endif
    	
    #endif
} ;

// 矪瞶Ч I/O 猧戈
UBYTE ubKeyReadFromPad[DEF_KEY_DEVICE_MAX]  ;
// 眖 I/O ┮弄戈
UBYTE ubKeySaveFromPad[DEF_KEY_DEVICE_MAX]  ;
// ヘ玡龄砆い耞丁
UWORD uwKeyAccessTime[DEF_KEY_DEVICE_MAX*8] ;
// ヘ玡龄篈
UBYTE ubKeyActionFlag[DEF_KEY_DEVICE_MAX*8] ;

UWORD uwKeyActionErrorTime[3] ;	// Coin . Keyin . HPSw(TKSw)

void vKey_SetActionErrorTime( ULONG mode , UWORD value )
{
	if( mode < 3 )
	{
		uwKeyActionErrorTime[ mode ] = value ;
	}
}

void vKey_MJKeyScan( ULONG id , ULONG mode )
{
	if( id < DEF_MJKEY_SCANLINEOUT_MAX )
	{
		if( mode )
		{
			if ( stcMJKeyScanLineOutInformation[id].ubDrive != IO_EMPTY )
			{
				vIO_Write( stcMJKeyScanLineOutInformation[id].ubDrive , stcMJKeyScanLineOutInformation[id].ubPort , stcMJKeyScanLineOutInformation[id].ubBit , 0 ) ;	
			}
		}
		else
		{
			if ( stcMJKeyScanLineOutInformation[id].ubDrive != IO_EMPTY )
			{
				vIO_Write( stcMJKeyScanLineOutInformation[id].ubDrive , stcMJKeyScanLineOutInformation[id].ubPort , stcMJKeyScanLineOutInformation[id].ubBit , stcMJKeyScanLineOutInformation[id].ubBit ) ;
			}
		}
	}
}

// ﹍闽跑计
void vKey_Initial( void )
{
	SLONG slLoop , slLoop1 , slLoop2 ;
	
	slLoop2 = 0 ;
	for ( slLoop = 0 ; slLoop < DEF_KEY_DEVICE_MAX ; slLoop ++ )
	{
		ubKeyReadFromPad[slLoop] = 0 ;
		ubKeySaveFromPad[slLoop] = 0 ;
		
		for ( slLoop1 = 0 ; slLoop1 < 8 ; slLoop1 ++ )
		{
			uwKeyAccessTime[slLoop2] = 0 ;
			
			ubKeyActionFlag[slLoop2] = DEF_KEY_DISABLE ;
			slLoop2 ++ ;
		}
	}
	
	for ( slLoop = 0 ; slLoop < DEF_MJKEY_SCANLINEOUT_MAX ; slLoop ++ )
	{
		vKey_MJKeyScan( slLoop , 0 ) ;
	}
}

// い耞 , 弄 Input 砞﹚闽戈癟
void vKey_ReadIOAndSetAccessProcess( void ) // Timer0 16ms or Timer1 4ms
{
	SLONG slReadIndex ;
	SLONG slBitIndex  ;
	SLONG slAccessIndex ;
	UBYTE ubReadTempIO , ubCheckIO ;
	
	for ( slReadIndex = 0 ; slReadIndex < DEF_KEY_DEVICE_MAX ; slReadIndex ++ )
	{
		ubReadTempIO = ubIO_Read( stcKeyDeviceInfo[slReadIndex].ubDrive , stcKeyDeviceInfo[slReadIndex].ubPort , stcKeyDeviceInfo[slReadIndex].ubBit ) ;
		ubReadTempIO = (~(ubReadTempIO ^ stcKeyDeviceInfo[slReadIndex].ubAct)) ;
		ubKeyReadFromPad[slReadIndex] = (ubKeySaveFromPad[slReadIndex] & ubReadTempIO) ;
		ubKeySaveFromPad[slReadIndex] = ubReadTempIO ;
		
		ubCheckIO = ubKeyReadFromPad[slReadIndex] ;
		slAccessIndex = slReadIndex * 8 ;
		for ( slBitIndex = 0 ; slBitIndex < 8 ; slBitIndex ++ )
		{
			if ( ubCheckIO & 0x01 )
			{
				uwKeyAccessTime[slAccessIndex] ++ ;
				
				if ( uwKeyAccessTime[slAccessIndex] >= 0xF000 )
				{
					uwKeyAccessTime[slAccessIndex] = 0xD000 ;
				}
			
			#ifdef DEF_USE_IOBOARD	
				if ( ubKeyActionFlag[slAccessIndex] == DEF_KEY_ENABLE )
				{
					if ( stcKeyDeviceInfo[slReadIndex].ubMax[slBitIndex] != 0 )
					{
						if ( uwKeyAccessTime[slAccessIndex] >= stcKeyDeviceInfo[slReadIndex].ubMax[slBitIndex] )
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ERROR ;
						}
					}
				}
			#endif
			#ifdef DEF_USE_IOPCI
				// Coin、HPSw、TKSw 长按会报警
				// Keyin 长按会开分
				if ( ubKeyActionFlag[slAccessIndex] == DEF_KEY_ENABLE )
				{
					if( ulKeyDefineInformation[ KEY_PCI_COIN_A ] == slAccessIndex )
					{
						if( uwKeyAccessTime[slAccessIndex] > uwKeyActionErrorTime[0] )
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ERROR ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_COIN_C ] == slAccessIndex )
					{
						if( uwKeyAccessTime[slAccessIndex] > uwKeyActionErrorTime[0] )
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ERROR ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_KEYIN_B ] == slAccessIndex )
					{
						if(( uwKeyAccessTime[slAccessIndex] > uwKeyActionErrorTime[1] )&&
							( uwKeyAccessTime[slAccessIndex] < (uwKeyActionErrorTime[1]*2) ))
						{
							uwKeyAccessTime[slAccessIndex] *= 2 ; // 防止重复读取
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION_10 ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_KEYIN_D ] == slAccessIndex )
					{
						if(( uwKeyAccessTime[slAccessIndex] > uwKeyActionErrorTime[1] )&&
							( uwKeyAccessTime[slAccessIndex] < (uwKeyActionErrorTime[1]*2) ))
						{
							uwKeyAccessTime[slAccessIndex] *= 2 ; // 防止重复读取
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION_10 ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_HPSW ] == slAccessIndex )
					{
						if( uwKeyActionErrorTime[2] )
						{
							if( uwKeyAccessTime[slAccessIndex] > uwKeyActionErrorTime[2] )
							{
								ubKeyActionFlag[slAccessIndex] = DEF_KEY_ERROR ;	
							}
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_TKSW ] == slAccessIndex )
					{
						if( uwKeyActionErrorTime[2] )
						{
							if( uwKeyAccessTime[slAccessIndex] > uwKeyActionErrorTime[2] )
							{
								ubKeyActionFlag[slAccessIndex] = DEF_KEY_ERROR ;	
							}
						}
					}
				}
			#endif
				
			}
			else
			{
				
			#ifdef DEF_USE_IOBOARD	
				if ( ubKeyActionFlag[slAccessIndex] == DEF_KEY_ENABLE )
				{
					if ( uwKeyAccessTime[slAccessIndex] > 2 )
					{
						ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION ;
					}
				}
			#endif	
			#ifdef DEF_USE_IOPCI	
				// Coin、HPSw、TKSw 短按会忽略
				// Keyin 短按会开分（但不能包含长按的分数）
				if ( ubKeyActionFlag[slAccessIndex] == DEF_KEY_ENABLE )
				{
					if( ulKeyDefineInformation[ KEY_PCI_COIN_A ] == slAccessIndex )
					{
						if( uwKeyAccessTime[slAccessIndex] )
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_COIN_C ] == slAccessIndex )
					{
						if( uwKeyAccessTime[slAccessIndex] )
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_KEYIN_B ] == slAccessIndex )
					{
						if(( uwKeyAccessTime[slAccessIndex] > 2 )&&
							( uwKeyAccessTime[slAccessIndex] < uwKeyActionErrorTime[1] ))
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION ;	
						}
					}
					else if( ulKeyDefineInformation[ KEY_PCI_KEYIN_D ] == slAccessIndex )
					{
						if(( uwKeyAccessTime[slAccessIndex] > 2 )&&
							( uwKeyAccessTime[slAccessIndex] < uwKeyActionErrorTime[1] ))
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION ;	
						}
					}
					else
					{
						if( uwKeyAccessTime[slAccessIndex] > 2 )
						{
							ubKeyActionFlag[slAccessIndex] = DEF_KEY_ACTION ;	
						}
					}
				}
			#endif
			
				uwKeyAccessTime[slAccessIndex] = 0 ;
				
			}
			slAccessIndex ++ ;
			ubCheckIO = ubCheckIO >> 1 ;
		}
	}
}

ULONG ulKey_ReadAccessTime( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulKeyID >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulKeyID-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { return ( 0 ) ; }
        }
        #endif
        #endif
		
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		return ( uwKeyAccessTime[ulKey] ) ;
	}
	return ( 0 ) ;
}

void vKey_SetAccessTime( ULONG ulKeyID , ULONG ulTimeValue )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ;
		}
		uwKeyAccessTime[ulKey] = ulTimeValue ;
	}
}

ULONG ulKey_Push( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulKeyID >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulKeyID-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { return ( 0 ) ; }
        }
        #endif
        #endif
        
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		if ( uwKeyAccessTime[ulKey] )
		{
			if ( uwKeyAccessTime[ulKey] < DEF_KEY_PUSH_ACCESS_TIME )
			{
				uwKeyAccessTime[ulKey] = DEF_KEY_PUSH_ACCESS_TIME ;
				return ( 1 ) ;
			}
		}
	}

	return ( 0 ) ;
}

ULONG ulKey_PushRange( ULONG ulKeyID , ULONG ulMin , ULONG ulMax )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulKeyID >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulKeyID-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { return ( 0 ) ; }
        }
        #endif
        #endif
		
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		if ( uwKeyAccessTime[ulKey] )
		{
			if ( uwKeyAccessTime[ulKey] >= ulMin )
			{
				if ( uwKeyAccessTime[ulKey] < ulMax )
				{
					uwKeyAccessTime[ulKey] = ulMax + 1 ;
					return ( 1 ) ;
				}
			}
		}
	}

	return ( 0 ) ;
}


ULONG ulKey_RePush( ULONG ulKeyID , ULONG ulFstDelay , ULONG ulSecDelay )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulKeyID >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulKeyID-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { return ( 0 ) ; }
        }
        #endif
        #endif
		
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		if ( uwKeyAccessTime[ulKey] )
		{
			if ( uwKeyAccessTime[ulKey] < DEF_KEY_PUSH_ACCESS_TIME )
			{
				uwKeyAccessTime[ulKey] = 0xD000 - ulFstDelay ;
				return ( 1 ) ;
			}
			else
			{
				/*
				if ( uwKeyAccessTime[ulKey] < (0xD000 - ulFstDelay) )
				{
					uwKeyAccessTime[ulKey] = 0xD000 - ulFstDelay ;
				}
				*/
			}
				
			if ( uwKeyAccessTime[ulKey] >= 0xD000 )
			{
				uwKeyAccessTime[ulKey] = 0xD000 - ulSecDelay ;
				return ( 1 ) ;
			}
		}
	}

	return ( 0 ) ;
}

ULONG ulKey_Gear( ULONG ulKeyID , ULONG ulG1Tim , ULONG ulG1Dly , ULONG ulG2Tim , ULONG ulG2Dly , ULONG ulG3Tim , ULONG ulG3Dly )
{
    ULONG ulKey ;
    ULONG ulTim ;

    if( ulKeyID < KEY_MAX )
    {
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulKeyID >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulKeyID-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { return ( 0 ) ; }
        }
        #endif
        #endif
		
        if( ulKeyDefineInformation[ulKeyID] == -1 )   { return ( 0 ) ; }

        ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
        ulTim = uwKeyAccessTime[ulKey] ;
        if( ulTim )
        {
            if( ulTim < 0x1000 )
            {
                if( ulG1Tim && ulG1Dly )
                {
                    uwKeyAccessTime[ulKey] = 0x1000 ;
                    return ( 1 ) ;
                }
            }
            else
            {
                if( ulTim < (0x1000 + ulG1Tim) )
                {
                    if( ( (ulTim - 0x1000) % ulG1Dly ) == 0 )   { return ( 1 ) ; }
                }
                else
                {
                    if( ulTim < 0x5000 )
                    {
                        if( ulG2Tim && ulG2Dly )
                        {
                            uwKeyAccessTime[ulKey] = 0x5000 ;
                            return ( 2 ) ;
                        }
                        if( ( (ulTim - 0x1000) % ulG1Dly ) == 0 )   { return ( 1 ) ; }
                    }
                    else
                    {
                        if( ulTim < (0x5000 + ulG2Tim) )
                        {
                            if( ( (ulTim - 0x5000) % ulG2Dly ) == 0 )   { return ( 2 ) ; }
                        }
                        else
                        {
                            if( ulTim < 0xA000 )
                            {
                                if( ulG3Tim && ulG3Dly )
                                {
                                    uwKeyAccessTime[ulKey] = 0xA000 ;
                                    return ( 3 ) ;
                                }
                                if( ( (ulTim - 0x5000) % ulG2Dly ) == 0 )   { return ( 2 ) ; }
                            }
                            else
                            {
                                if( ( (ulTim - 0xA000) % ulG3Dly ) == 0 )   { return ( 3 ) ; }
                            }
                        }
                    }
                }
            }
        }
    }
    return ( 0 ) ;
}

ULONG ulKey_Touch( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulKeyID >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulKeyID-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { return ( 0 ) ; }
        }
        #endif
        #ifdef DEF_TEST_AUTOPLAY_ALWAYS
        if( ulKeyID == KEY_PCI_97_TEST ) 
        {
        	return ( 1 ) ;
        }
        #endif
        #endif
		
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		if ( uwKeyAccessTime[ulKey] )
		{
			return ( 1 ) ;
		}
	}

	return ( 0 ) ;
}

ULONG ulKey_Get( void )
{
	ULONG ulKey , ulLoop ;
	
	for ( ulLoop = 0 ; ulLoop < KEY_MAX ; ulLoop ++ )
	{
        #ifdef DEF_DEFINE_DEBUG_PCKEY
        #ifdef DEF_USE_IOBOARD
        if( ulLoop >= KEY_1P_KEYIN )
        {
            if( !uwKeyAccessTime[ ulKeyDefineInformation[ KEY_SEL_1P + ((ulLoop-KEY_1P_KEYIN) / DEF_USER_KEY) ] ] )  { continue ; }
        }
        #endif
        #endif

		ulKey = ulKeyDefineInformation[ulLoop] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			continue ;
		}
		if ( uwKeyAccessTime[ulKey] )
		{
			if ( uwKeyAccessTime[ulKey] < DEF_KEY_PUSH_ACCESS_TIME )
			{
				uwKeyAccessTime[ulKey] = DEF_KEY_PUSH_ACCESS_TIME ;
				
				return ( ulLoop ) ; // 0~KEY_MAX
			}
		}
	}

	return ( KEY_MAX ) ;
}

ULONG ulKey_CheckIsSame( ULONG ulKey1 , ULONG ulKey2 )
{
	if ( ulKey1 >= KEY_MAX )
	{
		return ( 0 ) ;
	}
	if ( ulKey2 >= KEY_MAX )
	{
		return ( 0 ) ;
	}
	if ( ulKeyDefineInformation[ulKey1] == ulKeyDefineInformation[ulKey2] )
	{
		return ( 1 ) ;
	}

	return ( 0 ) ;
}

void vKey_EnableActionFlag( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ;
		}
		if ( ubKeyActionFlag[ulKey] == DEF_KEY_DISABLE )
		{
			ubKeyActionFlag[ulKey] = DEF_KEY_ENABLE ;
		}
	}

}

void vKey_DisableActionFlag( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ;
		}
		if ( ubKeyActionFlag[ulKey] != DEF_KEY_DISABLE )
		{
			ubKeyActionFlag[ulKey] = DEF_KEY_DISABLE ;
		}
	}

}

void vKey_CleanActionFlag( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ;
		}
		if ( ubKeyActionFlag[ulKey] == DEF_KEY_ACTION )
		{
			ubKeyActionFlag[ulKey] = DEF_KEY_ENABLE ;
		}
	}

}

ULONG ulKey_ReadActionFlag( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		if ( ubKeyActionFlag[ulKey] == DEF_KEY_ACTION )
		{
			ubKeyActionFlag[ulKey] = DEF_KEY_ENABLE ;
			return ( 1 ) ;
		}
		if ( ubKeyActionFlag[ulKey] == DEF_KEY_ACTION_10 )
		{
			ubKeyActionFlag[ulKey] = DEF_KEY_ENABLE ;
			return ( 10 ) ;
		}
	}

	return ( 0 ) ;	
}

ULONG ulKey_ActionIsError( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
		if ( ubKeyActionFlag[ulKey] == DEF_KEY_ERROR )
		{
			return ( 1 ) ;
		}
	}
	
	return ( 0 ) ;
}

UBYTE ubKey_GetActionStatus( ULONG ulKeyID )
{
	ULONG ulKey ;
	
	if ( ulKeyID < KEY_MAX )
	{
		ulKey = ulKeyDefineInformation[ulKeyID] ;
		if ( ulKey >= (DEF_KEY_DEVICE_MAX*8) )
		{
			return ( 0 ) ;
		}
	
		return ( ubKeyActionFlag[ulKey] ) ;
	}
	
	return ( 0 ) ;
}
