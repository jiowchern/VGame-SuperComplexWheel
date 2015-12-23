#ifndef DEF_INCLUDE_BUFFER_H
    #define DEF_INCLUDE_BUFFER_H

    #ifdef DEF_BUFFER_C
        #define EXTERN
    #else
        #define EXTERN extern
    #endif

    typedef struct __BUFFER__
    {
        SLONG slValue ;
        SLONG slCount ;
        ULONG ulLife  ;
    } BUFFER ;

    typedef struct __VIRBUF__
    {
        SLONG slValue ;
        SLONG slCount ;

        ULONG ulVGate ;
        ULONG ulVRate ;
        ULONG ulVTop ;
    } VIRBUF ;

    // For Physical Buffer
    EXTERN void vBuffer_Init( BUFFER *stcBuf ) ; // ȫ����0
    EXTERN void  vBuffer_Empty( BUFFER *stcBuf ) ; // ֻ��Value��Count
    EXTERN void  vBuffer_SetLife( BUFFER *stcBuf , ULONG ulLifeCycle ) ; // �趨life

    EXTERN SLONG slBuffer_Read( BUFFER *stcBuf ) ; // ��ȡbufֵ

    EXTERN SLONG slBuffer_Add( BUFFER *stcBuf , SLONG slValue ) ; // buf+value
    EXTERN SLONG slBuffer_Sub( BUFFER *stcBuf , SLONG slValue ) ; // buf-value
    // ���� rate(1000Ϊ100.0%) �ۻ� value �� buf��rate
    EXTERN SLONG slBuffer_AddRate( BUFFER *stcBuf , SLONG slValue , ULONG ulRate ) ; // buf+(value*Rate)
    EXTERN SLONG slBuffer_SubRate( BUFFER *stcBuf , SLONG slValue , ULONG ulRate ) ; // buf-(value*rate)
    EXTERN ULONG ulBuffer_CountLife( BUFFER *stcBuf ) ; // life-1, life=0 return 1

    // For Virtual Buffer
    EXTERN void  vBuffer_VBufInit( VIRBUF *stcVBuf ) ; // ȫ����0
    EXTERN void  vBuffer_VBufSetGate( VIRBUF *stcVBuf , ULONG ulVGate ) ; // �趨VGate
    EXTERN void  vBuffer_VBufSetVRate( VIRBUF *stcVBuf , ULONG ulVRate ) ; // �趨VRate
    EXTERN void  vBuffer_VBufSetRRate( VIRBUF *stcVBuf , ULONG ulRealRate ) ; // �趨VRate, (RRate*1000)/VGate
    EXTERN void  vBuffer_VBufSetTop( VIRBUF *stcVBuf  , ULONG ulVTop ) ; // �趨VTop

    EXTERN void  vBuffer_VBufEmpty( VIRBUF *stcVBuf ) ; // ֻ��Value��Count
    EXTERN SLONG slBuffer_VBufAddRate( VIRBUF *stcVBuf , SLONG slValue ) ; // buf+(value*VRate)
    EXTERN SLONG slBuffer_VBufSub( VIRBUF *stcVBuf , SLONG slValue ) ; // buf-value

    EXTERN SLONG slBuffer_VBufRead( VIRBUF *stcVBuf ) ; // ��ȡbuf
    EXTERN SLONG slBuffer_VBufIsTop( VIRBUF *stcVBuf ) ; // ���buf>VTop
    EXTERN SLONG slBuffer_VBufIsPass( VIRBUF *stcVBuf , ULONG ulRandom ) ; // ���buf>VTop,����Random<VGate

    #undef EXTERN
#endif
