#include "WheelDumper.h"
#include "Field.h"

namespace VGame
{
	namespace Native
	{
		namespace Dump
		{
			template<typename TTarget, int  TLength, typename TSource = TTarget>
			array<TTarget>^  _ArrayConver(const TSource input[TLength], TTarget(*setter)(const TSource&) );

			template<typename TType>
			TType _ArrayConverSetter(const TType& element)
			{
				return element;
			}
			template<typename TType>
			TType _ArrayConverSetter(const TType% element)
			{
				return element;
			}

			template<typename TType>
			void _ArrayConverSetter(TType& element1 , const TType& element2)
			{
				element1 = element2;
			}
			template<typename TType>
			void _ArrayConverSetter(TType& element1, const TType% element2)
			{
				element1 = element2;
			}
			

			template<typename TTypeBase, int size>
			array<TTypeBase>^ _ArrayConverSetter(const TTypeBase(&s)[size])
			{
				return _ArrayConver<TTypeBase , size >(s );
			}

			template<typename TTypeBase, int size>
			void _ArrayConverSetter(TTypeBase(&dest)[size] , const array<TTypeBase>^% src)
			{
				for (int i = 0; i < size; ++i)
				{
					_ArrayConverSetter(dest[i] , src[i]);
				}
			}

			// 紂
			template<typename TTarget , int  TLength  , typename TSource = TTarget>
			array<TTarget>^  _ArrayConver(const TSource input[TLength] , TTarget(*setter)(const TSource&) = _ArrayConverSetter)
			{				
				auto ary = gcnew array<TTarget>(TLength);
				
				if (input == NULL)
					return ary;

				for (int i = 0; i < TLength; i++)
				{					
					ary[i] = setter(input[i]);
				}
				return ary;
			}
			
			template<typename TTarget, int  TLength, typename TSource = TTarget>
			void CSArrayToArray(TTarget target[TLength], const array<TSource>^ src , void(*setter)(TTarget& target , const TSource%) = _ArrayConverSetter )
			{
				for (int i = 0; i < TLength; i++)
				{
					setter(target[i] , src[i]);
				}
			}
			
			VGame::CLR::Dump::Buffer _DumpBuffer(const BUFFER& buf)
			{
				auto out = VGame::CLR::Dump::Buffer();
				out.slCount = buf.slCount;
				out.slValue = buf.slValue;
				out.ulLife = buf.ulLife;
				return out;
			}

