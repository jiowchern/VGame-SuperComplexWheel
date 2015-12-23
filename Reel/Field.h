#pragma once
#include "Source\common.h"
using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
namespace VGame
{
	namespace CLR
	{
		namespace Dump
		{
			public value struct Buffer
			{
				SLONG slValue;
				SLONG slCount;
				ULONG ulLife;
			};
			public value struct FeverChanceBuf
			{
				UBYTE	ubData;
				ULONG	ulWin;
				ULONG	ulPlayTimes;
				UBYTE	ubLoseTimes;
			};
			public value struct MainChanceBuf
			{
				array<VGame::CLR::Dump::Buffer>^	Buffer;// [DEF_CHANCE_BUFMAX];
				array<ULONG>^						ulRate;// [DEF_CHANCE_BUFMAX];
				ULONG								ulBase;
				ULONG								 ulMainRetakeTime;
				SLONG								 slFeverOdds;
				array<VGame::CLR::Dump::Buffer>^	VirtualBuffer;// [8];          
				array<ULONG>^						ulVirtualRate;// [8];           
				array<ULONG>^						ulVirtualBufGate;// [8];        

				array<VGame::CLR::Dump::Buffer>^	SpecBuffer;// [8];               
				array<ULONG>^						ulSpecRate;// [8];                 //8��Spec Rate 
				array<ULONG>^						ulSpecValue;// [8];                 //8��Spec�ͳ���ֵ

				array<SLONG>^						 slVirtualBufTopValue;// [8];       //8�����ⴥ��ֵ
				array<ULONG>^						 ulVirtualBufAsnGift;// [8];        //8��ǿ�ƽ���
				SLONG								slReturnBufValue;              //�ع�Buffer
				ULONG								slReturnBetValue;              //�ع��ۼ�Ѻ��
				ULONG								ulReturnMainValue;             //�ع�Main����
				VGame::CLR::Dump::Buffer			ReturnSpec;                   //�ع�Spec����

				array<ULONG>^						ulWinTimes;// [DEF_CHANCE_BUFMAX]; // ��BUF Ӯ�������					
				ULONG								ulPlayTimes; // Chance �������	
				SLONG								slAvgBet; //��ʱ��ƽ��Ѻע 
				SLONG								slAvgBetTotal; //����ƽ��Ѻע�õĲο��ܶ�Ѻע  
				ULONG								ulActBuf; // �趨������ʹ�õ� Buffer	
				ULONG								ulAsnGift; // �趨ǿ�ƽ���

				ULONG								ulAsnState;      //��������ǿ��Ϊ0,Specǿ��Ϊ1


				ULONG								ulFreeTotalWin, ulFreeType;
				ULONG								ulFeverTotalWin, ulFeverType;

				array<ULONG>^						ulBufferGate;// [DEF_CHANCE_BUFMAX];
				array<ULONG>^						ulRecSpecValue;// [3];	//ͳ��?�ƽoFREE,FEVER,BONUS�ķ֔�
				array<ULONG>^						ulRecFever;// [2];
				array<ULONG>^						ulRecMainAsn;// [3];
				array<array<ULONG>^>^				ulRecVirAsnTimes;// [8][3];
				array<ULONG>^						ulRecReelSymTimes;// [13];
				array<array<ULONG>^>^				ulRecBetArray;// [5][11];//ͳ�Ƽo?Ѻע�ցѠ�B�֔�
				array<array<ULONG>^>^				ulRecBufArray;// [5][51];//ͳ�Ƹ��MBuffer�ցѠ�B
				array<ULONG>^						ulRecFreeArray;// [20];//ͳ����FREE����
				ULONG								ulRecFreeTimes;
				array<ULONG >^						ulRecReturnIn;// [5];
			};
			public value struct ChanceSet
			{
				MainChanceBuf	stcChance;
				FeverChanceBuf	stcFeverChance;
			};
			public value struct Reel
			{
				array<UBYTE>^	ubShowID;// [DEF_REEL_MAX_SHOW];
				array<UBYTE>^	ubStopID;// [DEF_REEL_MAX_SHOW];
				array<UBYTE>^	ubSaveID;// [DEF_REEL_MAX_SHOW];
				UBYTE			ubState;
				UBYTE			ubAsnState;
				UBYTE			 ubAdjustIndex;
				SWORD			 swMoveY;
				SWORD			 swSpeed;
				SWORD			 swCount;
				UWORD			 uwGetIndex;
				array<UBYTE>^	ubReelData; // DEF_REEL_MAX_SYM
			};
			public value struct ReelSet
			{
				array<Reel>^	stcReelData;
				array<Reel>^	stcReelFeverData;
				ULONG ulReelNeedSoundEft;
			};

