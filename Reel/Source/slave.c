#define DEF_SLAVE_C
#include "common.h"
#define FILE_NAME "SLAVE.C"

UBYTE t_ubVersionMemString[32] ;
ULONG t_ulVersionValue ; 
volatile SLONG slBetMinValue ;
volatile SLONG slBetMaxValue ;
SLONG slTempBetValue;//�����ʱ��߷���
SLONG slWinTakeValue ;
ULONG ulWinTakeSpeed ;
SLONG slWinTakeMaxValue ;
UBYTE ubKeyoutFlag;
SLONG slWinValue ;
SLONG slWinRefreshValue ;
SLONG slWupWinValue ;
SLONG slWupWinRefreshValue ;
BETLINE stcBet[DEF_BET_MAXID] ;	
SLONG slBetRefreshValue ;

void vSlave_RefreshInitial( void )
{
	slWinRefreshValue = -1 ;
	slWupWinRefreshValue = -1 ;
	slBetRefreshValue = -1;
}

SLONG slSlave_WinRead( void )
{
	return ( slWinValue ) ;
}

void vSlave_WinAdd( SLONG slValue )
{
	slWinValue += slValue ;
}

void vSlave_WinSub( SLONG slValue )
{
	slWinValue -= slValue ;
}

void vSlave_WinSet( SLONG slValue )
{
	slWinValue = slValue ;
}

SLONG slSlave_WinIsRefresh( void )
{
	if ( slWinRefreshValue != slWinValue )
	{
		slWinRefreshValue = slWinValue ;
		return ( 1 ) ;
	}
	return ( 0 ) ;
}



SLONG slSlave_WupWinRead( void )
{
	return ( slWupWinValue ) ;
}

void vSlave_WupWinAdd( SLONG slValue )
{
	slWupWinValue += slValue ;
}

void vSlave_WupWinSub( SLONG slValue )
{
	slWupWinValue -= slValue ;
}

void vSlave_WupWinSet( SLONG slValue )
{
	slWupWinValue = slValue ;
}

SLONG slSlave_WupWinIsRefresh( void )
{
	if ( slWupWinRefreshValue != slWupWinValue )
	{
		slWupWinRefreshValue = slWupWinValue ;
		return ( 1 ) ;
	}
	return ( 0 ) ;
}

void vSlave_Reset( void )
{
	UBYTE ubSlaveID ;
	
	// +1 ����Ϊ DEF_GAME_PLAYER_MAX �����λ����������и������ܺ�
	for (ubSlaveID = 0 ; ubSlaveID < DEF_GAME_PLAYER_MAX+1 ; ++ubSlaveID)
	{
		vMemory_Set( (UBYTE *)&stcSlave[ubSlaveID] , 0x00 , sizeof(SLAVE_INFO) ) ;
	}
	vMemory_Set( (UBYTE *)&stcBet, 0x00 , sizeof(stcBet) ) ;
	slBetMinValue  = mGame_ReadMinBet( ) ;
	slBetMaxValue  = mGame_ReadMaxBet( ) ;
	slWinValue=0;
	slWupWinValue=0;
	vSlave_SetLastLine(9);
    vSlave_SetLine(9);
    vSlave_BetSet(slBetMaxValue);    
    ulUiRefreshValue[DEF_UI_BET]=slBetMaxValue;
    ulUiRefreshValue[DEF_UI_TOTAL] = slSlave_ReadTotalBet();
	vSlave_UpDateLastBet( );
}

void vSlave_Initial( void )
{
	UBYTE ubSlaveID ;
	
	for (ubSlaveID = 0 ; ubSlaveID < DEF_GAME_PLAYER_MAX ; ++ubSlaveID)
	{
		stcSlave[ubSlaveID].ubState = PROC_MASTER_GAME_INIT ;
	}
	vSlave_RefreshInitial( );
	slBetMinValue  = mGame_ReadMinBet( ) ;
	slBetMaxValue  = mGame_ReadMaxBet( ) ;
}





void vSlave_WinTakeInitial( SLONG slMaxValue )
{
	ulWinTakeSpeed = 8 ;
	slWinTakeValue = 2 ;
	if(slMaxValue<63)
	{
		slMaxValue = 63;	
	}	
	//if(slMaxValue == 0)	slMaxValue = 1;	
	slWinTakeMaxValue = slMaxValue ;
}

void vSlave_WinJPTakeInitial( void )
{
	ulWinTakeSpeed = 0 ;
	slWinTakeValue = 1 ;
}
ULONG ulSlave_WinJPTakeAddSpeed( ULONG ulValue )
{	
	ulWinTakeSpeed++;
	if(ulWinTakeSpeed >= 10)
	{
		ulWinTakeSpeed=0;
		if(ulValue>11*slWinTakeValue)
		{
			slWinTakeValue *= 11;	
		}			
	}	
	if(ulValue==slWinTakeValue)
	{
		if(slWinTakeValue>=11)
		{
			slWinTakeValue /= 11; 	
		}		
	}	
	if(ulValue < slWinTakeValue)
	{
		while(1)
		{
			if(slWinTakeValue>=11)
			{
				slWinTakeValue /= 11; 	
				if(ulValue > slWinTakeValue)
				{
					break;		
				}		
				
			}
			else
			{
				slWinTakeValue=1;
				break;	
			}		
				
		}	
	
	}	
	return slWinTakeValue;
	
}

void vSlave_WinTakeAddSpeed( void )
{
	if(slWinTakeValue<=2)
	{
		ulWinTakeSpeed = 4;
    	slWinTakeValue = 4;
	}	
	else if(slWinTakeValue<=4)
	{
		ulWinTakeSpeed = 2;
    	slWinTakeValue = 8;
	}	
	else if(slWinTakeValue<=8)
	{
		ulWinTakeSpeed = 1;
    	slWinTakeValue = 16;
	}	
	else if(slWinTakeValue<=16)
	{
		ulWinTakeSpeed = 1;
    	slWinTakeValue = 63;
	}
	else 
	{
		ulWinTakeSpeed = 1;
		if(slWinTakeMaxValue>=slWinTakeValue)
		{
			slWinTakeValue = slWinTakeMaxValue;
		}	
		else
		{
			slWinTakeValue = 63;
		}	
    	
	}
	
	/*
	if ( ulWinTakeSpeed > 1 )
    {
    		
        ulWinTakeSpeed -- ;
    }
    else
    {
        if ( slWinTakeValue < slWinTakeMaxValue )
        {
            slWinTakeValue = slWinTakeValue * 2 ;
        }
    }
    */
}


void vSlave_SetWinTakeValueMax( void )
{
	slWinTakeValue = slWinTakeMaxValue;
}

SLONG slSlave_WinCanTake( ULONG ulCount )
{
	if ( ulWinTakeSpeed == 0 )
	{
		return ( 1 ) ;
	}
	if ( ulWinTakeSpeed >= 10 )
	{
		return ( 1 ) ;
	}
	if ( ( ulCount % ulWinTakeSpeed ) == 0 )
	{
		return ( 1 ) ;
	}
	#ifdef DEF_TEST_AUTOPLAY
	if ( ulKey_Touch( KEY_PCI_97_TEST ) )
	{
		return ( 1 ) ;
	}
	#endif
	return ( 0 ) ;
}

SLONG slSlave_TakeWinToCredit( void )
{
	SLONG slWin;
	slWin = slSlave_WinRead();
	if ( slWin  <= 0 )
	{
		//vPlaySound_Play(DEF_WAV_SCORE_05,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_20);
		return ( 0 ) ;
	}
	
	#ifdef DEF_TEST_AUTOPLAY
	if ( ulKey_Touch( KEY_PCI_97_TEST ) )
	{
		slWinTakeValue = slSlave_WinRead() ;
	}
	#endif
	//vShowLib_GameLightWin( );
	//vPlaySound_Effect(DEF_WAV_MAIN_SCORE,DEF_SOUND_VOL_SMALL);	
	if ( slWin >= slWinTakeValue )
	{
		
		vSlave_WinSub(slWinTakeValue);
		ulCredit_Add(DEF_GAME_ONLY_PLAY, slWinTakeValue ) ;
	}
	else
	{
		ulCredit_Add(DEF_GAME_ONLY_PLAY, slWin ) ;
		vSlave_WinSet(0);
	}	
	vSlaveShow_ShowWin( ) ;		
	return ( 1 ) ;
}

SLONG slSlave_TakeToCredit( ULONG ulCount )
{
	if ( ulWinTakeSpeed == 0 )
	{
		ulWinTakeSpeed = 1 ;
	}
	if ( ulWinTakeSpeed >= 9 )
	{
		ulWinTakeSpeed = 8 ;
	}
	if ( slWinTakeValue <= 0 )
	{
		slWinTakeValue = 1 ;
	}
	if ( slWinTakeValue > slWinTakeMaxValue )
	{
		slWinTakeValue = slWinTakeMaxValue ;
	}
	if ( slSlave_WinCanTake( ulCount ) )
	{
		return ( slSlave_TakeWinToCredit( ) ) ;
	}
	return ( 1 ) ;
}


