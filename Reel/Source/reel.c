#define DEF_REEL_C
#include "common.h"
#define FILE_NAME "REEL.C"

// ﹚竡锣近篈

ULONG	ulReelRunSpeed ;	// 0=Auto1(slow), 1=Auto2(fast)

enum __REEL_FLAG__ {
	DEF_REEL_SHOW_FLAG   = 0x00000001 ,
	DEF_REEL_CAL_FLAG    = 0x00000002 ,
	DEF_REEL_ADJUST_FLAG = 0x00000004 ,
	DEF_REEL_JUMP_FLAG   = 0x00000008 ,
	DEF_REEL_SP_FLAG     = 0x00000080 ,
} ;

SLONG const slReelSlowNearData[2] = 
{
	#ifdef __PCSIM__
	34 , 50 ,
	#else
	70 , 110 ,
	#endif
} ;

SLONG const slReelAddSpeedData[2][20] = 
{
	#ifdef __PCSIM__
	{ 1 ,  2 ,  3 ,  5 ,  9 , 14 , 18 , 20 , 22 ,  24 , 26, 28 ,  30,  32,  34 ,  0 , 0  ,  0 , 0  ,  0  },
	{ 1 ,  2 ,  3 ,  5 ,  9 , 14 , 18 , 20 , 22 ,  24 , 26, 28 ,  32,  40,  50 ,  0 , 0  ,  0 , 0  ,  0  },
	#else	
	{ 1,2,3,5,8,12,17,23,30,38,47,57,70,0, } , // DEF_AUTO_1
	{ 1,2,4,8,14,22,32,46,64,86,110,0, } , // DEF_AUTO_2
	#endif
} ;

//强制减速停止时的表格
SLONG const slReelAsnSubSpeedData[2][20] = 
{
	#ifdef __PCSIM__	
	{120,100,60,11,1,0,0},
	{120,80,50,9,1,0,0 },
	#else	
	{ 120,80,19,1,0,0, } , // DEF_AUTO_1
	{ 120,19,1,0,0 } , // DEF_AUTO_2
	#endif    
} ;


//正常减速停止时的表格
SLONG const slReelSubSpeedData[2][20] = 
{
	#ifdef __PCSIM__
	{ 34,32,30,28,26,24,22 , 21 , 19 , 17 ,  15 ,  13 ,  10 ,  1 ,0,0,0,0,0,0 } ,
	{ 34,32,30,28,26,24,22 , 21 , 19 , 17 ,  15 ,  13 ,  10 ,  1 ,0,0,0,0,0,0 } ,
	#else	
	{ 70,30,23,20,17,14,12,10,8,6,4,3,2,1,0,0, } , // DEF_AUTO_1
	{ 110,12,8,4,3,2,1,0,0, } , // DEF_AUTO_2
	#endif    
} ;


SLONG const slFeverReelAddSpeedData[20] = 
{
     1 ,  2 ,  3 ,  5 ,  9 , 12 , 16 , 20 , 24 ,  28 ,
     32 ,  36 ,  40 ,  44 ,  48 ,  52 , 56  ,  60 , 0  ,  0 

} ;

SLONG const slFeverReelSubSpeedData[20] = 
{
	60,56,52,48,44,40,36,32,28,24,20,16,14,9,8,6,4,2,1,0
} ;

REELINFO const stcReelInfoData[DEF_REEL_MAX] = 
{// { MaxD, MaxR , slX , slY     , slStartY, slEndY     , slH} , 
    { 128 , 2096 , 78  , 116     , 116     , 116+180    , 180 } ,
    { 128 , 2096 , 252 , 116     , 116     , 116+180    , 180 } ,
    { 128 , 2096 , 426 , 116     , 116     , 116+180    , 180 } ,
    { 128 , 2096 , 600 , 116     , 116     , 116+180    , 180 } ,
    { 128 , 2096 , 774 , 116     , 116     , 116+180    , 180 } ,

    { 128 , 2096 , 78  , 298     , 298     , 298+180    , 180 } ,
    { 128 , 2096 , 252 , 298     , 298     , 298+180    , 180 } ,
    { 128 , 2096 , 426 , 298     , 298     , 298+180    , 180 } ,
    { 128 , 2096 , 600 , 298     , 298     , 298+180    , 180 } ,
    { 128 , 2096 , 774 , 298     , 298     , 298+180    , 180 } ,

    { 128 , 4096 , 78  , 480     , 480     , 480+180    , 180 } ,
    { 128 , 4096 , 252 , 480     , 480     , 480+180    , 180 } ,
    { 128 , 4096 , 426 , 480     , 480     , 480+180    , 180 } ,
    { 128 , 4096 , 600 , 480     , 480     , 480+180    , 180 } ,
    { 128 , 4096 , 774 , 480     , 480     , 480+180    , 180 } ,
} ;

REELINFO const stcReelFeverInfoData[3] = 
{// { MaxD, MaxR , slX , slY     , slStartY, slEndY     , slH} , 
    { 7 , 1024 , 314 , 313     , 313     , 313+310    , 310 } ,
    { 7 , 1024 , 448 , 313     , 313     , 313+310    , 310 } ,
    { 7 , 1024 , 582 , 313     , 313     , 313+310    , 310 } ,
};   

//
UBYTE const ubSymbolData[DEF_SYMBOL_MAX] =
{
	33 , 23 , 18 , 14 , 10 , 7 , 6 , 5 , 3 , 3 , 2 , 2 , 2
};


UBYTE const ubScrollSymbolDataCS[3][DEF_REEL_MAX_SYM] ={
	{
		DEF_SYMBOL_00,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,
		DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,
		DEF_SYMBOL_01,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_04,
		DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_06,
		DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_04,
		DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_03,
		DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_06,
		DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_03,
		DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_03,
		DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_05,
		DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_01,
		DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_06,
		DEF_SYMBOL_02,	DEF_SYMBOL_06
	},

	{
		DEF_SYMBOL_00,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_03,
		DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
		DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_04,
		DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_01,
		DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_05,
		DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_05,
		DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_05,
		DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,
		DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_01,
		DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_06,
		DEF_SYMBOL_02,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
		DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,
		DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
		DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_03,
		DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,
		DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_05,
		DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_04,
		DEF_SYMBOL_01,	DEF_SYMBOL_05
		
		
	},
	{
		DEF_SYMBOL_00,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_03,	DEF_SYMBOL_01,	DEF_SYMBOL_01,
		DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_01,
		DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_05,
		DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,	DEF_SYMBOL_01,
		DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_02,
		DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_02,
		DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,
		DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_02,
		DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_04,
		DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
		DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_02,	DEF_SYMBOL_04,
		DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_03,
		DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_05,
		DEF_SYMBOL_01,	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_03,
		DEF_SYMBOL_05,	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	DEF_SYMBOL_05,	DEF_SYMBOL_05,
		DEF_SYMBOL_05,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_06,
		DEF_SYMBOL_02,	DEF_SYMBOL_06
	}


};

