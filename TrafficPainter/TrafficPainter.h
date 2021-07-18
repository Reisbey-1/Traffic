// TrafficPainter.h : main header file for the TrafficPainter DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTrafficPainterApp
// See TrafficPainter.cpp for the implementation of this class
//

class CTrafficPainterApp : public CWinApp
{
public:
	CTrafficPainterApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
