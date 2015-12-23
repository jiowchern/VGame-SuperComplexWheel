#pragma once
#include "..\Source\common.h"
NAMESPACE_NATIVE_BEGIN
class Reel
{

	friend class VGame::Native::Dump::WheelDumper;
	REEL stcReelData[DEF_REEL_MAX];
	REEL stcReelFeverData[DEF_FEVER_REEL_MAX];
	ULONG ulReelNeedSoundEft;
	GAMEINFO&		stcGameInfo;
public:
		Reel	(GAMEINFO& info);
		~Reel	();

	void	Initial(SLONG slReel, UBYTE *ubReelData);
	void	SaveData(SLONG slReel);
	void	SetRandData(SLONG slReel);
	void	StopDataToShowData(SLONG slReel);
	void	LoadStopData(SLONG slReel);
	void	SaveStopData(SLONG slReel);
	UBYTE 	GetData(SLONG slReel)const;
	void	SetStopData(SLONG slReel, UBYTE ubData);

	void	StartRun(SLONG slReel);

	void	AllNowStopRun();

	void	FeverSetStopData	(SLONG slReel, UBYTE ubData);

	UBYTE	GetFerverStopID		(SLONG slReel, UBYTE ubData);

	void	FeverInitial		(SLONG slReel, UBYTE *ubReelData);

	void	FeverSaveData		(SLONG slReel);

	void	FeverStartRun		(SLONG slReel);

	void	FeverStopRun		(SLONG slReel);
};
NAMESPACE_NATIVE_END
