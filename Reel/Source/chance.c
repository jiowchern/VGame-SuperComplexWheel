#define DEF_CHANCE_C
#include "common.h"

#define FILE_NAME  "CHANCE.C"

UBYTE H_ubVersionMemString[32] ;
ULONG H_ulVersionValue ;

//ULONG const ulFeverGameWinOdds[5] = {5,4,3,2,1};



BONUSINFO const stcChanceBonusGameInfoData[3] = 
{// {ulAsnNum,  ulGame } , 
    { 3 ,       2300 } ,
    { 4 ,       1139 } ,
    { 5 ,       425  } ,
}; 


BONUSINFO const stcChanceFreeGameInfoData[3] = 
{// {ulAsnNum,  ulGame } , 
    { 3 ,       36 } ,
    { 4 ,       20 } ,
    { 5 ,       8 } ,
}; 

FEVERINFO const stcChanceFeverGameInfoData[12] = 
{// {ulAsnNum, ulGame ,ulMinOdds, ulMaxOdds  } , 
    {   3 ,    1596  ,  3  ,       6	  } ,
    {   3 ,    1428  ,  4  ,       10	  } ,
    {   3 ,    1260  ,  7  ,       19	  } ,
    {   3 ,    1092   , 15 ,       30	  } ,
    {   4 ,    1140  ,  4  ,       10	  } ,
    {   4 ,    1020  ,  7  ,       19	  } ,
    {   4 ,    900   ,  15 ,       30	  } ,
    {   4 ,    780   ,  25 ,       45	  } ,
    {   5 ,    874   ,  7  ,       19	  } ,
    {   5 ,    782   ,  15 ,       30	  } ,
    {   5 ,    690   ,  25 ,       45	  } ,
    {   5 ,    598   ,  30 ,       60	  } ,
}; 


VIRTUALINFO const stcChanceVirtualInfoData1[5] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_05 ,    300 ,     6499 } ,
    { DEF_SYMBOL_06 ,    240 ,     8124 } ,
    { DEF_SYMBOL_07 ,    150 ,     12998} ,
    { DEF_SYMBOL_08 ,    120 ,     16248} ,
    { DEF_SYMBOL_09 ,    90  ,     21667} ,
};    

VIRTUALINFO const stcChanceVirtualInfoData2[5] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_00 ,    4500 ,     4405 } ,
    { DEF_SYMBOL_01 ,    3000 ,     6608 } ,
    { DEF_SYMBOL_02 ,    2400 ,     8260 } ,
    { DEF_SYMBOL_03 ,    1500 ,     13217} ,
    { DEF_SYMBOL_04 ,    600  ,     33046} ,
};  

VIRTUALINFO const stcChanceVirtualInfoData3[5] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_05 ,    200 ,     6499 } ,
    { DEF_SYMBOL_06 ,    160 ,     8124 } ,
    { DEF_SYMBOL_07 ,    100 ,     12998} ,
    { DEF_SYMBOL_08 ,    80  ,     16248} ,
    { DEF_SYMBOL_09 ,    60  ,     21667} ,
};

VIRTUALINFO const stcChanceVirtualInfoData4[5] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_00 ,    3000 ,     6405 } ,
    { DEF_SYMBOL_01 ,    2000 ,     7608 } ,
    { DEF_SYMBOL_02 ,    1600 ,     8260 } ,
    { DEF_SYMBOL_03 ,    1000 ,     12217} ,
    { DEF_SYMBOL_04 ,    400  ,     31046} ,
};

VIRTUALINFO const stcChanceVirtualInfoData5[6] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_05 ,    300 ,     6154 } ,
    { DEF_SYMBOL_06 ,    240 ,     7693 } ,
    { DEF_SYMBOL_07 ,    150 ,     12309} ,
    { DEF_SYMBOL_08 ,    120 ,     15386} ,
    { DEF_SYMBOL_09 ,    90  ,     20515} ,
    { DEF_SYMBOL_FREE,   177 ,     3479 } ,
};

VIRTUALINFO const stcChanceVirtualInfoData6[6] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_00 ,    4500 ,     3386 } ,
    { DEF_SYMBOL_01 ,    3000 ,     5079 } ,
    { DEF_SYMBOL_02 ,    2400 ,     6349 } ,
    { DEF_SYMBOL_03 ,    1500 ,     10159} ,
    { DEF_SYMBOL_04 ,    600  ,     25398} ,
    { DEF_SYMBOL_FEVER,  515  ,     15165 } ,
};

VIRTUALINFO const stcChanceVirtualInfoData7[6] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_05 ,    200 ,     5782 } ,
    { DEF_SYMBOL_06 ,    160 ,     7228 } ,
    { DEF_SYMBOL_07 ,    100 ,     11565} ,
    { DEF_SYMBOL_08 ,    80  ,     14456} ,
    { DEF_SYMBOL_09 ,    60  ,     19275} ,
    { DEF_SYMBOL_WILD,   160 ,     7230 } ,
};



VIRTUALINFO const stcChanceVirtualInfoData8[5] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_00 ,    3000 ,     11405 } ,
    { DEF_SYMBOL_01 ,    2000 ,     10608 } ,
    { DEF_SYMBOL_02 ,    1600 ,     9260 } ,
    { DEF_SYMBOL_03 ,    1000 ,     11217} ,
    { DEF_SYMBOL_04 ,    400  ,     23046} ,
};



VIRTUALINFO const stcChanceFeverInfoData1[5] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_01 ,    5,      28 } ,
    { DEF_SYMBOL_02 ,    4 ,     25 } ,
    { DEF_SYMBOL_03 ,    3 ,     20 } ,
    { DEF_SYMBOL_04 ,    2 ,     15 } ,
    { DEF_SYMBOL_05 ,    1 ,     12} ,
};


VIRTUALINFO const stcChanceFeverInfoData2[4] = 
{// { ulAsnGift,     ulTopValue , ulGame } ,     
    { DEF_SYMBOL_02 ,    4 ,     35 } ,
    { DEF_SYMBOL_03 ,    3 ,     30 } ,
    { DEF_SYMBOL_04 ,    2 ,     20 } ,
    { DEF_SYMBOL_05 ,    1 ,     15} ,
};

VIRTUALINFO const stcChanceFeverInfoData3[3] = 
{// { ulAsnGift,     ulTopValue , ulGame } ,      
    { DEF_SYMBOL_03 ,    3 ,     55 } ,
    { DEF_SYMBOL_04 ,    2 ,     30 } ,
    { DEF_SYMBOL_05 ,    1 ,     15} ,
};

VIRTUALINFO const stcChanceFeverInfoData4[2] = 
{// { ulAsnGift,     ulTopValue , ulGame } , 
    { DEF_SYMBOL_04 ,    2 ,     75 } ,
    { DEF_SYMBOL_05 ,    1 ,     25 } ,
};





//求表格的那组数据
ULONG ulChance_TakeValueNum( VIRTUALINFO *stcVirtual,ULONG ulValue,ULONG ulSize )
{
	ULONG	i ;	
	if ( ulSize >= 100 )
	{
		return 0;
	}
	for(i=0;i<ulSize;i++)
	{
		if( ulValue < stcVirtual[i].ulGate ) break ;
		ulValue -= stcVirtual[i].ulGate ;
	}	
	if(i>=ulSize)
	{
		i = ulSize-1;	
	}
	return 	i;
}

//求多次随机最大与最小范围的最小值
ULONG ulChance_TakeMinValue(ULONG ulMin,ULONG ulMax,ULONG ulCount)
{
	ULONG ulValue,ulTemp;
	SLONG slLoop;
	ulValue = ulMin + ulRand_ReadMod(ulMax-ulMin+1);
	if(ulCount>0)
	{
		for ( slLoop = 0 ; slLoop < (ulCount-1)  ; slLoop ++ )
		{
			ulTemp =  ulMin + ulRand_ReadMod(ulMax-ulMin+1);
			if(ulTemp<ulValue)	
			{
				ulValue = ulTemp;
			}		
		}
	}	
	return ulValue;
		
		
	
}
	

#define DEF_GAME_NUM  65536
//设置单个虚拟触顶值
void  vChance_VirtualTopValue( ULONG ulLoc )
{
	ULONG ulNum,ulRand,ulBet;
	if(ulLoc<8)
	{
		ulRand = ulRand_ReadMod(DEF_GAME_NUM) ;
		ulBet = mGame_ReadMaxBet();
		switch ( ulLoc )	
		{
			 case 1	: 			 	
				ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData2[0],ulRand,5);
				stcChance.slVirtualBufTopValue[1] = stcChanceVirtualInfoData2[ulNum].ulTopValue*ulBet;
				stcChance.ulVirtualBufAsnGift[1] = stcChanceVirtualInfoData2[ulNum].ulAsnGift;
				stcChance.ulVirtualBufAsnGift[1] |= 0x100;				
				break ;  
			 case 2	: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData3[0],ulRand,5);
				stcChance.slVirtualBufTopValue[2] = stcChanceVirtualInfoData3[ulNum].ulTopValue*ulBet*9;
				stcChance.ulVirtualBufAsnGift[2] = stcChanceVirtualInfoData3[ulNum].ulAsnGift;
				stcChance.ulVirtualBufAsnGift[2] |= 0x200;
			 	break ;
			 case 3	: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData4[0],ulRand,5);
			 	//ulNum = 0;
				stcChance.slVirtualBufTopValue[3] = stcChanceVirtualInfoData4[ulNum].ulTopValue*ulBet*9;
				stcChance.ulVirtualBufAsnGift[3] = stcChanceVirtualInfoData4[ulNum].ulAsnGift;
				stcChance.ulVirtualBufAsnGift[3] |= 0x200;
			 	break ;
			 case 4	: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData5[0],ulRand,6);
				stcChance.slVirtualBufTopValue[4] = stcChanceVirtualInfoData5[ulNum].ulTopValue*ulBet;
				stcChance.ulVirtualBufAsnGift[4] = stcChanceVirtualInfoData5[ulNum].ulAsnGift;
				if(ulNum !=5 )
				{
					stcChance.ulVirtualBufAsnGift[4] |= 0x100;	
				}	
			 	break ;
			 case 5	: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData6[0],ulRand,6);
				stcChance.slVirtualBufTopValue[5] = stcChanceVirtualInfoData6[ulNum].ulTopValue*ulBet;
				stcChance.ulVirtualBufAsnGift[5] = stcChanceVirtualInfoData6[ulNum].ulAsnGift;
				if(ulNum !=5 )
				{
					stcChance.ulVirtualBufAsnGift[5] |= 0x100;	
				}	
			 	break ;
			 case 6	: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData7[0],ulRand,6);
				stcChance.slVirtualBufTopValue[6] = stcChanceVirtualInfoData7[ulNum].ulTopValue*ulBet*9;
				stcChance.ulVirtualBufAsnGift[6] = stcChanceVirtualInfoData7[ulNum].ulAsnGift; 
				if(ulNum !=5 )
				{
					stcChance.ulVirtualBufAsnGift[6] |= 0x200;	
				}	
			 	break ;
			 case 7	: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData8[0],ulRand,5);
			 	//ulNum = 1;
				stcChance.slVirtualBufTopValue[7] = stcChanceVirtualInfoData8[ulNum].ulTopValue*ulBet*9;
				stcChance.ulVirtualBufAsnGift[7] = stcChanceVirtualInfoData8[ulNum].ulAsnGift;	
				stcChance.ulVirtualBufAsnGift[7] |= 0x200;
			 	break ;						
			 default: 
			 	ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceVirtualInfoData1[0],ulRand,5);
				stcChance.slVirtualBufTopValue[0] = stcChanceVirtualInfoData1[ulNum].ulTopValue*ulBet;
				stcChance.ulVirtualBufAsnGift[0] = stcChanceVirtualInfoData1[ulNum].ulAsnGift; 
				stcChance.ulVirtualBufAsnGift[0] |= 0x100;				
			 	break ;  
		}
	}	
} 