SLONG slSlave_WupTakeWinToCredit( void )
{
	SLONG slWin;
	slWin = slSlave_WupWinRead();
	if ( slWin  <= 0 )
	{		
		return ( 0 ) ;
	}
		
	#ifdef DEF_TEST_AUTOPLAY
	if ( ulKey_Touch( KEY_PCI_97_TEST ) )
	{
		slWinTakeValue = slWin ;
	}
	#endif
	
	if ( slWin >= slWinTakeValue )
	{		
		vSlave_WupWinSub(slWinTakeValue);
		ulCredit_Add(DEF_GAME_ONLY_PLAY, slWinTakeValue ) ;
	}
	else
	{
		ulCredit_Add(DEF_GAME_ONLY_PLAY, slWin ) ;
		 vSlave_WupWinSet(0);	
	}		
	return ( 1 ) ;
}

SLONG slSlave_WupTakeToCredit( ULONG ulCount )
{
	if ( ulWinTakeSpeed == 0 )
	{
		ulWinTakeSpeed = 1 ;
	}
	if ( ulWinTakeSpeed >= 9 )
	{
		ulWinTakeSpeed = 8 ;
	}
	if ( slWinTakeValue <= 0 )
	{
		slWinTakeValue = 1 ;
	}
	if ( slWinTakeValue > slWinTakeMaxValue )
	{
		slWinTakeValue = slWinTakeMaxValue ;
	}
	if ( slSlave_WinCanTake( ulCount ) )
	{
		return ( slSlave_WupTakeWinToCredit( ) ) ;
	}
	return ( 1 ) ;
}


















SLONG slSlave_ReadLastLine( void )
{
    return (stcBet[DEF_BET_LST].slLine ) ;
}
SLONG slSlave_ReadLastBet( void )
{
    return ( stcBet[DEF_BET_LST].slBet ) ;
}
SLONG slSlave_ReadLastTotalBet( void )
{
    return ( stcBet[DEF_BET_LST].slLine * stcBet[DEF_BET_LST].slBet ) ;
}


// Ѻע�ۼӴ������
// ����  1 ���������Ѻעֵ
// ���� -1 ���� Credit ����
// ����  0 �������Լ���Ѻע 

SLONG slSlave_AddBetProcess(SLONG slAddValue,ULONG ulCount )
{
    SLONG slBetValue,slLineBet,slLoop,slLine ;
    SLONG slTotalBet,slBet ;
    ULONG ulCredit;
    slBetMinValue  = mGame_ReadMinBet( ) ;
	slBetMaxValue  = mGame_ReadMaxBet( ) ;	
	ulCredit = ulCredit_Read(DEF_GAME_ONLY_PLAY);	
	slLine = stcBet[DEF_BET_NOW].slLine;
	slTotalBet = slSlave_ReadTotalBet( );
	slBet = slSlave_ReadBet( );
	if(ulCredit)
	{
		if(slTotalBet > ulCredit)
		{
			for( slLoop = slLine ; slLoop > 0 ; slLoop -= 2 )    	
    		{
    			slLineBet =  ulCredit /slLoop;	
    			if (slLineBet)
	            {
	            	if(slLineBet > slBetMinValue)
	            	{
	            		slLineBet = slBetMinValue;	
	            		slTempBetValue = slLineBet;
	            	}	
	                stcBet[DEF_BET_NOW].slLine = slLoop ;
	                stcBet[DEF_BET_NOW].slBet  = slLineBet  ;
	                return ( 1 ) ;
	                
	            }
	            else 
	            {
	                if ( slLine == 1 )
	                {
	                    stcBet[DEF_BET_NOW].slLine = 1 ;
	                    stcBet[DEF_BET_NOW].slBet  = ulCredit ;	 
	                    return ( 1 ) ;                  
	                }
	            }
    		}	
		}			
		else
		{			
			slLineBet =  ulCredit / slLine;	
			if(slLineBet>=slBetMaxValue)	
			{
				slLineBet = slBetMaxValue;
			}			
			if (( slBet >= slBetMaxValue )||(slLineBet==slBet))
			{
				if(ulCount==1)
				{
					if(slLineBet >= slBetMinValue)
	            	{
	            		slLineBet = slBetMinValue;	
	            		stcBet[DEF_BET_NOW].slBet  = slLineBet  ;	
	            		slTempBetValue = slLineBet;               
	            	}	
				}				
				return ( 1 ) ;
			} 
			slBetValue = (slBet+slAddValue) * slLine ;
			if(ulCredit>=slBetValue)
			{
				stcBet[DEF_BET_NOW].slBet += slAddValue;
				if(stcBet[DEF_BET_NOW].slBet>=slBetMinValue)
				{
					slTempBetValue = stcBet[DEF_BET_NOW].slBet;
				}
				return ( 1 ) ;			
			}	
			else
			{
				if(slLineBet < slBet+slAddValue)
				{				
					stcBet[DEF_BET_NOW].slBet = slLineBet;
					if(slLineBet>=slBetMinValue)
					{
						slTempBetValue = slLineBet;
					}	
					return ( 1 ) ;	
				}
			}	
				
			
			
		}	
	}	
    else
    {
    	return ( -1 ) ; // Error
    }	
    
    
	return ( 0 ) ;
}

SLONG slSlave_SetFixBet( SLONG slMaxBet )
{
    SLONG slLine ;
    SLONG slLineBet ;

    if( slMaxBet )
    {
        for( slLine = stcBet[DEF_BET_LST].slLine ; slLine > 0 ; slLine -= 2 )
        {
            slLineBet =  slMaxBet /  slLine ;
            if ( slLineBet )
            {
            	if(slLineBet > slBetMaxValue)
            	{
            		slLineBet = slBetMaxValue;	
            	}	
                stcBet[DEF_BET_NOW].slLine = slLine ;
                stcBet[DEF_BET_NOW].slBet  = slLineBet  ;
                return 1 ;
            }
            else 
            {
                if ( slLine == 1 )
                {
                    stcBet[DEF_BET_NOW].slLine = 1 ;
                    stcBet[DEF_BET_NOW].slBet  = slMaxBet  ;
                    return 1 ; 
                }
            }
        }
    }
    return 0 ;
}





// ֱ�����ϱ�ѺעΪѺעֵ������Ѻעֵ
// ���� 0 �����޷�ֱ���Զ�Ѻע
// ���� 1 �����ֱ��Ѻע 
SLONG slSlave_BetStartGame( void )
{
	slBetMinValue  = mGame_ReadMinBet( ) ;
	slBetMaxValue  = mGame_ReadMaxBet( ) ;
	if( ulCredit_Read(DEF_GAME_ONLY_PLAY) )
    {    	
        if( slSlave_ReadTotalBet() )
        {
            if( ulCredit_Read(DEF_GAME_ONLY_PLAY) >= slSlave_ReadTotalBet() )
            {            	
            	if(slSlave_ReadTotalBet() < slBetMinValue*slSlave_ReadLine())
            	{
            		if(ulCredit_Read(DEF_GAME_ONLY_PLAY)>=slBetMinValue*slSlave_ReadLine())
            		{
            			vSlave_BetSet(slBetMinValue ) ;                    
                    	ulCredit_Sub(DEF_GAME_ONLY_PLAY, slBetMinValue*slSlave_ReadLine()) ;
            		}	
            		else
            		{
            			ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;
            		}	
            	}
            	else
            	{
            		ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;            		
            	}	
                return 1 ; 
            }
            else
            {
                if( slSlave_SetFixBet( ulCredit_Read(DEF_GAME_ONLY_PLAY) ) )
                {
                    if( ulCredit_Read(DEF_GAME_ONLY_PLAY) >= slSlave_ReadTotalBet() )
                    {
                        ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;
                        return 1 ; 
                    }
                } 
            }  
        }
        else
        {
            if( slSlave_ReadLastTotalBet() )
            {
                if( ulCredit_Read(DEF_GAME_ONLY_PLAY) >= slSlave_ReadLastTotalBet() )
                {
                	if(slSlave_ReadLastTotalBet() < slBetMinValue*slSlave_ReadLine())
                	{
                		vSlave_BetSet(slBetMinValue ) ;                    
	                    ulCredit_Sub(DEF_GAME_ONLY_PLAY, slBetMinValue*slSlave_ReadLine()) ;
                		
                	}
                	else
                	{
                		vSlave_BetSet( stcBet[DEF_BET_LST].slBet ) ;
	                    vSlave_SetLine(stcBet[DEF_BET_LST].slLine ) ; 
	                    ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;
                		
                	}		
                    
                    return 1 ; 
                }
                else
                {
                    if( slSlave_SetFixBet( ulCredit_Read(DEF_GAME_ONLY_PLAY) ) )
                    {
                        if( ulCredit_Read(DEF_GAME_ONLY_PLAY) >= slSlave_ReadTotalBet() )
                        {
                            ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;
                            return 1 ; 
                        }
                    } 
                }   
            }
            else
            {
				if ( ulCredit_Read( DEF_GAME_ONLY_PLAY) >= slBetMinValue*slSlave_ReadLine() )
				{
						vSlave_BetSet(slBetMinValue ) ;                    
	                    ulCredit_Sub(DEF_GAME_ONLY_PLAY, slBetMinValue*slSlave_ReadLine()) ;
						return ( 1 ) ;
				}
				else
				{
					if ( ulCredit_Read( DEF_GAME_ONLY_PLAY) >= slBetMinValue)
					{
						vSlave_BetSet(slBetMinValue ) ;
	                    vSlave_SetLine( 1 ) ; 
	                    ulCredit_Sub(DEF_GAME_ONLY_PLAY, slBetMinValue ) ;
						return ( 1 ) ;
						
					}
					else
					{
						if ( ulCredit_Read( DEF_GAME_ONLY_PLAY) )
						{
							vSlave_BetSet(ulCredit_Read( DEF_GAME_ONLY_PLAY) ) ;
		                    vSlave_SetLine( 1 ) ;
							ulCredit_Sub( DEF_GAME_ONLY_PLAY,ulCredit_Read( DEF_GAME_ONLY_PLAY ) ) ;
							return ( 1 ) ;
						}	
						
					}	
				}	
               
            }
        }
    }
    else
    {
        //ASSERT( 0 )
    }
    return 0 ;  
}

