
// Finger.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFingerApp: 
// �йش����ʵ�֣������ Finger.cpp
//

class CFingerApp : public CWinApp
{
public:
	CFingerApp();
	
	

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFingerApp theApp;
