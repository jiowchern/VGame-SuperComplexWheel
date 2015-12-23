#include "Source\common.h"





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


};

REELINFO const stcReelInfoData[DEF_REEL_MAX] =
{// { MaxD, MaxR , slX , slY     , slStartY, slEndY     , slH} , 
	{ 128 , 2096 , 78  , 116     , 116     , 116 + 180    , 180 } ,
	{ 128 , 2096 , 252 , 116     , 116     , 116 + 180    , 180 } ,
	{ 128 , 2096 , 426 , 116     , 116     , 116 + 180    , 180 } ,
	{ 128 , 2096 , 600 , 116     , 116     , 116 + 180    , 180 } ,
	{ 128 , 2096 , 774 , 116     , 116     , 116 + 180    , 180 } ,

	{ 128 , 2096 , 78  , 298     , 298     , 298 + 180    , 180 } ,
	{ 128 , 2096 , 252 , 298     , 298     , 298 + 180    , 180 } ,
	{ 128 , 2096 , 426 , 298     , 298     , 298 + 180    , 180 } ,
	{ 128 , 2096 , 600 , 298     , 298     , 298 + 180    , 180 } ,
	{ 128 , 2096 , 774 , 298     , 298     , 298 + 180    , 180 } ,

	{ 128 , 4096 , 78  , 480     , 480     , 480 + 180    , 180 } ,
	{ 128 , 4096 , 252 , 480     , 480     , 480 + 180    , 180 } ,
	{ 128 , 4096 , 426 , 480     , 480     , 480 + 180    , 180 } ,
	{ 128 , 4096 , 600 , 480     , 480     , 480 + 180    , 180 } ,
	{ 128 , 4096 , 774 , 480     , 480     , 480 + 180    , 180 } ,
};