UBYTE const ubScrollSymbolData[DEF_REEL_MAX_SYM] = 
{

	DEF_SYMBOL_00,DEF_SYMBOL_09,DEF_SYMBOL_08,DEF_SYMBOL_07,DEF_SYMBOL_10,DEF_SYMBOL_01,DEF_SYMBOL_04,DEF_SYMBOL_06,
	DEF_SYMBOL_11,DEF_SYMBOL_05,DEF_SYMBOL_02,DEF_SYMBOL_08,DEF_SYMBOL_00,DEF_SYMBOL_09,DEF_SYMBOL_07,DEF_SYMBOL_03,
	DEF_SYMBOL_06,DEF_SYMBOL_04,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_07,DEF_SYMBOL_05,DEF_SYMBOL_01,DEF_SYMBOL_07,
	DEF_SYMBOL_03,DEF_SYMBOL_00,DEF_SYMBOL_08,DEF_SYMBOL_02,DEF_SYMBOL_06,DEF_SYMBOL_08,DEF_SYMBOL_09,DEF_SYMBOL_12,
	DEF_SYMBOL_03,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_04,DEF_SYMBOL_07,DEF_SYMBOL_02,DEF_SYMBOL_08,DEF_SYMBOL_05,
	DEF_SYMBOL_01,DEF_SYMBOL_09,DEF_SYMBOL_06,DEF_SYMBOL_04,DEF_SYMBOL_00,DEF_SYMBOL_08,DEF_SYMBOL_02,DEF_SYMBOL_03,
	DEF_SYMBOL_09,DEF_SYMBOL_05,DEF_SYMBOL_07,DEF_SYMBOL_06,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_08,DEF_SYMBOL_04,
	DEF_SYMBOL_05,DEF_SYMBOL_06,DEF_SYMBOL_01,DEF_SYMBOL_09,DEF_SYMBOL_07,DEF_SYMBOL_03,DEF_SYMBOL_08,DEF_SYMBOL_06,
	DEF_SYMBOL_07,DEF_SYMBOL_01,DEF_SYMBOL_03,DEF_SYMBOL_09,DEF_SYMBOL_00,DEF_SYMBOL_06,DEF_SYMBOL_04,DEF_SYMBOL_12,
	DEF_SYMBOL_08,DEF_SYMBOL_07,DEF_SYMBOL_02,DEF_SYMBOL_05,DEF_SYMBOL_04,DEF_SYMBOL_10,DEF_SYMBOL_09,DEF_SYMBOL_05,
	DEF_SYMBOL_06,DEF_SYMBOL_07,DEF_SYMBOL_03,DEF_SYMBOL_08,DEF_SYMBOL_00,DEF_SYMBOL_04,DEF_SYMBOL_06,DEF_SYMBOL_05,
	DEF_SYMBOL_01,DEF_SYMBOL_08,DEF_SYMBOL_05,DEF_SYMBOL_02,DEF_SYMBOL_09,DEF_SYMBOL_10,DEF_SYMBOL_08,DEF_SYMBOL_03,
	DEF_SYMBOL_07,DEF_SYMBOL_02,DEF_SYMBOL_04,DEF_SYMBOL_03,DEF_SYMBOL_05,DEF_SYMBOL_06,DEF_SYMBOL_09,DEF_SYMBOL_00,
	DEF_SYMBOL_01,DEF_SYMBOL_08,DEF_SYMBOL_07,DEF_SYMBOL_06,DEF_SYMBOL_02,DEF_SYMBOL_04,DEF_SYMBOL_05,DEF_SYMBOL_09,
	DEF_SYMBOL_11,DEF_SYMBOL_07,DEF_SYMBOL_08,DEF_SYMBOL_04,DEF_SYMBOL_01,DEF_SYMBOL_06,DEF_SYMBOL_03,DEF_SYMBOL_05,
	DEF_SYMBOL_04,DEF_SYMBOL_10,DEF_SYMBOL_09,DEF_SYMBOL_07,DEF_SYMBOL_06,DEF_SYMBOL_08,DEF_SYMBOL_02,DEF_SYMBOL_05


} ;


UBYTE const ubScrollSymbolFreeData[DEF_REEL_MAX_SYM] = 
{

	DEF_SYMBOL_00,	DEF_SYMBOL_04,  DEF_SYMBOL_01,  DEF_SYMBOL_05,	DEF_SYMBOL_10,  DEF_SYMBOL_07,  DEF_SYMBOL_02,	DEF_SYMBOL_06,
	DEF_SYMBOL_12,	DEF_SYMBOL_05,	DEF_SYMBOL_03, 	DEF_SYMBOL_02,	DEF_SYMBOL_07,	DEF_SYMBOL_00,	DEF_SYMBOL_06,	DEF_SYMBOL_05,	
	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_07, 	DEF_SYMBOL_10,	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_02,	DEF_SYMBOL_07,	
	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_04, 	DEF_SYMBOL_06,	DEF_SYMBOL_00,	DEF_SYMBOL_07,	DEF_SYMBOL_04,	DEF_SYMBOL_11,
	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_10, 	DEF_SYMBOL_05,	DEF_SYMBOL_01,	DEF_SYMBOL_07,	DEF_SYMBOL_04,	DEF_SYMBOL_00,	
	DEF_SYMBOL_03,	DEF_SYMBOL_02,	DEF_SYMBOL_06, 	DEF_SYMBOL_04,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_00,	DEF_SYMBOL_07,	
	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_01, 	DEF_SYMBOL_04,	DEF_SYMBOL_06,	DEF_SYMBOL_10,	DEF_SYMBOL_07,	DEF_SYMBOL_02,	
	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_00, 	DEF_SYMBOL_03,	DEF_SYMBOL_07,	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_02,
	DEF_SYMBOL_06,	DEF_SYMBOL_01,	DEF_SYMBOL_03, 	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_07,	DEF_SYMBOL_04,	DEF_SYMBOL_11,	
	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_05, 	DEF_SYMBOL_02,	DEF_SYMBOL_07,	DEF_SYMBOL_10,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	
	DEF_SYMBOL_01,	DEF_SYMBOL_05,	DEF_SYMBOL_07, 	DEF_SYMBOL_00,	DEF_SYMBOL_06,	DEF_SYMBOL_03,	DEF_SYMBOL_05,	DEF_SYMBOL_04,	
	DEF_SYMBOL_07,	DEF_SYMBOL_02,	DEF_SYMBOL_06, 	DEF_SYMBOL_01,	DEF_SYMBOL_04,	DEF_SYMBOL_10,	DEF_SYMBOL_03,	DEF_SYMBOL_05,																															
	DEF_SYMBOL_03,	DEF_SYMBOL_07,	DEF_SYMBOL_00, 	DEF_SYMBOL_05,	DEF_SYMBOL_02,	DEF_SYMBOL_06,	DEF_SYMBOL_04,	DEF_SYMBOL_07,	
	DEF_SYMBOL_00,	DEF_SYMBOL_05,	DEF_SYMBOL_06, 	DEF_SYMBOL_01,	DEF_SYMBOL_07,	DEF_SYMBOL_02,	DEF_SYMBOL_03,	DEF_SYMBOL_06,	
	DEF_SYMBOL_12,	DEF_SYMBOL_04,	DEF_SYMBOL_07, 	DEF_SYMBOL_01,	DEF_SYMBOL_06,	DEF_SYMBOL_00,	DEF_SYMBOL_05,	DEF_SYMBOL_03,	
	DEF_SYMBOL_07,	DEF_SYMBOL_10,	DEF_SYMBOL_04, 	DEF_SYMBOL_03,	DEF_SYMBOL_06,	DEF_SYMBOL_07,	DEF_SYMBOL_02,	DEF_SYMBOL_05


} ;

