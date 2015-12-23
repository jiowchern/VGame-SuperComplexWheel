#ifndef DEF_INCLUDE_METER_H
	#define DEF_INCLUDE_METER_H

	#ifdef DEF_METER_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif
	
	enum __METER__ {
		DEF_METER_COIN_A ,
		DEF_METER_COIN_C ,
		DEF_METER_KEYIN  ,
		DEF_METER_PAYOUT ,
		DEF_METER_KEYOUT ,
		DEF_METER_5   ,
		DEF_METER_6   ,
		DEF_METER_7   ,
		DEF_METER_MAX
	} ;

	EXTERN void vMeter_Reset( void ) ; // ��0��������
	EXTERN void vMeter_Initial( void ) ; // �����ָ���ʼ״̬���������δ�����������
	
	EXTERN void vMeter_Add( ULONG ulMeterID , ULONG ulValue ) ;
	EXTERN void vMeter_AddInInterrupt( ULONG ulMeterID , ULONG ulValue ) ;
	
	EXTERN void vMeter_SetRate( ULONG ulMeterID , ULONG ulRate ) ; // �趨���ı��ʣ�ʵ�������Ĵ���Ϊ Value/Rate	

	EXTERN void vMeter_SetWaitTimes( ULONG ulValue ) ; // �趨���������ٶ�(�ӳ�ʱ��)
	
	EXTERN void vMeter_Process( void ) ;
	
	#undef EXTERN
#endif