//设置全部虚拟触顶值
void  vChance_VirtualAllTopValue( void )
{
	ULONG i;
	for(i=0;i<8;i++)
	{
		vChance_VirtualTopValue(i);	
		stcChance.VirtualBuffer[i].slValue = 0;	//虚拟Buffer清零
	}

} 

#ifdef DEF_CHANCE_FOR_UART_SLAVE
// 虚拟Buffer累积率
ULONG const ulSpecVirtualRate[8] ={150,	150,	150,	150,	400,	350,	400,	50 };
#else
ULONG const ulSpecVirtualRate[8] ={150,	150,	150,	150,	400,	400,	400,	50 };
#endif

//累加虚拟BUFFER
void vChance_VirtualBufAdd(ULONG ulBet )
{
	ULONG i,ulRate[8]; 	
	ULONG ulValue;
	SLONG slBufValue;
	slBufValue  = stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue;
	ulValue =mGame_ReadMaxBet() * 9;
	for(i=0;i<8;i++)
	{		
		ulRate[i]=ulSpecVirtualRate[i];
	}	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	if(slBufValue>800*ulValue)
	#else
	if(slBufValue>4500*ulValue)
	#endif	
	{
		#ifdef DEF_FIX_CHANCE_BUG_20150126
		for(i=0;i<4;i++)
		{		
			ulRate[i] = 1000;
			ulRate[i+4] = 1000;
		}	
		#endif
	}	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	else if(slBufValue>650*ulValue)
	#else
	else if(slBufValue>4000*ulValue)
	#endif	
	{
		for(i=1;i<4;i++)
		{		
			ulRate[i] *=2;
			ulRate[i+4] *=2;
		}	
	}
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	else if(slBufValue>500*ulValue)
	#else
	else if(slBufValue>3500*ulValue)
	#endif	
	{
		for(i=2;i<4;i++)
		{		
			ulRate[i] *=2;
			ulRate[i+4] *=2;
		}	
	}
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	#else
	else if(slBufValue>3000*ulValue)
	{
		for(i=3;i<4;i++)
		{		
			ulRate[i] *=2;
			ulRate[i+4] *=2;
		}	
	}
	#endif	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	ulRate[3] = 0 ;
	ulRate[7] = 0 ;
	#endif
	for(i=0;i<8;i++)
	{
		stcChance.ulVirtualRate[i] = ulRate[i] ; // REX
		slBuffer_AddRate( &stcChance.VirtualBuffer[i] , ulBet , ulRate[i] ) ;	//虚拟
		slBuffer_AddRate( &stcChance.SpecBuffer[i] , ulBet , stcChance.ulSpecRate[i] ) ;	//实际
	}
				
}



//虚拟Buffer的做法
void  vChance_VirtualProcess(void)
{
	SLONG slLoop,slBufValue,slVirtBufValue;
	ULONG ulRand,ulAsnGift,ulValue;

	#ifdef DEF_TEST_ONLY_NATURE
	return ;
	#endif
	
	/*
	if( stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue > 0 )
	{
		stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue -= 100000 ; // ForTest
	}
	*/
	slBufValue = stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue;	
	stcChance.ulAsnState = 0;   //清除强制标志
	for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
	{
		#ifdef DEF_CHANCE_FOR_UART_SLAVE
		if(( slLoop == 3 )||( slLoop == 7 )) continue ;
		#endif
		
		slVirtBufValue  = stcChance.VirtualBuffer[slLoop].slValue;
		if(slVirtBufValue>=stcChance.slVirtualBufTopValue[slLoop])
		{
			stcChance.VirtualBuffer[slLoop].slValue = 0;	//虚拟Buffer清零
			ulRand = ulRand_ReadMod(1000);
			if(slBufValue>stcChance.slVirtualBufTopValue[slLoop])
			{		
				if(ulRand<stcChance.ulVirtualBufGate[slLoop])
				{
					stcChance.ulRecVirAsnTimes[slLoop][0] ++ ;	
					ulAsnGift = stcChance.ulVirtualBufAsnGift[slLoop] & 0x0F;
					stcChance.ulActBuf = DEF_CHANCE_BUF_SPEC ;  
					stcChance.ulAsnGift = slLoop;            //求真实那组Buff有用到				
					if(stcChance.ulVirtualBufAsnGift[slLoop] & 0x100)
					{
						vGameAssign_Spec5Line(ulAsnGift,slLoop);	
					}	
					else if(stcChance.ulVirtualBufAsnGift[slLoop] & 0x200)
					{
						vGameAssign_AllSame(ulAsnGift);		
					}	
					else
					{
						stcChance.ulAsnState = 1;                //说明虚拟强制
						vGameAssign_MinSpecialSymbol(ulAsnGift,5);	
						if(ulAsnGift==DEF_SYMBOL_FREE)       
						{
							ulValue = stcChanceVirtualInfoData5[5].ulTopValue*slSlave_ReadBet();
							stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue -= ulValue ;
							stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue += ulValue ;
							stcChance.ulRecSpecValue[0] += ulValue ; //统计给FREE分数
							stcChance.ulActBuf = DEF_CHANCE_BUF_FREE ; 
						}	
						if(ulAsnGift==DEF_SYMBOL_FEVER)       
						{
							ulValue = stcChanceVirtualInfoData6[5].ulTopValue*slSlave_ReadBet();
							stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue -= ulValue ;
							stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue += ulValue ;								
							stcChance.ulRecSpecValue[1] += ulValue ; //统计给FEVER分数							
							stcChance.ulActBuf = DEF_CHANCE_BUF_FEVER ;  
							stcChance.slFeverOdds = ulChance_TakeMinValue(50,80,3);//倍数
							//stcChance.slFeverOdds *= slSlave_ReadLine( ) ; // Rex 
							stcChance.ulRecFever[0] += stcChance.slFeverOdds*slSlave_ReadLine( ) ;
						}
						if(ulAsnGift==DEF_SYMBOL_WILD)       
						{
							ulValue = stcChanceVirtualInfoData7[5].ulTopValue*slSlave_ReadTotalBet();
							stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue -= ulValue;
							stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue += ulValue ;
							stcChance.ulRecSpecValue[2] += ulValue ; //统计给BONUS分数
							stcChance.ulActBuf = DEF_CHANCE_BUF_BONUS ; 	
						}
							
					}	
					vChance_VirtualTopValue(slLoop);
					break;
				}
				else
				{
					stcChance.ulRecVirAsnTimes[slLoop][2] ++ ;	
					vChance_VirtualTopValue(slLoop);
				}
			}	
			else
			{
				stcChance.ulRecVirAsnTimes[slLoop][1] ++ ;	
				vChance_VirtualTopValue(slLoop);
			}
		}	
	}
	
	
	
}
//ULONG const ulSpecVirtualGate[10] ={500,	460,	420,	380,	340,	300,	260,	220,	180,	140};
//ULONG const ulSpecBufRate[10] ={214 ,   212 ,  210 ,   208 ,   206 ,   204 ,   202 ,   200 , 198 , 196};
// 系统设定有修改的时候，必须重新设定游戏几率等相关数据
void  vChance_GameRateSet( void )
{	
	stcChance.ulRate[ DEF_CHANCE_BUF_MAIN ] 		= 655 ;
	stcChance.ulRate[ DEF_CHANCE_BUF_SPEC ] 	    = 214-(mGame_ReadGameRateLevel()%10)*2;
	stcChance.ulRate[ DEF_CHANCE_BUF_BONUS ] 		= 43 ;
	stcChance.ulRate[ DEF_CHANCE_BUF_FEVER ] 	    = 43 ;
	stcChance.ulRate[ DEF_CHANCE_BUF_FREE ] 		= 43 ;
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	// 实际总SpecBuffer累积率
	stcChance.ulRate[ DEF_CHANCE_BUF_SPEC ] 	    = 162 ;
	#endif
	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	// 触顶 Gate
	stcChance.ulVirtualBufGate[0]                   = 280;
	stcChance.ulVirtualBufGate[1]                   = 200;   
	stcChance.ulVirtualBufGate[2]                   = 140;        
	stcChance.ulVirtualBufGate[3]                   = 0;       
	stcChance.ulVirtualBufGate[4]                   = 80; 
	stcChance.ulVirtualBufGate[5]                   = 60;        
	stcChance.ulVirtualBufGate[6]                   = 40;        
	stcChance.ulVirtualBufGate[7]                   = 0;  
	#else
	stcChance.ulVirtualBufGate[0]                   = 320;
	stcChance.ulVirtualBufGate[1]                   = 240;   
	stcChance.ulVirtualBufGate[2]                   = 160;        
	stcChance.ulVirtualBufGate[3]                   = 80;       
	stcChance.ulVirtualBufGate[4]                   = 80; 
	stcChance.ulVirtualBufGate[5]                   = 60;        
	stcChance.ulVirtualBufGate[6]                   = 40;        
	stcChance.ulVirtualBufGate[7]                   = 500-(mGame_ReadGameRateLevel()%10)*40;  
	#endif

	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	// 实际累积率
	stcChance.ulSpecRate[0]            			    = 42;
	stcChance.ulSpecRate[1]            			    = 30;   
	stcChance.ulSpecRate[2]            			    = 21;        
	stcChance.ulSpecRate[3]            			    = 0;        
	stcChance.ulSpecRate[4]            			    = 32; 
	stcChance.ulSpecRate[5]            			    = 21;        
	stcChance.ulSpecRate[6]            			    = 16;        
	stcChance.ulSpecRate[7]            			    = 0;         
	#else
	stcChance.ulSpecRate[0]            			    = 45;
	stcChance.ulSpecRate[1]            			    = 33;   
	stcChance.ulSpecRate[2]            			    = 27;        
	stcChance.ulSpecRate[3]            			    = 15;        
	stcChance.ulSpecRate[4]            			    = 29; 
	stcChance.ulSpecRate[5]            			    = 22;        
	stcChance.ulSpecRate[6]            			    = 18;        
	stcChance.ulSpecRate[7]            			    = 25-(mGame_ReadGameRateLevel()%10)*2;         
	#endif
	 
	
	/*
	ULONG	i;
	for(i=0;i<DEF_CHANCE_BUFMAX;i++)
	{
		stcChance.ulRate[ i ] = stcChanceInfo[i].slGameRate[mGame_ReadRateModeLevel()][mGame_ReadGameRateLevel()] ;		
	} 
	*/


}