			void SetBuffer(BUFFER& buffer , const VGame::CLR::Dump::Buffer% set)
			{				
				buffer.slCount = set.slCount;
				buffer.slValue = set.slValue;
				buffer.ulLife = set.ulLife;				
			}
			void DumpChance(MAINCHANCE_BUF&	out , const VGame::CLR::Dump::MainChanceBuf% stcChance)
			{
				CSArrayToArray<BUFFER , DEF_CHANCE_BUFMAX , VGame::CLR::Dump::Buffer >(out.Buffer , stcChance.Buffer , SetBuffer );
				CSArrayToArray<ULONG, DEF_CHANCE_BUFMAX >(out.ulRate, stcChance.ulRate);				
				
				out.ulBase = stcChance.ulBase;
				out.ulMainRetakeTime = stcChance.ulMainRetakeTime;
				out.slFeverOdds = stcChance.slFeverOdds;

				CSArrayToArray<BUFFER, 8 ,VGame::CLR::Dump::Buffer>(out.VirtualBuffer, stcChance.VirtualBuffer , SetBuffer);

				CSArrayToArray<ULONG, 8>(out.ulVirtualRate, stcChance.ulVirtualRate);
				CSArrayToArray<ULONG, 8>(out.ulVirtualBufGate, stcChance.ulVirtualBufGate);
				
				
				CSArrayToArray<BUFFER, 8, VGame::CLR::Dump::Buffer>(out.SpecBuffer, stcChance.SpecBuffer, SetBuffer);
				CSArrayToArray<ULONG, 8>(out.ulSpecRate, stcChance.ulSpecRate);
				CSArrayToArray<ULONG, 8>(out.ulSpecValue, stcChance.ulSpecValue);

				CSArrayToArray<SLONG, 8>(out.slVirtualBufTopValue, stcChance.slVirtualBufTopValue);
				CSArrayToArray<ULONG, 8>(out.ulVirtualBufAsnGift, stcChance.ulVirtualBufAsnGift);
				
				out.slReturnBufValue = stcChance.slReturnBufValue;
				out.slReturnBetValue = stcChance.slReturnBetValue;
				out.ulReturnMainValue = stcChance.ulReturnMainValue;
				SetBuffer(out.ReturnSpec , stcChance.ReturnSpec);
				
				CSArrayToArray<ULONG, DEF_CHANCE_BUFMAX>(out.ulWinTimes, stcChance.ulWinTimes);
				
				out.ulPlayTimes = stcChance.ulPlayTimes; // Chance 总玩次数	
				out.slAvgBet = stcChance.slAvgBet; //当时的平均押注 
				out.slAvgBetTotal = stcChance.slAvgBetTotal; //计算平均押注用的
				out.ulActBuf = stcChance.ulActBuf; // 设定本局所使用的 Bu
				out.ulAsnGift = stcChance.ulAsnGift; // 设定强制奖项

				out.ulAsnState = stcChance.ulAsnState;      //正常本身强制为

				out.ulFreeTotalWin = stcChance.ulFreeTotalWin;
				out.ulFreeType = stcChance.ulFreeType;
				out.ulFeverTotalWin = stcChance.ulFeverTotalWin;
				out.ulFeverType = stcChance.ulFeverType;

				CSArrayToArray<ULONG, DEF_CHANCE_BUFMAX>(out.ulBufferGate, stcChance.ulBufferGate);
				CSArrayToArray<ULONG, 2>(out.ulRecFever, stcChance.ulRecFever);
				CSArrayToArray<ULONG, 3>(out.ulRecMainAsn, stcChance.ulRecMainAsn);
				
				CSArrayToArray<ULONG[3], 8 , array<ULONG>^>(out.ulRecVirAsnTimes, stcChance.ulRecVirAsnTimes);
				CSArrayToArray<ULONG, 13 >(out.ulRecReelSymTimes, stcChance.ulRecReelSymTimes);
								
				CSArrayToArray<ULONG[11], 5, array<ULONG>^ >(out.ulRecBetArray, stcChance.ulRecBetArray);
				
				CSArrayToArray<ULONG[51], 5, array<ULONG>^ >(out.ulRecBufArray, stcChance.ulRecBufArray);
				CSArrayToArray<ULONG, 20>(out.ulRecFreeArray, stcChance.ulRecFreeArray);
				
				
				out.ulRecFreeTimes = stcChance.ulRecFreeTimes;
				CSArrayToArray<ULONG, 5>(out.ulRecReturnIn, stcChance.ulRecReturnIn);				

				
			}
			VGame::CLR::Dump::MainChanceBuf  DumpChance(const 	MAINCHANCE_BUF&	stcChance)			
			{
				auto out = VGame::CLR::Dump::MainChanceBuf();

				out.Buffer= _ArrayConver<VGame::CLR::Dump::Buffer, DEF_CHANCE_BUFMAX , BUFFER>(stcChance.Buffer , _DumpBuffer );// [DEF_CHANCE_BUFMAX];
				out.ulRate = _ArrayConver<ULONG , DEF_CHANCE_BUFMAX >(stcChance.ulRate);// [DEF_CHANCE_BUFMAX];
				out.ulBase = stcChance.ulBase;
				out.ulMainRetakeTime = stcChance.ulMainRetakeTime;
				out.slFeverOdds = stcChance.slFeverOdds;
				out.VirtualBuffer = _ArrayConver<VGame::CLR::Dump::Buffer, 8, BUFFER>(stcChance.VirtualBuffer, _DumpBuffer);// [8];          
				out.ulVirtualRate = _ArrayConver<ULONG, 8>(stcChance.ulVirtualRate);// [8];           
				out.ulVirtualBufGate = _ArrayConver<ULONG, 8>(stcChance.ulVirtualBufGate);// [8];        

				out.SpecBuffer = _ArrayConver<VGame::CLR::Dump::Buffer, 8, BUFFER>(stcChance.SpecBuffer, _DumpBuffer);// [8];              
				out.ulSpecRate = _ArrayConver<ULONG, 8>(stcChance.ulSpecRate);// [8];              
				out.ulSpecValue = _ArrayConver<ULONG, 8>(stcChance.ulSpecValue);// [8];             

				out.slVirtualBufTopValue = _ArrayConver<SLONG, 8>(stcChance.slVirtualBufTopValue);// [8];   
				out.ulVirtualBufAsnGift = _ArrayConver<ULONG, 8>(stcChance.ulVirtualBufAsnGift);// [8];    
				out.slReturnBufValue = stcChance.slReturnBufValue;
				out.slReturnBetValue = stcChance.slReturnBetValue;
				out.ulReturnMainValue = stcChance.ulReturnMainValue;
				out.ReturnSpec = _DumpBuffer(stcChance.ReturnSpec);                   //

				out.ulWinTimes = _ArrayConver<ULONG, DEF_CHANCE_BUFMAX>(stcChance.ulWinTimes);// [DEF_CHANCE_BUFMAX
				out.ulPlayTimes = stcChance.ulPlayTimes; // Chance 总玩次数	
				out.slAvgBet = stcChance.slAvgBet; //当时的平均押注 
				out.slAvgBetTotal = stcChance.slAvgBetTotal; //计算平均押注用的
				out.ulActBuf = stcChance.ulActBuf; // 设定本局所使用的 Bu
				out.ulAsnGift = stcChance.ulAsnGift; // 设定强制奖项

				out.ulAsnState = stcChance.ulAsnState;      //正常本身强制为

				out.ulFreeTotalWin = stcChance.ulFreeTotalWin;
				out.ulFreeType = stcChance.ulFreeType;
				out.ulFeverTotalWin = stcChance.ulFeverTotalWin;
				out.ulFeverType = stcChance.ulFeverType;

				out.ulBufferGate = _ArrayConver<ULONG, DEF_CHANCE_BUFMAX>(stcChance.ulBufferGate);// [DEF_CHANCE_BUFM
				out.ulRecSpecValue = _ArrayConver<ULONG, 3>(stcChance.ulRecSpecValue);// [3];	//统计?制
				out.ulRecFever = _ArrayConver<ULONG, 2>(stcChance.ulRecFever);// [2];
				out.ulRecMainAsn = _ArrayConver<ULONG, 3>(stcChance.ulRecMainAsn);// [3];
				out.ulRecVirAsnTimes = _ArrayConver<array<ULONG>^, 8 , ULONG[3] >(stcChance.ulRecVirAsnTimes);// [8][3];
				out.ulRecReelSymTimes = _ArrayConver<ULONG ,13>(stcChance.ulRecReelSymTimes);// [13];
				out.ulRecBetArray = _ArrayConver<array<ULONG>^, 5, ULONG[11] >(stcChance.ulRecBetArray);// [5][11];//统计紀
				out.ulRecBufArray = _ArrayConver<array<ULONG>^, 5, ULONG[51] >(stcChance.ulRecBufArray);// [5][51];//统计各
				out.ulRecFreeArray = _ArrayConver<ULONG, 20>(stcChance.ulRecFreeArray);// [20];//统计送F
				out.ulRecFreeTimes = stcChance.ulRecFreeTimes;
				out.ulRecReturnIn = _ArrayConver<ULONG, 5>(stcChance.ulRecReturnIn);// [5];

				return out;
			}

