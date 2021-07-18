#include "stdafx.h"
#include "Verkehr_Maler.h"
namespace TrafficPainter
{ 
	CVerkehr_Maler* TrafficPainter::CVerkehr_Maler::m_pMaler = NULL;

	CVerkehr_Maler* CVerkehr_Maler::GetMaler()
	{
		if (m_pMaler == NULL)
			m_pMaler = new CVerkehr_Maler;
		return m_pMaler;

	}
	void CVerkehr_Maler::KillMaler()
	{
		if (m_pMaler)
		{
			delete m_pMaler;
			m_pMaler = NULL;
		}
	}
	
	CVerkehr_Maler::CVerkehr_Maler()
	{
		//m_GridPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));				// Blau);

	}

	CVerkehr_Maler::~CVerkehr_Maler()
	{
	}
	void CVerkehr_Maler::Draw_TLightState(CDC *pDC, int X, int Y, CTL_State& st)
	{
		if (st.nlamp == RED)
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y, COLORREF(RGB(255, 0, 0)));
		else
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y);

		Y = Y + 25;
		if (st.nlamp == YELLOW)
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y, COLORREF(RGB(255, 255, 0)));
		else
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y);

		Y = Y + 25;
		if (st.nlamp == GREEN)
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y, COLORREF(RGB(0, 255, 0)));
		else
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y);

	}

	void CVerkehr_Maler::Draw_PedLightState(CDC *pDC, int X, int Y, CPL_State& st)
	{
		if (st.nlamp == RED)
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y, COLORREF(RGB(255, 0, 0)));
		else
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y);

		Y = Y + 25;
		if (st.nlamp == GREEN)
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y, COLORREF(RGB(0, 255, 0)));
		else
			CVerkehr_Maler::GetMaler()->MarkNode(pDC, X, Y);
	}

	void CVerkehr_Maler::Draw_VehicleOnRoad(CDC *pDC, CVehicleState& st)
	{
		float nRes = 600;
		CPen carPen;
		carPen.CreatePen(PS_SOLID, 1, RGB(10, 225, 0));				// green);

	//	float nXScale = 0;
		float nYPos = 0;
		float nwidth = 100;
		float clengt = 25;		// half car length 
		float cwidth = 30;		// car width 
		int nYtol = 10;			// pedestrian line count;
		int nOrtaCzg = 20;		// pedestrian line count;

		RECT rc0;
		pDC->GetClipBox(&rc0);
		if (st.m_nAxis == 0)
			nYPos = (rc0.bottom ) / 2  ;
		else
			nYPos = (rc0.bottom- nwidth) / 2;

		//nXScale = (rc0.right - nwidth) / 2;
		float nXPos = st.m_nPos*((rc0.right - rc0.left) / nRes);

	//	int nXmid = (rc0.right - rc0.left) / 2;
	//	int nYmid = (rc0.bottom - rc0.top) / 2;

		CString csText;
		CPen* pOriginalPen = (CPen*)pDC->SelectObject(&carPen);

		// car
		pDC->MoveTo(rc0.left+ nXPos - clengt,			rc0.top + nYPos + nYtol);
		pDC->LineTo(rc0.left + nXPos + clengt,			rc0.top + nYPos + nYtol);
		pDC->LineTo(rc0.left + nXPos + clengt,			rc0.top + nYPos + nYtol + cwidth);
		pDC->LineTo(rc0.left + nXPos - clengt,			rc0.top + nYPos + nYtol + cwidth);
		pDC->LineTo(rc0.left + nXPos - clengt,			rc0.top + nYPos + nYtol);


		carPen.Detach();
		carPen.DeleteObject();
		pDC->SelectObject(*pOriginalPen);
	}

	// see bild roadvehicle_02.png 
	void CVerkehr_Maler::Draw_TrafficFacility_K0(CDC *pDC)
	{
		float nRes = 600;
		CPen floorPen;
		floorPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));				// green);
		
		float X = 0;
		float Y = 0;
		float nwidth = 100;
		float nPdW = 30;			// pedestrian with
		float nPdCount = 10;		// pedestrian line count;
		float nOrtaCzg = 20;		// pedestrian line count;

		RECT rc0;
		pDC->GetClipBox(&rc0);
		Y = (rc0.bottom - nwidth) / 2;
		//nXPos = 300.*(rc0.right - nwidth) / (2.0 * nRes);
		X = (rc0.right - nwidth) / (2.0 );

		float nXmid = (rc0.right - rc0.left) / (2.0 );
		float nYmid = (rc0.bottom - rc0.top) / 2;
	
		CString csText;
		CPen* pOriginalPen = (CPen*)pDC->SelectObject(&floorPen);
	
		// road
		pDC->MoveTo(rc0.left,						rc0.top + Y);
		pDC->LineTo(rc0.left+ 2* X + nwidth,	rc0.top + Y);
		
		pDC->MoveTo(rc0.left,						rc0.top + Y + nwidth);
		pDC->LineTo(rc0.left + 2* X + nwidth,	rc0.top + Y + nwidth);
		
		// pedestrian (yaya cizgileri)
		float Yrmt = 0;
		for (int i = 0; i < nPdCount; i++)
		{
			Yrmt = i * (nwidth/nPdCount);
			pDC->MoveTo(rc0.left + nXmid - nPdW /2,	rc0.top + Y +  Yrmt);
			pDC->LineTo(rc0.left + nXmid + nPdW /2,	rc0.top + Y +  Yrmt);
		}
	
		floorPen.Detach();
		floorPen.DeleteObject();
		pDC->SelectObject(*pOriginalPen);

		// orta cizgiler
		float Incrmnt = 0;				// increment
		float nXstep = ((2 * X) + nwidth )/ nOrtaCzg;
	
		for (int i = 1; i < nOrtaCzg/2; i++)
		{
			Incrmnt = i * nXstep ;
			// sol taraf
			pDC->MoveTo(rc0.left + nXmid - Incrmnt,				rc0.top + Y + nwidth / 2);
			pDC->LineTo(rc0.left + nXmid - Incrmnt - nXstep / 2,	rc0.top + Y + nwidth / 2);

			// sag taraf
			pDC->MoveTo(rc0.left + nXmid + Incrmnt, rc0.top + Y + nwidth / 2);
			pDC->LineTo(rc0.left + nXmid + Incrmnt + nXstep / 2, rc0.top + Y + nwidth / 2);

			if (i == 1)
			{/**/
				pDC->MoveTo(rc0.left + nXmid - Incrmnt,	rc0.top + Y + nwidth / 2);
				pDC->LineTo(rc0.left + nXmid - Incrmnt,	rc0.top + Y + nwidth );

				pDC->MoveTo(rc0.left + nXmid + Incrmnt,	rc0.top + Y + nwidth / 2);
				pDC->LineTo(rc0.left + nXmid + Incrmnt,	rc0.top + Y);

			}
		}
	}
	void CVerkehr_Maler::Draw_TrafficFacility_K1(CDC *pDC)
	{
		CPen floorPen;
		floorPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));				// green);

		int nXScale = 0;
		int nYScale = 0;
		int nwidth = 100;

		int nCol = 0;
		int nRow = 0;
		//BYTE i = st.GetStairNo();

		RECT rc0;
		RECT rc1;
		pDC->GetClipBox(&rc0);
		nYScale = (rc0.bottom - nwidth) / 2;
		nXScale = (rc0.right - nwidth) / 2;

		pDC->GetClipBox(&rc1);

		rc1.bottom = rc1.bottom / 2;
		rc1.right = rc1.right / 2;

		CString csText;
		//csText.Format(L"0x%x", no);
		CPen* pOriginalPen = (CPen*)pDC->SelectObject(&floorPen);
		//nCol = st.GetOffset();
		//nRow = st.GetY() *(NUM_FLOORS - 1 - i) + st.GetOffset();
		//nRow = st.GetY() *(NUM_FLOORS - 3- i) + st.GetOffset();
		//GetCellRect(rc0, CCell(nCol, nRow));

		// floor line
		//nCol = st.GetOffset() + st.GetX() * NUM_CARS;
		//GetCellRect(rc1, CCell(nCol, nRow));

		//DC.ExtTextOut(rc.left, rc.top, ETO_OPAQUE, NULL, csName, NULL);

		//	pDC->MoveTo(rc0.left + 2 * m_stXScale, rc0.top + 2 * m_stYScale);
		//	pDC->LineTo(rc1.left + 2 * m_stXScale, rc0.top + 2 * m_stYScale);

		//PrintText(DC, nCol, nRow, csText);

		//return;
		// down demad buttons
		//if (st.GetFloorRequest(DOWN) == true)
		//	DC.SelectObject(&m_DemandPen_Active);
		//else DC.SelectObject(&m_DemandPen_Passive);


		pDC->MoveTo(rc0.left, rc0.top + nYScale);
		pDC->LineTo(rc0.left + nXScale, rc0.top + nYScale);
		pDC->LineTo(rc0.left + nXScale, rc0.top);

		pDC->MoveTo(rc0.left + nXScale + nwidth, rc0.top);
		pDC->LineTo(rc0.left + nXScale + nwidth, rc0.top + nYScale);
		pDC->LineTo(rc0.left + 2 * nXScale + nwidth, rc0.top + nYScale);

		pDC->MoveTo(rc0.left, rc0.top + nYScale + nwidth);
		pDC->LineTo(rc0.left + nXScale, rc0.top + nYScale + nwidth);
		pDC->LineTo(rc0.left + nXScale, rc0.top + 2 * nYScale + nwidth);

		pDC->MoveTo(rc0.left + nXScale + nwidth, rc0.top + 2 * nYScale + nwidth);
		pDC->LineTo(rc0.left + nXScale + nwidth, rc0.top + nYScale + nwidth);
		pDC->LineTo(rc0.left + 2 * nXScale + nwidth, rc0.top + nYScale + nwidth);

		/*		pDC->LineTo(rc0.left / 2 - (20 * m_stXScale), rc0.top);
		pDC->LineTo(rc0.left / 2, rc0.top + 20 * m_stYScale);

		// up demad buttons
		if (st.GetFloorRequest(UP) == true)
		DC.SelectObject(&m_DemandPen_Active);
		else
		DC.SelectObject(&m_DemandPen_Passive);

		pDC->MoveTo(rc0.left / 2 + 2 * (2 * m_stXScale), rc0.top);
		pDC->LineTo(rc0.left / 2 + 3 * (2 * m_stXScale), rc0.top + 2 * m_stYScale);
		pDC->LineTo(rc0.left / 2 + 1 * (2 * m_stXScale), rc0.top + 2 * m_stYScale);
		pDC->LineTo(rc0.left / 2 + 2 * (2 * m_stXScale), rc0.top);
		*/
		floorPen.Detach();
		floorPen.DeleteObject();
		pDC->SelectObject(*pOriginalPen);

	}
	void CVerkehr_Maler::DrawBackColor(CDC* pDC)
	{
		COLORREF	bkcolor = RGB(250,0,170);			// back color
		RECT rc;
		pDC->GetClipBox(&rc);
		//rc.left -= m_pointOrigin.x;
		//rc.top   -= m_pointOrigin.y;
		CBrush backGroundBrush;
		backGroundBrush.CreateSolidBrush(bkcolor);
		CBrush* pOriginalBrush = (CBrush*) pDC->SelectObject(&backGroundBrush);
		pDC->FillRect(&rc, &backGroundBrush);	
		backGroundBrush.Detach();
		backGroundBrush.DeleteObject();
		pDC->SelectObject(*pOriginalBrush);
	}

	/////
	void	CVerkehr_Maler::MarkNode(CDC* pDC, int X, int Y, COLORREF color )
	{

		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		CBrush nodeBrush;
		CPen nodePen;
		COLORREF  nodeColor_HL = RGB(255, 0, 0);
		//COLORREF  nodeColor = RGB(0, 0, 255);

		//RECT rc = { X,Y,X+25,Y+25 };
		RECT NodeRc{ X,Y,X + 25,Y + 25 };
		nodePen.CreatePen(PS_SOLID, 1, nodeColor_HL);
		nodeBrush.CreateSolidBrush(color);

		CPen * pOldPen = pDC->SelectObject(&nodePen);
		CBrush* pbOldBrs = pDC->SelectObject(&nodeBrush);

/*
		NodeRc.top = rc.top + (rc.bottom - rc.top) / 8;
		NodeRc.bottom = rc.bottom - (rc.bottom - rc.top) / 8;
		NodeRc.left = rc.left + (rc.right - rc.left) / 2;
		NodeRc.right = rc.right - (rc.right - rc.left) / 2;
*/

		CRgn rgn;
		rgn.CreateEllipticRgnIndirect(&NodeRc);
		pDC->FillRgn(&rgn, &nodeBrush);
		pDC->Ellipse(&NodeRc);

		// select old objects
		pDC->SelectObject(pOldPen)->DeleteObject();
		pDC->SelectObject(pbOldBrs)->DeleteObject();

		// Free resource
		nodeBrush.Detach();
		nodeBrush.DeleteObject();
		
		nodePen.Detach();
		nodePen.DeleteObject();

		rgn.Detach();
		rgn.DeleteObject();
	}

	
} // name space