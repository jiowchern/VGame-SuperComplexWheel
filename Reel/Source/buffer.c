#define DEF_BUFFER_C
#include "common.h"
#define FILE_NAME  "BUFFER.C"

// ================================================= //
// 實體 Buffer 函式區
// ================================================= //
void vBuffer_Init( BUFFER *stcBuf )
{
    stcBuf->slValue = 0 ;
    stcBuf->slCount = 0 ;
    stcBuf->ulLife = 0 ;
}
void vBuffer_Empty( BUFFER *stcBuf )
{
    stcBuf->slValue = 0 ;
    stcBuf->slCount = 0 ; 
}
void vBuffer_SetLife( BUFFER *stcBuf , ULONG ulLifeCycle )
{
    stcBuf->ulLife = ulLifeCycle ;
}

SLONG slBuffer_Read( BUFFER *stcBuf )   { return ( stcBuf->slValue ) ; }

SLONG slBuffer_Add( BUFFER *stcBuf , SLONG slValue )
{
    stcBuf->slValue += slValue ;

    return ( stcBuf->slValue ) ;
}
SLONG slBuffer_Sub( BUFFER *stcBuf , SLONG slValue )
{
    stcBuf->slValue -= slValue ;

    return ( stcBuf->slValue ) ;
}
SLONG slBuffer_AddRate( BUFFER *stcBuf , SLONG slValue , ULONG ulRate )
{
    stcBuf->slCount += ( slValue * (SLONG)ulRate ) ;
    if ( stcBuf->slCount >= 1000 )
    {
        stcBuf->slValue += ( stcBuf->slCount / 1000 ) ;
        stcBuf->slCount  = ( stcBuf->slCount % 1000 ) ;
    }
    return ( stcBuf->slValue ) ;
}
SLONG slBuffer_SubRate( BUFFER *stcBuf , SLONG slValue , ULONG ulRate )
{
    SLONG slTmp ;
	 
    slTmp = ( slValue * (SLONG)ulRate ) / 1000 ;
    if( slTmp < 1 ) slTmp = 1 ;

    stcBuf->slValue -= slTmp ;
    stcBuf->slCount += ( 1000 * slTmp ) ;
    stcBuf->slCount -= ( slValue * (SLONG)ulRate ) ;
    return ( stcBuf->slValue ) ;
}

ULONG ulBuffer_CountLife( BUFFER *stcBuf )
{
    if( stcBuf->ulLife )
    {
        stcBuf->ulLife-- ;
        return 0 ;
    }
    return 1 ;
}

// ================================================= //
// Virtual Buffer 函式區
// ================================================= //
void vBuffer_VBufInit( VIRBUF *stcVBuf )
{
    stcVBuf->slValue = 0 ;
    stcVBuf->slCount = 0 ;
    stcVBuf->ulVGate = 0 ;
    stcVBuf->ulVRate = 0 ;
    stcVBuf->ulVTop  = 0 ;
}

void vBuffer_VBufSetGate( VIRBUF *stcVBuf , ULONG ulVGate )
{
    stcVBuf->ulVGate = ulVGate ;
}
void vBuffer_VBufSetVRate( VIRBUF *stcVBuf , ULONG ulVRate )
{
    stcVBuf->ulVRate = ulVRate ;
}
void vBuffer_VBufSetRRate( VIRBUF *stcVBuf , ULONG ulRealRate )
{
    if( stcVBuf->ulVGate )
    {
        stcVBuf->ulVRate = (ulRealRate * 1000) / stcVBuf->ulVGate ;
    }
    else
    {
        stcVBuf->ulVRate = 0 ;
    }
}

void vBuffer_VBufSetTop( VIRBUF *stcVBuf  , ULONG ulVTop )
{
    stcVBuf->ulVTop = ulVTop ;
}

void vBuffer_VBufEmpty( VIRBUF *stcVBuf )
{
    stcVBuf->slValue = 0 ;
    stcVBuf->slCount = 0 ;
}

SLONG slBuffer_VBufAddRate( VIRBUF *stcVBuf , SLONG slValue )
{
    stcVBuf->slCount += ( slValue * (SLONG)stcVBuf->ulVRate ) ;
    if ( stcVBuf->slCount >= 1000 )
    {
        stcVBuf->slValue += ( stcVBuf->slCount / 1000 ) ;
        stcVBuf->slCount =  ( stcVBuf->slCount % 1000 ) ;
    }
    return ( stcVBuf->slValue ) ;
}

SLONG slBuffer_VBufSub( VIRBUF *stcVBuf , SLONG slValue )
{
    stcVBuf->slValue -= slValue ;

    return ( stcVBuf->slValue ) ;
}

SLONG slBuffer_VBufRead( VIRBUF *stcVBuf )
{
    return ( stcVBuf->slValue ) ;
}

SLONG slBuffer_VBufIsTop( VIRBUF *stcVBuf )
{
    return ( stcVBuf->slValue >= (SLONG)stcVBuf->ulVTop ) ;
}

SLONG slBuffer_VBufIsPass( VIRBUF *stcVBuf , ULONG ulRandom )
{
    if( !slBuffer_VBufIsTop( stcVBuf ) )  return 0 ;

    if( ulRandom < stcVBuf->ulVGate )
    {
        return 1 ;
    }
    else
    {
        stcVBuf->slValue -= stcVBuf->ulVTop ;
        return 0 ;
    }
}