SLONG slBet_MaxBetStartGame( void )
{	
	slBetMinValue  = mGame_ReadMinBet( ) ;
	slBetMaxValue  = mGame_ReadMaxBet( ) ;
    if( ulCredit_Read(DEF_GAME_ONLY_PLAY) >= slBetMaxValue * stcBet[DEF_BET_NOW].slLine )
    {
        stcBet[DEF_BET_NOW].slBet = slBetMaxValue ;
        ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;
        return 1 ; 
    }	
    if( slSlave_SetFixBet( ulCredit_Read(DEF_GAME_ONLY_PLAY) ) )
    {
        if( ulCredit_Read(DEF_GAME_ONLY_PLAY) >= slSlave_ReadTotalBet() )
        {
            ulCredit_Sub( DEF_GAME_ONLY_PLAY,slSlave_ReadTotalBet() ) ;
            return 1 ; 
        }
    }
    return 0 ; 
}


void vSlave_SetLine( SLONG slLine )
{
    stcBet[DEF_BET_NOW].slLine = slLine ;
}

void vSlave_SetLastLine( SLONG slLine )
{
    stcBet[DEF_BET_LST].slLine = slLine ;
}  

SLONG slSlave_BetIsRefresh( void )
{
    if( slBetRefreshValue != ((stcBet[DEF_BET_NOW].slLine*1000) + stcBet[DEF_BET_NOW].slBet) )
    {
        slBetRefreshValue = ((stcBet[DEF_BET_NOW].slLine*1000) + stcBet[DEF_BET_NOW].slBet) ;
        return ( 1 ) ;
    }
    return ( 0 ) ;
}

void vSlave_LineProcess( void )
{
    SLONG slLine,slLoop,slLineBet;
    ULONG ulCredit;
    ulCredit = ulCredit_Read(DEF_GAME_ONLY_PLAY);
    switch( stcBet[DEF_BET_NOW].slLine )
    {
        case 1 : slLine = 3 ; break ;
        case 3 : slLine = 5 ; break ;
        case 5 : slLine = 7 ; break ;   
        case 7 : slLine = 9 ; break ;  	    
        case 9 : slLine = 1 ; break ;
        default: slLine = 9 ; break ;
    }
    if(ulCredit )
    {    	
    	if(ulCredit >= slLine*slTempBetValue)
    	{
    		stcBet[DEF_BET_NOW].slLine = slLine ;
	        stcBet[DEF_BET_NOW].slBet  = slTempBetValue ; 	        
    	}	
    	else
    	{
    		for( slLoop = slLine ; slLoop > 0 ; slLoop -= 2 )    	
    		{
    			slLineBet =  ulCredit /  slLoop;	
    			if ( slLineBet )
	            {
	            	if(slLineBet > slBetMaxValue)
	            	{
	            		slLineBet = slBetMaxValue;	
	            	}	
	                stcBet[DEF_BET_NOW].slLine = slLine ;
	                stcBet[DEF_BET_NOW].slBet  = slLineBet  ;
	                return ; 
	                
	            }
	            else 
	            {
	                if ( slLine == 1 )
	                {
	                    stcBet[DEF_BET_NOW].slLine = 1 ;
	                    stcBet[DEF_BET_NOW].slBet  = ulCredit ;	 
	                    return ;                   
	                }
	            }
    		}	
    	}	
    }
}

//�ж��Ƿ񶯵���̬����
void vSlave_UiIsRefresh( void )
{
	
	if ( ulUiRefreshValue[DEF_UI_LINE] != slSlave_ReadLine() )
	{
		if(ulUiRefreshValue[DEF_UI_LINE])
		{
			ubUiRefreshFlag[DEF_UI_LINE] = 1;
		}			
		ulUiRefreshValue[DEF_UI_LINE] = slSlave_ReadLine();
	}
	if ( ulUiRefreshValue[DEF_UI_BET] != slSlave_ReadBet() )
	{
		if(slSlave_ReadBet())
		{
			ubUiRefreshFlag[DEF_UI_BET] = 1;
			if(stcMaster.ulState == PROC_MASTER_GAME_BET)
			{						
				vPlaySound_Play(DEF_WAV_SOUND_SCORE,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);				
			}	
		}			
		ulUiRefreshValue[DEF_UI_BET] = slSlave_ReadBet();
	}
	if ( ulUiRefreshValue[DEF_UI_TOTAL] != slSlave_ReadTotalBet() )
	{
		if(slSlave_ReadTotalBet())
		{
			ubUiRefreshFlag[DEF_UI_TOTAL] = 1;
		}		
		ulUiRefreshValue[DEF_UI_TOTAL] = slSlave_ReadTotalBet();
	}
	if ( ulUiRefreshValue[DEF_UI_PAID] != slSlave_WinRead() )
	{
		ubUiRefreshFlag[DEF_UI_PAID] = 1;
		ulUiRefreshValue[DEF_UI_PAID] = slSlave_WinRead();
	}
	if ( ulUiRefreshValue[DEF_UI_CREDIT] != ulCredit_Read(DEF_GAME_ONLY_PLAY) )
	{
		ubUiRefreshFlag[DEF_UI_CREDIT] = 1;
		ulUiRefreshValue[DEF_UI_CREDIT] = ulCredit_Read(DEF_GAME_ONLY_PLAY);
	}
	
	if ( ulUiRefreshValue[DEF_UI_WIN] != slSlave_WupWinRead() )
	{
		if((stcMaster.ulState < PROC_MASTER_WUP_EFT)||(stcMaster.ulState > PROC_MASTER_WUP_LIMIT))
		{
			ubUiRefreshFlag[DEF_UI_WIN] = 1;			
		}	
		ulUiRefreshValue[DEF_UI_WIN] = slSlave_WupWinRead();
	}
	
}


SLONG slSlave_ReadTotalBet( void )
{
    return ( stcBet[DEF_BET_NOW].slLine * stcBet[DEF_BET_NOW].slBet ) ;   
}
SLONG slSlave_ReadLine( void )
{
    return ( stcBet[DEF_BET_NOW].slLine ) ;
}
SLONG slSlave_ReadBet( void )
{
    return ( stcBet[DEF_BET_NOW].slBet ) ;
}

void vSlave_BetSet( SLONG slValue )
{
   stcBet[DEF_BET_NOW].slBet = slValue ;
}

void vSlave_UpDateLastBet( void )
{	
    stcBet[DEF_BET_LST].slLine = stcBet[DEF_BET_NOW].slLine ;
    if( stcBet[DEF_BET_NOW].slBet>=slBetMinValue )
    {
        stcBet[DEF_BET_LST].slBet  = stcBet[DEF_BET_NOW].slBet  ;
        slTempBetValue = stcBet[DEF_BET_NOW].slBet;
    }
}

void vSlave_GameInitial( UBYTE ubSlaveID )
{
	//ULONG	i ;
	
	if( ubSlaveID >= DEF_GAME_PLAYER_MAX ) return ;

	stcSlave[ubSlaveID].ulBet = 0 ;
	stcSlave[ubSlaveID].ulWin = 0 ;
	//stcChance.ulHandselWin = 0 ;   
	/*
	for(i=0;i<DEF_HANDCARD_MAX;i++)
	{
		stcSlave[ubSlaveID].ubHold[i] = 0 ;
		stcSlave[ubSlaveID].ubHoldCount[i] = 0 ;
		stcSlave[ubSlaveID].ubJKCount[i] = 0 ;
		stcSlave[ubSlaveID].ubOpenCard[i] = 0;
	}
	*/
	
	vSlaveShow_ShowBet(  ) ;	
	vSlaveShow_ShowWin(  ) ;
	//vSlaveShow_ShowExtraMoney( ubSlaveID,stcChance.ulHandselWin) ;
}