#define mReel_SetFlag( mFlag , mSet ) { mFlag |= mSet ; }

//REEL stcReelData[DEF_REEL_MAX] ;
ULONG ulReelNeedSoundEft ;

void vReel_Initial( SLONG slReel , UBYTE *ubReelData )
{
	SLONG slLoop ;
	
	if ( slReel < DEF_REEL_MAX )
	{
		stcReelData[slReel].ubReelData       = ubReelData       ;
		
		stcReelData[slReel].uwGetIndex  = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData) ;
		for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
		{
			stcReelData[slReel].ubShowID[slLoop] = stcReelData[slReel].ubReelData[stcReelData[slReel].uwGetIndex] ;
			stcReelData[slReel].ubStopID[slLoop] = stcReelData[slReel].ubShowID[slLoop] ;
			stcReelData[slReel].uwGetIndex ++ ;
			if ( stcReelData[slReel].uwGetIndex >= stcReelInfoData[slReel].ulMaxData )
			{
				stcReelData[slReel].uwGetIndex = 0 ;
			}
		}
		stcReelData[slReel].ubState       = DEF_REEL_STOP ;
		stcReelData[slReel].ubAdjustIndex = 0 ;
		stcReelData[slReel].swMoveY       = 0 ;
		stcReelData[slReel].swSpeed       = 0 ;
		stcReelData[slReel].swCount       = 0 ;
	}
	
	ulReelNeedSoundEft = 0 ;
	ulReelRunSpeed = 0 ;
	
}

void vReel_FeverInitial( SLONG slReel , UBYTE *ubReelData )
{
	SLONG slLoop ;
	
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		stcReelFeverData[slReel].ubReelData       = ubReelData       ;
		
		stcReelFeverData[slReel].uwGetIndex  = 126 ;
		for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
		{
			stcReelFeverData[slReel].ubShowID[slLoop] = stcReelFeverData[slReel].ubReelData[stcReelFeverData[slReel].uwGetIndex] ;
			stcReelFeverData[slReel].ubStopID[slLoop] = stcReelFeverData[slReel].ubShowID[slLoop] ;
			stcReelFeverData[slReel].uwGetIndex ++ ;
			if ( stcReelFeverData[slReel].uwGetIndex >= stcReelInfoData[slReel].ulMaxData )
			{
				stcReelFeverData[slReel].uwGetIndex = 0 ;
			}
		}
		stcReelFeverData[slReel].ubState       = DEF_REEL_STOP ;
		stcReelFeverData[slReel].ubAdjustIndex = 0 ;
		stcReelFeverData[slReel].swMoveY       = 0 ;
		stcReelFeverData[slReel].swSpeed       = 0 ;
		stcReelFeverData[slReel].swCount       = 0 ;
	}
	
	ulReelNeedSoundEft = 0 ;
}

void vReel_OpenSound( void )
{
	ulReelNeedSoundEft = 1 ;	
}

void vReel_CloseSound( void )
{
	ulReelNeedSoundEft = 0 ;
}

void vReel_ReSetReelData( SLONG slReel , UBYTE *ubReelData )
{
	if ( slReel < DEF_REEL_MAX )
	{
		stcReelData[slReel].ubReelData = ubReelData       ;
	}
}

void vReel_RefreshShowScr( SLONG slReel )
{
	if ( slReel < DEF_REEL_MAX )
	{		
		if ( stcReelData[slReel].ubState == DEF_REEL_STOP )
		{
			stcReelData[slReel].ubState = DEF_REEL_SHOW ;
		}
	}
}

void vReel_LocSwap( SLONG slA , SLONG slB )
{
	SLONG 	slLoop ;
	UBYTE	ubTemp ;
	
	if (( slA < DEF_REEL_MAX )&&( slB < DEF_REEL_MAX ))
	{	
		for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
		{
			mMacro_Swap( stcReelData[slA].ubStopID[slLoop] , stcReelData[slB].ubStopID[slLoop] , ubTemp ) ;
		}
	}		
}

void vReel_FeverRefreshShowScr( SLONG slReel )
{
	if ( slReel < DEF_FEVER_REEL_MAX )
	{		
		if ( stcReelFeverData[slReel].ubState == DEF_REEL_STOP )
		{
			stcReelFeverData[slReel].ubState = DEF_REEL_SHOW ;
		}
	}
}


void vReel_InitState( SLONG slReel )
{
	if ( slReel >= DEF_REEL_MAX )
	{
		return ;
	}
	stcReelData[slReel].ubState       = DEF_REEL_STOP ;
	stcReelData[slReel].ubAdjustIndex = 0 ;
	stcReelData[slReel].swMoveY       = 0 ;
	stcReelData[slReel].swSpeed       = 0 ;
	stcReelData[slReel].swCount       = 0 ;	
	
}



UBYTE ubReel_GetData( SLONG slReel )
{
	if ( slReel >= DEF_REEL_MAX )
	{
		return ( 0 ) ;
	}
	return ( stcReelData[slReel].ubStopID[2] ) ;
}

void vReel_SaveData( SLONG slReel )
{
	SLONG slLoop ;
	
	if ( slReel >= DEF_REEL_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelData[slReel].ubSaveID[slLoop] = stcReelData[slReel].ubShowID[slLoop] ;
	}
}

void vReel_SaveStopData( SLONG slReel )
{
	SLONG slLoop ;
	
	if ( slReel >= DEF_REEL_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelData[slReel].ubSaveID[slLoop] = stcReelData[slReel].ubStopID[slLoop] ;
	}
}

