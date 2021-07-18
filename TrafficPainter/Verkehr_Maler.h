#pragma once
// file : Verkehr_Maler.h
#include "stdafx.h"

namespace TrafficPainter
{
	class TRAFFICPAINTER_API CVerkehr_Maler
	{
	public:
		static CVerkehr_Maler* GetMaler();
		static void KillMaler();
		static CVerkehr_Maler*  m_pMaler;
		void Draw_TLightState(CDC *pDC, int X, int Y, CTL_State& st);
		void Draw_PedLightState(CDC *pDC, int X, int Y, CPL_State& st);

		void Draw_VehicleOnRoad(CDC *pDC, CVehicleState& st);
		void Draw_TrafficFacility_K0(CDC *pDC);
		void Draw_TrafficFacility_K1(CDC *pDC);
		void DrawBackColor(CDC *pDC);
		void MarkNode(CDC *pDC, int X= 0, int Y= 0,COLORREF color=RGB(125,125,125));
	protected:
		CVerkehr_Maler();
		~CVerkehr_Maler();
		CBrush		m_BackGroundBrush;	//(m_bkcolor);
		CPen		m_GridPen;
		COLORREF	m_bkcolor;			// back color
		COLORREF	m_gridcolor;		// back color

	};
	
}	// name space