//虚拟觸?Gate
void  vChance_VirtualGate(void)
{
	SLONG slLoop;
	ULONG ulValue,ulBase;
	if(stcChance.ulPlayTimes>0)
	{
		stcChance.ulVirtualBufGate[0]                   = 320;
		stcChance.ulVirtualBufGate[1]                   = 240;   
		stcChance.ulVirtualBufGate[2]                   = 160;        
		stcChance.ulVirtualBufGate[3]                   = 80;       
		stcChance.ulVirtualBufGate[4]                   = 80; 
		stcChance.ulVirtualBufGate[5]                   = 60;        
		stcChance.ulVirtualBufGate[6]                   = 40;        
		stcChance.ulVirtualBufGate[7]                   = 500-(mGame_ReadGameRateLevel()%10)*40; 
		
		for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
		{	
			ulBase = 100;	
			//送出的大于等于期望值		
			if(stcChance.ulSpecValue[slLoop]>=stcChance.SpecBuffer[slLoop].slValue)
			{
				#ifdef DEF_OPEN_FAST_TEST			//快测时不屏蔽			
				#else
				stcChance.ulSpecValue[slLoop] -= stcChance.SpecBuffer[slLoop].slValue ;
				stcChance.SpecBuffer[slLoop].slValue = 0 ;
				#endif	
				ulValue = stcChance.ulSpecValue[slLoop] - stcChance.SpecBuffer[slLoop].slValue;
				if(ulValue>30*stcChance.ulBase)
				{
					ulBase = 70;						
				}	
				else if(ulValue>20*stcChance.ulBase)
				{
					ulBase = 80;						
				}
				else if(ulValue>10*stcChance.ulBase)
				{
					ulBase = 90;						
				}	
				else if(ulValue>4*stcChance.ulBase)
				{
					ulBase = 200;						
				}					
				else if(ulValue>2*stcChance.ulBase)
				{
					ulBase = 300;							
				}	
				else
				{
					ulBase = 500;		
				}					
			}
			else			
			{
				#ifdef DEF_OPEN_FAST_TEST						
				#else
				stcChance.SpecBuffer[slLoop].slValue -= stcChance.ulSpecValue[slLoop] ;
				stcChance.ulSpecValue[slLoop] = 0 ;
				#endif					
				ulBase = 500;		
			}
			stcChance.ulVirtualBufGate[slLoop] = (stcChance.ulVirtualBufGate[slLoop]*ulBase)/100; 
			if(stcChance.ulVirtualBufGate[slLoop]>1000)
			{
				stcChance.ulVirtualBufGate[slLoop] = 1000;
			}	
		}	
	}	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	stcChance.ulVirtualBufGate[3] = 0 ;
	stcChance.ulVirtualBufGate[7] = 0 ;
	#endif
}



// 有更新系统设定值的时候，处理一些相关事情，包含炒场设定
void vChance_Update( ULONG ulMode )
{	
	vChance_GameRateSet( ) ;
	vWupChance_SetRate( ) ;
	vChance_VirtualAllTopValue( );
}

// 初始化变数 , 只有归零才做一次
void vChance_Reset( void )
{	

	vMemory_Set((UBYTE *)&stcRecordMain , 0x00 , sizeof(stcRecordMain)) ;
	vMemory_Set((UBYTE *)&stcRecordWup , 0x00 , sizeof(stcRecordWup)) ;
	vMemory_Set((UBYTE *)&stcChance , 0x00 , sizeof(stcChance)) ;
	vMemory_Set((UBYTE *)&stcFeverChance , 0x00 , sizeof(stcFeverChance)) ;
    vMemory_Set((UBYTE *)&stcGameInfo , 0x00 , sizeof(stcGameInfo)) ;
    vMemory_Set((UBYTE *)&stcGameInfoLast , 0x00 , sizeof(stcGameInfoLast)) ;
	vWupChance_Reset( ) ;	
	vChance_Update( 0 ) ;	// 20131128 // REX		

}

ULONG const ulBigWinBufTable[8] = { 
		DEF_CHANCE_BUF_SPEC ,	
		DEF_CHANCE_BUF_FEVER ,			
		DEF_CHANCE_BUF_BONUS ,			
		DEF_CHANCE_BUF_FREE ,
		DEF_CHANCE_BUF_SPEC  ,
		DEF_CHANCE_BUF_MAIN ,
		DEF_CHANCE_BUF_MAIN ,
		DEF_CHANCE_BUF_MAIN ,	
} ;


ULONG const ulBigWinKeyTable[8] = { 
	KEY_0 ,		// All
	KEY_1 ,		// FeverGame
	KEY_2 ,		// JP
	KEY_3 ,		// FreeGame
	KEY_4 ,
	KEY_5 ,
	KEY_6 ,
	KEY_7 ,
	/*
	KEY_PCI_STOP1 ,
	KEY_PCI_GIP02 , //B
	KEY_PCI_STOP4 , 
	KEY_PCI_GIP27 ,	//8
	KEY_PCI_GIP01 , //A
	KEY_PCI_BIG ,
	KEY_PCI_WUP ,
	KEY_PCI_WUP ,
	*/
} ;