void vReel_FeverSaveData( SLONG slReel )
{
	SLONG slLoop ;
	
	if ( slReel >= DEF_FEVER_REEL_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelFeverData[slReel].ubSaveID[slLoop] = stcReelFeverData[slReel].ubShowID[slLoop] ;
	}
}

void vReel_LoadData( SLONG slReel )
{
	SLONG slLoop ;
	
	if ( slReel >= DEF_REEL_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelData[slReel].ubShowID[slLoop] = stcReelData[slReel].ubSaveID[slLoop] ;
	}
	
	stcReelData[slReel].ubState       = DEF_REEL_STOP ;
	stcReelData[slReel].ubAdjustIndex = 0 ;
	stcReelData[slReel].swMoveY       = 0 ;
	stcReelData[slReel].swSpeed       = 0 ;
	stcReelData[slReel].swCount       = 0 ;
}

void vReel_LoadStopData( SLONG slReel )
{
	SLONG slLoop ;
	
	if ( slReel >= DEF_REEL_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelData[slReel].ubStopID[slLoop] = stcReelData[slReel].ubSaveID[slLoop] ;
	}
}

void vReel_FeverLoadData( SLONG slReel )
{
	SLONG slLoop ;
	
	if ( slReel >= DEF_FEVER_REEL_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelFeverData[slReel].ubShowID[slLoop] = stcReelFeverData[slReel].ubSaveID[slLoop] ;
	}
	
	stcReelFeverData[slReel].ubState       = DEF_REEL_STOP ;
	stcReelFeverData[slReel].ubAdjustIndex = 0 ;
	stcReelFeverData[slReel].swMoveY       = 0 ;
	stcReelFeverData[slReel].swSpeed       = 0 ;
	stcReelFeverData[slReel].swCount       = 0 ;
}

void vReel_StartRun( SLONG slReel )
{
	if ( slReel < DEF_REEL_MAX )
	{
		stcReelData[slReel].ubState  = DEF_REEL_START ;
	}
}

void vReel_FeverStartRun( SLONG slReel )
{
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		stcReelFeverData[slReel].ubState  = DEF_REEL_START ;
	}
}

void vReel_SetStopData( SLONG slReel , UBYTE ubData )
{
	SLONG slIndex , slPointer ;
	UBYTE *ubTurnData ;
	
	if ( slReel < DEF_REEL_MAX )
	{
		ubTurnData = (UBYTE *)stcReelData[slReel].ubReelData ;		
		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData) ;
	
		for ( slIndex = 0 ; slIndex < stcReelInfoData[slReel].ulMaxData ; slIndex ++ )
		{
			if ( ubTurnData[slPointer] == ubData )
			{
				break ;
			}
			slPointer = slPointer + 1 ;
			if ( slPointer >= stcReelInfoData[slReel].ulMaxData )
			{
				slPointer = 0 ;
			}
		}
	
		if ( slPointer < 2 )
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 2 ;
		}
		else
		{
			slPointer -= 2 ;
		}
	
		for ( slIndex = (DEF_REEL_MAX_SHOW-1) ; slIndex >=0 ; slIndex -- )
		{
			stcReelData[slReel].ubStopID[slIndex] = ubTurnData[slPointer] ;
			slPointer = slPointer + 1 ;
			if ( slPointer >= stcReelInfoData[slReel].ulMaxData )
			{
				slPointer = 0 ;
			}
		}
	}
}

void vReel_FeverSetRandData( SLONG slReel )
{
	SLONG slIndex , slPointer ;
	UBYTE *ubTurnData ;	
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		ubTurnData = (UBYTE *)stcReelFeverData[slReel].ubReelData ;
	
		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData) ;
	
		if ( slPointer < 3 )
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 3 ;
		}
		else
		{
			slPointer -= 2 ;
		}		
		for ( slIndex = (DEF_REEL_MAX_SHOW-1) ; slIndex >=0 ; slIndex -- )
		{
			stcReelFeverData[slReel].ubStopID[slIndex] = ubTurnData[slPointer] ;
			slPointer = slPointer + 1 ;
			if ( slPointer >= stcReelInfoData[slReel].ulMaxData )
			{
				slPointer = 1 ;
			}
		}
	}
}

void vReel_FeverSetStopData( SLONG slReel , UBYTE ubData )
{
	SLONG slIndex , slPointer ;
	UBYTE *ubTurnData ;
	
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		ubTurnData = (UBYTE *)stcReelFeverData[slReel].ubReelData ;		
		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData) ;
	
		for ( slIndex = 0 ; slIndex < stcReelInfoData[slReel].ulMaxData ; slIndex ++ )
		{
			if ( ubTurnData[slPointer] == ubData )
			{
				break ;
			}
			slPointer = slPointer + 1 ;
			if ( slPointer >= stcReelInfoData[slReel].ulMaxData )
			{
				slPointer = 1 ;
			}
		}
	
		if ( slPointer < 3 )
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 3 ;
		}
		else
		{
			slPointer -= 2 ;
		}	
	
		for ( slIndex = (DEF_REEL_MAX_SHOW-1) ; slIndex >=0 ; slIndex -- )
		{
			stcReelFeverData[slReel].ubStopID[slIndex] = ubTurnData[slPointer] ;
			slPointer = slPointer + 1 ;
			if ( slPointer >= stcReelInfoData[slReel].ulMaxData )
			{
				slPointer = 1 ;
			}
		}
	}
}

void vReel_SetRandData( SLONG slReel )
{
	SLONG slIndex , slPointer ;
	UBYTE *ubTurnData ;
	
	if ( slReel < DEF_REEL_MAX )
	{
		if(stcGameInfo.ulFreeNowLife==0)
		{
			ubTurnData = (UBYTE *)stcReelData[slReel].ubReelData ;
		}
		else
		{
			ubTurnData = (UBYTE *)ubScrollSymbolFreeData ;
		}		
		
	
		slPointer = ulRand_ReadMod(stcReelInfoData[slReel].ulMaxData) ;
	
		if ( slPointer < 2 )
		{
			slPointer = (slPointer + stcReelInfoData[slReel].ulMaxData) - 2 ;
		}
		else
		{
			slPointer -= 2 ;
		}		
		for ( slIndex = (DEF_REEL_MAX_SHOW-1) ; slIndex >=0 ; slIndex -- )
		{
			stcReelData[slReel].ubStopID[slIndex] = ubTurnData[slPointer] ;
			slPointer = slPointer + 1 ;
			if ( slPointer >= stcReelInfoData[slReel].ulMaxData )
			{
				slPointer = 0 ;
			}
		}
	}
}




