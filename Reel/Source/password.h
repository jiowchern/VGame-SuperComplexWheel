#ifndef DEF_INCLUDE_PASSWORD_H
	#define DEF_INCLUDE_PASSWORD_H

	#ifdef DEF_PASSWORD_C
		#define EXTERN
	#else
		#define EXTERN extern
	#endif

	enum __PASSWORD_ID__ {
		DEF_PASSWORD_ID_00 ,	// 总额记录
		DEF_PASSWORD_ID_01 ,	// 系统设置
		DEF_PASSWORD_ID_02 ,
		DEF_PASSWORD_ID_03 ,
		DEF_PASSWORD_ID_04 ,
		DEF_PASSWORD_ID_05 ,
		DEF_PASSWORD_ID_06 ,
		DEF_PASSWORD_ID_07 ,	// 万用密码
		DEF_PASSWORD_ID_MAX
	} ;

	EXTERN void  vPassword_Reset( void ) ; // 全部回到默认值
	EXTERN void  vPassword_ResetID( ULONG ulPasswordID ) ; // 将某一个回到默认值
	
	EXTERN void  vPassword_Initial( void ) ; // 输入密码初始化
	EXTERN SLONG slPassword_ReadInputIndex( void ) ; // 输入到第几个密码位置的索引值
	
	// 返回2，表示密码输入完成。返回1，表示有输入一个新的密码值。
	EXTERN SLONG slPassword_Input( void ) ; // 等待输入密码完成
	
	EXTERN SLONG slPassword_Check( ULONG ulPasswordID ) ; // 检查密码是否正确

	EXTERN void  vPassword_IDToFix( ULONG ulPasswordID ) ; // 将某个密码备份到Fix
	EXTERN void  vPassword_InputToFix( void ) ; // 输入密码备份到Fix
	EXTERN SLONG slPassword_CheckFix( ULONG ulPasswordID ) ; // 检查密码是否与Fix相同
	EXTERN void  vPassword_FixPassword( ULONG ulPasswordID , UBYTE *ubIn ) ; // 将Fix更新到密码(修改密码)
	
	#undef EXTERN
#endif