			void DumpFeverChance(FEVERCHANCE_BUF& out, const VGame::CLR::Dump::FeverChanceBuf% stcChance)
			{
				out.ubData = stcChance.ubData;
				out.ubLoseTimes = stcChance.ubLoseTimes;
				out.ulPlayTimes = stcChance.ulPlayTimes;
				out.ulWin = stcChance.ulWin;
			}

			VGame::CLR::Dump::FeverChanceBuf DumpFeverChance(const FEVERCHANCE_BUF&	stcChance)
			{
				auto out = VGame::CLR::Dump::FeverChanceBuf();
				out.ubData = stcChance.ubData;
				out.ubLoseTimes = stcChance.ubLoseTimes;
				out.ulPlayTimes = stcChance.ulPlayTimes;
				out.ulWin = stcChance.ulWin;
				return out;
			}
			VGame::CLR::Dump::ChanceSet WheelDumper::_GetChance(const VGame::Native::Chance& chance)const
			{
				auto set = VGame::CLR::Dump::ChanceSet();
				set.stcChance = DumpChance(chance.stcChance);
				set.stcFeverChance = DumpFeverChance(chance.stcFeverChance);
				return set;
			}
			VGame::CLR::Dump::Reel _DumpReel(const REEL& reel)
			{
				auto out = VGame::CLR::Dump::Reel();

				out.ubShowID= _ArrayConver<UBYTE , DEF_REEL_MAX_SHOW>(reel.ubShowID);// [DEF_REEL_MAX_SHOW];
				out.ubStopID = _ArrayConver<UBYTE, DEF_REEL_MAX_SHOW>(reel.ubStopID);// [DEF_REEL_MAX_SHOW];
				out.ubSaveID = _ArrayConver<UBYTE, DEF_REEL_MAX_SHOW>(reel.ubSaveID);// [DEF_REEL_MAX_SHOW];
				out.ubState = reel.ubState;
				out.ubAsnState = reel.ubAsnState;
				out.ubAdjustIndex = reel.ubAdjustIndex;
				out.swMoveY = reel.swMoveY;
				out.swSpeed = reel.swSpeed;
				out.swCount = reel.swCount;
				out.uwGetIndex = reel.uwGetIndex;
				out.ubReelData = _ArrayConver<UBYTE, DEF_REEL_MAX_SYM>(reel.ubReelData); // DEF_REEL_MAX_SYM
				return out;
			}
			VGame::CLR::Dump::ReelSet WheelDumper::_GetReel(const VGame::Native::Reel& reel)const
			{
				auto set = VGame::CLR::Dump::ReelSet();
				set.stcReelData= _ArrayConver<VGame::CLR::Dump::Reel , DEF_REEL_MAX , REEL  >( reel.stcReelData  , _DumpReel );
				set.stcReelFeverData = _ArrayConver<VGame::CLR::Dump::Reel, DEF_FEVER_REEL_MAX , REEL  >(reel.stcReelFeverData, _DumpReel);
				set.ulReelNeedSoundEft = reel.ulReelNeedSoundEft;
				return set;
			}
			VGame::CLR::Dump::BetLine DumpBetLine(const BETLINE& bet)
			{
				auto out = VGame::CLR::Dump::BetLine();
				out.slBet = bet.slBet;
				out.slLine = bet.slLine;
				return out;
			}

