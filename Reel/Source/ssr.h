#ifndef DEF_INCLUDE_SSR_H
	#define DEF_INCLUDE_SSR_H

	#ifdef DEF_SSR_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	enum __SSR__ {
		DEF_SSR_HP ,
		DEF_SSR_TK ,
		DEF_SSR_2 ,
		DEF_SSR_3 ,
		DEF_SSR_4 ,
		DEF_SSR_5 ,
		DEF_SSR_6 ,
		DEF_SSR_7 ,
		DEF_SSR_MAX
	} ;

	EXTERN void vSSR_Initial( void ) ;
	EXTERN void vSSR_On( ULONG ulID ) ;
	EXTERN void vSSR_Off( ULONG ulID ) ;
	EXTERN void vSSR_AllOff( void ) ;
	EXTERN ULONG ulSSR_IsON(ULONG ulID) ;
	
	#undef EXTERN
#endif
