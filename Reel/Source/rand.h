#include "common.h"

#ifndef DEF_INCLUDE_RAND_H
	#define DEF_INCLUDE_RAND_H

	#ifdef DEF_RAND_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	EXTERN void  vRand_Reset( void ) ;
	EXTERN void  vRand_Initial( void ) ;
    
	EXTERN ULONG ulRand_ReadMod( ULONG mod ) ;	// 0 ~ mod-1
    EXTERN void  vRand_ChgSeed( void ) ;

	#define mRandByte()		ulRand_ReadMod(0x100)
	#define mRandWord()		ulRand_ReadMod(0x10000)
	#define mRandLong()		ulRand_ReadMod(0)
	
	#undef EXTERN
#endif