#ifdef DEF_TEST_KEYWINBIG
void vChance_TestKeyWinBig(void)
{
	ULONG	i,ulValue,ulRand ;		
	
	#ifdef DEF_OPEN_FAST_TEST_x
	for(i=0;i<1;i++)
	{
		if(1)//( stcChance.ulPlayTimes == 10 )&&(stcGameInfo.ulFreeNowLife==0)) 
		{
			switch( stcChance.ulPlayTimes % 5 )
			{
			default :	
			case 0 : i = 0 ; break ;
			case 1 : i = 1 ; break ;
			case 2 : i = 2 ; break ;
			case 3 : i = 3 ; break ;
			case 4 : i = 4 ; break ;	
			}
			if(stcGameInfo.ulFreeNowLife) i = 5 ; 
			
	#else
	for(i=0;i<5;i++)
	{
		if(ulKey_Touch(ulBigWinKeyTable[i]))
		{
	#endif				
			if(i==0)
			{	// AllSame
				if(stcGameInfo.ulFreeNowLife==0)
				{
					/*
					vGameAssign_5Line(ulRand_ReadMod(6));	
					stcChance.ulActBuf = ulBigWinBufTable[0];		
					*/							
					#ifdef DEF_CHANCE_TW_EXAMINE
					vGameAssign_AllSame( 0 ) ;	
					#else
					vGameAssign_AllSame( ulRand_ReadMod(10)) ;	
					#endif
					stcChance.ulActBuf = ulBigWinBufTable[i];
					break ;											
				}	
				
			}	
			if(i==1)
			{	// Fever
				if(stcGameInfo.ulFreeNowLife==0)
	        	{	        		
	        		stcChance.ulActBuf = ulBigWinBufTable[i];
	        		#ifdef DEF_CHANCE_TW_EXAMINE
	        		ulValue = 8 ;	
	        		#else
	        		ulValue = ulRand_ReadMod(12);	
	        		#endif        		
	        		vGameAssign_MinSpecialSymbol(DEF_SYMBOL_FEVER,stcChanceFeverGameInfoData[ulValue].ulAsnNum);	
	        		stcChance.slFeverOdds = ulChance_TakeMinValue(stcChanceFeverGameInfoData[ulValue].ulMinOdds,stcChanceFeverGameInfoData[ulValue].ulMaxOdds,3);//倍数
					//stcChance.slFeverOdds *= slSlave_ReadLine( ) ; // Rex //WCM直接改用算TotalBet倍数
					stcChance.ulRecFever[0] += stcChance.slFeverOdds*slSlave_ReadLine( ) ;
					break ;	
	        	}	
			}	
			if(i==2)
			{	// JP
				stcChance.ulActBuf = ulBigWinBufTable[i];
				#ifdef DEF_CHANCE_TW_EXAMINE
				vGameAssign_MinSpecialSymbol(DEF_SYMBOL_WILD,3+2);
				#else
				vGameAssign_MinSpecialSymbol(DEF_SYMBOL_WILD,3+ulRand_ReadMod(3));
				#endif
				break ;	
			}				
			if(i==3)
			{	// Free
				if(stcGameInfo.ulFreeNowLife<60)
	        	{	        		
	        		stcChance.ulActBuf = ulBigWinBufTable[i];
	        		#ifdef DEF_CHANCE_TW_EXAMINE
	        		vGameAssign_MinSpecialSymbol(DEF_SYMBOL_FREE,3+2);
	        		#else
	        		vGameAssign_MinSpecialSymbol(DEF_SYMBOL_FREE,3+ulRand_ReadMod(3));
	        		#endif
					break ;		
	        	}	
			}				
			if(i==4)
			{
				if(stcGameInfo.ulFreeNowLife==0)
				{					
					SLONG slValue ;
					ulRand = ulRand_ReadMod(2);
					slValue = stcChance.slVirtualBufTopValue[ulRand]+1;	
					if(stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue<slValue)
					{
						stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue = slValue;
					}					
					if(stcChance.VirtualBuffer[ulRand].slValue<slValue)
					{
						stcChance.VirtualBuffer[ulRand].slValue = slValue;
					}						
					stcChance.ulVirtualBufGate[ulRand] = 1000;	
//					vPcVideo2D_Debug_OutMsg( "FEVERODDS : ", stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue );		
//					vPcVideo2D_Debug_OutMsg( "12FEVERODDS : ", stcChance.ulVirtualBufGate[ulRand] );																				
//					while ( ulKey_RePush( KEY_1 , 10 , 3 ) == 0 );						
					break ;	
					
				}	
				
			}	
			
		}		
	}
	
}
#endif
ULONG ulEffectState;
void vChance_DemoWinBig(void)
{

	ULONG ulValue,ulRand;	
	if(stcGameInfo.ulFreeNowLife==0)  
	{
		switch ( ulEffectState )
		{
			case 1:   //全盤?(全部選一)
			{
				vGameAssign_AllSame( ulRand_ReadMod(10)) ;	
				stcChance.ulActBuf = ulBigWinBufTable[0];
						
			}	
			break ;	
			case 2:   //FREE / FEVER / BONUS 三選一
			{
				ulRand = ulRand_ReadMod(3);
				if(ulRand==0)
				{
					stcChance.ulActBuf = ulBigWinBufTable[1];
	        		ulValue = ulRand_ReadMod(12);	        		
	        		vGameAssign_SpecialSymbol(DEF_SYMBOL_FEVER,stcChanceFeverGameInfoData[ulValue].ulAsnNum);	
	        		stcChance.slFeverOdds = ulChance_TakeMinValue(stcChanceFeverGameInfoData[ulValue].ulMinOdds,stcChanceFeverGameInfoData[ulValue].ulMaxOdds,3);//倍数
				}	
				else if(ulRand==1)
				{
					stcChance.ulActBuf = ulBigWinBufTable[2];
					vGameAssign_SpecialSymbol(DEF_SYMBOL_WILD,3+ulRand_ReadMod(3));
				}
				else
				{
					stcChance.ulActBuf = ulBigWinBufTable[3];
	        		vGameAssign_SpecialSymbol(DEF_SYMBOL_FREE,3+ulRand_ReadMod(3));
					
				}		
	
			}	
			break ;	
			default :   //100倍以上5??選一
			{
				vGameAssign_5Line(ulRand_ReadMod(6));	
				stcChance.ulActBuf = ulBigWinBufTable[0];				
			}					
			break ;					

		}
		ulEffectState++;	
		
	}	
	else
	{		
		vGameAssign_Natural();	//强制自然牌    
	}		
	
}
//基数设定
void vChance_SetBase(void)
{
	ULONG ulValue;
	UWORD uwLevel;
	uwLevel = mGame_ReadRateModeLevel();
	ulValue = mGame_ReadMaxBet() * 9;
	if(stcChance.ulPlayTimes==0)
	{
		switch(	uwLevel )
		{
			case 1:  stcChance.ulBase = ulValue*20;      break ;
				  
			case 2:	 stcChance.ulBase = ulValue*30;      break ;
			
			default:  stcChance.ulBase = ulValue*10;      break ;
		}
	}	
	else
	{
		if((stcChance.ulPlayTimes%1000)==0)
		{
			/*
			switch(	uwLevel )
			{
				case 1: 
					stcChance.ulBase += ulValue*5; 	
					break ;
					  
				case 2: 
					stcChance.ulBase += ulValue*10;  		
					break ;
				
				default:  
					stcChance.ulBase += ulValue*2;  
					break ;
			}
			*/
			stcChance.ulBase += ulValue;  // 20140813  WCM  规则B2 	
			
		}		
	}
	switch(	uwLevel )
	{
		case 1: 
			if(stcChance.ulBase < 20*ulValue)
			{
				stcChance.ulBase = 20*ulValue;  	
			}	
			if(stcChance.ulBase > 100*ulValue)
			{
				stcChance.ulBase = 100*ulValue;  	
			}	
			break ;
			  
		case 2: 
			if(stcChance.ulBase < 30*ulValue)
			{
				stcChance.ulBase = 30*ulValue;  	
			}	
			if(stcChance.ulBase > 150*ulValue)
			{
				stcChance.ulBase = 150*ulValue;  	
			}	
			break ;
		
		default:  
			if(stcChance.ulBase < 10*ulValue)
			{
				stcChance.ulBase = 10*ulValue;  	
			}	
			if(stcChance.ulBase > 50*ulValue)
			{
				stcChance.ulBase = 50*ulValue;  	
			}	
			break ;
	}	
		
	
}


//自然机率出牌
void vChance_NaturalDeal( void )
{
	ULONG ulOdds,ulValue;
	SLONG slBufValue,slLine;
	DLONG dlPlay,dlWin; 
	 
	if(stcChance.ulMainRetakeTime>0)
	{
		stcChance.ulMainRetakeTime--;	
	}	
	vGameAssign_Natural();	//强制自然牌
	#ifdef DEF_TEST_ONLY_NATURE
	/*
	{
		vScroll_SaveStopData( );	
		vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
		ulOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
		
		vGameAssign_Natural();	
		vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
		ulValue = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;

		if(ulValue>ulOdds)
		{
			vScroll_LoadStopData( );  //取小的	
			stcChance.ulRecMainAsn[0] ++ ;
			stcChance.ulRecMainAsn[1] += (ulOdds-ulValue) ;
		}	
	}
	*/
	if(0)
	#else
	slBufValue  = stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue;
	if((slBufValue > stcChance.ulBase)||(slBufValue < -1*(SLONG)stcChance.ulBase))
	#endif	
	{
		if(stcChance.ulMainRetakeTime==0)
		{
			vScroll_SaveStopData( );	
			vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
			ulOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
			
			vGameAssign_Natural();	
			vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
			ulValue = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
			
			if(slBufValue < -4*(SLONG)stcChance.ulBase)
			{
				stcChance.ulRecMainAsn[0] ++ ;
				if(ulValue>ulOdds)
				{
					vScroll_LoadStopData( );  //取小的	
				}	
				if(slBufValue < (-10)*(SLONG)stcChance.ulBase)
				{
					stcChance.ulMainRetakeTime = 5+ulRand_ReadMod(6);						
				}	
				else if(slBufValue< (-8)*(SLONG)stcChance.ulBase)
				{
					stcChance.ulMainRetakeTime = 5+ulRand_ReadMod(11);	
				}
				else if(slBufValue< (-6)*(SLONG)stcChance.ulBase)
				{
					stcChance.ulMainRetakeTime = 10+ulRand_ReadMod(11);	
				}	
				else
				{
					stcChance.ulMainRetakeTime = 15+ulRand_ReadMod(11);	
				}	
			}	
			else if(slBufValue > 4*(SLONG)stcChance.ulBase)
			{
				stcChance.ulRecMainAsn[1] ++ ;
				if(ulValue<ulOdds)
				{
					vScroll_LoadStopData( );  //取大的						
				}	
				if(slBufValue> 10*(SLONG)stcChance.ulBase)
				{
					stcChance.ulMainRetakeTime = 5+ulRand_ReadMod(6);	
				}	
				else if(slBufValue> 8*(SLONG)stcChance.ulBase)
				{
					stcChance.ulMainRetakeTime = 5+ulRand_ReadMod(11);	
				}
				else if(slBufValue> 6*(SLONG)stcChance.ulBase)
				{
					stcChance.ulMainRetakeTime = 10+ulRand_ReadMod(11);	
				}	
				else
				{
					stcChance.ulMainRetakeTime = 15+ulRand_ReadMod(11);	
				}		
			}	
			
		}		
		
	}	
	//20140813 WCM  初期灌分
	if(stcChance.ulPlayTimes<10000)
	{		
		vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
		ulOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo ) ;
		if(ulOdds==0)
		{
			dlPlay = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTOTAL);
            dlWin  = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL);
			ulValue = 0;
			if(dlWin&&dlPlay)
			{
				ulValue = (ULONG)(dlWin*1000/dlPlay);
			}				
			if(ulValue<1000)
			{
				if(ulRand_ReadMod(10)==0)
				{
					stcChance.ulRecMainAsn[2] ++ ;				
					vGameAssign_Natural();	
					vGameCheck_CheckOdds( (GAMEINFO*)&stcGameInfo ) ;
					ulOdds = slGameCheck_ReadAllOdds( (GAMEINFO*)&stcGameInfo );
					if(ulOdds)
					{
						ulValue = stcGameInfo.ulAllSameOdds *  slSlave_ReadTotalBet() ;
					    for ( slLine = 0 ; slLine < 9 ; slLine ++ )
					    {
					        ulValue += stcGameInfo.stcLine[slLine].ulOdds[0] * slSlave_ReadBet() ;
					        ulValue += stcGameInfo.stcLine[slLine].ulOdds[1] * slSlave_ReadBet() ;
					    }   
						stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue += ulValue ;	
						stcChance.ulReturnMainValue += ulValue;	// only record					
					}	
					
					
				}	
				
			}	
			
		}	
		
	}	
	
	

}
//处理虚拟回灌Buffer
void vChance_VirtualReturnBuf( void )
{
	ULONG  ulValue,ulLoc;
	if(stcChance.slReturnBufValue>=8)
	{
		stcChance.slReturnBetValue += slSlave_ReadTotalBet();
		if(stcChance.slReturnBetValue>=100)
		{
			ulLoc = stcChance.slReturnBetValue/100; 	
			ulValue = ulLoc * 8;
			if(ulValue <= stcChance.slReturnBufValue)
			{
				stcChance.slReturnBetValue -= 100* ulLoc;
				stcChance.slReturnBufValue -= ulValue;
				stcChance.ulRecReturnIn[4] += ulValue;
				stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue += 5* ulLoc;
				stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue +=  ulLoc;
				stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue +=  ulLoc;
				stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue +=  ulLoc;		
			}	
			else
			{
				ulLoc = stcChance.slReturnBufValue/8; 	
				stcChance.slReturnBetValue = 0;
				stcChance.slReturnBufValue -= ulLoc*8;
				stcChance.ulRecReturnIn[4] += ulLoc*8;
				stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue += 5* ulLoc;
				stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue +=  ulLoc;
				stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue +=  ulLoc;
				stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue +=  ulLoc;	
				
				
			}	
		}			
	}	
	
}