			public value struct MasterInfo
			{
				UBYTE 	ubRunFlag;
				UBYTE 	ubDemoFlag;
				ULONG 	ulState;
				ULONG 	ulIndex;
				ULONG 	ulCount;
				ULONG 	ulEftCnt;
				ULONG 	ulMapTime;
				ULONG   ulTestCount;
				ULONG   ulSceneState; //����״̬��0����Ϸ��1 Free��Ϸ
				ULONG   ulTemp;   //�ݴ�
				ULONG 	ulAllCount; //
				ULONG   ulAutoKeyState;//0�����棬1����һ�ο�ʼ��÷֣�2�ڶ��ο�ʼ+ȫͣ+�÷�+����    
				ULONG   ulAutoKeyGameState; //����ʱ���Զ�״̬
				ULONG   ulSaveAutoKeyState;//�Զ�FREE��Ϸʱ����״̬ 
				array<ULONG>^  ulBackUp;//[3];
			};
			public value struct BetLine
			{
				SLONG slLine;
				SLONG slBet;
			};
			public value struct SlaveSet
			{
				array<BetLine>^ stcBet;// [DEF_BET_MAXID];
				SLONG	slWinValue;
				SLONG	slWupWinValue;
			};
			
			public value struct WupChanceBuf
			{
				Buffer			Buffer;
				ULONG			ulRate;
				UBYTE			ubData;
				UBYTE			ubGuess;
			
				array<UBYTE>^	ubHistory;
				array<UBYTE>^	ubDemoHistory;
				UBYTE			ubDemoTime;
				ULONG 			ulPlayTimes; 
									 

				ULONG			ulAsnLose;	
				ULONG			ulAsnKill;	
				array<ULONG>^ 	ulRecAsnValue;
				array<ULONG>^ 	ulRecAsnTimes;
				array<ULONG>^ 	ulRecTimes;	
				array<ULONG>^ 	ulRecPass;		
				array<ULONG>^ 	ulRecInsure;	
				array<ULONG>^ 	ulRecLimit;		
				array<ULONG>^ 	ulRecLose;		
				array<ULONG>^ 	ulRecKill;		
				array<array<ULONG>^>^ 	ulRecOver;
				array<ULONG>^ 	ulJKTimes;
			};
			public value struct AdjustValueSet
			{
				array<UBYTE>^ ubAdjustValueDataForSW;
				array<UBYTE>^ ubAdjustValueTempDataForSW;
			};

			public value struct GameInfoLine
			{
				array<ULONG>^ ulOdds;
				array<ULONG>^ ulWinSym;
				array<ULONG>^ ulWinNum;
				array<UBYTE>^ ubSym;
				array<array<UBYTE>^>^ ubAct;
			};
			public value struct GameInfo
			{
				array<GameInfoLine>^	stcLine;
				ULONG ulAllSameOdds;
				ULONG ulAllSameSym;
				ULONG ulFeverSetLife;
				ULONG ulFeverNowLife;
				ULONG ulFeverType;
				ULONG ulFever1Odds;
				ULONG ulFever2Odds;
				ULONG ulFever3Odds;
				ULONG ulFreeSetLife;
				ULONG ulFreeNowLife;
				ULONG ulFreeType;
				ULONG ulBonusType;
				ULONG ulBonusWin;
				ULONG ulBonusValue;
			};

