#ifndef DEF_INCLUDE_CREDIT_H
    #define DEF_INCLUDE_CREDIT_H

    #ifdef DEF_CREDIT_C
        #define EXTERN
    #else
        #define EXTERN extern
    #endif

	#define DEF_CREDIT_USER_MAX     ( 10 )
	
    EXTERN void  vCredit_Reset( void ) ;
    EXTERN void  vCredit_Initial( void ) ;
 

    EXTERN ULONG ulCredit_Set( ULONG ulPlrID , ULONG ulSet ) ;
    EXTERN ULONG ulCredit_Add( ULONG ulPlrID , ULONG ulAdd ) ;
    EXTERN ULONG ulCredit_Sub( ULONG ulPlrID , ULONG ulSub ) ;

    EXTERN ULONG ulCredit_Read( ULONG ulPlrID ) ;// ∂¡»°Credit÷µ
    EXTERN ULONG ulCredit_IsRefresh( ULONG ulPlrID ) ;

    #undef EXTERN
#endif