//20141028 WCM 紀?分佈狀態的
void vChance_RecArray(void )
{	
	ULONG ulValue,ulLoc,i;
	SLONG slBufValue,slLoop;
	ulValue =mGame_ReadMaxBet()/10;	
	if(ulValue==0)
	{
		ulValue = 1;	
	}	
	ulValue = (slSlave_ReadBet()/ulValue)%11;	
	switch(slSlave_ReadLine( ))
    {
        case 1 : ulLoc = 0 ; break ;
        case 3 : ulLoc = 1 ; break ;
        case 5 : ulLoc = 2 ; break ;   
        case 7 : ulLoc = 3 ; break ;  	    
        case 9 : ulLoc = 4 ; break ;
        default: ulLoc = 0 ; break ;
    }		
	stcChance.ulRecBetArray[ulLoc][ulValue]++;
	
	if((stcChance.ulPlayTimes%100)==0)
	{
		ulValue =mGame_ReadMaxBet();
		slBufValue  = stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue;
		if((slBufValue >= (-500)*(SLONG)ulValue)&&(slBufValue <= 500*(SLONG)ulValue))
		{
			slBufValue += 500*(SLONG)ulValue;
			ulLoc = (slBufValue/(20*(SLONG)ulValue))%51;
			stcChance.ulRecBufArray[0][ulLoc]++;		
		}	
		slBufValue  = stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue;
		if((slBufValue >= 0)&&(slBufValue <= 5000*(SLONG)ulValue))
		{		
			ulLoc = (slBufValue/(100*(SLONG)ulValue))%51;
			stcChance.ulRecBufArray[1][ulLoc]++;		
		}
		i = 2;
		for ( slLoop = DEF_CHANCE_BUF_BONUS ; slLoop < DEF_CHANCE_BUFMAX  ; slLoop ++,i++ )
		{
			slBufValue  = stcChance.Buffer[slLoop].slValue;
			if((slBufValue >= (-1000)*(SLONG)ulValue)&&(slBufValue <= 1000*(SLONG)ulValue))
			{
				slBufValue += 1000*(SLONG)ulValue;
				ulLoc = (slBufValue/(40*(SLONG)ulValue))%51;
				stcChance.ulRecBufArray[i][ulLoc]++;		
			}	
			
		}
		
	}	
	
	
}


//20141028 WCM 紀?押注分布清零
void vChance_RecBetArrayReset(void )
{	
	ULONG i,j;
	for(i=0;i<5;i++)
	{
		for(j = 0 ; j < 11 ; j ++)	
		{
			stcChance.ulRecBetArray[i][j] = 0;
		}	
		for(j = 0 ; j < 51 ; j ++)	
		{
			stcChance.ulRecBufArray[i][j] = 0;
		}		
	}	
	
}

#ifdef DEF_CHANCE_FOR_UART_SLAVE

void vChance_MAsn_BufProcess( void )
{
	ULONG i ;
	
	if( stcChance.ubMAsnItem ) 			return ;
	if( stcChance.ubMAsnItemReturn ) 	return ;
	if( stcGameInfo.ulFreeNowLife )		return ;
			
	for(i=0;i<DEF_CHANCE_MBUF_MAX; i++ )
	{
		if( stcChance.MBuf[i].ulValue )
		{
			// asn
			stcChance.ubMAsnItem = i+1 ;
			
			stcChance.MBuf[i].ulAsnTop = ulGameCheckAllSameOddsTable[i] ;
			stcChance.MBuf[i].ulAsnTop *= mGame_ReadMaxBet( ) ;
			stcChance.MBuf[i].ulAsnTop *= 9 ;

			stcChance.MBuf[i].ulAsnTimes ++ ;		

			if( stcChance.MBuf[i].ulValue >= stcChance.MBuf[i].ulAsnTop )
			{
				vGameAssign_AllSame( i ) ;
			}
			else
			{
    			// 没钱送了，结束
    			stcChance.ubMAsnItem  = 0 ;
				stcChance.ubMAsnItemReturn = i+1 ;	
			}
			break ;
		}
	}
		
}

void vChance_MAsn_WinProcess( ULONG ulWin )
{
	ULONG i ;	
	
	i = stcChance.ubMAsnItem-1 ;		
		
	if( ulWin )
	{
		stcChance.MBuf[i].dlRecWin += ulWin ;
		
		// 因为接下来 vChance_WinProcess ,还会从 MainBuf 里面扣掉赢分
		stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue += ulWin ;
		
		if( stcChance.MBuf[i].ulValue >= ulWin )
		{
			stcChance.MBuf[i].ulValue -= ulWin ;
		}
		else
		{
			stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue -= (ulWin-stcChance.MBuf[i].ulValue) ;
			
			stcChance.MBuf[i].ulValue = 0 ;
		}
	}

	// 只有一局的机会，没强制成功，分数就返回给主机	
	if( stcChance.MBuf[i].ulValue )
	{
		stcChance.ubMAsnItemReturn = i+1 ;
		//stcChance.MBuf[i].dlRecRet += stcChance.MBuf[i].ulValue ;		
	}	
	stcChance.ubMAsnItem = 0 ;	
	
}

#endif

// 主游戏几率处理
void vChance_GameProcess( void )
{
	
	if(stcGameInfo.ulFreeNowLife==0)
	{
		vChance_SetBase( ) ;				//基数设置
		vChance_AddBet(slSlave_ReadTotalBet());
		vChance_VirtualBufAdd(slSlave_ReadTotalBet());//虚拟累加
		vChance_VirtualGate( );				//虚拟触顶Gate
		vChance_VirtualReturnBuf( );		//虚拟回灌
		vChance_RecArray( );   //记录押注分布
		stcChance.ulFreeTotalWin = 0 ;	
	}	

	#ifdef DEF_TEST_ALWAYS_AUTO_2
    {    	
    	char cStr[256] ;
    	DLONG dlTmpVal , dlRate ;

    	dlTmpVal = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_MAIN_PLAYTIMES ) ;
    	
    	if(( dlTmpVal%10 )==0)
    	{
	        vSprint((char *)cStr , STR"%8l%8l " , (ULONG)(dlTmpVal/100000000) , (ULONG)(dlTmpVal%100000000) ) ;        	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-1 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*0 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;
	
	    	dlTmpVal = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_MAIN_WINTIMES ) ;
	        vSprint((char *)cStr , STR"%8l%8l " , (ULONG)(dlTmpVal/100000000) , (ULONG)(dlTmpVal%100000000) ) ;        	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-2 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*1 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

	    	dlTmpVal = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALPLAY ) ;
	        vSprint((char *)cStr , STR"%8l%8l %d %d " , 
	        	(ULONG)(dlTmpVal/100000000) , (ULONG)(dlTmpVal%100000000) , mGame_ReadGameRateLevel() , mGame_ReadRateModeLevel() ) ;       	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-3 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*2 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

			dlRate = 0 ;
			if( dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALPLAY ) )
			{
				dlRate  = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALWIN ) ;
				dlRate *= 1000 ;
				dlRate /= dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALPLAY ) ;
			}
			
	    	dlTmpVal = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALWIN ) ;
	        vSprint((char *)cStr , STR"%8l%8l %l " , (ULONG)(dlTmpVal/100000000) , (ULONG)(dlTmpVal%100000000) , 
	        	(ULONG)dlRate ) ;        	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-4 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*3 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

			/*
	        vSprint((char *)cStr , STR"%10l %10l %10l " , stcChance.AMBuf[DEF_CHANCE_AMBUF_1].slValue , stcChance.AMBuf[DEF_CHANCE_AMBUF_1].ulTop , stcChance.AMBuf[DEF_CHANCE_AMBUF_1].ulInitTop ) ;    	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-5 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*4 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

	        vSprint((char *)cStr , STR"%10l %10l %10l " , stcChance.AMBuf[DEF_CHANCE_AMBUF_2].slValue , stcChance.AMBuf[DEF_CHANCE_AMBUF_2].ulTop , stcChance.AMBuf[DEF_CHANCE_AMBUF_2].ulInitTop ) ;    	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-6 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*5 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

	        vSprint((char *)cStr , STR"%10l %10l %10l " , stcChance.AMBuf[DEF_CHANCE_AMBUF_3].slValue , stcChance.AMBuf[DEF_CHANCE_AMBUF_3].ulTop , stcChance.AMBuf[DEF_CHANCE_AMBUF_3].ulInitTop ) ;    	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-7 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*6 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

	        vSprint((char *)cStr , STR"%10l " , stcChance.AMBuf[DEF_CHANCE_AMBUF_TMP].slValue ) ;    	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-8 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*7 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;
			*/
			
	        vSprint((char *)cStr , STR"%10l " , stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue ) ;    	
	        vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-9 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*8 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;

			#ifdef DEF_CHANCE_FOR_UART_SLAVE
	        {
	        	SLONG slChk ;
	        	DLONG dlVal[5] ;
	        	
	        	dlVal[0] = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALPLAY ) ;
	        	dlVal[1] = dlRecord_ReadCurrTotal( DEF_RECORD_PLR_ALL , DEF_RECORD_DATA_TOTALWIN ) ;
	        	
	        	// 按累积率算出来的
	            dlVal[2]  = stcChance.ulRate[ DEF_CHANCE_BUF_MAIN ] ;
	            dlVal[2] += stcChance.ulRate[ DEF_CHANCE_BUF_SPEC ] ;
	            dlVal[2] += stcChance.ulRate[ DEF_CHANCE_BUF_BONUS ] ;
	            dlVal[2] += stcChance.ulRate[ DEF_CHANCE_BUF_FEVER ] ;	                
	            dlVal[2] += stcChance.ulRate[ DEF_CHANCE_BUF_FREE ] ;	                
	            dlVal[0] *= dlVal[2] ;
	            dlVal[0] /= 1000 ;	
	            
	            // 加上初期灌分
	            dlVal[0] += stcChance.ReturnSpec.slValue ;
	            dlVal[0] += stcChance.ulReturnMainValue ;
	            
	            // 目前Buf总值
	            dlVal[3]  = stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue ;
	            dlVal[3] += stcChance.Buffer[DEF_CHANCE_BUF_SPEC].slValue ;
	            dlVal[3] += stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue ;
	            dlVal[3] += stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue ;
	            dlVal[3] += stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue ;
	            dlVal[3] += stcChance.slReturnBufValue ;
	            	
	            // 主机给的	
	            dlVal[4]  = stcChance.MBuf[DEF_CHANCE_MBUF_ALL_A].dlRecIn ;
	            dlVal[4] += stcChance.MBuf[DEF_CHANCE_MBUF_ALL_B].dlRecIn ;
	            dlVal[4] += stcChance.MBuf[DEF_CHANCE_MBUF_ALL_C].dlRecIn ;
	            dlVal[4] += stcChance.MBuf[DEF_CHANCE_MBUF_ALL_D].dlRecIn ;
	            dlVal[4] += stcChance.MBuf[DEF_CHANCE_MBUF_ALL_E].dlRecIn ;

				// 返回给主机的
	            dlVal[4] -= stcChance.MBuf[DEF_CHANCE_MBUF_ALL_A].dlRecRet ;
	            dlVal[4] -= stcChance.MBuf[DEF_CHANCE_MBUF_ALL_B].dlRecRet ;
	            dlVal[4] -= stcChance.MBuf[DEF_CHANCE_MBUF_ALL_C].dlRecRet ;
	            dlVal[4] -= stcChance.MBuf[DEF_CHANCE_MBUF_ALL_D].dlRecRet ;
	            dlVal[4] -= stcChance.MBuf[DEF_CHANCE_MBUF_ALL_E].dlRecRet ;
				
				slChk = dlVal[0]-dlVal[1]-dlVal[3]+dlVal[4] ;
	
	            vSprint((char *)cStr , STR" [%8l%8l] %l %l (%l) " ,
	            	(ULONG)(dlVal[0]/100000000) , (ULONG)(dlVal[0]%100000000) , 
		        	(ULONG)dlVal[3] , (ULONG)dlVal[4] , slChk ) ;
	            vPcVideo2D_Img_ShowString( DEF_ANIMNO_DEBUG-10 , mMacro_Img( DEF_FONT_ASCII_000 ) , 50 , 400+24*10 , DEF_PCVIDEO2D_ZOBASE+DEF_ANIMNO_DEBUG , DEF_BLU , 24 , cStr ) ;
			}
			#endif
	    }
    }            
    #endif
	
	stcChance.ulFeverTotalWin = 0 ;
	
	stcChance.ulActBuf  = DEF_CHANCE_BUF_MAIN ;//设定本局所使用的Buffer次数为0	
	
	vChance_AsnBufProcess();//强制奖项判断	
	#ifdef DEF_TEST_KEYWINBIG 
	vChance_TestKeyWinBig();  //按键强制奖项
	#endif
	
	if(stcGameInfo.ulFreeNowLife==0)
	{
		if(stcChance.ulActBuf  == DEF_CHANCE_BUF_MAIN )
		{
			vChance_VirtualProcess( ); //处理虚拟奖项	
		}	
		stcChance.ulPlayTimes ++ ;
    	if( stcChance.ulPlayTimes > 1010000000 ) stcChance.ulPlayTimes -= 1000000000 ;	    
	}	
	
	if(stcChance.ulActBuf  == DEF_CHANCE_BUF_MAIN)
	{
		vChance_NaturalDeal( );	    //自然机率出奖
	}	
	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	if(stcChance.ulActBuf  == DEF_CHANCE_BUF_MAIN)
	{
		vChance_MAsn_BufProcess( ) ;
	}
	#endif
	
    	

	
}





