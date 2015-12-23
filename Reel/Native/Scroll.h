#pragma once

#include "..\Source\common.h"

NAMESPACE_NATIVE_BEGIN


class GameCheck;
class Reel;
class Scroll
{	
	GameCheck&	_GameCheck;
	Reel&		_Reel;
public:
			Scroll			(Reel& reel, GameCheck& check);
			~Scroll			();

	void	Reset			();

	UBYTE 	GetData			(SLONG slReel)const;
	void	SaveStopData	(void);
	void	LoadStopData	(void);
	void	SetStopData		(ULONG ulReel, UBYTE ubData);

	void	SetRandData		(ULONG ulReel);

	void	StartAllRun		(void);
	void	FeverReset		(void);
	void	FeverStartAllRun(void);
	void	FeverAllStop	(void);
};

NAMESPACE_NATIVE_END
