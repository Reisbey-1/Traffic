
// TrafficTester.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTrafficTesterApp:
// See TrafficTester.cpp for the implementation of this class
//

class CTrafficTesterApp : public CWinApp
{
public:
	CTrafficTesterApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTrafficTesterApp theApp;