// adjust.
ADJUSTVALUE const stcAdjustValueInformationForSW[DEF_ADJUSTVALUE_MAX] =
{
	//00-> DEF_ADJUSTVALUE_COIN_A_RATE
#ifdef DEF_GTRULE_GTHS
{ 11 ,  0 ,{ 1,2,5,10,20,50,100,200,250,500,1000 } } ,
#else
{ 12 ,  1 ,{ 0,1,2,5,10,20,50,100,200,250,500,1000 } } ,
#endif
//01-> DEF_ADJUSTVALUE_MONEY_RATE
{ 12 ,  7 ,{ 1 ,    2 ,    5 ,   10 ,   20 ,   25 ,   50 ,  100 ,  200 ,  250 ,  500 , 1000 } } ,
//02-> DEF_ADJUSTVALUE_OPTION_TYPE
{ 4 ,  3 ,{ 0 , 1 , 2 , 3 } } ,
//03-> DEF_ADJUSTVALUE_REPORT_DAY
#ifdef DEF_GTRULE_GTHS
{ 30 ,  9 ,{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 } } ,
#else
{ 7 ,  0 ,{ 0,1,2,3,4,5,6 } } ,
#endif
//04-> DEF_ADJUSTVALUE_REPORT_HOUR
{ 24 ,  6 ,{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 } } ,
//05-> DEF_ADJUSTVALUE_REPORT_COIN
{ 30 ,  9 ,{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 } } ,
//06-> DEF_ADJUSTVALUE_SYS_TIME
{ 7 ,  0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//07-> DEF_ADJUSTVALUE_HOT_MODE
{ 2 ,  0 ,{ 0 , 1 } } ,
//08-> DEF_ADJUSTVALUE_HOT_ASSIGN
#ifdef DEF_GTRULE_GTHS
{ 10 ,  0 ,{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 } } ,
#else
{ 10 ,  0 ,{ 50000 , 20000 , 10000 , 5000 , 1000 , 0 , 1005000 , 1010000 , 1020000 , 1050000 } } ,
#endif

//09-> DEF_ADJUSTVALUE_COIN_C_RATE
{ 12 ,  1 ,{ 0,1,2,5,10,20,50,100,200,250,500,1000 } } ,
//0A-> DEF_ADJUSTVALUE_KEYIN_B_RATE
{ 17 ,  15 ,{ 0,1,2,5,10,20,50,100,200,250,500,1000,2000,5000,10000,50000,100000 } } ,
//0B-> DEF_ADJUSTVALUE_KEYIN_D_RATE
{ 17 ,  15 ,{ 0,1,2,5,10,20,50,100,200,250,500,1000,2000,5000,10000,50000,100000 } } ,
//0C-> DEF_ADJUSTVALUE_KEYOUT_RATE
{ 17 ,  11 ,{ 0,1,2,5,10,20,50,100,200,250,500,1000,2000,5000,10000,50000,100000 } } ,
//0D-> DEF_ADJUSTVALUE_PAYOUT_MODE   ÖÍ?®a£D(??®a£D)
{ 2 ,  0 ,{ 0 , 1 } } ,
//0E-> DEF_ADJUSTVALUE_TICKET_RATE   ÒÑ¥¬??
{ 24 , 11 ,{ 10100 , 10080 , 10050 , 10025 , 10015 , 10010 , 10008 , 10005 , 10004 , 10003 , 10002 , 1 , 2 , 3 , 4 , 5 , 8 , 10 , 15 , 20 , 25 , 50 , 80 , 100 } },

//0F-> DEF_ADJUSTVALUE_GAME_UNDULATE  
{ 3 ,  1 ,{ 0 ,    1 ,    2 } } ,
//10-> DEF_ADJUSTVALUE_GAME_RATE	
#ifdef DEF_ADD_GAMERATE_ADJ
{ 6 ,  3 ,{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 } } ,
#else
{ 10 ,  3 ,{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 } } ,
#endif
//11-> DEF_ADJUSTVALUE_WUP_RATE	
{ 4 ,   3 ,{ 0 , 1 , 2 , 3 } } ,

//12-> DEF_ADJUSTVALUE_MIN_BET
{ 5 ,  0 ,{ 1 , 2 , 3 , 5 , 10 } } ,
//13-> DEF_ADJUSTVALUE_MAX_BET
{ 6 ,  5 ,{ 5 , 10 , 20 , 30 , 40 , 50 } } ,
//14-> DEF_ADJUSTVALUE_BETADD
{ 4 ,  0 ,{ 1 , 2 , 5 , 10 } } ,
//15-> DEF_ADJUSTVALUE_GIFT_BET
{ 15 ,  0 ,{ 10,20,25,30,40,50,100,150,200,250,300,350,400,450,500 } } ,

//16-> DEF_ADJUSTVALUE_CREDIT_LIMIT
{ 11 ,  5 ,{ 50000 , 100000 , 200000 , 300000 , 400000 , 500000 , 600000 , 700000 , 800000 , 900000 , 1000000 } } ,
//17-> DEF_ADJUSTVALUE_SYS_LIMIT
{ 18 ,  15 ,{ 50000 , 100000 , 200000 , 300000 , 400000 , 500000 , 600000 , 700000 , 800000 , 900000 , 1000000 , 1200000 , 1400000 , 1600000 , 1800000 , 2000000 , 4000000 , 5000000 } } ,
//18-> DEF_ADJUSTVALUE_WUP_LIMIT
{ 18 ,  10 ,{ 0 , 10000 , 20000 , 30000 , 40000 , 50000 , 60000 , 70000 , 80000 , 90000 , 100000 , 120000 , 150000 , 200000 , 300000 , 400000 , 500000 , 600000 } } ,
//19-> DEF_ADJUSTVALUE_WUP_LOSE
{ 10 ,  2 ,{ 0 , 0 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 } } ,	// 20131202 // REX
															//1A-> DEF_ADJUSTVALUE_WUP_KILL
{ 10 ,  2 ,{ 0 , 0 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 } } , // 20131202 // REX

														 //1B-> DEF_ADJUSTVALUE_GAME_MUSIC
{ 4 ,  1 ,{ 0 ,  1 , 2 , 3 } } ,
//1C-> DEF_ADJUSTVALUE_MUSIC_VOLUME
{ 9 ,  4 ,{ 0 ,    1 ,    2 ,    3 ,    4 ,    5 ,    6 ,    7 , 8 } } ,
//1D-> DEF_ADJUSTVALUE_DEMOMUSIC	
{ 2 ,  1 ,{ 0 ,    1 } } ,
//1E->DEF_ADJUSTVALUE_SYMBOL	
{ 2 ,  0 ,{ 0 ,    1 } } ,
//1F-> DEF_ADJUSTVALUE_FONT_TYPE     ??úH?
{ 3 ,  0 ,{ 0 , 1 , 2 , 3 } } ,
//20-> DEF_ADJUSTVALUE_ACTIV_LIMIT
#ifdef DEF_M100CHP_ACTIVATE_LIMIT
{ 31 ,  0 ,{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 } } ,
#else
{ 0 ,  0 ,{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
#endif
//21->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//22->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//23->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//24->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//25->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//26->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//27->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//28->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//29->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//2A->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//2B->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//2C->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//2D->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//2E->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//2F->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//30->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//31->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//32->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//33->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//34->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//35->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//36->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//37->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//38->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//39->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//3A->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//3B->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//3C->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//3D->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//3E->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
//3F->No Use	
{ 0 , 0 ,{ 0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 ,    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } } ,
};



ULONG const ulFeverGameWinOdds[5] = { 5,4,3,2,1 };