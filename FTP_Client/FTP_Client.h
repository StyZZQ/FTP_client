
// FTP_Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFTP_ClientApp: 
// �йش����ʵ�֣������ FTP_Client.cpp
//

class CFTP_ClientApp : public CWinApp
{
public:
	CFTP_ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFTP_ClientApp theApp;