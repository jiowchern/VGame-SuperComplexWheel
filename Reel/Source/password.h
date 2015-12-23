#ifndef DEF_INCLUDE_PASSWORD_H
	#define DEF_INCLUDE_PASSWORD_H

	#ifdef DEF_PASSWORD_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	enum __PASSWORD_ID__ {
		DEF_PASSWORD_ID_00 ,	// �ܶ��¼
		DEF_PASSWORD_ID_01 ,	// ϵͳ����
		DEF_PASSWORD_ID_02 ,
		DEF_PASSWORD_ID_03 ,
		DEF_PASSWORD_ID_04 ,
		DEF_PASSWORD_ID_05 ,
		DEF_PASSWORD_ID_06 ,
		DEF_PASSWORD_ID_07 ,	// ��������
		DEF_PASSWORD_ID_MAX
	} ;

	EXTERN void  vPassword_Reset( void ) ; // ȫ���ص�Ĭ��ֵ
	EXTERN void  vPassword_ResetID( ULONG ulPasswordID ) ; // ��ĳһ���ص�Ĭ��ֵ
	
	EXTERN void  vPassword_Initial( void ) ; // ���������ʼ��
	EXTERN SLONG slPassword_ReadInputIndex( void ) ; // ���뵽�ڼ�������λ�õ�����ֵ
	
	// ����2����ʾ����������ɡ�����1����ʾ������һ���µ�����ֵ��
	EXTERN SLONG slPassword_Input( void ) ; // �ȴ������������
	
	EXTERN SLONG slPassword_Check( ULONG ulPasswordID ) ; // ��������Ƿ���ȷ

	EXTERN void  vPassword_IDToFix( ULONG ulPasswordID ) ; // ��ĳ�����뱸�ݵ�Fix
	EXTERN void  vPassword_InputToFix( void ) ; // �������뱸�ݵ�Fix
	EXTERN SLONG slPassword_CheckFix( ULONG ulPasswordID ) ; // ��������Ƿ���Fix��ͬ
	EXTERN void  vPassword_FixPassword( ULONG ulPasswordID , UBYTE *ubIn ) ; // ��Fix���µ�����(�޸�����)
	
	#undef EXTERN
#endif