void vReel_StopDataToShowData( SLONG slReel )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX_SHOW ; slLoop ++ )
	{
		stcReelData[slReel].ubShowID[slLoop] = stcReelData[slReel].ubStopID[slLoop] ;	
	}
}

void vReel_StopRun( SLONG slReel )
{
	if ( slReel < DEF_REEL_MAX )
	{
		if ( stcReelData[slReel].ubState == DEF_REEL_RUN )
		{
			stcReelData[slReel].ubState = DEF_REEL_ADJUST ;
        	stcReelData[slReel].swCount = 0 ;
			stcReelData[slReel].ubAdjustIndex = 2 ;
		}
	}
}

//手动强制停止
void vReel_AsnStopRun( SLONG slReel )
{
	if ( slReel < DEF_REEL_MAX )
	{
		if ( stcReelData[slReel].ubState == DEF_REEL_RUN )
		{
			stcReelData[slReel].ubState = DEF_REEL_ADJUST ;
        	stcReelData[slReel].swCount = 0 ;
			stcReelData[slReel].ubAdjustIndex = 2 ;
			stcReelData[slReel].ubAsnState = 1;
		}
	}
}

//马上全部停止

void vReel_AllNowStopRun( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_REEL_MAX ; slLoop ++ )
	{
		
		//if ( stcReelData[slReel].ubState == DEF_REEL_RUN )
		{
			stcReelData[slLoop].ubState = DEF_REEL_STOP ;
        	stcReelData[slLoop].swCount = 0 ;
			stcReelData[slLoop].ubAdjustIndex = 0 ;
		}
		
	}
	
}
void vReel_FeverAllNowStopRun(void)
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < DEF_FEVER_REEL_MAX ; slLoop ++ )
	{
		//if ( stcReelFeverData[slReel].ubState == DEF_REEL_RUN )
		{
			stcReelFeverData[slLoop].ubState = DEF_REEL_ADJUST ;
        	stcReelFeverData[slLoop].swCount = 0 ;
			stcReelFeverData[slLoop].ubAdjustIndex = 0 ;
		}
	}
}
void vReel_FeverStopRun( SLONG slReel )
{
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		if ( stcReelFeverData[slReel].ubState == DEF_REEL_RUN )
		{
			stcReelFeverData[slReel].ubState = DEF_REEL_ADJUST ;
        	stcReelFeverData[slReel].swCount = 0 ;
			stcReelFeverData[slReel].ubAdjustIndex = 0 ;
		}
	}
}

ULONG ulReel_CheckIsRun( SLONG slReel )
{
	if ( slReel < DEF_REEL_MAX )
	{
		if ( stcReelData[slReel].ubState != DEF_REEL_STOP )
		{
			return ( 1 ) ;
		}
	}
	
	return ( 0 ) ;
}

ULONG ulReel_FeverCheckIsRun( SLONG slReel )
{
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		if ( stcReelFeverData[slReel].ubState != DEF_REEL_STOP )
		{
			return ( 1 ) ;
		}
	}
	
	return ( 0 ) ;
}


SLONG slReel_MoveAddReelY( SLONG slReel , UBYTE ubNextSym )
{
	SLONG slShiftIndex ;
	
	if ( slReel < DEF_REEL_MAX )
	{
		stcReelData[slReel].swMoveY += stcReelData[slReel].swSpeed ;
		if ( stcReelData[slReel].swMoveY >= stcReelInfoData[slReel].slIntervalHeight )
		{
			stcReelData[slReel].swMoveY -= stcReelInfoData[slReel].slIntervalHeight ;
			for ( slShiftIndex = (DEF_REEL_MAX_SHOW-1) ; slShiftIndex >= 1 ; slShiftIndex -- )
			{
				stcReelData[slReel].ubShowID[slShiftIndex] = stcReelData[slReel].ubShowID[slShiftIndex-1] ;
			}
			stcReelData[slReel].ubShowID[0] = ubNextSym ;
			return ( 1 ) ;
		}
	}
	else
	{
		return ( 1 ) ;
	}
	return ( 0 ) ;
}

void vReel_MoveOneReel( SLONG slReel )
{
	UBYTE *ubTurnData ;
	
	if ( slReel < DEF_REEL_MAX )
	{
		ubTurnData = (UBYTE *)stcReelData[slReel].ubReelData ;
		if ( slReel_MoveAddReelY( slReel , ubTurnData[stcReelData[slReel].uwGetIndex] ) )
		{
			stcReelData[slReel].uwGetIndex ++ ;
			if ( stcReelData[slReel].uwGetIndex >= stcReelInfoData[slReel].ulMaxData )
			{
				stcReelData[slReel].uwGetIndex = 0 ;
			}
		}
		
		if ( stcReelData[slReel].swMoveY < 0 )
		{
			stcReelData[slReel].swMoveY += stcReelInfoData[slReel].slIntervalHeight ;
		}
	}
}

void vReel_MoveAdjustOneReel( SLONG slReel )
{	
	if ( slReel < DEF_REEL_MAX )
	{
		if ( stcReelData[slReel].ubAdjustIndex >= 5 )
		{
			stcReelData[slReel].ubAdjustIndex = 0 ;
		}
		if ( slReel_MoveAddReelY( slReel , stcReelData[slReel].ubStopID[stcReelData[slReel].ubAdjustIndex] ) )
		{
			stcReelData[slReel].ubAdjustIndex ++ ;
		}
	
		if ( stcReelData[slReel].swMoveY < 0 )
		{
			stcReelData[slReel].swMoveY += stcReelInfoData[slReel].slIntervalHeight ;
		}
	}
}

void vReel_MoveJumpOneReel( SLONG slReel )
{
    if ( slReel < DEF_REEL_MAX )
    {
        if ( stcReelData[slReel].ubAdjustIndex >= 5 )
        {
            stcReelData[slReel].ubAdjustIndex = 0 ;
        }
        stcReelData[slReel].swMoveY += stcReelData[slReel].swSpeed ;
    }
}

void vReel_ShowOneReel( SLONG slReel , ULONG ulAnim )
{
    SLONG slData ;
    SLONG slX , slY , slSym ;
    if ( slReel < DEF_REEL_MAX )
    {    	
        for ( slData = 1 ; slData < DEF_REEL_MAX_SHOW-2 ; slData ++ )
        {
            slX    = stcReelInfoData[slReel].slLocX ;
            slY    = stcReelInfoData[slReel].slLocY + ((slData-2) * (stcReelInfoData[slReel].slIntervalHeight)) + stcReelData[slReel].swMoveY ;
            slSym  = stcReelData[slReel].ubShowID[slData] ;
            if ( slSym < DEF_SYMBOL_MAX )
            {
            	vShowLib_Reel( ulAnim + (slData-1) , slSym , slX ,slY ,  stcReelInfoData[slReel].slViewStartY , stcReelInfoData[slReel].slViewEndY ,stcReelInfoData[slReel].slIntervalHeight);              
            }
        }
    }
}

