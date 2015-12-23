#ifndef DEF_INCLUDE_MACRO_H
	#define DEF_INCLUDE_MACRO_H
	
    #define mMacro_ReadLoWord(n)     	( n & 0x0000FFFF )
    #define mMacro_ReadHiWord(n)     	( ( n >> 16 ) & 0x0000FFFF )
    #define mMacro_WriteLoWord(n,m)  	( n = ( n & 0xFFFF0000 ) | ( m & 0x0000FFFF ) )
    #define mMacro_WriteHiWord(n,m)  	( n = ( n & 0x0000FFFF ) | ( ( m << 16 ) & 0xFFFF0000 ) )

    #define mMacro_Img(n)     			( n & 0x0000FFFF )
    #define mMacro_Wav(n)     			( n & 0x0000FFFF )
	
    //#define mMacro_Rand()                	(mRandWord() & 0xFFFF)
	#define mMacro_Rate(mValue)  	  	((0x0000FFFF*mValue)/1000)
    #define mMacro_Chance(mValue)       ((mRandWord() & 0xFFFF)<=mValue)
	#define mMacro_Swap(mA,mB,mT)	  	{ mT = mA ; mA = mB ; mB = mT ; }
	#define mMacro_ABS(mValue)          ( (mValue<0) ? (-mValue) : (mValue) )

	#define mMacro_ReadLoByte(n)		( n & 0xFF )
	#define mMacro_ReadHiByte(n)		( ( n >> 8 ) & 0xFF )

	//#define mCommon_Rate(mValue)  	  	((0x0000FFFF*mValue)/1000)
	//#define mCommon_Chance(mValue)    	((ulRand_ReadWord() & 0xFFFF)<=mValue)
	//#define mCommon_Swap(mA,mB,mT)	  	{ mT = mA ; mA = mB ; mB = mT ; }
	
	#define mMacro_SystemWait()        {vInterrupt_Timer0Wait();}
#endif