void vSlave_CoinProcess( UBYTE ubSlaveID )
{
	ULONG	ulCoinBit,ulWav ;
	
	ulCoinBit = 0;
	if( ubSlaveID >= DEF_GAME_PLAYER_MAX ) return ;

	if( stcSlave[ubSlaveID].ulError & DEF_SLAVE_ERROR_COIN )
	{	// ��Ͷ�Ҵ���״̬������£���ʾ����ѶϢ
		//vSlaveShow_ShowCoinError( ubSlaveID ) ;		
		// �ȴ�һ��ʱ����Զ��ų�����״̬
		stcSlaveShow[ubSlaveID].ulCoinErrorCount ++ ;
		if( stcSlaveShow[ubSlaveID].ulCoinErrorCount >= 1800+14 )
		{			
			stcSlaveShow[ubSlaveID].ulCoinErrorCount = 0;
			stcSlave[ubSlaveID].ulError &= ~DEF_SLAVE_ERROR_COIN ;
			#ifdef DEF_USE_IOBOARD
				vUserIO_CleanCoinError( ubSlaveID ) ;
			#endif
			#ifdef DEF_USE_IOPCI
				vKey_EnableActionFlag( KEY_PCI_COIN_A ) ; vLamp_On( LAMP_PCI_COIN_A_POWER ) ;
				vKey_EnableActionFlag( KEY_PCI_COIN_C ) ; vLamp_On( LAMP_PCI_COIN_C_POWER ) ;
			#endif	
		}
	}
	else 
	{
	#ifdef DEF_USE_IOBOARD	
		if( ulUserIO_CheckISCoinError( ubSlaveID ) )
	#endif
	#ifdef DEF_USE_IOPCI
		if(( ulKey_ActionIsError( KEY_PCI_COIN_A ) )||( ulKey_ActionIsError( KEY_PCI_COIN_C ) ))
	#endif		
		{	// ����Ƿ���Ͷ�Ҵ���
			//vSlaveShow_ShowCoinError( ubSlaveID ) ;		
			
			stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_COIN ;
			//stcSlave[ubSlaveID].ulCoinErrorShowTimer = 0 ;
			
		#ifdef DEF_USE_IOBOARD
		#endif
		#ifdef DEF_USE_IOPCI
			vKey_DisableActionFlag( KEY_PCI_COIN_A ) ; vLamp_Off( LAMP_PCI_COIN_A_POWER ) ;
			vKey_DisableActionFlag( KEY_PCI_COIN_C ) ; vLamp_Off( LAMP_PCI_COIN_C_POWER ) ;
		#endif	
		}	
		else
		{
		
		#ifdef DEF_USE_IOBOARD
			{	// ��IO�������£�Ͷ�ҡ����ֵķ������Ǵ�userio������ģ�����Ͳ���Ҫ����
			}
		#endif
		#ifdef DEF_USE_IOPCI
			if( ulCredit_Read( ubSlaveID ) < mGame_ReadCreditLimit( ) )
			{	// û��IO�������£����봦���Լ���Ͷ�ҵķ���
				
				ULONG	ulTemp ;
				
				if( ubKey_GetActionStatus( KEY_PCI_COIN_A ) == DEF_KEY_DISABLE )
				{
					vKey_EnableActionFlag( KEY_PCI_COIN_A ) ; vLamp_On( LAMP_PCI_COIN_A_POWER ) ;
				}				
				if( ulKey_ReadActionFlag( KEY_PCI_COIN_A ) )
				{
					ulTemp = mGame_ReadCoinARate( ) ;					
					if( ulTemp )
					{
						ulCredit_Add( ubSlaveID , ulTemp ) ;
						
						vRecord_Add( ubSlaveID , DEF_RECORD_DATA_COIN , ulTemp ) ;
						vRecord_Add( ubSlaveID , DEF_RECORD_DATA_COIN_A , ulTemp ) ;
						#ifdef DEF_USE_VGAME_UART_SLAVE
						ulUartCmdRec[DEF_RECORD_DATA_COIN][0] += ulTemp ;
						ulUartCmdRec[DEF_RECORD_DATA_COIN_A][0] += ulTemp ;
						#endif
						vMeter_Add( DEF_METER_COIN_A , 1 ) ;

						vPlaySound_Play(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_20);
						//vPlaySound_Effect(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_SMALL);
						ulCoinBit = 1;//����Ͷ�ұ�־ 
						#ifdef DEF_GTRULE_GTVG	
						vGTVG_UpdateRepoRecord( ulTemp , 0 , 0 ) ;
						#endif
					}
				}

				if( ubKey_GetActionStatus( KEY_PCI_COIN_C ) == DEF_KEY_DISABLE )
				{
					vKey_EnableActionFlag( KEY_PCI_COIN_C ) ; vLamp_On( LAMP_PCI_COIN_C_POWER ) ;
				}
				if( ulKey_ReadActionFlag( KEY_PCI_COIN_C ) )
				{
					ulTemp = mGame_ReadCoinCRate( ) ;
					
					if( ulTemp )
					{
						ulCredit_Add( ubSlaveID , ulTemp ) ;
						
						vRecord_Add( ubSlaveID , DEF_RECORD_DATA_COIN , ulTemp ) ;
						vRecord_Add( ubSlaveID , DEF_RECORD_DATA_COIN_C , ulTemp ) ;
						#ifdef DEF_USE_VGAME_UART_SLAVE
						ulUartCmdRec[DEF_RECORD_DATA_COIN][0] += ulTemp ;
						ulUartCmdRec[DEF_RECORD_DATA_COIN_C][0] += ulTemp ;
						#endif
						vMeter_Add( DEF_METER_COIN_A , 1 ) ;

						vPlaySound_Play(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_20);
						//vPlaySound_Effect(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_SMALL);
						ulCoinBit = 1;//����Ͷ�ұ�־ 
						#ifdef DEF_GTRULE_GTVG	
						vGTVG_UpdateRepoRecord( ulTemp , 0 , 0 ) ;
						#endif
					}
				}
			}
			else
			{				
				

				if((ulKey_Push( KEY_PCI_COIN_A )||ulKey_Push( KEY_PCI_COIN_C ))&&mGame_ReadCoinCRate( ))
			    {			    	
			    	vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_030),161,664);	
			    	stcSlave[ubSlaveID].ulCoinLimitTimer = 120;				
			    }	
			
				if( ubKey_GetActionStatus( KEY_PCI_COIN_A ) != DEF_KEY_DISABLE )
				{
					vKey_DisableActionFlag( KEY_PCI_COIN_A ) ; vLamp_Off( LAMP_PCI_COIN_A_POWER ) ;
				}
				if( ubKey_GetActionStatus( KEY_PCI_COIN_C ) != DEF_KEY_DISABLE )
				{
					vKey_DisableActionFlag( KEY_PCI_COIN_C ) ; vLamp_Off( LAMP_PCI_COIN_C_POWER ) ;
				}				
				
			}
		#endif
		
		}
	}
	
	#ifdef DEF_USE_IOPCI
	{	// û��IO�������£����봦���Լ��Ŀ��ֵķ���
		
		ULONG	ulTemp ;
				
		// ��Ϊ�����ж������������һ��10�����̰�һ��1��
		ulTemp = ulKey_ReadActionFlag( KEY_PCI_KEYIN_B ) ;
		if(ulCredit_Read( ubSlaveID ) >= mGame_ReadCreditLimit( ))
		{			
			if(ulTemp&&mGame_ReadKeyInBRate( ))
			{
				vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_030),161,664);									
				stcSlave[ubSlaveID].ulCoinLimitTimer = 120;	
			}	
			
		}
		#ifdef DEF_TEST_AUTOPLAY_COIN
		#ifdef DEF_TEST_ALWAYS_AUTO_2
		if ( ubAutoPlay2_isRun )
		#else
		if ( ulKey_Touch( KEY_PCI_97_TEST ) )
		#endif	
		{
			if( ulCredit_Read( ubSlaveID ) < ( mGame_ReadMaxBet( ) * 10 ) )  //���ʱ�Զ��Ϸ�
			{
				ulTemp = 10 ;
			}
		}
		#endif			
		if(( ulTemp )&&( ulCredit_Read( ubSlaveID ) < mGame_ReadCreditLimit( ) )&&( mGame_ReadKeyInBRate() ))
		{
			ulTemp *= mGame_ReadKeyInBRate( ) ;
			
			ulCredit_Add( ubSlaveID , ulTemp ) ;
			
			{
				stcSlave[ubSlaveID].slShowKeyinValue += ulTemp ;
				stcSlave[ubSlaveID].ulShowKeyinValueCnt = 5*60 ;
			}

			vRecord_Add( ubSlaveID , DEF_RECORD_DATA_KEYIN , ulTemp ) ;
			vRecord_Add( ubSlaveID , DEF_RECORD_DATA_KEYIN_B , ulTemp ) ;
			#ifdef DEF_USE_VGAME_UART_SLAVE
			ulUartCmdRec[DEF_RECORD_DATA_KEYIN][0] += ulTemp ;
			ulUartCmdRec[DEF_RECORD_DATA_KEYIN_B][0] += ulTemp ;
			#endif
			vMeter_Add( DEF_METER_KEYIN , 1 ) ;

			vPlaySound_Play(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_20);
			//vPlaySound_Effect(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_SMALL);
			ulCoinBit = 2;//���п��ֱ�־ 
			#ifdef DEF_GTRULE_GTVG	
			vGTVG_UpdateRepoRecord( ulTemp , 0 , 0 ) ;
			#endif
		}

		ulTemp = ulKey_ReadActionFlag( KEY_PCI_KEYIN_D ) ;
		if(ulCredit_Read( ubSlaveID ) >= mGame_ReadCreditLimit( ))
		{			
			if(ulTemp&&mGame_ReadKeyInBRate( ))
			{
				vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_030),161,664);									
				stcSlave[ubSlaveID].ulCoinLimitTimer = 120;	
			}	
			
		}
		if(( ulTemp )&&( ulCredit_Read( ubSlaveID ) < mGame_ReadCreditLimit( ) )&&( mGame_ReadKeyInDRate() ))
		{
			ulTemp *= mGame_ReadKeyInDRate( ) ;
			
			ulCredit_Add( ubSlaveID , ulTemp ) ;

			{
				stcSlave[ubSlaveID].slShowKeyinValue += ulTemp ;
				stcSlave[ubSlaveID].ulShowKeyinValueCnt = 5*60 ;
			}

			vRecord_Add( ubSlaveID , DEF_RECORD_DATA_KEYIN , ulTemp ) ;
			vRecord_Add( ubSlaveID , DEF_RECORD_DATA_KEYIN_D , ulTemp ) ;
			#ifdef DEF_USE_VGAME_UART_SLAVE
			ulUartCmdRec[DEF_RECORD_DATA_KEYIN][0] += ulTemp ;
			ulUartCmdRec[DEF_RECORD_DATA_KEYIN_D][0] += ulTemp ;
			#endif
			vMeter_Add( DEF_METER_KEYIN , 1 ) ;

			vPlaySound_Play(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_MAX,DEF_SOUND_CH_NONE_20);
			//vPlaySound_Effect(DEF_WAV_SOUND_COIN,DEF_SOUND_VOL_SMALL);
			ulCoinBit = 2;//���п��ֱ�־ 
			#ifdef DEF_GTRULE_GTVG	
			vGTVG_UpdateRepoRecord( ulTemp , 0 , 0 ) ;
			#endif
		}
		
	}
	

	if( stcSlave[ubSlaveID].ulError & DEF_SLAVE_ERROR_SYSLIMIT )
	{
		if( ulCredit_Read( ubSlaveID ) < mGame_ReadSystemLimit( ) )			
		{
			// �����ϵͳ��̨��ѶϢ
			stcSlave[ubSlaveID].ulError &= ~DEF_SLAVE_ERROR_SYSLIMIT ;
		}
	}
	else
	{	
		if( ulCredit_Read( ubSlaveID ) > mGame_ReadSystemLimit( ) )
		{
			// ��ʾ��ϵͳ��̨����ѶϢ�����ҽ�ֹ������һ����Ϸ
			stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_SYSLIMIT ;
		}
	}

	#endif
	if( ulCredit_IsRefresh( ubSlaveID ) )
	{	
		if(ulCoinBit == 0)
		{
			switch ( stcMaster.ulState )
			{
				case PROC_MASTER_FEVER_CHOOSE:
				case PROC_MASTER_GAME_OVERALEFT:
				case PROC_MASTER_GAME_BIGODDSEFT:
				case PROC_MASTER_GAME_EXITFREE:
				case PROC_MASTER_GAME_BONUSEFT:
					if(stcMaster.ulIndex != 2)
					{
						vPlaySound_Play(DEF_WAV_SOUND_SCORE,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);	
						break ;
					}
				case PROC_MASTER_GAME_TAKE:
				case PROC_MASTER_WUP_GTAKE:
				case PROC_MASTER_WUP_TAKE:
				{						
					if(slWinTakeValue<=4)
					{
						ulWav = DEF_WAV_SOUND_46;	
					}	
					else if(slWinTakeValue<=16)
					{
						ulWav = DEF_WAV_SOUND_47;	
					}
					else
					{							
				    	ulWav = DEF_WAV_SOUND_48;	
					}					
					vPlaySound_Play(ulWav,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);										
					
				}
				break ;
				default :
					if(stcMaster.ulState != PROC_MASTER_GAME_CHANCE)
					{						
						vPlaySound_Play(DEF_WAV_SOUND_SCORE,DEF_SOUND_VOL_SMALL,DEF_SOUND_CH_NONE_20);	
						//while ( ulKey_RePush( KEY_1, 10 , 3 ) == 0 );				
					}	
				break ;				
			}				
		}	
		/*			
		stcMaster.ulCreditCount = 4;
		
		if(stcMaster.ubCreditFlag == 0)
		{
			stcMaster.ubCreditFlag = 1;
			if(stcMaster.ulState >= PROC_MASTER_WUP_INIT)
			{
				//vShow_WupUiLightCredit();		
			}
			else
			{
				//vShow_GameUiLightCredit( );					
			}	
			
		}
		*/
		// �и���Credit����������£��Ÿ���Credit����ѶϢ	
		
		vSlaveShow_ShowCredit( ubSlaveID ) ;	
	}
}

