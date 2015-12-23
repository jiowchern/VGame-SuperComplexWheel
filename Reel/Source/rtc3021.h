#ifndef DEF_INCLUDE_RTC3021_H
	#define DEF_INCLUDE_RTC3021_H

	#ifdef DEF_RTC3021_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	typedef struct __RTC3021__
    {
        UBYTE ubSeconds    ;
        UBYTE ubMinutes    ;
        UBYTE ubHours      ;
        UBYTE ubDay        ;
        UBYTE ubMonth      ;
        UBYTE ubYear       ;
        UBYTE ubWeekDay    ;
        UBYTE ubWeekNumber ;
    } RTC3021 ;
    
	EXTERN RTC3021 stcRtc3021Data ;
	
	EXTERN void vRtc3021_ReadTime( void ) ;
	EXTERN void vRtc3021_WriteTime( void ) ;
	EXTERN void vRtc3021_PowerOnCheck( void ) ;
	
	#undef EXTERN 
#endif
