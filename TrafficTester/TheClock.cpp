#pragma once
#include "stdafx.h"
#include "theClock.h"
#include "Process.h"
#include "TrafficTesterDlg.h"
CPerformanceCounter myClock(10);
LONG clock_tick()
{
	{
		Master_Tick();
		myClock.Reset();
	}
	return 1;
}