#ifdef DEF_DEFINE_FOR_QCTEST
extern ULONG ulTestCredit[DEF_USERIO_USER_MAX] ;
#endif

void vSlave_PayoutInterruptProcess( void )
{
#ifdef DEF_USE_IOPCI
		
	UBYTE	ubSlaveID ;

	// û��IO�������£������Լ�����HPSW��TKSW��Ѷ��
	// HPSW �˱һ����۵�Ѷ��
	// TKSW ��Ʊ�����۵�Ѷ��
	
	ubSlaveID = DEF_GAME_ONLY_PLAY ;
	
	if( ubSlaveID >= DEF_GAME_PLAYER_MAX ) return ;
	
	if( stcSlave[ubSlaveID].ubPayoutChoose == 0 ) return ;
		
	if( ulKey_ActionIsError( KEY_PCI_HPSW ) )
	{		
		vSSR_Off( DEF_SSR_HP ) ;
		vKey_DisableActionFlag( KEY_PCI_HPSW ) ;
		vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;
		
		stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_PAYOUT ;
	}
	else	
	if( ulKey_ReadActionFlag( KEY_PCI_HPSW ) )
	{
		stcSlave[ubSlaveID].ulPayoutEmptyCnt = 0 ;
		
	#ifdef DEF_DEFINE_FOR_QCTEST
		if( stcSlave[ubSlaveID].ubPayoutChoose == 2 )
		{
			// Test Mode
			
			if( ulTestCredit[0] )
			{
				ulTestCredit[0] -- ;
				
				if( ulTestCredit[0] == 0 )
				{
					vSSR_Off( DEF_SSR_HP ) ;
					vKey_DisableActionFlag( KEY_PCI_HPSW ) ;	
				}
			}			
		}
		else
	#endif	
		{
			ULONG	ulTemp ;
			
			ulTemp =  mGame_ReadCoinRate( ) ;
			if( ulTemp )
			{
				if( ulCredit_Sub( ubSlaveID , ulTemp ) < ulTemp )
				{
					vSSR_Off( DEF_SSR_HP ) ;
					vKey_DisableActionFlag( KEY_PCI_HPSW ) ;
					vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;
				}
				
				vRecord_Add( ubSlaveID , DEF_RECORD_DATA_PAYOUT , ulTemp ) ;
				#ifdef DEF_USE_VGAME_UART_SLAVE
				ulUartCmdRec[DEF_RECORD_DATA_PAYOUT][0] += ulTemp ;
				#endif
				vMeter_Add( DEF_METER_PAYOUT , 1 ) ;
	
				#ifdef DEF_GTRULE_GTVG	
				vGTVG_UpdateRepoRecord( 0 , ulTemp , 0 ) ;
				#endif
			}
		}
	}

	if( ulKey_ActionIsError( KEY_PCI_TKSW ) )
	{
		vSSR_Off( DEF_SSR_TK ) ;		
		vKey_DisableActionFlag( KEY_PCI_TKSW ) ;
		vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;

		stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_PAYOUT ;
	}
	else
	if( ulKey_ReadActionFlag( KEY_PCI_TKSW ) )
	{
		stcSlave[ubSlaveID].ulPayoutEmptyCnt = 0 ;
		
	#ifdef DEF_DEFINE_FOR_QCTEST
		if( stcSlave[ubSlaveID].ubPayoutChoose == 2 )
		{
			// Test Mode
			
			if( ulTestCredit[1] )
			{
				ulTestCredit[1] -- ;
				
				if( ulTestCredit[1] == 0 )
				{
					vSSR_Off( DEF_SSR_TK ) ;	
					vKey_DisableActionFlag( KEY_PCI_TKSW ) ;
				}
			}			
		}
		else
	#endif	
		{
			ULONG	ulTicketRate ;
			// ��� ulTicketRate < 10000 ����ʾ��N�Ų�Ʊ�����ݲż�һ
			// ���򣬱�ʾ��һ�ţ����ݼ�N					
			ulTicketRate = mGame_ReadTicketRate( ) ;
			if( ulTicketRate < 10000 )
			{
				stcSlave[ubSlaveID].ubTicketOut ++ ;
				if( stcSlave[ubSlaveID].ubTicketOut >= ulTicketRate )
				{
					stcSlave[ubSlaveID].ubTicketOut -= ulTicketRate ;
		
					{
						ULONG	ulTemp ;
						
						ulTemp =  mGame_ReadCoinRate( ) ;
						if( ulTemp )
						{
							if( ulCredit_Sub( ubSlaveID , ulTemp ) < ulTemp )
							{
								vSSR_Off( DEF_SSR_TK ) ;
								vKey_DisableActionFlag( KEY_PCI_TKSW ) ;
								vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;
							}						
							vRecord_Add( ubSlaveID , DEF_RECORD_DATA_PAYOUT , ulTemp ) ;
							#ifdef DEF_USE_VGAME_UART_SLAVE
							ulUartCmdRec[DEF_RECORD_DATA_PAYOUT][0] += ulTemp ;
							#endif
							vMeter_Add( DEF_METER_PAYOUT , 1 ) ;
	
							#ifdef DEF_GTRULE_GTVG	
							vGTVG_UpdateRepoRecord( 0 , ulTemp , 0 ) ;
							#endif
						}
					}
				}
			}
			else
			{		
				{
					ULONG	ulTemp ;
					
					ulTicketRate -= 10000 ;
					ulTemp =  ulTicketRate * mGame_ReadCoinRate( ) ;
					if(( ulCredit_Read( ubSlaveID ) >= ulTemp )&&( ulTemp ))
					{
						if( ulCredit_Sub( ubSlaveID , ulTemp ) < ulTemp )
						{
							vSSR_Off( DEF_SSR_TK ) ;
							vKey_DisableActionFlag( KEY_PCI_TKSW ) ;
							vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;
						}
						vRecord_Add( ubSlaveID , DEF_RECORD_DATA_PAYOUT , ulTemp ) ;
						#ifdef DEF_USE_VGAME_UART_SLAVE
						ulUartCmdRec[DEF_RECORD_DATA_PAYOUT][0] += ulTemp ;
						#endif
						vMeter_Add( DEF_METER_PAYOUT , ulTicketRate ) ;

						#ifdef DEF_GTRULE_GTVG	
						vGTVG_UpdateRepoRecord( 0 , ulTemp , 0 ) ;
						#endif
					}
					else
					{
						vSSR_Off( DEF_SSR_TK ) ;
						vKey_DisableActionFlag( KEY_PCI_TKSW ) ;
						vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;						
					}
				}
			}
		}
	}

#endif

}

