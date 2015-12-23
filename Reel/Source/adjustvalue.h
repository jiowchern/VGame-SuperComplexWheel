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

	EXTERN void  vAdjustValue_Reset( void ) ; // ��_�q�{��SW,Temp
	EXTERN ULONG ulAdjustValue_Initial( ULONG version ) ;
	EXTERN void  vAdjustValue_Break( void ) ;
		
	EXTERN void  vAdjustValue_SetBitValue( ULONG ulID , ULONG ulValue ) ; // �g�JSW��
	EXTERN ULONG ulAdjustValue_ReadBitValue( ULONG ulID ) ; // Ū��SW��
	
	EXTERN void  vAdjustValue_Set( ULONG ulID , ULONG ulValue ) ; // �g�JTemp
	EXTERN ULONG ulAdjustValue_ReadTempBits( ULONG ulID ) ; // Ū��Temp��
	
	EXTERN void  vAdjustValue_Setup( void ) ; // �NSW�ȳƥ���Temp
	EXTERN void  vAdjustValue_Inc( ULONG ulID ) ; // Temp+1
	EXTERN void  vAdjustValue_IncLoop( ULONG ulID ) ; // Temp+1, �W�L�`��
	EXTERN void  vAdjustValue_Dec( ULONG ulID ) ; // Temp-1
	EXTERN void  vAdjustValue_DecLoop( ULONG ulID ) ; // Temp-1, �W�L�`��
	EXTERN void  vAdjustValue_UpDate( void ) ; // �NTemp�٭��SW
	
	EXTERN ULONG ulAdjustValue_Read( ULONG ulID ) ; // �qSWŪ�]�w��
	EXTERN ULONG ulAdjustValue_ReadTemp( ULONG ulID ) ; // �qTempŪ�]�w��

    #ifdef DEF_ENABLE_MULTI_SELECT
    EXTERN void  vAdjustGameSel_Initial( void ) ;
                                                    
    EXTERN void  vAdjustGameSel_Setup( void ) ;     // �NSW�ȳƥ���Temp
    EXTERN void  vAdjustGameSel_Inc( void ) ;       // Temp+1
    EXTERN void  vAdjustGameSel_IncLoop( void ) ;   // Temp+1, �W�L�`�� 
    EXTERN void  vAdjustGameSel_Dec( void ) ;       // Temp-1
    EXTERN void  vAdjustGameSel_DecLoop( void ) ;   // Temp-1, �W�L�`��
    EXTERN void  vAdjustGameSel_UpDate( void ) ;    // �NTemp�٭��SW

    EXTERN ULONG ulAdjustGameSel_Read( void ) ;     // �qSWŪ�]�w��
    EXTERN ULONG ulAdjustGameSel_ReadTemp( void ) ; // �qTempŪ�]�w��
    #endif
    
	#ifdef __NO_UART__
	#else
    EXTERN void  vAdjustSlaveIDSel_Initial( void ) ;
                                                    
    EXTERN void  vAdjustSlaveIDSel_Setup( void ) ;     // �NSW�ȳƥ���Temp
    EXTERN void  vAdjustSlaveIDSel_Inc( void ) ;       // Temp+1
    EXTERN void  vAdjustSlaveIDSel_IncLoop( void ) ;   // Temp+1, �W�L�`�� 
    EXTERN void  vAdjustSlaveIDSel_Dec( void ) ;       // Temp-1
    EXTERN void  vAdjustSlaveIDSel_DecLoop( void ) ;   // Temp-1, �W�L�`��
    EXTERN void  vAdjustSlaveIDSel_UpDate( void ) ;    // �NTemp�٭��SW

    EXTERN ULONG ulAdjustSlaveIDSel_Read( void ) ;     // �qSWŪ�]�w��
    EXTERN ULONG ulAdjustSlaveIDSel_ReadTemp( void ) ; // �qTempŪ�]�w��
    #endif
    
	#undef EXTERN
#endif
