#ifndef DEF_INCLUDE_IO_H
	#define DEF_INCLUDE_IO_H

	#ifdef DEF_IO_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	enum __IO_DEVICE__ 
    {
		IO_EMPTY   ,
		IO_CPU     ,
		IO_MAP     ,
		IO_PCI     ,
		IO_CMDBUF  ,
		IO_KEYBUF  ,
		IO_6       ,
		IO_7       ,
		IO_DEVICE_MAX
	} ;

	enum __IO_PORT__ 
    {
		IO_PORTA ,
		IO_PORTB ,
		IO_PORTC ,
		IO_PORTD ,
		
		IO_PORTE ,
		IO_PORTF ,
		IO_PORTG ,
		IO_PORTH ,
		
		IO_PORTI ,
		IO_PORTJ ,
		IO_PORTK ,
		IO_PORTL ,

		IO_PORTM ,
		IO_PORTN ,
		IO_PORTO ,
		IO_PORTP ,

		IO_PORTQ ,
		IO_PORTR ,
		IO_PORTS ,
		IO_PORTT ,

		IO_PORTU ,
		IO_PORTV ,
		IO_PORTW ,
		IO_PORTX ,

		IO_PORT_MAX
	} ;
	
	enum __IO_BIT__ 
    {
		IO_BIT0 = 0x01 ,
		IO_BIT1 = 0x02 ,
		IO_BIT2 = 0x04 ,
		IO_BIT3 = 0x08 ,
		IO_BIT4 = 0x10 ,
		IO_BIT5 = 0x20 ,
		IO_BIT6 = 0x40 ,
		IO_BIT7 = 0x80 ,
		IO_BIT_FULL  = 0xFF ,
		IO_BIT_EMPTY = 0x00
	} ;

	typedef struct __IO__
	{
		UBYTE	 ubDrive  ;
		UBYTE	 ubPort   ;
		UBYTE	 ubBit	  ;
		UBYTE    ubAct    ;
		UBYTE    ubMax[8] ;
	} IO ;
	
	EXTERN void  vIO_Reset( void ) ;
	EXTERN void  vIO_Initial( void ) ;
	EXTERN void  vIO_Write( UBYTE ubDevice , UBYTE ubPort , UBYTE ubBit  , UBYTE ubInputData ) ;
	EXTERN UBYTE ubIO_Read( UBYTE ubDevice , UBYTE ubPort , UBYTE ubBit ) ;
	
	#undef EXTERN
#endif
