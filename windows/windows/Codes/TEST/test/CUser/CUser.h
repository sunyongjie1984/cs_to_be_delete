// CUser.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CCUserApp:
// このクラスの実装については、CUser.cpp を参照してください。
//

class CCUserApp : public CWinApp
{
public:
	CCUserApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCUserApp theApp;