#ifdef DEF_USE_IOBOARD
void vSlave_PayoutProcess_ForIOBOARD( UBYTE ubSlaveID )
{
	ULONG	ulValue ;
	
	// ��IO�������£�������Ұ����˱ҵ�����
	// ������ѡ���Ƿ��˱ҵ�����
	
	if( ubSlaveID >= DEF_GAME_PLAYER_MAX ) return ;

	if( stcSlave[ubSlaveID].ubPayoutChoose )
	{	// ����Ѿ������˱Ҽ����ȴ�ѡ���Ƿ��˱�
		
		// ʱ�䵽���Զ�����ѡ��
		stcSlave[ubSlaveID].ulPayoutChooseTimer ++ ;
		if( stcSlave[ubSlaveID].ulPayoutChooseTimer > 600 )
		{			
			vSlaveShow_ShowPayoutChoose( ubSlaveID , 0 ) ;		
			stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
			return ;
		}
		
		if( ulKey_Push( mKey_GetUserKey( KEY_1P_LF , ubSlaveID ) ) )
		{	// �����ѡ��
			vSlaveShow_ShowPayoutChoose( ubSlaveID , 2 ) ; // ��ʾѡ��		
			stcSlave[ubSlaveID].ubPayoutChoose = 2 ;
			stcSlave[ubSlaveID].ulPayoutChooseTimer = 0 ;
		}
		if( ulKey_Push( mKey_GetUserKey( KEY_1P_RT , ubSlaveID ) ) )
		{	// �Ҽ���ѡ��
			vSlaveShow_ShowPayoutChoose( ubSlaveID , 1 ) ; // ��ʾѡ��				
			stcSlave[ubSlaveID].ubPayoutChoose = 1 ;
			stcSlave[ubSlaveID].ulPayoutChooseTimer = 0 ;
		}
		if( ulKey_Push( mKey_GetUserKey( KEY_1P_FIRE , ubSlaveID ) ) )
		{	// ��Ұ���ȷ�ϼ�		
			vSlaveShow_ShowPayoutChoose( ubSlaveID , 0 ) ;

			if( stcSlave[ubSlaveID].ubPayoutChoose == 2 )
			{	// ѡ�ǵ������
				if( stcSlave[ubSlaveID].ulError & DEF_SLAVE_ERROR_PAYOUT )
				{
					// ������˱Ҵ��������£�ѡ��
					// �Ƚ�֮ǰû������ı�������������һ��
					
					stcSlave[ubSlaveID].ulError &= ~DEF_SLAVE_ERROR_PAYOUT ;
					
					if( mGamePayISHPMode( ) )
					{
						ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_HPOUT ) ;
						ulUserIO_CleanPayoutError( ubSlaveID , DEF_USERIODATA_HPOUT ) ;
					}
					else
					{
						ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_TKOUT ) ;
						ulUserIO_CleanPayoutError( ubSlaveID , DEF_USERIODATA_TKOUT ) ;
					}			
				}
				else
				{		
					// û���˱Ҵ��������£�ѡ��
					// �����е�Credit����ɱ���������IO���������˱Ҷ���
									
					ulValue = ulCredit_Read( ubSlaveID ) / mGame_ReadCoinRate( ) ;					
					stcSlave[ubSlaveID].ulPayoutLast = ulValue * mGame_ReadCoinRate( ) ;	// ��¼�ϴ��˱ҵķ���
					ulCredit_Sub( ubSlaveID , stcSlave[ubSlaveID].ulPayoutLast ) ;
				}
				
				if( ulValue )
				{
					if( mGamePayISHPMode( ) )
					{
						ulUserIO_AddGamePayoutTotal( ubSlaveID , DEF_USERIODATA_HPOUT , ulValue ) ;						
					}
					else
					{
						ulValue *= mGame_ReadTicketRate( ) ;
						ulUserIO_AddGamePayoutTotal( ubSlaveID , DEF_USERIODATA_TKOUT , ulValue ) ;
					}
				}
				
				stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
				return ;
			}
			else if( stcSlave[ubSlaveID].ubPayoutChoose == 1 )	
			{	// ѡ��������
				if( stcSlave[ubSlaveID].ulError & DEF_SLAVE_ERROR_PAYOUT )
				{
					// ������˱Ҵ��������£�ѡ��
					// �Ƚ�֮ǰû������ı��������㲢�ӻ�Credit

					stcSlave[ubSlaveID].ulError &= ~DEF_SLAVE_ERROR_PAYOUT ;
					
					if( mGamePayISHPMode( ) )
					{
						ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_HPOUT ) ;
						ulUserIO_CleanPayoutError( ubSlaveID , DEF_USERIODATA_HPOUT ) ;
					}
					else
					{
						ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_TKOUT ) ;
						ulUserIO_CleanPayoutError( ubSlaveID , DEF_USERIODATA_TKOUT ) ;
						ulValue /= mGame_ReadTicketRate( ) ;
					}			
					
					if( ulValue )
					{
						ulValue *= mGame_ReadCoinRate( ) ;
						ulCredit_Add( ubSlaveID , ulValue ) ;
					}
				}

				stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
				return ;
			}
		}
	}
	else
	{	// ��һ�û�н���ѡ���Ƿ��˱ҵ�״̬��
		
		if( stcSlave[ubSlaveID].ulError & DEF_SLAVE_ERROR_PAYOUT )
		{	// �Ѿ������˱Ҵ����״̬�£���ʾ�˱Ҵ����ѶϢ
			
			if( mGamePayISHPMode( ) )
			{
				ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_HPOUT ) ;
			}
			else
			{
				ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_TKOUT ) ;
			}			
			//vSlaveShow_ShowPayoutError( ubSlaveID , ulValue ) ;

			stcSlaveShow[ubSlaveID].ulPayoutErrorCount++;
			if( ulKey_Push( mKey_GetUserKey( KEY_1P_PAYOUT , ubSlaveID ) ) )
			{	// ��Ұ����˱Ҽ�������ѡ���Ƿ��˱ҵ�״̬				
				vSlaveShow_CleanPayoutError( ubSlaveID ) ;
				
				vSlaveShow_ShowPayoutChoose( ubSlaveID , 3 ) ;				
				stcSlave[ubSlaveID].ubPayoutChoose = 1 ;
				stcSlave[ubSlaveID].ulPayoutChooseTimer = 0 ;
				return ;
			}			
		}
		else
		{	// û�з����˱Ҵ���������
			
		
			if( mGamePayISHPMode( ) )
			{
				// ����Ƿ����˱Ҵ������������趨����״̬
				if( ulUserIO_CheckISPayoutError( ubSlaveID ) & DEF_BUS_CMD_ERROR_HP )
				{
					stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_PAYOUT ;
					return ;
				}
				ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_HPOUT ) ;
			}
			else
			{
				// ����Ƿ����˱Ҵ������������趨����״̬
				if( ulUserIO_CheckISPayoutError( ubSlaveID ) & DEF_BUS_CMD_ERROR_TK )
				{
					stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_PAYOUT ;
					return ;
				}
				ulValue = ulUserIO_PayoutISRuning( ubSlaveID , DEF_USERIODATA_TKOUT ) ;
			}
			// ���´��˱�����ѶϢ
			if( stcSlave[ubSlaveID].ulPayoutRefresh != ulValue )
			{
				stcSlave[ubSlaveID].ulPayoutRefresh = ulValue ;
				vSlaveShow_ShowPayoutValue( ubSlaveID , ulValue ) ;
			}
			if( ulValue )
			{	// ����Ѿ����˱�״̬��
				
				// ���IO���Ƿ����
				if( ubUserIO_CheckLink( ) == 0 )
				{
					stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_PAYOUT ;
					return ;
				}
			}
			else
			{	// ƽʱû�µ�״̬

				if( ulKey_Push( mKey_GetUserKey( KEY_1P_PAYOUT , ubSlaveID ) ) )
				{	// ��Ұ����˱Ҽ�������ѡ���Ƿ��˱ҵ�״̬
					if( ulCredit_Read( ubSlaveID ) >= mGame_ReadCoinRate( ) )
					{											
						vSlaveShow_ShowPayoutChoose( ubSlaveID , 3 ) ;
						stcSlave[ubSlaveID].ubPayoutChoose = 1 ;
						stcSlave[ubSlaveID].ulPayoutChooseTimer = 0 ;
						return ;
					}
				}
			}
		}
	}
}
#endif
#ifdef DEF_USE_IOPCI
void vSlave_PayoutProcess_SetPayoutStatus( UBYTE ubSlaveID )
{	
	ULONG ulMap;	
	if(( ulCredit_Read( ubSlaveID ) >= mGame_ReadCoinRate( ) )&&( mGame_ReadCoinRate( ) ))
	{	
		if(mGame_ReadPayMode())
		{
			ulMap = DEF_MASTERSHOW_MSG_031;
		}
		else
		{
			ulMap = DEF_MASTERSHOW_MSG_029;
		}	
		vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),ulMap),161,664);						

		if( mGamePayISHPMode( ) )
		{
			vSSR_On( DEF_SSR_HP ) ;
			vKey_EnableActionFlag( KEY_PCI_HPSW ) ;
			vLamp_On( LAMP_PCI_PAYOUT_BOX ) ;
							
			// �趨Ϊ�˱�״̬
			stcSlave[ubSlaveID].ubPayoutChoose = 1 ;
		}
		else
		{	
			ULONG	ulTicketRate ;
			// ��� ulTicketRate < 10000 ����ʾ��N�Ų�Ʊ�����ݲż�һ
			// ���򣬱�ʾ��һ�ţ����ݼ�N					
			ulTicketRate = mGame_ReadTicketRate( ) ;
			if( ulTicketRate < 10000 )
			{
				vSSR_On( DEF_SSR_TK ) ;
				vKey_EnableActionFlag( KEY_PCI_TKSW ) ;
				vLamp_On( LAMP_PCI_PAYOUT_BOX ) ;
				
				// �趨Ϊ�˱�״̬
				stcSlave[ubSlaveID].ubPayoutChoose = 1 ;
			}
			else
			{
				ulTicketRate -= 10000 ;
				if( ulCredit_Read( ubSlaveID ) >= ( ulTicketRate * mGame_ReadCoinRate( ) ) )
				{
					vSSR_On( DEF_SSR_TK ) ;
					vKey_EnableActionFlag( KEY_PCI_TKSW ) ;
					vLamp_On( LAMP_PCI_PAYOUT_BOX ) ;

					// �趨Ϊ�˱�״̬
					stcSlave[ubSlaveID].ubPayoutChoose = 1 ;					
				}
			}
		}	
		if(stcSlave[ubSlaveID].ubPayoutChoose == 1)
		{
			if(mGame_ReadPayMode())
			{
				ulMap = DEF_MASTERSHOW_MSG_031;
			}
			else
			{
				ulMap = DEF_MASTERSHOW_MSG_029;
			}	
			vShow_GameMap(DEF_ANIMNO_PLAYER_MESS,mMSMessage_GetImg(mGame_ReadFontType(),ulMap),161,664);						

			mSetMasterState( PROC_MASTER_PAY_OUT );	  //�����˱ҵȴ�״̬	
		}	
							
	}

	if( stcSlave[ubSlaveID].ubPayoutChoose )
	{
		ULONG	ulValue ;
				
		ulValue = ulCredit_Read( ubSlaveID ) / mGame_ReadCoinRate( ) ;
		stcSlave[ubSlaveID].ulPayoutLast = ulValue * mGame_ReadCoinRate( ) ;	// ��¼�ϴ��˱ҵķ���

		stcSlave[ubSlaveID].ulPayoutEmptyCnt = 0 ;
	}
}
void vSlave_PayoutProcess_ForIOPCI( UBYTE ubSlaveID )
{
	ULONG	ulValue ;

	// û��IO�������£�������Ұ����˱ҵ�����
	// ����Ҫѡ������̣�ֱ�ӽ����˱Ҷ���

	if( ubSlaveID >= DEF_GAME_PLAYER_MAX ) return ;

	if( stcSlave[ubSlaveID].ubPayoutChoose )
	{	// �˱�״̬��
				
		if( mGame_ReadCoinRate( ) == 0 )
		{			
			vSlaveShow_CleanPayoutValue( ubSlaveID ) ;
			stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
			//vMasterShow_PayOutMessage(DEF_MASTERSHOW_MSG_CLEAN );
			//vMasterShow_Message(DEF_MASTERSHOW_MSG_NO);
			return ;
		}
		
		if( stcSlave[ubSlaveID].ulError & DEF_SLAVE_ERROR_PAYOUT )
		{	// �з����˱Ҵ���������
			ulValue = ulCredit_Read( ubSlaveID ) / mGame_ReadCoinRate( ) ;
			//vSlaveShow_ShowPayoutError( ubSlaveID , ulValue ) ; 
			
			stcSlaveShow[ubSlaveID].ulPayoutErrorCount++;
			if(( ulKey_Push( KEY_PCI_PAYOUT ) )&&
				( stcMaster.ulState<=PROC_MASTER_GAME_BET ))

			{	// �����˱Ҽ����ų��˱Ҵ����״̬
				stcSlave[ubSlaveID].ulError &= ~DEF_SLAVE_ERROR_PAYOUT ;
				vSlaveShow_CleanPayoutError( ubSlaveID ) ;
				
				// �������������˱�
				stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
				vSlave_PayoutProcess_SetPayoutStatus( ubSlaveID ) ;
			}
		}
		else
		{	// û�д��������£�Ҫ����Ƿ��˱�����Ѿ��յ���
//			if(stcSlaveShow[ubSlaveID].ulPayoutErrorCount)
//			{
//				vShowLib_RemoveAddBoxMessage(stcSlave[ubSlaveID].ulPayoutEmptyCnt,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_007));	
//			}
//			if(stcSlaveShow[DEF_GAME_ONLY_PLAY].ulCoinErrorCount)
//			{
//				vShowLib_RemoveAddBoxMessage(stcSlave[ubSlaveID].ulPayoutEmptyCnt,mMSMessage_GetImg(mGame_ReadFontType(),DEF_MASTERSHOW_MSG_008));	
//			}		
			stcSlave[ubSlaveID].ulPayoutEmptyCnt ++ ;
			if( stcSlave[ubSlaveID].ulPayoutEmptyCnt > 300 )
			{
				if( mGamePayISHPMode( ) )
				{
					vSSR_Off( DEF_SSR_HP ) ;
					vKey_DisableActionFlag( KEY_PCI_HPSW ) ;
					vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;
				}
				else
				{
					vSSR_Off( DEF_SSR_TK ) ;
					vKey_DisableActionFlag( KEY_PCI_TKSW ) ;
					vLamp_Off( LAMP_PCI_PAYOUT_BOX ) ;
				}
				stcSlave[ubSlaveID].ulError |= DEF_SLAVE_ERROR_PAYOUT ;
				
			}

			// ���¡����˱�����
			ulValue = ulCredit_Read( ubSlaveID ) / mGame_ReadCoinRate( ) ;
			if( ulValue )
			{
				if( mGamePayISHPMode( ) )
				{
				}
				else
				{
					ULONG	ulTicketRate ;
					// ��� ulTicketRate < 10000 ����ʾ��N�Ų�Ʊ�����ݲż�һ
					// ���򣬱�ʾ��һ�ţ����ݼ�N					
					ulTicketRate = mGame_ReadTicketRate( ) ;
					if( ulTicketRate < 10000 )
					{
						ulValue *= ulTicketRate ;
					}
					else
					{
						ulTicketRate -= 10000 ;
						if( ulValue < ulTicketRate )
						{	// Credit�Ѿ�����һ���ҵķ����ˣ�ֹͣ�˱�״̬
							vSlaveShow_CleanPayoutValue( ubSlaveID ) ;
							stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
						}
						ulValue /= ulTicketRate ;												
					}
				}		
				if( stcSlave[ubSlaveID].ulPayoutRefresh != ulValue )
				{
					stcSlave[ubSlaveID].ulPayoutRefresh = ulValue ;
					vSlaveShow_ShowPayoutValue( ubSlaveID , ulValue ) ;					
				}
			}	
			else	
			{	// Credit�Ѿ�����һ���ҵķ����ˣ�ֹͣ�˱�״̬
				vSlaveShow_CleanPayoutValue( ubSlaveID ) ;
				stcSlave[ubSlaveID].ubPayoutChoose = 0 ;
				//vMasterShow_PayOutMessage(DEF_MASTERSHOW_MSG_CLEAN );
				//vMasterShow_Message(DEF_MASTERSHOW_MSG_NO);
				
				// SSR �� vSlave_PayoutInterruptProcess ����ͻ��ȱ��ر�							
			}
		}
	}
	else
	{	// ƽʱû�µ�״̬
		if(( ulKey_Push( KEY_PCI_PAYOUT ) )&&
			( stcMaster.ulState<=PROC_MASTER_GAME_BET ) && ( mGame_ReadCoinRate() ))
		{	// ��Ұ����˱Ҽ�
			vSlave_PayoutProcess_SetPayoutStatus( ubSlaveID ) ;
		}
	}
}
#endif		

