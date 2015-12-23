#ifndef DEF_INCLUDE_GAMEASSIGN_H
	#define DEF_INCLUDE_GAMEASSIGN_H

	#ifdef DEF_GAMEASSIGN_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	EXTERN void vGameAssign_AllSame( UBYTE ubSymID ) ;
	EXTERN void vGameAssign_FeverSymbol(UBYTE ubSymID);
	EXTERN void vGameAssign_FeverNull(void);
	EXTERN void vGameAssign_Line(UBYTE ubSymID,UBYTE ubLoc );
	EXTERN void vGameAssign_MinSpecialSymbol( UBYTE ubSymID,UBYTE ubLoc );
	EXTERN void vGameAssign_Natural( void );
	EXTERN void vGameAssign_Spec5Line(UBYTE ubSymID,ULONG ulLoc );
	EXTERN void vGameAssign_5Line( UBYTE ubSymID );
	EXTERN void vGameAssign_SpecialSymbol( UBYTE ubSymID,UBYTE ubLoc );
	#undef EXTERN 
#endif
