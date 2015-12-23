#define DEF_PASSWORD_C
#include "../../h/common.h"
#define FILE_NAME "PASSWORD.C"

ULONG ulPasswordInputIndex ;
UBYTE ubPasswordInputKey[8] ;
UBYTE ubPasswordForFix[8] ;
UBYTE ubPasswordKeyData[DEF_PASSWORD_ID_MAX][8] ;

void vPassword_Reset( void )
{
	SLONG slLoop , slLoop1 ;
	
	ulPasswordInputIndex = 0 ;
	
	for ( slLoop = 0 ; slLoop < DEF_PASSWORD_ID_MAX ; slLoop ++ )
	{
		for ( slLoop1 = 0 ; slLoop1 < 8 ; slLoop1 ++ )
		{
			ubPasswordKeyData[slLoop][slLoop1] = ubPasswordDefault[slLoop][slLoop1] ;
		}
	}
}

void vPassword_ResetID( ULONG ulPasswordID )
{
	SLONG slLoop1 ;
	
	if ( ulPasswordID >= DEF_PASSWORD_ID_MAX )
	{
		return ;
	}
	for ( slLoop1 = 0 ; slLoop1 < 8 ; slLoop1 ++ )
	{
		ubPasswordKeyData[ulPasswordID][slLoop1] = ubPasswordDefault[ulPasswordID][slLoop1] ;
	}
}

void vPassword_Initial( void )
{
	SLONG slLoop ;
	
	ulPasswordInputIndex = 0 ;
	for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
	{
		ubPasswordInputKey[slLoop] = 0 ;
	}
}

SLONG slPassword_ReadInputIndex( void ) 
{
	return ( ulPasswordInputIndex ) ;
}

SLONG slPassword_Input( void )
{
	ULONG ulKeyInput ;
	
	ulKeyInput = ulKey_Get( ) ;
	if ( ulKeyInput <= KEY_RTN )
	{
		ubPasswordInputKey[ulPasswordInputIndex] = ulKeyInput ;
		ulPasswordInputIndex ++ ;
		if ( ulPasswordInputIndex >= 8 )
		{
			return ( 2 ) ;
		}
		return ( 1 ) ;
	}
	return ( 0 ) ;
}

void vPassword_InputToFix( void )
{
	SLONG slLoop ;
	
	for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
	{
		ubPasswordForFix[slLoop] = ubPasswordInputKey[slLoop] ;
	}
}

void vPassword_IDToFix( ULONG ulPasswordID )
{
	SLONG slLoop ;

	if ( ulPasswordID >= DEF_PASSWORD_ID_MAX )
	{
		return ;
	}
	
	for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
	{
		ubPasswordForFix[slLoop] = ubPasswordKeyData[ulPasswordID][slLoop] ;
	}
}

SLONG slPassword_CheckKeyTable( UBYTE *ubIn , UBYTE *ubTable )
{
	SLONG slLoop , slOK ;
	
	slOK = 1 ;
	for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
	{
		if ( ulKey_CheckIsSame( ubIn[slLoop] , ubTable[slLoop] ) )
		{
		}
		else
		{
			slOK = 0 ;
			break ;
		}
	}
	return ( slOK ) ;
}

SLONG slPassword_Check( ULONG ulPasswordID )
{
	if ( ulPasswordID >= DEF_PASSWORD_ID_MAX )
	{
		return ( 0 ) ;
	}
	if ( slPassword_CheckKeyTable( (UBYTE *)&ubPasswordInputKey[0] , (UBYTE *)&ubPasswordKeyData[ulPasswordID][0] ) )
	{
		return ( 1 ) ;
	}
	if ( slPassword_CheckKeyTable( (UBYTE *)&ubPasswordInputKey[0] , (UBYTE *)&ubPasswordDefault[7][0] ) )
	{
		return ( 2 ) ;
	}

	return ( 0 ) ;
}

SLONG slPassword_CheckFix( ULONG ulPasswordID )
{
	SLONG slLoop ;
	
	if ( ulPasswordID >= DEF_PASSWORD_ID_MAX )
	{
		return ( 0 ) ;
	}
	if ( slPassword_CheckKeyTable( (UBYTE *)&ubPasswordInputKey[0] , (UBYTE *)&ubPasswordForFix[0] ) )
	{
		for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
		{
			ubPasswordKeyData[ulPasswordID][slLoop] = ubPasswordForFix[slLoop] ;
		}
		return ( 1 ) ;
	}

	return ( 0 ) ;
}

void vPassword_FixPassword( ULONG ulPasswordID , UBYTE *ubIn )
{
	SLONG slLoop ;
	
	if ( ulPasswordID >= DEF_PASSWORD_ID_MAX )
	{
		return ;
	}
	for ( slLoop = 0 ; slLoop < 8 ; slLoop ++ )
	{
		ubPasswordKeyData[ulPasswordID][slLoop] = ubIn[slLoop] ;
	}
}