void vSlave_KeyoutProcess( UBYTE ubSlaveID )
{	
	ULONG	ulTemp ;
	if(ubKeyoutFlag)
	{
		ulTemp = mGame_ReadKeyOutRate( ) ;
		if(( ulCredit_Read( ubSlaveID ) >= ulTemp )&&(ulTemp))
		{
			//while ( ulKey_RePush( KEY_1, 10 , 3 ) == 0 );	
			ulCredit_Sub( ubSlaveID , ulTemp ) ;

			{
				stcSlave[ubSlaveID].slShowKeyinValue -= ulTemp ;
				stcSlave[ubSlaveID].ulShowKeyinValueCnt = 5*60 ;
			}
			
			vRecord_Add( ubSlaveID , DEF_RECORD_DATA_KEYOUT , ulTemp ) ;
			#ifdef DEF_USE_VGAME_UART_SLAVE
			ulUartCmdRec[DEF_RECORD_DATA_KEYOUT][0] += ulTemp ;
			#endif
			vMeter_Add( DEF_METER_KEYOUT , 1 ) ;

			#ifdef DEF_GTRULE_GTVG	
			vGTVG_UpdateRepoRecord( 0 , ulTemp , 0 ) ;
			#endif
		}
		else
		{
			ubKeyoutFlag = 0;	
		}	
	}
	else
	{
	#ifdef DEF_USE_IOBOARD
		if( ulKey_Push( mKey_GetUserKey( KEY_1P_KEYOUT , ubSlaveID ) ) )
	#endif	
	#ifdef DEF_USE_IOPCI
		if( ulKey_Push( KEY_PCI_KEYOUT ) )
	#endif
		{	
			ubKeyoutFlag = 1;				
		}		
		
	}

#ifdef DEF_USE_IOPCI
	{
		#ifdef DEF_TEST_AUTOPLAY_COIN
		#ifdef DEF_TEST_ALWAYS_AUTO_2
		if ( ubAutoPlay2_isRun )
		#else
		if ( ulKey_Touch( KEY_PCI_97_TEST ) )  //���ʱ�Զ��·�
		#endif	
		{
			if( ulCredit_Read( ubSlaveID ) > ( mGame_ReadMaxBet( ) * 10 ) )
			{
				if(ulCredit_Read( ubSlaveID ) > ( mGame_ReadKeyOutRate( ) * 40 ) )	
				{
					ulTemp = mGame_ReadKeyOutRate( ) * 20 ;
					if( ulCredit_Read( ubSlaveID ) >= ulTemp )
					{
						ulCredit_Sub( ubSlaveID , ulTemp ) ;
			
						vRecord_Add( ubSlaveID , DEF_RECORD_DATA_KEYOUT , ulTemp ) ;
						#ifdef DEF_USE_VGAME_UART_SLAVE
						ulUartCmdRec[DEF_RECORD_DATA_KEYOUT][0] += ulTemp ;
						#endif
						vMeter_Add( DEF_METER_KEYOUT , 1 ) ;

						#ifdef DEF_GTRULE_GTVG	
						vGTVG_UpdateRepoRecord( 0 , ulTemp , 0 ) ;
						#endif
					}	
					
				}	
			}
		}
		#endif	
		
	}	
#endif	
	
	
}