void vReel_ShowOneJumpReel( SLONG slReel , ULONG ulAnim )
{
    SLONG slData ;
    SLONG slX , slY , slSym ;    
    if ( slReel < DEF_REEL_MAX )
    {
        slData = 2 ;        
        {
            slX    = stcReelInfoData[slReel].slLocX ;
            slY    = stcReelInfoData[slReel].slLocY + ((slData-2) * (stcReelInfoData[slReel].slIntervalHeight)) + stcReelData[slReel].swMoveY ;
            slSym  = stcReelData[slReel].ubShowID[slData] ;
            if ( slSym < DEF_SYMBOL_MAX )
            {
            	vShowLib_Reel( ulAnim + (slData-1) , slSym , slX ,slY ,  stcReelInfoData[slReel].slViewStartY , stcReelInfoData[slReel].slViewEndY ,stcReelInfoData[slReel].slIntervalHeight);
            }
        }
    }
}

void vReel_Process( SLONG slReel , ULONG ulAnim )
{
    ULONG ulFlag;
	ULONG ulValue;
    ulFlag = 0 ;    

    if ( slReel < DEF_REEL_MAX )
    {
    	if(stcMaster.ulAutoKeyGameState==2)
    	{
    		ulReelRunSpeed = 1;
    	}
    	else
    	{
    		ulReelRunSpeed = 0;
    	}		
        switch( stcReelData[slReel].ubState )
        {
            case DEF_REEL_STOP   :
                break ;
            case DEF_REEL_SHOW   :
                mReel_SetFlag( ulFlag , DEF_REEL_SHOW_FLAG ) ;
                stcReelData[slReel].ubState = DEF_REEL_STOP ;
                break ;
            case DEF_REEL_START  :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_CAL_FLAG) ) ;
                stcReelData[slReel].ubState = DEF_REEL_ADD ;
                stcReelData[slReel].swCount = 0 ;
                stcReelData[slReel].swSpeed = slReelAddSpeedData[ulReelRunSpeed][0] ;
                break ;
            case DEF_REEL_ADD    :
                                
                stcReelData[slReel].swCount ++ ;          
                if ( stcReelData[slReel].swCount >= 0 )
                {
                    mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_CAL_FLAG|DEF_REEL_SP_FLAG) ) ;

                    if ( stcReelData[slReel].swCount < 20 )
                    {
                        if ( slReelAddSpeedData[ulReelRunSpeed][stcReelData[slReel].swCount] )
                        {
                            stcReelData[slReel].swSpeed = slReelAddSpeedData[ulReelRunSpeed][stcReelData[slReel].swCount] ;
                        }
                        else
                        {
                            stcReelData[slReel].ubState = DEF_REEL_RUN ;
                            stcReelData[slReel].swCount = 0 ;
                        }
                    }
                }
                break ;
            case DEF_REEL_RUN    :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_CAL_FLAG|DEF_REEL_SP_FLAG) ) ;
                stcReelData[slReel].swCount ++ ;
                    
                if ( stcReelData[slReel].swCount >= stcReelInfoData[slReel].ulMaxRun )
                {
                    stcReelData[slReel].ubState       = DEF_REEL_ADJUST ;
                    stcReelData[slReel].swCount       = 0 ;
                    stcReelData[slReel].ubAdjustIndex = 2 ;
                }
                break ;
            case DEF_REEL_ADJUST :            	
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_ADJUST_FLAG|DEF_REEL_SP_FLAG) ) ;
                if ( stcReelData[slReel].ubAdjustIndex == (DEF_REEL_MAX_SHOW-2) )
                { 
	               	
                    if ( stcReelData[slReel].swMoveY >= 0 && stcReelData[slReel].swMoveY <= slReelSlowNearData[ulReelRunSpeed] )
                    {
                    	//while ( ulKey_RePush( KEY_1, 10 , 3 ) == 0 );	                    	
                        stcReelData[slReel].swMoveY     = slReelSlowNearData[ulReelRunSpeed] ;
                        stcReelData[slReel].ubState     = DEF_REEL_SUB ;
                        stcReelData[slReel].swCount     = 0 ;
                    }
                }
                break ;
            case DEF_REEL_SUB    :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_ADJUST_FLAG|DEF_REEL_SP_FLAG) ) ;
    
                if ( stcReelData[slReel].swCount < 20 )
                {
                	if(stcReelData[slReel].ubAsnState)
                	{
                		ulValue = slReelAsnSubSpeedData[ulReelRunSpeed][ stcReelData[slReel].swCount ];
                	}	
                	else
                	{
                		ulValue = slReelSubSpeedData[ulReelRunSpeed][ stcReelData[slReel].swCount ];
                	}	
                    if (ulValue)
                    {
                        stcReelData[slReel].swSpeed = ulValue ;
                    }  
                }
                stcReelData[slReel].swCount ++ ;
                
                if ( stcReelData[slReel].ubAdjustIndex == (DEF_REEL_MAX_SHOW-1) )
                {                	
                    if ( stcReelData[slReel].swMoveY >= (stcReelInfoData[slReel].slIntervalHeight-1))
                    {                    	
                        stcReelData[slReel].ubState = DEF_REEL_JUMP ;
                        stcReelData[slReel].swCount = 0 ;	
                    }
                }
                break ;
            case DEF_REEL_JUMP   :
                if ( ulReelNeedSoundEft )
                {
                    if (( stcReelData[slReel].swCount == 0 )&&(slReel==14))
                    {
					   vPlaySound_Play( DEF_WAV_SOUND_04,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_1);              
                    }
                }
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_JUMP_FLAG) ) ;
                switch( stcReelData[slReel].swCount )
                {
	                case 0 :
	                		stcReelData[slReel].swSpeed = +6 ; break ;
	                case 1 : 
	                case 2 :
	                case 3 : 
	                case 4 :
	                		stcReelData[slReel].swSpeed = -3 ; break ;
                
	                case 5 :
                    case 6 : 
	                case 7 :
                    case 8 : 
                    case 9 :
                    case 10 : stcReelData[slReel].swSpeed = +1 ; break ;
                }

                stcReelData[slReel].swCount ++ ;
    
                if ( stcReelData[slReel].swCount >=11 )
                {
                	stcReelData[slReel].ubAsnState = 0;
                    stcReelData[slReel].swSpeed = 0 ;
                    stcReelData[slReel].ubState = DEF_REEL_STOP ;
                    stcReelData[slReel].swCount = 0 ;
                    stcReelData[slReel].swMoveY = 0 ;
                }
                //while ( ulKey_RePush( KEY_2, 10 , 3 ) == 0 );	
                break ;
            default :
            	stcReelData[slReel].ubAsnState = 0;
                stcReelData[slReel].ubState = DEF_REEL_STOP ;                
                break ;
        }

        if ( ulFlag&DEF_REEL_CAL_FLAG )
        {
            vReel_MoveOneReel( slReel ) ;
        }
        if ( ulFlag&DEF_REEL_ADJUST_FLAG )
        {
            vReel_MoveAdjustOneReel( slReel ) ;
        }
        if ( ulFlag&DEF_REEL_JUMP_FLAG )
        {
            vReel_MoveJumpOneReel( slReel ) ;
        }
        if ( ulFlag&DEF_REEL_SHOW_FLAG )
        {
            if( ulFlag&DEF_REEL_JUMP_FLAG )
            {
                vReel_ShowOneJumpReel( slReel , ulAnim ) ;
            }
            else
            {            
				vReel_ShowOneReel( slReel , ulAnim ) ;
            }
        }
    }
}

