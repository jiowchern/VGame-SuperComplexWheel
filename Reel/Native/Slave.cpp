#include "Slave.h"

VGame::Native::Slave::Slave()
{
	memset(stcBet, 0, sizeof(BETLINE) * DEF_BET_MAXID);
}

VGame::Native::Slave::~Slave()
{
}

SLONG VGame::Native::Slave::ReadBet()
{	
	return stcBet[DEF_BET_NOW].slBet;
}

void VGame::Native::Slave::BetSet(SLONG val)
{
	stcBet[DEF_BET_NOW].slBet = val;
}

SLONG VGame::Native::Slave::ReadTotalBet(void)
{
	return (stcBet[DEF_BET_NOW].slLine * stcBet[DEF_BET_NOW].slBet);
}

SLONG VGame::Native::Slave::ReadLine(void)
{
	return (stcBet[DEF_BET_NOW].slLine);
}

void VGame::Native::Slave::WinSet(SLONG slValue)
{
	slWinValue = slValue;
}

void VGame::Native::Slave::WinAdd(SLONG slValue)
{
	slWinValue += slValue;
}

SLONG VGame::Native::Slave::WinRead(void)
{
	return slWinValue;
}

void VGame::Native::Slave::WupWinSet(SLONG slValue)
{
	slWupWinValue = slValue;
}

SLONG VGame::Native::Slave::WupWinRead(void)
{
	return (slWupWinValue);
}

void VGame::Native::Slave::SetLine(SLONG slLine)
{
	stcBet[DEF_BET_NOW].slLine = slLine;
}