//累加下各种奖项BUFFER
void vChance_AddBet(ULONG ulBet )
{
	ULONG	i,ulValue;	
	DLONG dlPlay,dlWin; 
	
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALPLAY , ulBet ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTOTAL , ulBet ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTIMES , 1 ) ;
	#ifdef DEF_USE_VGAME_UART_SLAVE
	ulUartCmdRec[DEF_RECORD_DATA_TOTALPLAY][0] += ulBet ;
	ulUartCmdRec[DEF_RECORD_MAIN_PLAYTOTAL][0] += ulBet ;
	ulUartCmdRec[DEF_RECORD_MAIN_PLAYTIMES][0] += 1 ;
	#endif
	
	for(i=0;i<DEF_CHANCE_BUFMAX;i++)
	{		
		slBuffer_AddRate( &stcChance.Buffer[i] , ulBet , stcChance.ulRate[i] ) ;
	}	
	//20140819 WCM Spec Buf初期灌分
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	if( ulBet )
	{
		stcChance.ulNoPlayTime = 60*60 ;
	}
	if(stcChance.ulPlayTimes<80000)
	#else
	if(stcChance.ulPlayTimes<100000)
	#endif	
	{			
		dlPlay = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_PLAYTOTAL);
        dlWin  = dlRecord_ReadCurrTotal(DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL);
		ulValue = 0;
		if(dlWin&&dlPlay)
		{
			ulValue = (ULONG)(dlWin*1000/dlPlay);
		}				
		if(ulValue<970)
		{				
			slBuffer_AddRate( &stcChance.ReturnSpec , ulBet , 30 ) ; // only record
			slBuffer_AddRate( &stcChance.Buffer[DEF_CHANCE_BUF_SPEC] ,ulBet , 30 ) ;
		}	
		
	}	
	
	
	
			
}



//求强制出奖的触顶押分
SLONG slChance_LmpAdd( SLONG slLmpBet )
{
	SLONG slMaxBet;
	slMaxBet = mGame_ReadMaxBet( );
	if( stcChance.ulPlayTimes < 101 )      //100局之内,平均押注=目前总押注分数/局数
	{
		stcChance.slAvgBetTotal += slLmpBet ;
		stcChance.slAvgBet = ( stcChance.slAvgBetTotal /  stcChance.ulPlayTimes ) ; 	    	
        if( stcChance.ulPlayTimes == 100 )
		{	    		
			stcChance.slAvgBetTotal *= 10 ;	
		}
	}
	else		//100局之后,平均押注=(总押注分数*0.999+当前押注分数)/1000
	{
		stcChance.slAvgBetTotal -= ( stcChance.slAvgBetTotal / 1000 ) ;
		stcChance.slAvgBetTotal += slLmpBet ;
		stcChance.slAvgBet = stcChance.slAvgBetTotal / 1000 ;
	}	
	return ( stcChance.slAvgBet );		
	
		
}



//强制特殊奖项
void vChance_AsnBufProcess( void )
{

	ULONG ulValue,ulRand,ulNumerator[12]; 
	SLONG slBufValue,slLoop,slLoop1;
	
	#ifdef DEF_TEST_ONLY_NATURE
	return ;
	#endif
	
	for ( slLoop = DEF_CHANCE_BUF_BONUS ; slLoop < DEF_CHANCE_BUFMAX  ; slLoop ++ )
	{		
		slBufValue  = stcChance.Buffer[slLoop].slValue;			
		if(slBufValue > 8*(SLONG)stcChance.ulBase)
		{
			ulValue = 175;	
		}	
		else if(slBufValue > 6*(SLONG)stcChance.ulBase)
		{
			ulValue = 150;		
		}	
		else if(slBufValue > 4*(SLONG)stcChance.ulBase)
		{
			ulValue = 125;		
		}	
		else if(slBufValue > (-4)*(SLONG)stcChance.ulBase)
		{
			ulValue = 100;
		}	
		else if(slBufValue > (-6)*(SLONG)stcChance.ulBase)
		{
			ulValue = 75;		
		}	
		else if(slBufValue > (-8)*(SLONG)stcChance.ulBase)
		{
			ulValue = 50;		
		}
		else
		{
			ulValue = 25;	
		}	
		stcChance.ulBufferGate[slLoop] = ulValue ;
		
		if(slLoop == DEF_CHANCE_BUF_BONUS)
		{
			for ( slLoop1 = 0 ; slLoop1 <3 ; slLoop1 ++ )	
			{
				ulNumerator[slLoop1] = (stcChanceBonusGameInfoData[slLoop1].ulGate*ulValue)/100;					
			}	
			ulRand = ulRand_ReadMod(0x400000);			
			for ( slLoop1 = 0 ; slLoop1 <3 ; slLoop1 ++ )	
			{
				if( ulRand < ulNumerator[slLoop1] ) break ;
				ulRand -= ulNumerator[slLoop1] ;
			}	
			if(slLoop1<3)
			{
				stcChance.ulActBuf = slLoop;
				vGameAssign_MinSpecialSymbol(DEF_SYMBOL_WILD,stcChanceBonusGameInfoData[slLoop1].ulAsnNum);
				break ;				
			}
		}	
		if(slLoop == DEF_CHANCE_BUF_FREE)
		{
			if(stcChance.ulAsnState==0)  //Spec强制出时不能在出,防止计算复杂
			{
				for ( slLoop1 = 0 ; slLoop1 <3 ; slLoop1 ++ )	
				{
					ulNumerator[slLoop1] = (stcChanceFreeGameInfoData[slLoop1].ulGate*ulValue)/100;					
				}	
				ulRand = ulRand_ReadMod(0x8000);
				for ( slLoop1 = 0 ; slLoop1 <3 ; slLoop1 ++ )	
				{
					if( ulRand < ulNumerator[slLoop1] ) break ;
					ulRand -= ulNumerator[slLoop1] ;
				}	
				if(slLoop1<3)
				{
					stcChance.ulActBuf = slLoop;
					vGameAssign_MinSpecialSymbol(DEF_SYMBOL_FREE,stcChanceFreeGameInfoData[slLoop1].ulAsnNum);
					break ;				
				}					
			}	
		}	
		if(slLoop == DEF_CHANCE_BUF_FEVER)
		{
			if(stcGameInfo.ulFreeNowLife==0)          //免费游戏时不出FEVER
			{
				for ( slLoop1 = 0 ; slLoop1 <12 ; slLoop1 ++ )	
				{
					ulNumerator[slLoop1] = (stcChanceFeverGameInfoData[slLoop1].ulGate*ulValue)/100;	//出现率根据Buffer调控	
				}	
				ulRand = ulRand_ReadMod(0x400000);					
				for ( slLoop1 = 0 ; slLoop1 <12 ; slLoop1 ++ )	
				{
					if( ulRand < ulNumerator[slLoop1] ) break ;
					ulRand -= ulNumerator[slLoop1] ;
				}	
				if(slLoop1<12)
				{					
					stcChance.ulActBuf = slLoop;
					vGameAssign_MinSpecialSymbol(DEF_SYMBOL_FEVER,stcChanceFeverGameInfoData[slLoop1].ulAsnNum);
					stcChance.slFeverOdds = ulChance_TakeMinValue(stcChanceFeverGameInfoData[slLoop1].ulMinOdds,stcChanceFeverGameInfoData[slLoop1].ulMaxOdds,3);//倍数	
					//stcChance.slFeverOdds *= slSlave_ReadLine( ) ; // Rex //WCM直接改用算TotalBet倍数
					stcChance.ulRecFever[0] += stcChance.slFeverOdds*slSlave_ReadLine( ) ;
					break ;				
				}		
			}
			
			
		}	
	
	}

   
}










