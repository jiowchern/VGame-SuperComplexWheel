// Reel.cpp : 定義 DLL 應用程式的匯出函式。
//

#include "stdafx.h"
#include "Reel.h"


// 這是匯出變數的範例
REEL_API int nReel=0;

// 這是匯出函式的範例。
REEL_API int fnReel(void)
{
    return 42;
}

// 這是已匯出的類別建構函式。
// 請參閱 Reel.h 中的類別定義
CReel::CReel()
{
    return;
}


namespace TESTENTEND
{
	void Test::Func()
	{

	}
}