SLONG slReel_FeverMoveAddReelY( SLONG slReel , UBYTE ubNextSym )
{
	SLONG slShiftIndex ;
	
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		stcReelFeverData[slReel].swMoveY += stcReelFeverData[slReel].swSpeed ;
		if ( stcReelFeverData[slReel].swMoveY >= stcReelFeverInfoData[slReel].slIntervalHeight )
		{
			stcReelFeverData[slReel].swMoveY -= stcReelFeverInfoData[slReel].slIntervalHeight ;
			for ( slShiftIndex = (DEF_REEL_MAX_SHOW-1) ; slShiftIndex >= 1 ; slShiftIndex -- )
			{
				stcReelFeverData[slReel].ubShowID[slShiftIndex] = stcReelFeverData[slReel].ubShowID[slShiftIndex-1] ;
			}
			stcReelFeverData[slReel].ubShowID[0] = ubNextSym ;
			return ( 1 ) ;
		}
	}
	else
	{
		return ( 1 ) ;
	}
	return ( 0 ) ;
}

void vReel_FeverMoveOneReel( SLONG slReel )
{
	UBYTE *ubTurnData ;
	
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		ubTurnData = (UBYTE *)stcReelFeverData[slReel].ubReelData ;
		if ( slReel_FeverMoveAddReelY( slReel , ubTurnData[stcReelFeverData[slReel].uwGetIndex] ) )
		{
			stcReelFeverData[slReel].uwGetIndex ++ ;
			if ( stcReelFeverData[slReel].uwGetIndex >= stcReelFeverInfoData[slReel].ulMaxData )
			{
				stcReelFeverData[slReel].uwGetIndex =1 ;
			}
		}
		
		if ( stcReelFeverData[slReel].swMoveY < 0 )
		{
			stcReelFeverData[slReel].swMoveY += stcReelFeverInfoData[slReel].slIntervalHeight ;
		}
	}
}

void vReel_FeverMoveAdjustOneReel( SLONG slReel )
{
	if ( slReel < DEF_FEVER_REEL_MAX )
	{
		if ( stcReelFeverData[slReel].ubAdjustIndex >= 5 )
		{
			stcReelFeverData[slReel].ubAdjustIndex = 0 ;
		}
		if ( slReel_FeverMoveAddReelY( slReel , stcReelFeverData[slReel].ubStopID[stcReelFeverData[slReel].ubAdjustIndex] ) )
		{
			stcReelFeverData[slReel].ubAdjustIndex ++ ;
		}
	
		if ( stcReelFeverData[slReel].swMoveY < 0 )
		{
			stcReelFeverData[slReel].swMoveY += stcReelFeverInfoData[slReel].slIntervalHeight ;
		}
	}
}

void vReel_FeverMoveJumpOneReel( SLONG slReel )
{
    if ( slReel < DEF_FEVER_REEL_MAX )
    {
        if ( stcReelFeverData[slReel].ubAdjustIndex >= 5 )
        {
            stcReelFeverData[slReel].ubAdjustIndex = 0 ;
        }
        stcReelFeverData[slReel].swMoveY += stcReelFeverData[slReel].swSpeed ;
    }
}

void vReel_FeverShowOneReel( SLONG slReel , ULONG ulAnim )
{
    SLONG slData ;
    SLONG slX , slY , slSym ;
//    ANIM_IMAGE *aiImgAdr ;
    
    if ( slReel < DEF_FEVER_REEL_MAX )
    {
    	//for ( slData = DEF_REEL_MAX_SHOW-2 ; slData > 0  ; slData -- )
        for ( slData = 1 ; slData < DEF_REEL_MAX_SHOW-2 ; slData ++ )
        {
            slX    = stcReelFeverInfoData[slReel].slLocX ;
            slY    = stcReelFeverInfoData[slReel].slLocY + ((slData-2) * (stcReelFeverInfoData[slReel].slIntervalHeight)) + stcReelFeverData[slReel].swMoveY ;
            slSym  = stcReelFeverData[slReel].ubShowID[slData]%7 ;
            if ( slSym < DEF_SYMBOL_MAX )
            {
            	vShowLib_FeverReel(slReel, ulAnim + (slData-1) , slSym , slX ,slY ,  stcReelFeverInfoData[slReel].slViewStartY , stcReelFeverInfoData[slReel].slViewEndY ,stcReelFeverInfoData[slReel].slIntervalHeight);
               // aiImgAdr = (ANIM_IMAGE *)stcReelSymbolImg[slSym] ;
              //  vAnimator_ShowWindows( (ANIM_IMAGE *)aiImgAdr , slX , slY , ulReelSymbolPal[slSym] , ulAnim + (slData-1) , 0 , stcReelFeverInfoData[slReel].slViewStartY , stcReelFeverInfoData[slReel].slViewEndY ) ;
            }
        }
    }
}