			public value struct RecordRecordEventWin
			{
				ULONG ulWin;
				array<UBYTE>^	ubStr;
			};
			public value struct RecordRecordFieldSet
			{
				DLONG dlCurTotal;
				DLONG dlLasTotal;
				DLONG dlHisTotal;
			};
			public enum class __RECORD_DATA__
			{
				DEF_RECORD_DATA_COIN, // ( ���[��] �֥[:�� )
				DEF_RECORD_DATA_PAYOUT, // ( �h��[��] �֥[:�� )
				DEF_RECORD_DATA_KEYIN, // ( �W��[��] �֥[:�� )
				DEF_RECORD_DATA_KEYOUT, // ( �U��[��] �֥[:�� )
				DEF_RECORD_DATA_TOTALPLAY, // ( �`��[��] �֥[:�� )
				DEF_RECORD_DATA_TOTALWIN, // ( �`Ĺ[��] �֥[:�� )
				DEF_RECORD_DATA_COIN_A,
				DEF_RECORD_DATA_COIN_C,
				DEF_RECORD_DATA_KEYIN_B,
				DEF_RECORD_DATA_KEYIN_D,
				DEF_RECORD_MAIN_WINTIMES,
				DEF_RECORD_MAIN_PLAYTIMES,
				DEF_RECORD_MAIN_WINTOTAL,
				DEF_RECORD_MAIN_PLAYTOTAL,
				DEF_RECORD_WUP_WINTIMES,
				DEF_RECORD_WUP_PLAYTIMES,
				DEF_RECORD_WUP_WINTOTAL,
				DEF_RECORD_WUP_PLAYTOTAL,

				DEF_RECORD_DATA_USER_01, 
				DEF_RECORD_DATA_USER_02, 
				DEF_RECORD_DATA_USER_03, 
				DEF_RECORD_DATA_USER_04, 
				DEF_RECORD_DATA_USER_05, 
				DEF_RECORD_DATA_USER_06, 
				DEF_RECORD_DATA_USER_07, 
				DEF_RECORD_DATA_USER_08, 
				DEF_RECORD_DATA_USER_09, 
				DEF_RECORD_DATA_USER_10, 
				DEF_RECORD_DATA_USER_11, 
				DEF_RECORD_DATA_USER_12, 
				DEF_RECORD_DATA_USER_13, 
				DEF_RECORD_DATA_USER_14, 
				DEF_RECORD_DATA_USER_15, 
				DEF_RECORD_DATA_USER_16, 
				DEF_RECORD_DATA_USER_17, 
				DEF_RECORD_DATA_USER_18, 
				DEF_RECORD_DATA_USER_19, 
				DEF_RECORD_DATA_USER_20, 
				DEF_RECORD_DATA_USER_21, 
				DEF_RECORD_DATA_USER_22, 
				DEF_RECORD_DATA_USER_23, 
				DEF_RECORD_DATA_USER_24, 
				DEF_RECORD_DATA_USER_25, 
				DEF_RECORD_DATA_USER_26, 
				DEF_RECORD_DATA_USER_27, 
				DEF_RECORD_DATA_USER_28, 
				DEF_RECORD_DATA_USER_29, 
				DEF_RECORD_DATA_USER_30, 
				DEF_RECORD_DATA_USER_31, 
				DEF_RECORD_DATA_USER_32, 
				DEF_RECORD_DATA_USER_33, 
				DEF_RECORD_DATA_USER_34, 
				DEF_RECORD_DATA_USER_35, 
				DEF_RECORD_DATA_USER_36, 
				DEF_RECORD_DATA_USER_37, 
				DEF_RECORD_DATA_USER_38, 
				DEF_RECORD_DATA_USER_39, 
				DEF_RECORD_DATA_USER_40, 
				DEF_RECORD_DATA_USER_41, 
				DEF_RECORD_DATA_USER_42, 
				DEF_RECORD_DATA_USER_43, 
				DEF_RECORD_DATA_USER_44, 
				DEF_RECORD_DATA_USER_45, 
				DEF_RECORD_DATA_USER_46, 
				DEF_RECORD_DATA_USER_47, 
				DEF_RECORD_DATA_USER_48, 
				DEF_RECORD_DATA_USER_49, 
				DEF_RECORD_DATA_USER_50, 
				DEF_RECORD_DATA_USER_51, 
				DEF_RECORD_DATA_USER_52, 
				DEF_RECORD_DATA_USER_53, 
				DEF_RECORD_DATA_USER_54, 
				DEF_RECORD_DATA_USER_55, 
				DEF_RECORD_DATA_USER_56, 
				DEF_RECORD_DATA_USER_57, 
				DEF_RECORD_DATA_USER_58, 
				DEF_RECORD_DATA_USER_59, 
				DEF_RECORD_DATA_USER_60, 
				DEF_RECORD_DATA_USER_61, 
				DEF_RECORD_DATA_USER_62, 
				DEF_RECORD_DATA_USER_63,  
				DEF_RECORD_DATA_USER_64,  
				DEF_RECORD_DATA_USER_65, 
				DEF_RECORD_DATA_USER_66, 
				DEF_RECORD_DATA_USER_67, 
				DEF_RECORD_DATA_USER_68, 
				DEF_RECORD_DATA_USER_69, 
				DEF_RECORD_DATA_USER_70, 
				 