			VGame::CLR::Dump::MasterInfo WheelDumper::_GetMaster(const MASTERINFO& master)const
			{
				auto set = VGame::CLR::Dump::MasterInfo();
				set.ubRunFlag= master.ubRunFlag;
				set.ubDemoFlag = master.ubDemoFlag;
				set.ulState = master.ulState;
				set.ulIndex = master.ulIndex;
				set.ulCount = master.ulCount;
				set.ulEftCnt = master.ulEftCnt;
				set.ulMapTime = master.ulMapTime;
				set.ulTestCount = master.ulTestCount;
				set.ulSceneState = master.ulSceneState; //场景状态，0主游
				set.ulTemp = master.ulTemp;   //暂存
				set.ulAllCount = master.ulAllCount; //
				set.ulAutoKeyState = master.ulAutoKeyState;//0正常玩，1，第
				set.ulAutoKeyGameState = master.ulAutoKeyGameState; //启动时的自
				set.ulSaveAutoKeyState = master.ulSaveAutoKeyState;//自动FREE游
				set.ulBackUp = _ArrayConver<ULONG , 3>( master.ulBackUp);
				return set;
			}

			VGame::CLR::Dump::SlaveSet WheelDumper::_GetSlave(const VGame::Native::Slave& slave)const
			{
				auto set = VGame::CLR::Dump::SlaveSet();

				set.slWinValue = slave.slWinValue;
				set.slWupWinValue = slave.slWupWinValue;
				
				set.stcBet = _ArrayConver<VGame::CLR::Dump::BetLine, 2, BETLINE >(slave.stcBet, DumpBetLine);
				return set;
			}


