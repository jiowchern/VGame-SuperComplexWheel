#ifndef DEF_INCLUDE_ADJUSTVALUE_H
	#define DEF_INCLUDE_ADJUSTVALUE_H

	#ifdef DEF_ADJUSTVALUE_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	#define DEF_ADJUSTVALUE_MAX	0x40

	typedef struct __ADJUSTVALUE__ {
		
		UWORD uwMax       ;
		UWORD uwDefault   ;
		ULONG ulValue[DEF_ADJUSTVALUE_MAX] ;
		
	} ADJUSTVALUE ;

	EXTERN void  vAdjustValue_Reset( void ) ; // 恢復默認值SW,Temp
	EXTERN ULONG ulAdjustValue_Initial( ULONG version ) ;
	EXTERN void  vAdjustValue_Break( void ) ;
		
	EXTERN void  vAdjustValue_SetBitValue( ULONG ulID , ULONG ulValue ) ; // 寫入SW值
	EXTERN ULONG ulAdjustValue_ReadBitValue( ULONG ulID ) ; // 讀取SW值
	
	EXTERN void  vAdjustValue_Set( ULONG ulID , ULONG ulValue ) ; // 寫入Temp
	EXTERN ULONG ulAdjustValue_ReadTempBits( ULONG ulID ) ; // 讀取Temp值
	
	EXTERN void  vAdjustValue_Setup( void ) ; // 將SW值備份到Temp
	EXTERN void  vAdjustValue_Inc( ULONG ulID ) ; // Temp+1
	EXTERN void  vAdjustValue_IncLoop( ULONG ulID ) ; // Temp+1, 超過循環
	EXTERN void  vAdjustValue_Dec( ULONG ulID ) ; // Temp-1
	EXTERN void  vAdjustValue_DecLoop( ULONG ulID ) ; // Temp-1, 超過循環
	EXTERN void  vAdjustValue_UpDate( void ) ; // 將Temp還原到SW
	
	EXTERN ULONG ulAdjustValue_Read( ULONG ulID ) ; // 從SW讀設定值
	EXTERN ULONG ulAdjustValue_ReadTemp( ULONG ulID ) ; // 從Temp讀設定值

    #ifdef DEF_ENABLE_MULTI_SELECT
    EXTERN void  vAdjustGameSel_Initial( void ) ;
                                                    
    EXTERN void  vAdjustGameSel_Setup( void ) ;     // 將SW值備份到Temp
    EXTERN void  vAdjustGameSel_Inc( void ) ;       // Temp+1
    EXTERN void  vAdjustGameSel_IncLoop( void ) ;   // Temp+1, 超過循環 
    EXTERN void  vAdjustGameSel_Dec( void ) ;       // Temp-1
    EXTERN void  vAdjustGameSel_DecLoop( void ) ;   // Temp-1, 超過循環
    EXTERN void  vAdjustGameSel_UpDate( void ) ;    // 將Temp還原到SW

    EXTERN ULONG ulAdjustGameSel_Read( void ) ;     // 從SW讀設定值
    EXTERN ULONG ulAdjustGameSel_ReadTemp( void ) ; // 從Temp讀設定值
    #endif
    
	#ifdef __NO_UART__
	#else
    EXTERN void  vAdjustSlaveIDSel_Initial( void ) ;
                                                    
    EXTERN void  vAdjustSlaveIDSel_Setup( void ) ;     // 將SW值備份到Temp
    EXTERN void  vAdjustSlaveIDSel_Inc( void ) ;       // Temp+1
    EXTERN void  vAdjustSlaveIDSel_IncLoop( void ) ;   // Temp+1, 超過循環 
    EXTERN void  vAdjustSlaveIDSel_Dec( void ) ;       // Temp-1
    EXTERN void  vAdjustSlaveIDSel_DecLoop( void ) ;   // Temp-1, 超過循環
    EXTERN void  vAdjustSlaveIDSel_UpDate( void ) ;    // 將Temp還原到SW

    EXTERN ULONG ulAdjustSlaveIDSel_Read( void ) ;     // 從SW讀設定值
    EXTERN ULONG ulAdjustSlaveIDSel_ReadTemp( void ) ; // 從Temp讀設定值
    #endif
    
	#undef EXTERN
#endif