//更新查账历史全部记录
void vChance_AllRecordUpdate( ULONG mode )
{
	/*
	SLONG slLoop, slLoop1 ;    
	
	if( mode )
	{
	    for ( slLoop = DEF_RECLAST_MAX ; slLoop >= 1 ; slLoop -- )
	    {
	    	for(slLoop1 = 0 ; slLoop1 < 11 ; slLoop1 ++)
	    	{
	    		stcRecordWup[slLoop].ulWupWin[slLoop1] =	stcRecordWup[slLoop-1].ulWupWin[slLoop1];	
	    		stcRecordWup[slLoop].ulWupMode[slLoop1] =	stcRecordWup[slLoop-1].ulWupMode[slLoop1];	
	    		stcRecordWup[slLoop].ulWupCard[slLoop1] =	stcRecordWup[slLoop-1].ulWupCard[slLoop1];	
	    		stcRecordWup[slLoop].ulWupGuess[slLoop1] =	stcRecordWup[slLoop-1].ulWupGuess[slLoop1];		    		
	    	}
	    	stcRecordWup[slLoop].ulWupGameMode = stcRecordWup[slLoop-1].ulWupGameMode;
	    	stcRecordWup[slLoop].ulWupGameWin = stcRecordWup[slLoop-1].ulWupGameWin;    	
	    }
		for(slLoop1 = 0 ; slLoop1 < 11 ; slLoop1 ++)
		{
			stcRecordWup[0].ulWupWin[slLoop1] =	0;	
			stcRecordWup[0].ulWupMode[slLoop1] =	DEF_CHANCE_WUP_MAX;	
			stcRecordWup[0].ulWupCard[slLoop1] =	DEF_POKER_BK;	
			stcRecordWup[0].ulWupGuess[slLoop1] = DEF_WUP_GUESS_TAKE ;    		
		}
	    stcRecordWup[0].ulWupGameMode = DEF_CHANCE_WUP_MAX;	
	  	stcRecordWup[0].ulWupGameWin = 0;
	}
	else
	{
	    for ( slLoop = DEF_RECLAST_MAX ; slLoop >= 1 ; slLoop -- )
	    {	    	
	    	stcRecordMain[slLoop].ulCredit = stcRecordMain[slLoop-1].ulCredit;
	    	stcRecordMain[slLoop].ulBet = stcRecordMain[slLoop-1].ulBet;
	    	stcRecordMain[slLoop].ulWin = stcRecordMain[slLoop-1].ulWin;
	    	for(slLoop1 = 0 ; slLoop1 < DEF_HANDCARD_MAX ; slLoop1 ++)
	    	{
	    		stcRecordMain[slLoop].ubFstCard[slLoop1] =	stcRecordMain[slLoop-1].ubFstCard[slLoop1];
	    		stcRecordMain[slLoop].ubSecCard[slLoop1] =	stcRecordMain[slLoop-1].ubSecCard[slLoop1];
	    	}
	    	stcRecordMain[slLoop].ulGameMode = stcRecordMain[slLoop-1].ulGameMode;
	    	stcRecordMain[slLoop].ulGameOdds = stcRecordMain[slLoop-1].ulGameOdds;
	    }
	    stcRecordMain[0].ulCredit = 0;
	    stcRecordMain[0].ulBet = 0;
	    stcRecordMain[0].ulWin = 0;
	    for(slLoop1 = 0 ; slLoop1 < DEF_HANDCARD_MAX ; slLoop1 ++)
	    {
	    	stcRecordMain[0].ubFstCard[slLoop1] =	DEF_POKER_BK;
			stcRecordMain[0].ubSecCard[slLoop1] =	DEF_POKER_BK;	
	    }
	   // stcRecordMain[0].ulGameMode = DEF_CHANCE_NO;
		stcRecordMain[0].ulGameOdds = 0;
	}
	*/
	
}









// 设定互换位置
void vChance_LocSwap( UBYTE *ubLoc,ULONG ulCount )
{
	SLONG slLoop , slSwapIndex ;
	UBYTE ubSwapData ;

    // 设定正常位置 0 1 2 3 4 
	for ( slLoop = 0 ; slLoop < ulCount ; slLoop ++ )
	{
		ubLoc[slLoop] = slLoop ;
	}
	
	// 搅乱位置 
	for ( slLoop = 0 ; slLoop < ulCount ; slLoop ++ )
	{
		slSwapIndex = ulRand_ReadMod(ulCount) ;
		mMacro_Swap( ubLoc[slLoop] , ubLoc[slSwapIndex] , ubSwapData ) ;
	}	
}









// 中奖后几率的处理
void vChance_WinProcess( ULONG	ulWin )
 {
	SLONG slMaxWin , slLoop ;
	
    for ( slLoop = 0 ; slLoop < 15 ; slLoop ++ )
    {
    	slMaxWin = ubScroll_GetData( slLoop ) ;
    	if( slMaxWin < 13 )
    	{
			stcChance.ulRecReelSymTimes[slMaxWin] ++ ;
		}
	}
	
	#ifdef DEF_CHANCE_FOR_UART_SLAVE
	if( stcChance.ubMAsnItem )
	{
		vChance_MAsn_WinProcess( ulWin );
	}
	#endif

	// 每一局的奖项记录，包含FreeGame    
	vGameCheck_SaveWinRule( (GAMEINFO*)&stcGameInfo ) ;
    		
	if(stcGameInfo.ulFreeNowLife==0)
	{		
		
		switch ( stcChance.ulActBuf )
		{			
			case DEF_CHANCE_BUF_SPEC :	
				if( ulWin )
				{					
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , ulWin ) ;
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL , ulWin ) ;
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTIMES , 1 ) ;	
					#ifdef DEF_USE_VGAME_UART_SLAVE
					ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += ulWin ;
					ulUartCmdRec[DEF_RECORD_MAIN_WINTOTAL][0] += ulWin ;
					ulUartCmdRec[DEF_RECORD_MAIN_WINTIMES][0] += 1 ;
					#endif

					stcChance.ulWinTimes[stcChance.ulActBuf]++;
					stcChance.ulSpecValue[stcChance.ulAsnGift] += ulWin; //累加送出的真实虚拟值 
//					slMaxWin = slGameCheck_MaxGameWinRule((GAMEINFO*)&stcGameInfo);	
//					if(slMaxWin>ulWin)                                   //放到回灌Buff
//					{
//						stcChance.Buffer[stcChance.ulActBuf].slValue -= slMaxWin ;	
//						stcChance.slReturnBufValue += slMaxWin - ulWin;
//						stcChance.ulRecReturnIn[0] += slMaxWin - ulWin;
//					}
//					else
//					{
//						stcChance.Buffer[stcChance.ulActBuf].slValue -= ulWin ;		
//					}	
					stcChance.Buffer[stcChance.ulActBuf].slValue -= ulWin ;	
				}	
				break ;	
			case DEF_CHANCE_BUF_MAIN :	
				if( ulWin )
				{
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , ulWin ) ;
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL , ulWin ) ;
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTIMES , 1 ) ;	
					#ifdef DEF_USE_VGAME_UART_SLAVE
					ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += ulWin ;
					ulUartCmdRec[DEF_RECORD_MAIN_WINTOTAL][0] += ulWin ;
					ulUartCmdRec[DEF_RECORD_MAIN_WINTIMES][0] += 1 ;
					#endif

					stcChance.Buffer[stcChance.ulActBuf].slValue -= ulWin ;		
					stcChance.ulWinTimes[stcChance.ulActBuf]++;		
				}	 	
				break ;	
			case DEF_CHANCE_BUF_BONUS:
				if( ulWin )
				{
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , ulWin ) ;
					vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL , ulWin ) ;				
					#ifdef DEF_USE_VGAME_UART_SLAVE
					ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += ulWin ;
					ulUartCmdRec[DEF_RECORD_MAIN_WINTOTAL][0] += ulWin ;
					#endif

					stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue -= ulWin ;
					stcChance.ulWinTimes[stcChance.ulActBuf]++;
				}	
				vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTIMES , 1 ) ;	 	
				#ifdef DEF_USE_VGAME_UART_SLAVE
				ulUartCmdRec[DEF_RECORD_MAIN_WINTIMES][0] += 1 ;
				#endif
				break ;	
			case DEF_CHANCE_BUF_FEVER:
		    case DEF_CHANCE_BUF_FREE :  
		     	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTIMES , 1 ) ;	
				#ifdef DEF_USE_VGAME_UART_SLAVE
				ulUartCmdRec[DEF_RECORD_MAIN_WINTIMES][0] += 1 ;
				#endif
		     	stcChance.ulWinTimes[stcChance.ulActBuf]++; 	
				break ;		 	
				
		}
	}	
	else
	{
		if( ulWin )
		{			
			stcChance.ulFreeTotalWin += ulWin ;
			
			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , ulWin ) ;
			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL , ulWin ) ;
			vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_FREE_WINTOTAL , ulWin ) ;
			#ifdef DEF_USE_VGAME_UART_SLAVE
			ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += ulWin ;
			ulUartCmdRec[DEF_RECORD_MAIN_WINTOTAL][0] += ulWin ;
			ulUartCmdRec[DEF_REC_FREE_WINTOTAL][0] += ulWin ;
			#endif

			if(stcChance.ulAsnState==0)
			{
//				slMaxWin = slGameCheck_MaxGameWinRule((GAMEINFO*)&stcGameInfo);	
//				if(slMaxWin>ulWin)                                   //放到回灌Buff
//				{
//					stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue -= slMaxWin ;	
//					stcChance.slReturnBufValue += slMaxWin - ulWin;
//					stcChance.ulRecReturnIn[1] += slMaxWin - ulWin;
//				}
//				else
//				{
//					stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue -= ulWin ;	
//				}	
				stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue -= ulWin ;	
			}	
			else
			{				
				stcChance.Buffer[DEF_CHANCE_BUF_FREE].slValue -= ulWin ;//Spec强制时不处理回灌Buff
				stcChance.ulSpecValue[stcChance.ulAsnGift] += ulWin; //累加送出的真实虚拟值 
			}	
									
		}
		if(stcGameInfo.ulFreeNowLife==1)//相当全部运行完
		{
			/*
			{
				char cStr[256];
				vSprint((char *)cStr , STR"WINFRE (%l) %l " , stcChance.ulFreeType , stcChance.ulFreeTotalWin ) ;
				vPcVideo2D_Debug_OutMsg( cStr, 0 ) ;
			}
			*/
			// FreeGame 的事件记录，必须等到 FreeGame 完全结束，才能记录
			vRecord_Save_WinEvent( stcChance.ulFreeTotalWin , stcChance.ulFreeType+2 , DEF_SYMBOL_12 ) ;
			// 
			//stcChance.ulFreeType = 0 ;
		}
		
	}	
}

