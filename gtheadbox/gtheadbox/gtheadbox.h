
// gtheadbox.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CgtheadboxApp:
// �� Ŭ������ ������ ���ؼ��� gtheadbox.cpp�� �����Ͻʽÿ�.
//

class CgtheadboxApp : public CWinApp
{
public:
	CgtheadboxApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CgtheadboxApp theApp;