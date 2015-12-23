#define DEF_RTC3021_C
#include "common.h"
#include "rtc3021.h"
#define FILE_NAME  "RTC3021.C"

#ifdef __ARM__
	#define mRtc3021_Write( mValue )  {*(volatile UBYTE *)0x80000000 = mValue ;}
	#define mRtc3021_Read()           (*(volatile UBYTE *)0x80000000)
#else
	// ORIGINAL #include <sys/time.h>
	#include <time.h>
#endif

enum __RTC3021CMD__
{
	RTC3021_STATUS_0               , /*   0  */
	RTC3021_STATUS_1               , /*   1  */
	RTC3021_SECONDS                , /*   2  */
	RTC3021_MINUTES                , /*   3  */
	RTC3021_HOURS                  , /*   4  */
	RTC3021_DAY                    , /*   5  */
	RTC3021_MONTH                  , /*   6  */
	RTC3021_YEAR                   , /*   7  */
	RTC3021_WEEK_DAY               , /*   8  */
	RTC3021_WEEK_NUMBER            , /*   9  */

	RTC3021_COPY_RAM_TO_CLOCK = 14 , /*  14  */
	RTC3021_COPY_CLOCK_TO_RAM        /*  15  */
} ;

UBYTE ubRtc3021_Bcd2Dec( UBYTE ubValue )
{
    return (((ubValue&0xF0) >> 4)*10 + (ubValue&0x0F));
}

UBYTE ubRtc3021_Dec2Bcd( UBYTE ubValue )
{
    return (((ubValue/10) << 4) + (ubValue%10));
}

void vRtc3021_CommandWrite( UBYTE ubCmd )
{
	#ifdef __ARM__
	SLONG slLoop ;

	/* bCmd (0 - 9, 14, 15) */
	for ( slLoop = 0 ; slLoop < 4 ; slLoop++ )
	{
		mRtc3021_Write( (ubCmd >> slLoop) & 0x01 ) ;
	}
    #endif
}

void vRtc3021_DataWrite( UBYTE ubData )
{
	#ifdef __ARM__
	SLONG slLoop ;

	for ( slLoop = 0 ; slLoop < 8 ; slLoop++ )
	{
		mRtc3021_Write( (ubData >> slLoop) & 0x01 ) ;
	}
    #endif
}

UBYTE ubRtc3021_DataRead( void )
{
	#ifdef __ARM__
    SLONG slLoop ;
    UBYTE ubData;

    ubData = 0;
    for ( slLoop = 0 ; slLoop < 8 ; slLoop++ )
    {
        ubData |= ((mRtc3021_Read()&0x01) << slLoop) ;
    }
    return ( ubData ) ;
    #endif
	return ( 0 ) ;
}