			VGame::CLR::Dump::WupChanceBuf WheelDumper::_GetWupChance(const WUPCHANCE_BUF& wupchance_buf)const
			{
				auto buf = VGame::CLR::Dump::WupChanceBuf();
				buf.Buffer.slCount = wupchance_buf.Buffer.slCount;
				buf.Buffer.slValue = wupchance_buf.Buffer.slValue;
				buf.Buffer.ulLife = wupchance_buf.Buffer.ulLife;
				buf.ulRate= wupchance_buf.ulRate;
				buf.ubData = wupchance_buf.ubData;
				buf.ubGuess = wupchance_buf.ubGuess;
				buf.ubHistory = _ArrayConver<UBYTE ,10>(wupchance_buf.ubHistory);
				buf.ubDemoHistory = _ArrayConver<UBYTE, 10>(wupchance_buf.ubDemoHistory);
				buf.ubDemoTime = wupchance_buf.ubDemoTime;
				buf.ulPlayTimes = wupchance_buf.ulPlayTimes;
				buf.ulAsnLose = wupchance_buf.ulAsnLose;
				buf.ulAsnKill = wupchance_buf.ulAsnKill;
				buf.ulRecAsnValue = _ArrayConver<ULONG,7>(wupchance_buf.ulRecAsnValue);
				buf.ulRecAsnTimes = _ArrayConver<ULONG, 7>(wupchance_buf.ulRecAsnTimes);
				buf.ulRecTimes = _ArrayConver<ULONG, 6>(wupchance_buf.ulRecTimes);
				buf.ulRecPass = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecPass);
				buf.ulRecInsure = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecInsure);
				buf.ulRecLimit = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecLimit);
				buf.ulRecLose = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecLose);
				buf.ulRecKill = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecKill);

				buf.ulRecOver = gcnew array<array<ULONG>^>(2);
				buf.ulRecOver[0] = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecOver[0]);
				buf.ulRecOver[1] = _ArrayConver<ULONG, 2>(wupchance_buf.ulRecOver[1]);
				buf.ulJKTimes = _ArrayConver<ULONG, 4>(wupchance_buf.ulJKTimes);
				return buf;
			}

			VGame::CLR::Dump::AdjustValueSet WheelDumper::_GetAdjustValue(const VGame::Native::AdjustValue& adjust_value) const
			{
				auto set = VGame::CLR::Dump::AdjustValueSet();
				set.ubAdjustValueDataForSW = gcnew array<UBYTE>(DEF_ADJUSTVALUE_MAX);
				set.ubAdjustValueTempDataForSW = gcnew array<UBYTE>(DEF_ADJUSTVALUE_MAX);

				for (size_t i = 0; i < DEF_ADJUSTVALUE_MAX; i++)
				{
					set.ubAdjustValueDataForSW[i] = adjust_value.ubAdjustValueDataForSW[i];
					set.ubAdjustValueTempDataForSW[i] = adjust_value.ubAdjustValueTempDataForSW[i];
				}
				return set;
			}
			array<VGame::CLR::Dump::GameInfoLine>^ _GetGameInfoLine(const GAMEINFOLINE info[9])
			{
				auto set = gcnew array<VGame::CLR::Dump::GameInfoLine>(9);
				for (size_t i = 0; i < 9; i++)
				{
					auto line = VGame::CLR::Dump::GameInfoLine();

					line.ubAct = gcnew array<array<UBYTE>^>(2);
					line.ubAct[0] = gcnew array<UBYTE>(5);
					line.ubAct[1] = gcnew array<UBYTE>(5);
					line.ubSym = gcnew array<UBYTE>(5);
					line.ulOdds = gcnew array<ULONG>(2);
					line.ulWinNum = gcnew array<ULONG>(2);
					line.ulWinSym = gcnew array<ULONG>(2);

					line.ubAct[0][0] = info[i].ubAct[0][0];
					line.ubAct[0][1] = info[i].ubAct[0][1];
					line.ubAct[0][2] = info[i].ubAct[0][2];
					line.ubAct[0][3] = info[i].ubAct[0][3];
					line.ubAct[0][4] = info[i].ubAct[0][4];

					line.ubAct[1][0] = info[i].ubAct[1][0];
					line.ubAct[1][1] = info[i].ubAct[1][1];
					line.ubAct[1][2] = info[i].ubAct[1][2];
					line.ubAct[1][3] = info[i].ubAct[1][3];
					line.ubAct[1][4] = info[i].ubAct[1][4];

					line.ubSym[0] = info[i].ubSym[0]; 
					line.ubSym[1] = info[i].ubSym[1];
					line.ubSym[2] = info[i].ubSym[2];
					line.ubSym[3] = info[i].ubSym[3];
					line.ubSym[4] = info[i].ubSym[4];

					line.ulOdds[0] = info[i].ulOdds[0];
					line.ulOdds[1] = info[i].ulOdds[1];

					line.ulWinNum[0] = info[i].ulWinNum[0];
					line.ulWinNum[1] = info[i].ulWinNum[1];

					line.ulWinSym[0] = info[i].ulWinSym[0];
					line.ulWinSym[1] = info[i].ulWinSym[1];


					set[i] = line;
				}
				
				return set;
			}


			void WheelDumper::_SetAdjustValue(VGame::Native::AdjustValue& adjust_value, const VGame::CLR::Dump::AdjustValueSet% set) const
			{
				CSArrayToArray<UBYTE, DEF_ADJUSTVALUE_MAX >(adjust_value.ubAdjustValueDataForSW, set.ubAdjustValueDataForSW);
				CSArrayToArray<UBYTE, DEF_ADJUSTVALUE_MAX >(adjust_value.ubAdjustValueTempDataForSW, set.ubAdjustValueTempDataForSW);
				
			}
			void _SetGAMEINFOLINE(GAMEINFOLINE& dest , const VGame::CLR::Dump::GameInfoLine% src)
			{
				
				CSArrayToArray<UBYTE ,5 >(dest.ubAct[0], src.ubAct[0]);
				CSArrayToArray<UBYTE ,5>(dest.ubAct[1], src.ubAct[1]);
				CSArrayToArray<UBYTE, 5>(dest.ubSym, src.ubSym);
				CSArrayToArray<ULONG, 2>(dest.ulOdds, src.ulOdds);
				CSArrayToArray<ULONG, 2>(dest.ulWinNum, src.ulWinNum);
				CSArrayToArray<ULONG, 2>(dest.ulWinSym, src.ulWinSym);								
			}
			void _SetGameInfo(GAMEINFO& info , const VGame::CLR::Dump::GameInfo% src)
			{
				CSArrayToArray<GAMEINFOLINE , 9 , VGame::CLR::Dump::GameInfoLine >(info.stcLine , src.stcLine , _SetGAMEINFOLINE );
				info.ulAllSameOdds = src.ulAllSameOdds;
				info.ulAllSameSym = src.ulAllSameSym;
				info.ulBonusType = src.ulBonusType;
				info.ulBonusValue = src.ulBonusValue;
				info.ulBonusWin = src.ulBonusWin;
				info.ulFever1Odds = src.ulFever1Odds;
				info.ulFever2Odds = src.ulFever2Odds;
				info.ulFever3Odds = src.ulFever3Odds;
				info.ulFeverNowLife = src.ulFeverNowLife;
				info.ulFeverSetLife = src.ulFeverSetLife;
				info.ulFeverType = src.ulFeverType;
				info.ulFreeNowLife = src.ulFreeNowLife;
				info.ulFreeSetLife = src.ulFreeSetLife;
				info.ulFreeType = src.ulFreeType;

				
			}
			VGame::CLR::Dump::GameInfo _GetGameInfo(const GAMEINFO& info)
			{
				auto set = VGame::CLR::Dump::GameInfo();

				set.ulAllSameOdds = info.ulAllSameOdds;
				set.ulAllSameSym = info.ulAllSameSym;
				set.ulFeverSetLife = info.ulFeverSetLife;
				set.ulFeverNowLife = info.ulFeverNowLife;
				set.ulFeverType = info.ulFeverType;
				set.ulFever1Odds = info.ulFever1Odds;
				set.ulFever2Odds = info.ulFever2Odds;
				set.ulFever3Odds = info.ulFever3Odds;
				set.ulFreeSetLife = info.ulFreeSetLife;
				set.ulFreeNowLife = info.ulFreeNowLife;
				set.ulFreeType = info.ulFreeType;
				set.ulBonusType = info.ulBonusType;
				set.ulBonusWin = info.ulBonusWin;
				set.ulBonusValue = info.ulBonusValue;

				set.stcLine = _GetGameInfoLine(info.stcLine);

				return set;
			}


			array<VGame::CLR::Dump::RecordRecordEventWin>^ _DumpRecordEventWin(const RECORD_EVENT_WIN record[100])
			{
				auto set = gcnew array<VGame::CLR::Dump::RecordRecordEventWin>(100);
				for (size_t i1 = 0; i1 < 100; i1++)
				{
					set[i1].ulWin = record[i1].ulWin;
					set[i1].ubStr = gcnew array<UBYTE>(DEF_RECORD_EVENT_STR_LEN);

					for (size_t i2 = 0; i2 < DEF_RECORD_EVENT_STR_LEN; i2++)
					{
						set[i1].ubStr[i2] = record[i1].ubStr[i2];
					}
				}
				return set;
			}

			VGame::CLR::Dump::RecordRecordFieldSet _DumpRecord(const RECORD& record)
			{
				auto val = VGame::CLR::Dump::RecordRecordFieldSet();
				val.dlCurTotal= record.dlCurTotal;
				val.dlLasTotal = record.dlLasTotal;
				val.dlHisTotal = record.dlHisTotal;
				return val;
			}

			System::Collections::Generic::Dictionary<VGame::CLR::Dump::__RECORD_DATA__, VGame::CLR::Dump::RecordRecordFieldSet>^ _DumpRecordDataSet(const RECORD records[DEF_RECORD_DATA_MAX])
			{
				auto recordDatas = System::Enum::GetValues(VGame::CLR::Dump::__RECORD_DATA__::typeid);
				auto recordDataSet = gcnew System::Collections::Generic::Dictionary<VGame::CLR::Dump::__RECORD_DATA__, VGame::CLR::Dump::RecordRecordFieldSet>();

				int recordDataIndex = 0;
				for each (VGame::CLR::Dump::__RECORD_DATA__ recordData in recordDatas)
				{				
					recordDataSet[recordData] = _DumpRecord(records[recordDataIndex]);										
					recordDataIndex++;
				}

				return recordDataSet;
			}

			

			void SetRecord(RECORD& dest , const VGame::CLR::Dump::RecordRecordFieldSet% src)
			{
				dest.dlCurTotal = src.dlCurTotal;
				dest.dlHisTotal = src.dlHisTotal;
				dest.dlLasTotal = src.dlLasTotal;
			}

			void _SetRECORD_EVENT_WIN(RECORD_EVENT_WIN & dest,const VGame::CLR::Dump::RecordRecordEventWin% src)
			{
				
				CSArrayToArray<UBYTE , DEF_RECORD_EVENT_STR_LEN>(dest.ubStr , src.ubStr);
				dest.ulWin = src.ulWin;				
			}
			void WheelDumper::_SetRecord(VGame::Native::Record& record, const VGame::CLR::Dump::RecordFieldSet% set) const
			{
				
				for (size_t i = 0; i < DEF_RECORD_PLR_MAX; i++)
				{
					auto data2 = set.stcRecordData[(VGame::CLR::Dump::__RECORD_PLR__)i];
					for (size_t j = 0; j < DEF_RECORD_DATA_MAX; j++)
					{
						auto data1 = record.stcRecordData[i][j];
						auto data3 = data2[(VGame::CLR::Dump::__RECORD_DATA__)j];

						SetRecord(data1 , data3);
					}
				}

				for (size_t j = 0; j < DEF_RECORD_DATA_MAX; j++)
				{
					auto data1 = record.stcRecordSymbolGift[j];
					auto data3 = set.stcRecordSymbolGift[(VGame::CLR::Dump::__RECORD_DATA__)j];

					SetRecord(data1, data3);
				}
					
				auto dest = record.stcRecordEvent_Win;
				auto src = set.stcRecordEvent_Win;

				CSArrayToArray<RECORD_EVENT_WIN, 100, VGame::CLR::Dump::RecordRecordEventWin>(dest ,src , _SetRECORD_EVENT_WIN );

			}

			

			VGame::CLR::Dump::RecordFieldSet WheelDumper::_GetRecord(const VGame::Native::Record& record) const
			{
				auto set = VGame::CLR::Dump::RecordFieldSet();
				set.stcRecordData = gcnew System::Collections::Generic::Dictionary<VGame::CLR::Dump::__RECORD_PLR__, System::Collections::Generic::Dictionary<VGame::CLR::Dump::__RECORD_DATA__, VGame::CLR::Dump::RecordRecordFieldSet>^>();
				
				auto recordPlrs = System::Enum::GetValues(VGame::CLR::Dump::__RECORD_PLR__::typeid);
				
				
				int recordPlrIndex = 0;
				for each (VGame::CLR::Dump::__RECORD_PLR__ recordPlr in recordPlrs)
				{
					auto recordDatas = record.stcRecordData[recordPlrIndex];
					auto recordDataSet = _DumpRecordDataSet(recordDatas);
					recordPlrIndex++;
					set.stcRecordData->Add(recordPlr, recordDataSet);
				}				

				set.stcRecordSymbolGift = _DumpRecordDataSet(record.stcRecordSymbolGift);

				set.stcRecordEvent_Win = _DumpRecordEventWin(record.stcRecordEvent_Win);
				return set;
			}

			WheelDumper::WheelDumper(VGame::Native::WheelImplement& wheel):
				_Wheel(wheel)
			{
				
			}

			
			void SetBet(BETLINE & dest,const VGame::CLR::Dump::BetLine% set)
			{
				
				dest.slBet = set.slBet;
				dest.slLine = set.slLine;				
			}

			void WheelDumper::_SetSlave(VGame::Native::Slave& slave,const VGame::CLR::Dump::SlaveSet% set)const
			{
				slave.slWinValue = set.slWinValue;
				slave.slWupWinValue = set.slWupWinValue;
				CSArrayToArray<BETLINE, DEF_BET_MAXID , VGame::CLR::Dump::BetLine>(slave.stcBet , set.stcBet , SetBet );				
			}
			void WheelDumper::_SetWupChance(WUPCHANCE_BUF& wupchance_buf, const VGame::CLR::Dump::WupChanceBuf% set)const
			{
				wupchance_buf.Buffer.slCount = set.Buffer.slCount;
				wupchance_buf.Buffer.slValue = set.Buffer.slValue;
				wupchance_buf.Buffer.ulLife = set.Buffer.ulLife;

				wupchance_buf.ubData = set.ubData;
				CSArrayToArray<UBYTE ,10>(wupchance_buf.ubDemoHistory , set.ubDemoHistory);				
				wupchance_buf.ubDemoTime = set.ubDemoTime;
				wupchance_buf.ubGuess = set.ubGuess;
				CSArrayToArray<UBYTE, 10>(wupchance_buf.ubHistory, set.ubHistory);
				wupchance_buf.ulAsnKill = set.ulAsnKill;
				wupchance_buf.ulAsnLose = set.ulAsnLose;
				CSArrayToArray<ULONG, 4>(wupchance_buf.ulJKTimes, set.ulJKTimes);
				wupchance_buf.ulPlayTimes = set.ulPlayTimes;
				wupchance_buf.ulRate = set.ulRate;
				CSArrayToArray<ULONG, 7>(wupchance_buf.ulRecAsnTimes, set.ulRecAsnTimes);
				CSArrayToArray<ULONG, 7>(wupchance_buf.ulRecAsnValue, set.ulRecAsnValue);
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecInsure, set.ulRecInsure);
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecKill, set.ulRecKill);				
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecLimit, set.ulRecLimit);
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecLose, set.ulRecLose);
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecOver[0], set.ulRecOver[0]);
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecOver[1], set.ulRecOver[1]);
				CSArrayToArray<ULONG, 2>(wupchance_buf.ulRecPass, set.ulRecPass);
				CSArrayToArray<ULONG, 6>(wupchance_buf.ulRecTimes, set.ulRecTimes);
				
			}

			void SetReel(REEL& dest , const VGame::CLR::Dump::Reel% reel)
			{
				
				dest.swCount = reel.swCount;
				dest.swMoveY = reel.swMoveY;
				dest.swSpeed = reel.swSpeed;
				dest.ubAdjustIndex = reel.ubAdjustIndex;
				dest.ubAsnState = reel.ubAsnState;
				//CSArrayToArray<UBYTE, DEF_REEL_MAX_SYM>(dest.ubReelData , reel.ubReelData);
				CSArrayToArray<UBYTE, DEF_REEL_MAX_SHOW>(dest.ubSaveID, reel.ubSaveID);
				CSArrayToArray<UBYTE, DEF_REEL_MAX_SHOW>(dest.ubShowID, reel.ubShowID);
				CSArrayToArray<UBYTE, DEF_REEL_MAX_SHOW>(dest.ubStopID, reel.ubStopID);
				dest.ubState = reel.ubState;
				dest.uwGetIndex = reel.uwGetIndex;				
			}
			void WheelDumper::_SetReel(VGame::Native::Reel& reel,const VGame::CLR::Dump::ReelSet% set)const
			{
				CSArrayToArray<REEL, DEF_REEL_MAX , VGame::CLR::Dump::Reel>(reel.stcReelData , set.stcReelData , SetReel );
				CSArrayToArray<REEL, DEF_FEVER_REEL_MAX, VGame::CLR::Dump::Reel>(reel.stcReelFeverData, set.stcReelFeverData, SetReel);
				reel.ulReelNeedSoundEft = set.ulReelNeedSoundEft;				
			}

			void WheelDumper::_SetMaster(MASTERINFO& master, const VGame::CLR::Dump::MasterInfo% set)const
			{
				master.ubRunFlag = set.ubRunFlag;
				master.ubDemoFlag = set.ubDemoFlag;
				master.ulState = set.ulState;
				master.ulIndex = set.ulIndex;
				master.ulCount = set.ulCount;
				master.ulEftCnt = set.ulEftCnt;
				master.ulMapTime = set.ulMapTime;
				master.ulTestCount = set.ulTestCount;
				master.ulSceneState = set.ulSceneState; //场景状态，0主游
				master.ulTemp = set.ulTemp;   //暂存
				master.ulAllCount = set.ulAllCount; //
				master.ulAutoKeyState = set.ulAutoKeyState;//0正常玩，1，第
				master.ulAutoKeyGameState = set.ulAutoKeyGameState; //启动时的自
				master.ulSaveAutoKeyState = set.ulSaveAutoKeyState;//自动FREE游
				CSArrayToArray<ULONG, 3>(master.ulBackUp , set.ulBackUp);
			}
			void WheelDumper::_SetChance(VGame::Native::Chance& chance, const VGame::CLR::Dump::ChanceSet% set)const
			{
				
				DumpChance(chance.stcChance , set.stcChance);
				DumpFeverChance(chance.stcFeverChance , set.stcFeverChance);
			}
			void WheelDumper::Import(const VGame::CLR::Dump::WheelFieldSet% set)
			{
				auto& wheel = _Wheel;
				
				
				wheel.slFeverWin = set.slFeverWin;
				wheel.slFreeWin = set.slFreeWin;
				wheel.ulPlayTimes = set.ulPlayTimes;
				wheel.ulWinTimes = set.ulWinTimes;
				wheel.dlPlayTotal = set.dlPlayTotal;
				wheel.dlWinTotal = set.dlWinTotal;
				wheel.dlRunTime = set.dlRunTime;

				wheel.ulSwitch = set.ulSwitch;
				wheel.ulRecCycle = set.ulRecCycle;

				wheel.slWupBet = set.slWupBet;
				wheel.ulWupTime = set.ulWupTime;
				wheel.ulWupPlayTimes = set.ulWupPlayTimes;

				wheel.ulWupCondi1 = set.ulWupCondi1;
				wheel.ulWupCondi2 = set.ulWupCondi2;

				_SetRecord(wheel._Record , set.Record);
				_SetGameInfo(wheel.stcGameInfo , set.stcGameInfo);
				_SetAdjustValue(wheel._AdjustValue , set.AdjustValue);
				_SetWupChance(wheel._WupChance.stcWupChance, set.stcWupChance);
				_SetSlave(wheel._Slave , set.Slave);
				_SetMaster(wheel._Master.stcMaster , set.stcMaster);
				_SetReel(wheel._Reel, set.Reel);
				_SetChance(wheel._Chance , set.Chance);
			}
			VGame::CLR::Dump::WheelFieldSet WheelDumper::Export() const
			{
				auto& wheel = _Wheel;
				auto set = VGame::CLR::Dump::WheelFieldSet();
				set.slFeverWin = wheel.slFeverWin;
				set.slFreeWin = wheel.slFreeWin;
				set.ulPlayTimes = wheel.ulPlayTimes;
				set.ulWinTimes = wheel.ulWinTimes;
				set.dlPlayTotal = wheel.dlPlayTotal;
				set.dlWinTotal = wheel.dlWinTotal;
				set.dlRunTime = wheel.dlRunTime;

				set.ulSwitch = wheel.ulSwitch;
				set.ulRecCycle = wheel.ulRecCycle;

				set.slWupBet = wheel.slWupBet;
				set.ulWupTime = wheel.ulWupTime;
				set.ulWupPlayTimes = wheel.ulWupPlayTimes;

				set.ulWupCondi1 = wheel.ulWupCondi1;
				set.ulWupCondi2 = wheel.ulWupCondi2;


				set.Record = _GetRecord(wheel._Record);
				set.stcGameInfo = _GetGameInfo(wheel.stcGameInfo);
				set.AdjustValue = _GetAdjustValue(wheel._AdjustValue);
				set.stcWupChance = _GetWupChance(wheel._WupChance.stcWupChance);
				set.Slave = _GetSlave(wheel._Slave);
				set.stcMaster = _GetMaster(wheel._Master.stcMaster);
				set.Reel = _GetReel(wheel._Reel);
				set.Chance = _GetChance(wheel._Chance);


				return set;

			}
		}
		
	}

}