void vSlave_Process( void )
{
	UBYTE ubSlaveID ;

	
#ifdef DEF_USE_IOBOARD
	for ( ubSlaveID = 0 ; ubSlaveID < DEF_GAME_PLAYER_MAX ; ++ubSlaveID )
#endif
#ifdef DEF_USE_IOPCI
	ubSlaveID = DEF_GAME_ONLY_PLAY ;
#endif	
	{

	#ifdef DEF_USE_IOBOARD
		switch( stcSlave[ubSlaveID].ubState )
		{
		}
	#endif
		
		vSlave_CoinProcess( ubSlaveID ) ; 
	#ifdef DEF_USE_IOBOARD
		vSlave_PayoutProcess_ForIOBOARD( ubSlaveID ) ;	
	#endif
	#ifdef DEF_USE_IOPCI
		vSlave_PayoutProcess_ForIOPCI( ubSlaveID ) ;	
	#endif
		
		vSlave_KeyoutProcess( ubSlaveID ) ;	 
		vSlaveShow_ShowError( ubSlaveID ) ;	 
	#ifdef DEF_USE_IOPCI	
		if( stcSlave[ubSlaveID].ulShowKeyinValueCnt )
		{		
			
			stcSlave[ubSlaveID].ulShowKeyinValueCnt -- ;
			
		#ifdef DEF_SHOWTMP_KEYIN
			UBYTE cStr[128] ;
			vSprint((char *)cStr , STR"%d" , stcSlave[ubSlaveID].slShowKeyinValue) ;
			if( stcSlave[ubSlaveID].slShowKeyinValue >= 0 )
			{
				vPcVideo2D_Img_ShowString( DEF_ANIMNO_FREE_END , mMacro_Img( DEF_FONT_ASCII_000 ) , 850 , 650 , DEF_PCVIDEO2D_ZOBASE+500 , DEF_GRN , DEF_FONT_SIZE , (char *)cStr  ) ;
				//vPcVideo2D_Debug_OutMsg( (char *)cStr , stcSlave[ubSlaveID].ulShowKeyinValueCnt ) ;
			}
			else
			{
				vPcVideo2D_Img_ShowString( DEF_ANIMNO_FREE_END , mMacro_Img( DEF_FONT_ASCII_000 ) , 850 , 650 , DEF_PCVIDEO2D_ZOBASE+500 , DEF_RED , DEF_FONT_SIZE , (char *)cStr  ) ;
			}
		#endif
			
			if( stcSlave[ubSlaveID].ulShowKeyinValueCnt == 0 )
			{
				vRecord_Save_InOutEvent( stcSlave[ubSlaveID].slShowKeyinValue ) ;	
				stcSlave[ubSlaveID].slShowKeyinValue = 0 ;
				
			#ifdef DEF_SHOWTMP_KEYIN	
				vPcVideo2D_Img_Clean( DEF_ANIMNO_FREE_END ) ;
			#endif	
			}
		}	
	#endif
	
	}
	
}