void vRtc3021_ReadTime( void )
{
	#ifdef __ARM__			
    UBYTE* ubAdr ;
    SLONG slLoop , slError ;
    RTC3021 stcRtc3021Temp ;
    
    slError = 0 ;
    
    while( 1 )
    {

	    ubAdr = (UBYTE*)&stcRtc3021Data ;
	    vRtc3021_CommandWrite( RTC3021_COPY_CLOCK_TO_RAM ) ;
	    ubRtc3021_DataRead( ) ;
	
		for ( slLoop = RTC3021_SECONDS ; slLoop <= RTC3021_WEEK_NUMBER ; slLoop ++ )
		{
			vRtc3021_CommandWrite( slLoop ) ;
			*ubAdr = ubRtc3021_Bcd2Dec( ubRtc3021_DataRead( ) ) ;
			ubAdr ++ ;
		}
		
	    ubAdr = (UBYTE*)&stcRtc3021Temp ;
	    vRtc3021_CommandWrite( RTC3021_COPY_CLOCK_TO_RAM ) ;
	    ubRtc3021_DataRead( ) ;
	
		for ( slLoop = RTC3021_SECONDS ; slLoop <= RTC3021_WEEK_NUMBER ; slLoop ++ )
		{
			vRtc3021_CommandWrite( slLoop ) ;
			*ubAdr = ubRtc3021_Bcd2Dec( ubRtc3021_DataRead( ) ) ;
			ubAdr ++ ;
		}
	
		if(( stcRtc3021Data.ubSeconds == stcRtc3021Temp.ubSeconds )&&
			( stcRtc3021Data.ubMinutes == stcRtc3021Temp.ubMinutes )&&
			( stcRtc3021Data.ubHours == stcRtc3021Temp.ubHours )&&
			( stcRtc3021Data.ubDay == stcRtc3021Temp.ubDay )&&
			( stcRtc3021Data.ubMonth == stcRtc3021Temp.ubMonth )&&
			( stcRtc3021Data.ubYear == stcRtc3021Temp.ubYear ))
		{
			break ;
		}
		
		slError ++ ;
		if( slError > 10 )
		{
			ASSERT(0);
			break ;
		}
	}
	
	#else
	time_t timep ;
	struct tm * timeinfo;

	time ( &timep );
	timeinfo = localtime ( &timep );

    stcRtc3021Data.ubSeconds    = timeinfo->tm_sec ;
    stcRtc3021Data.ubMinutes    = timeinfo->tm_min ;
    stcRtc3021Data.ubHours      = timeinfo->tm_hour ;
    stcRtc3021Data.ubDay        = timeinfo->tm_mday ;
    stcRtc3021Data.ubMonth      = timeinfo->tm_mon +1 ;
    stcRtc3021Data.ubYear       = timeinfo->tm_year -100 ;
    stcRtc3021Data.ubWeekDay    = timeinfo->tm_wday ;
    stcRtc3021Data.ubWeekNumber = timeinfo->tm_yday ;
	#endif
}

void vRtc3021_WriteTime( void )
{
	#ifdef __ARM__
    UBYTE* ubAdr ;
    SLONG slLoop ;


    ubAdr = (UBYTE*)&stcRtc3021Data ;
    
	for ( slLoop = RTC3021_SECONDS ; slLoop <= RTC3021_WEEK_NUMBER ; slLoop ++ )
	{
		vRtc3021_CommandWrite( slLoop ) ;
		vRtc3021_DataWrite( ubRtc3021_Dec2Bcd( *ubAdr ) ) ;
		ubAdr ++ ;
	}
	
	vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
	vRtc3021_DataWrite( 0 ) ;
	
	vRtc3021_CommandWrite( RTC3021_COPY_RAM_TO_CLOCK ) ;
	
	vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
	vRtc3021_DataWrite( 0x10 ) ;
	#endif
}

void vRtc3021_PowerOnCheck( void )
{
	#ifdef __ARM__
    UBYTE ubData ;

    vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
    ubData = ubRtc3021_DataRead( ) ;

    /* clear frequency measurement */
    vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
    vRtc3021_DataWrite( (~0x01) & ubData ) ;

    /* clear cold start  */
    vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
    vRtc3021_DataWrite( (~0x03) & ubData ) ;

    /* Set Time Set Lock */
    vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
    vRtc3021_DataWrite( 0x10 ) ;

    /*if ((ubData & 0x02) != 0)
    {
        // clear frequency measurement
        vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
        vRtc3021_DataWrite( (~0x01) & ubData ) ;

        // clear cold start
        vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
        vRtc3021_DataWrite( (~0x03) & ubData ) ;

        // Set Time Set Lock
        vRtc3021_CommandWrite( RTC3021_STATUS_0 ) ;
        vRtc3021_DataWrite( 0x10 ) ;

        stcRtc3021Data.ubYear    = 10 ;   // 2000 + ubYear
    	stcRtc3021Data.ubMonth   = 1 ;
    	stcRtc3021Data.ubDay     = 1 ;
    	stcRtc3021Data.ubHours   = 0 ;
    	stcRtc3021Data.ubMinutes = 0 ;
    	stcRtc3021Data.ubSeconds = 0 ;
        vRtc3021_WriteTime( ) ;
    }*/
    #endif
}