				DEF_RECORD_INFO_PROFIT_SCOR , // ( �էQ����[��]   (TotalIn - TotalOut)            �֥[:���i )
				DEF_RECORD_INFO_PROFIT_COIN , // ( �禬����[��]   (TotalIn - TotalOut)/CoinRate   �֥[:���i )
				DEF_RECORD_INFO_BOOT_DAYS , // ( �}���Ѽ�[���] 8'BCD[DDDDDDhh] Ex: 00078923    �֥[:���i )
				DEF_RECORD_INFO_GAME_DAYS , // ( �C���Ѽ�[���] 8'BCD[DDDDDDhh] Ex: 00078923    �֥[:���i )

				DEF_RECORD_MAX,
				DEF_RECORD_DATA_MAX = DEF_RECORD_INFO_PROFIT_SCOR,
			};
			public enum class __RECORD_PLR__
			{
				DEF_RECORD_PLR_1P,
				/*
				DEF_RECORD_PLR_2P   ,
				DEF_RECORD_PLR_3P   ,
				DEF_RECORD_PLR_4P   ,
				DEF_RECORD_PLR_5P   ,
				DEF_RECORD_PLR_6P   ,
				DEF_RECORD_PLR_7P   ,
				DEF_RECORD_PLR_8P   ,
				DEF_RECORD_PLR_9P   ,
				DEF_RECORD_PLR_10P  ,
				*/
				DEF_RECORD_PLR_ALL,
				DEF_RECORD_PLR_MAX
			};

			public value struct RecordFieldSet
			{				
				System::Collections::Generic::Dictionary<__RECORD_PLR__, System::Collections::Generic::Dictionary<__RECORD_DATA__, RecordRecordFieldSet>^>^	stcRecordData;
				System::Collections::Generic::Dictionary<__RECORD_DATA__, RecordRecordFieldSet>^ stcRecordSymbolGift;
				array<RecordRecordEventWin>^ stcRecordEvent_Win;
			};
			public value struct WheelFieldSet
			{
				SLONG slFeverWin;
				SLONG slFreeWin;
				ULONG ulPlayTimes;
				ULONG ulWinTimes;
				DLONG dlPlayTotal;
				DLONG dlWinTotal;
				DLONG dlRunTime;

				ULONG ulSwitch;
				ULONG ulRecCycle;

				SLONG slWupBet;
				ULONG ulWupTime;
				ULONG ulWupPlayTimes;

				ULONG ulWupCondi1;
				ULONG ulWupCondi2;

				AdjustValueSet	AdjustValue;
				RecordFieldSet	Record;
				GameInfo	stcGameInfo;
				WupChanceBuf stcWupChance;
				SlaveSet	Slave;
				ReelSet		Reel;
				MasterInfo stcMaster;
				ChanceSet	Chance;
			};
		}
		
	}
}

