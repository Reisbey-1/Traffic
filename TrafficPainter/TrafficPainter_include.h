
// TrafficPainter_include.h
#if !defined(TRAFFIC_PAINTER_H_INCLUDED_)
#define TRAFFIC_PAINTER_H_INCLUDED_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ELLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ELLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TRAFFICPAINTER_EXPORTS
#define TRAFFICPAINTER_API __declspec(dllexport)
#else
#define TRAFFICPAINTER_API __declspec(dllimport)
#endif

#include "Verkehr_Maler.h" 


#endif // TRAFFIC_PAINTER_H_INCLUDED_