#pragma once
#include "..\Source\common.h"
namespace VGame
{
	namespace Native
	{
		class Slave
		{
			friend class VGame::Native::Dump::WheelDumper;
			BETLINE stcBet[DEF_BET_MAXID];
			SLONG	slWinValue;
			SLONG	slWupWinValue	;
		public:
					Slave			();
					~Slave			();
			SLONG	ReadBet			();
			void	BetSet			(SLONG val);
			SLONG	ReadTotalBet	(void);			
			SLONG	ReadLine		(void);
			void	WinSet			(SLONG slValue);
			void	WinAdd			(SLONG slValue);
			SLONG	WinRead			(void);

			void	WupWinSet		(SLONG slValue);
			SLONG	WupWinRead		(void);

			void	SetLine			(SLONG slLine);
		};
	}
}
