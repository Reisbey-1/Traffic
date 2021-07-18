// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#import "../../bin/CanBusServer.tlb"				raw_interfaces_only, raw_native_types,   no_namespace ,  named_guids//


//#include "..\..\dtl\implement\dtl_include.h"
#include "..\..\dtl\implement\LinkedList.h"
using namespace dtl;

/**/


#include "TrafficLib_include.h"
/*
#ifdef TRAFFICLIB_EXPORTS
#define TRAFFICLIB_API __declspec(dllexport)
#else
#define TRAFFICLIB_API __declspec(dllimport)
#endif
*/

// TODO: reference additional headers your program requires here