// vMaster_Game_BonusEffect
void vChance_WinBonusProcess( void )
{
	SLONG slMaxWin ;

	slMaxWin = stcGameInfo.ulBonusWin ;
	
			/*
			{
				char cStr[256];
				vSprint((char *)cStr , STR"WINBNS (%l) %l " , stcGameInfo.ulBonusType , slMaxWin ) ;
				vPcVideo2D_Debug_OutMsg( cStr, 0 ) ;
			}
			*/
	
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , slMaxWin ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL , slMaxWin ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_BONUS_WINTOTAL , slMaxWin ) ;
	#ifdef DEF_USE_VGAME_UART_SLAVE
	ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += slMaxWin ;
	ulUartCmdRec[DEF_RECORD_MAIN_WINTOTAL][0] += slMaxWin ;
	ulUartCmdRec[DEF_REC_BONUS_WINTOTAL][0] += slMaxWin ;
	#endif
	
	// Bonus 次数的记录，是效果演出时，就先记录
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM_WILD_X3+stcGameInfo.ulBonusType-1 , 1 ) ;
	if( slSlave_ReadTotalBet( ) >= mGame_ReadBetForGift( ) )
	{
		vRecord_Add_GiftBet( DEF_REC_SYM_WILD_X3+stcGameInfo.ulBonusType-1 , 1 ) ;
	}
	vRecord_Save_WinEvent( stcGameInfo.ulBonusWin , stcGameInfo.ulBonusType+2 , DEF_SYMBOL_10 ) ;

	if(stcChance.ulAsnState==0)
	{
//		slMaxWin = (stcGameInfo.ulBonusWin*mGame_ReadMaxBet())/slSlave_ReadBet();
//		if(slMaxWin>stcGameInfo.ulBonusWin)                                   //放到回灌Buff
//		{
//			stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue -= slMaxWin ;	
//			stcChance.slReturnBufValue += slMaxWin - stcGameInfo.ulBonusWin;
//			stcChance.ulRecReturnIn[2] += slMaxWin - stcGameInfo.ulBonusWin;
//		}
//		else
//		{
//			stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue -= stcGameInfo.ulBonusWin ;		
//		}	
		stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue -= stcGameInfo.ulBonusWin ;			
	}	
	else
	{
		stcChance.Buffer[DEF_CHANCE_BUF_BONUS].slValue -= stcGameInfo.ulBonusWin ;	//Spec强制时不处理回灌Buff
		stcChance.ulSpecValue[stcChance.ulAsnGift] += stcGameInfo.ulBonusWin; //累加送出的真实虚拟值 	
		
	}	
	

}

// vMaster_Fever_Lose
void vChance_WinFeverProcess( void )
{
	SLONG slMainWin , slFeverWin , slMaxWin ;
		
	slMaxWin = slSlave_WinRead() ;	
	slFeverWin = stcChance.ulFeverTotalWin ;
	slMainWin = slMaxWin - slFeverWin ;

			/*
			{
				char cStr[256];
				vSprint((char *)cStr , STR"WINFVR (%l) %l %l " , stcChance.ulFeverType , slMaxWin , slFeverWin ) ;
				vPcVideo2D_Debug_OutMsg( cStr, 0 ) ;
			}
			*/

	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_DATA_TOTALWIN , slMaxWin ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_RECORD_MAIN_WINTOTAL , slMaxWin ) ;
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_FEVER_WINTOTAL , slFeverWin ) ;
	#ifdef DEF_USE_VGAME_UART_SLAVE
	ulUartCmdRec[DEF_RECORD_DATA_TOTALWIN][0] += slMaxWin ;
	ulUartCmdRec[DEF_RECORD_MAIN_WINTOTAL][0] += slMaxWin ;
	ulUartCmdRec[DEF_REC_FEVER_WINTOTAL][0] += slFeverWin ;
	#endif
	
	// FeverGame 次数的记录，是在游戏结束后，才记录	
	vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM_FEVER_X3+stcChance.ulFeverType-1 , 1 ) ;
	if( slSlave_ReadTotalBet( ) >= mGame_ReadBetForGift( ) )
	{
		vRecord_Add_GiftBet( DEF_REC_SYM_FEVER_X3+stcChance.ulFeverType-1 , 1 ) ;
	}
	vRecord_Save_WinEvent( stcChance.ulFeverTotalWin , stcChance.ulFeverType+2 , DEF_SYMBOL_11 ) ;
			
	stcChance.Buffer[DEF_CHANCE_BUF_MAIN].slValue -=  slMainWin ;		
	if(stcChance.ulAsnState==0)
	{
//		slMaxWin = ( slFeverWin*mGame_ReadMaxBet())/slSlave_ReadBet();
//		if(slMaxWin> slFeverWin)                                   //放到回灌Buff
//		{
//			stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue -= slMaxWin ;	
//			stcChance.slReturnBufValue += slMaxWin -  slFeverWin;
//			stcChance.ulRecReturnIn[3] += slMaxWin -  slFeverWin;
//		}
//		else
//		{
//			stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue -=  slFeverWin ;		
//		}	
		stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue -=  slFeverWin ;		
	}
	else
	{
		stcChance.Buffer[DEF_CHANCE_BUF_FEVER].slValue -=  slFeverWin ;	//Spec强制时不处理回灌Buff	
		stcChance.ulSpecValue[stcChance.ulAsnGift] += slFeverWin; //累加送出的真实虚拟值 	
	}		
					
}

// vMaster_Game_FreeEffect
void vChance_WinFreeProcess( void )
{
		/*
		{
			char cStr[256];
			vSprint((char *)cStr , STR"FRE (%l) %l " , stcGameInfo.ulFreeType , stcGameInfo.ulFreeNowLife ) ;
			vPcVideo2D_Debug_OutMsg( cStr, 0 ) ;
		}
		*/

		// FreeGame 次数的记录，是效果演出时，就先记录
		stcChance.ulRecFreeTimes += stcGameInfo.ulFreeSetLife;
		vRecord_Add( DEF_GAME_ONLY_PLAY , DEF_REC_SYM_FREE_X3+stcGameInfo.ulFreeType-1 , 1 ) ;
		if( slSlave_ReadTotalBet( ) >= mGame_ReadBetForGift( ) )
		{
			vRecord_Add_GiftBet( DEF_REC_SYM_FREE_X3+stcGameInfo.ulFreeType-1 , 1 ) ;
		}	
		
		stcChance.ulFreeType = stcGameInfo.ulFreeType ;
}

//更新Free历史记录
void vChance_RecordFreeUpdate( void )
{
	SLONG slLoop;
	for ( slLoop = 19 ; slLoop >= 1 ; slLoop -- )
	{
		stcChance.ulRecFreeArray[slLoop] = stcChance.ulRecFreeArray[slLoop-1];
	}
	stcChance.ulRecFreeArray[0] = stcChance.ulRecFreeTimes;
	stcChance.ulRecFreeTimes = 0;
		
}

//void vChance_WinProcess( void )
//处理Fever几率
void vChance_FeverProcess( void )
{
	ULONG ulTemp,ulRand,ulNum;
//	SLONG slValue; 
//	UBYTE ubSymID;
	//SLONG slBet;
	if(stcMaster.ubDemoFlag==0)
	{
		stcChance.ulRecFever[1] ++ ;
	}		
	//slBet = slSlave_ReadBet();
//	ulRand = ulRand_ReadMod(64);	
//	if(ulRand<16)
//	{
//		vGameAssign_FeverNull();
//		return;	
//	}	
	if(stcChance.slFeverOdds<=0)
	{
		vGameAssign_FeverSymbol(DEF_SYMBOL_06);
		return;		
	}	
	if(stcGameInfo.ulFeverNowLife>=2)
	{
		ulTemp = ((stcGameInfo.ulFeverNowLife - 1)*3072)/stcChance.slFeverOdds; // WCM
		ulRand = ulRand_ReadMod(0x400);
		if(ulRand<ulTemp)
		{
			vGameAssign_FeverSymbol(DEF_SYMBOL_06);
			return;		
		}

	}
//	slValue = stcChance.slFeverOdds;
//	if(slValue>=5)
//	{
//		slValue = 5;	
//	}
//	slValue = 4 - ulRand_ReadMod(slValue);	
//	ubSymID = DEF_SYMBOL_01 + slValue;	
//	vGameAssign_FeverSymbol(ubSymID);	
//	stcChance.slFeverOdds -= ulFeverGameWinOdds[slValue];	
		
	
	ulRand = ulRand_ReadMod(100);
	if(stcChance.slFeverOdds>=5)
	{
		ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceFeverInfoData1[0],ulRand,5);
		vGameAssign_FeverSymbol(stcChanceFeverInfoData1[ulNum].ulAsnGift);	
		stcChance.slFeverOdds -= stcChanceFeverInfoData1[ulNum].ulTopValue;	
	}	
	else if(stcChance.slFeverOdds>=4)
	{
		ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceFeverInfoData2[0],ulRand,4);
		vGameAssign_FeverSymbol(stcChanceFeverInfoData2[ulNum].ulAsnGift);	
		stcChance.slFeverOdds -= stcChanceFeverInfoData2[ulNum].ulTopValue;	
			
	}	
	else if(stcChance.slFeverOdds>=3)
	{
		ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceFeverInfoData3[0],ulRand,3);
		vGameAssign_FeverSymbol(stcChanceFeverInfoData3[ulNum].ulAsnGift);	
		stcChance.slFeverOdds -= stcChanceFeverInfoData3[ulNum].ulTopValue;	
			
	}	
	else if(stcChance.slFeverOdds>=2)
	{
		ulNum = ulChance_TakeValueNum((VIRTUALINFO*)&stcChanceFeverInfoData4[0],ulRand,2);
		vGameAssign_FeverSymbol(stcChanceFeverInfoData4[ulNum].ulAsnGift);	
		stcChance.slFeverOdds -= stcChanceFeverInfoData4[ulNum].ulTopValue;					
	}	
	else
	{
		vGameAssign_FeverSymbol(DEF_SYMBOL_05);	
		stcChance.slFeverOdds -= 1;	
	}			
	
}
