void vReel_FeverShowOneJumpReel( SLONG slReel , ULONG ulAnim )
{
    SLONG slData ;
    SLONG slX , slY , slSym ;
   // ANIM_IMAGE *aiImgAdr ;
    
    if ( slReel < DEF_FEVER_REEL_MAX )
    {
        slData = 2 ;
        //for ( slData = 1 ; slData < DEF_REEL_MAX_SHOW-1 ; slData ++ )
        {
            slX    = stcReelFeverInfoData[slReel].slLocX ;
            slY    = stcReelFeverInfoData[slReel].slLocY + ((slData-2) * (stcReelFeverInfoData[slReel].slIntervalHeight)) + stcReelFeverData[slReel].swMoveY ;
            slSym  = stcReelFeverData[slReel].ubShowID[slData]%7 ;
            if ( slSym < DEF_SYMBOL_MAX )
            {
            	vShowLib_FeverReel( slReel,ulAnim + (slData-1) , slSym , slX ,slY ,  stcReelFeverInfoData[slReel].slViewStartY , stcReelFeverInfoData[slReel].slViewEndY ,stcReelFeverInfoData[slReel].slIntervalHeight);
               // aiImgAdr = (ANIM_IMAGE *)stcReelSymbolImg[slSym] ;
               // vAnimator_ShowWindows( (ANIM_IMAGE *)aiImgAdr , slX , slY , ulReelSymbolPal[slSym] , ulAnim + (slData-1) , 0 , stcReelFeverInfoData[slReel].slViewStartY , stcReelFeverInfoData[slReel].slViewEndY ) ;
            }
        }
    }
}
void vReel_FeverProcess( SLONG slReel , ULONG ulAnim )
{
    ULONG ulFlag;

    ulFlag = 0 ;    

    if ( slReel < DEF_FEVER_REEL_MAX )
    {
        switch( stcReelFeverData[slReel].ubState )
        {
            case DEF_REEL_STOP   :
                break ;
            case DEF_REEL_SHOW   :
                mReel_SetFlag( ulFlag , DEF_REEL_SHOW_FLAG ) ;
                stcReelFeverData[slReel].ubState = DEF_REEL_STOP ;
                break ;
            case DEF_REEL_START  :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_CAL_FLAG) ) ;
                stcReelFeverData[slReel].ubState = DEF_REEL_ADD ;
                stcReelFeverData[slReel].swCount = 0 ;
                stcReelFeverData[slReel].swSpeed = slFeverReelAddSpeedData[0] ;
                break ;
            case DEF_REEL_ADD    :
                                
                stcReelFeverData[slReel].swCount ++ ;          
                if ( stcReelFeverData[slReel].swCount >= 0 )
                {
                    mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_CAL_FLAG|DEF_REEL_SP_FLAG) ) ;

                    if ( stcReelFeverData[slReel].swCount < 20 )
                    {
                        if ( slFeverReelAddSpeedData[stcReelFeverData[slReel].swCount] )
                        {
                            stcReelFeverData[slReel].swSpeed = slFeverReelAddSpeedData[stcReelFeverData[slReel].swCount] ;
                        }
                        else
                        {
                            stcReelFeverData[slReel].ubState = DEF_REEL_RUN ;
                            stcReelFeverData[slReel].swCount = 0 ;
                        }                     
                    }
                }
                break ;
            case DEF_REEL_RUN    :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_CAL_FLAG|DEF_REEL_SP_FLAG) ) ;
                stcReelFeverData[slReel].swCount ++ ;
                    
                if ( stcReelFeverData[slReel].swCount >= stcReelFeverInfoData[slReel].ulMaxRun )
                {
                    stcReelFeverData[slReel].ubState       = DEF_REEL_ADJUST ;
                    stcReelFeverData[slReel].swCount       = 0 ;
                    stcReelFeverData[slReel].ubAdjustIndex = 0 ;
                }
                break ;
            case DEF_REEL_ADJUST :            	
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_ADJUST_FLAG|DEF_REEL_SP_FLAG) ) ;
                if ( stcReelFeverData[slReel].ubAdjustIndex == (DEF_REEL_MAX_SHOW-2) )
                {                	
                    if ( stcReelFeverData[slReel].swMoveY >= 0 && stcReelFeverData[slReel].swMoveY <= DEF_FEVER_REEL_SLOW_NEAR )
                    {                    	
                        stcReelFeverData[slReel].swMoveY     = DEF_FEVER_REEL_SLOW_NEAR ;
                        stcReelFeverData[slReel].ubState     = DEF_REEL_SUB ;
                        stcReelFeverData[slReel].swCount     = 0 ;

                    }
                }
                break ;
            case DEF_REEL_SUB    :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_ADJUST_FLAG|DEF_REEL_SP_FLAG) ) ;
    
                if ( stcReelFeverData[slReel].swCount < 20 )
                {
                    if ( slFeverReelSubSpeedData[ stcReelFeverData[slReel].swCount ] )
                    {
                        stcReelFeverData[slReel].swSpeed = slFeverReelSubSpeedData[ stcReelFeverData[slReel].swCount ] ;
                    }                    
                    
                }  
                stcReelFeverData[slReel].swCount ++ ;
                
                if ( stcReelFeverData[slReel].ubAdjustIndex == (DEF_REEL_MAX_SHOW-1) )
                {                	
                    if ( stcReelFeverData[slReel].swMoveY >= (stcReelFeverInfoData[slReel].slIntervalHeight-1))
                    {                    	
                        stcReelFeverData[slReel].ubState = DEF_REEL_JUMP ;
                        stcReelFeverData[slReel].swCount = 0 ;	
                    }
                }
                break ;
            case DEF_REEL_JUMP   :
                mReel_SetFlag( ulFlag , (DEF_REEL_SHOW_FLAG|DEF_REEL_JUMP_FLAG) ) ;
                switch( stcReelFeverData[slReel].swCount )
                {
	                case 0 :
	                		stcReelFeverData[slReel].swSpeed = +10 ; break ;
	                case 1 : 
	                case 2 :
	                case 3 : 
	                case 4 :
	                		stcReelFeverData[slReel].swSpeed = -5 ; break ;
                
	                case 5 :
                    case 6 : 
	                case 7 :
                    case 8 : 
                    case 9 : 
                    	stcReelFeverData[slReel].swSpeed = +2 ; break ;
                 
                }

                stcReelFeverData[slReel].swCount ++ ;
    
                if ( stcReelFeverData[slReel].swCount >=10 )
                {
                    stcReelFeverData[slReel].swSpeed = 0 ;
                    stcReelFeverData[slReel].ubState = DEF_REEL_STOP ;
                    stcReelFeverData[slReel].swCount = 0 ;
                    stcReelFeverData[slReel].swMoveY = 0 ;
                }               
                break ;
            default :
                stcReelFeverData[slReel].ubState = DEF_REEL_STOP ;
                break ;
        }

        if ( ulFlag&DEF_REEL_CAL_FLAG )
        {
            vReel_FeverMoveOneReel( slReel ) ;
        }
        if ( ulFlag&DEF_REEL_ADJUST_FLAG )
        {
            vReel_FeverMoveAdjustOneReel( slReel ) ;
        }
        if ( ulFlag&DEF_REEL_JUMP_FLAG )
        {
            vReel_FeverMoveJumpOneReel( slReel ) ;
        }
        if ( ulFlag&DEF_REEL_SHOW_FLAG )
        {
            if( ulFlag&DEF_REEL_JUMP_FLAG )
            {
                vReel_FeverShowOneJumpReel( slReel , ulAnim ) ;
            }
            else
            {
                vReel_FeverShowOneReel( slReel , ulAnim ) ;
            }
        }
    }
}
