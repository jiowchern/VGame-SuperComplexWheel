#ifndef DEF_INCLUDE_MEMORY_H
	#define DEF_INCLUDE_MEMORY_H

	#ifdef DEF_MEMORY_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	EXTERN void  vMemory_Set( UBYTE *ubD , UBYTE ubValue , ULONG ulSize ) ;
	EXTERN void  vMemory_Copy( UBYTE *ubD , UBYTE *ubS , ULONG ulSize ) ;
	EXTERN ULONG ulMemory_CompSame( UBYTE *ubD , UBYTE *ubS , ULONG ulSize ) ;

	#undef EXTERN
#endif
