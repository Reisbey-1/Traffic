
// TrafficTesterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrafficTester.h"
#include "TrafficTesterDlg.h"
#include "afxdialogex.h"
#include "TheClock.h"
#include "Process.h"
#include "Resource.h"

#include "LinkedList.h"
using namespace dtl;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrafficTesterDlg dialog


CTrafficTesterDlg * CTrafficTesterDlg::theObjectPtr = NULL;				// objet pointer to itself

CTrafficTesterDlg::CTrafficTesterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAFFICTESTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_tls.m_nState = RED;

}

void CTrafficTesterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTrafficTesterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CTrafficTesterDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &CTrafficTesterDlg::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD, &CTrafficTesterDlg::OnBnClickedButtonBackward)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CTrafficTesterDlg::OnBnClickedButtonChange)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CTrafficTesterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD2, &CTrafficTesterDlg::OnBnClickedButtonAdd2)
	ON_BN_CLICKED(IDC_BUTTON_ADD1, &CTrafficTesterDlg::OnBnClickedButtonAdd1)
END_MESSAGE_MAP()


BOOL CTrafficTesterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	// init process
	InitProcess();
	theObjectPtr = this;
	/*
	// clok
	typedef  LONG(*f)();
	f func = &clock_tick;
	myClock.AddCallBackFunction((LONG*)func);
	myClock.StartThread();
	*/

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2));
	SetIcon(hIcon, FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrafficTesterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrafficTesterDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CVerkehr_Maler::GetMaler()->Draw_TrafficFacility_K0(&dc);
		CVehicle* cv1 = CReflector::GetReflector()->GetFirst();
		CVehicleState vs1;	
		while (cv1)
		{
			cv1->get_state(vs1);
			CVerkehr_Maler::GetMaler()->Draw_VehicleOnRoad(&dc, vs1);
			cv1 = CReflector::GetReflector()->Next();

		}
		
	//	CVehicle* cv2 = CReflector::GetReflector()->GetLast();
	/*	
		if (cv1)
			
		if (cv2)
			cv2->get_state(vs2);

	
		CVerkehr_Maler::GetMaler()->Draw_VehicleOnRoad(&dc, vs1);
		CVerkehr_Maler::GetMaler()->Draw_VehicleOnRoad(&dc, vs2);
		//CVerkehr_Maler::GetMaler()->Draw_VehicleOnRoad(&dc, m_vs2);*/

		CTL_State& tls = theTrafficLight.GetState();
		CVerkehr_Maler::GetMaler()->Draw_TLightState(&dc, 610, 75, tls);

		CPL_State& pls = thePedestrianLight.GetState();
		CVerkehr_Maler::GetMaler()->Draw_PedLightState(&dc, 610, 300, pls);

		//	CVerkehr_Maler::GetMaler()->Draw_PedLightState(&dc,610, 100, m_pls);
	
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrafficTesterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrafficTesterDlg::OnBnClickedButtonTest()
{


}


void CTrafficTesterDlg::OnBnClickedButtonForward()
{
	
	//m_vs0.m_nPos = m_vs0.m_nPos + 1;
	//m_vs1.m_nPos = m_vs1.m_nPos - 1;
	CVehicle * pV;
	POSITION pos = theVehiclesList.GetHeadPosition();
	while (pos)
	{
		pV= theVehiclesList.GetNext(pos);
		if (pV->m_nAxis)
			pV->move_backward();
		else 
			pV->move_forward();
	}
	Invalidate();

}

void CTrafficTesterDlg::OnBnClickedButtonBackward()
{
	CVehicle * pV;
	POSITION pos = theVehiclesList.GetHeadPosition();
	while (pos)
	{
		pV = theVehiclesList.GetNext(pos);
		if (pV->m_nAxis)
			pV->move_forward();
		else
			pV->move_backward();
	}
	Invalidate();
}

void CTrafficTesterDlg::OnBnClickedButtonChange()
{
	CTL_State& ls = theTrafficLight.GetState();

	ls.nlamp++;
	if (ls.nlamp > GREEN)
		ls.nlamp = RED;
	/**/
	Invalidate();
}

void CTrafficTesterDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	ReleaseProcess();
	CDialogEx::OnClose();
}

void CTrafficTesterDlg::OnBnClickedOk()
{
	ReleaseProcess();
	CDialogEx::OnOK();
}

void CTrafficTesterDlg::OnBnClickedButtonAdd2()
{	
	sTCP_IP_ADDRESS ad0(0);
	CVehicle* pv0 = new CVehicle(ad0, 0, 0, 2);					// create new vehicle on axis 0
	CReflector::GetReflector()->addObstruction(*pv0);			// add it to reflector (for virtual distance sensor)
	theVehiclesList.AddHead(pv0);								// add vehicle list for process
	CWiFi::GetWifi()->AddInternetObject(pv0);					// vehicle is also wifi objet. add it to wifi
	Invalidate();
}

void CTrafficTesterDlg::OnBnClickedButtonAdd1()
{	
	sTCP_IP_ADDRESS ad0(0);
	CVehicle* pv0 = new CVehicle(ad0, 600, 1, 2);				// create new vehicle on axis 1
	CReflector::GetReflector()->addObstruction(*pv0);			// add it to reflector (for virtual distance sensor)
	theVehiclesList.AddHead(pv0);								// add vehicle list for process
	CWiFi::GetWifi()->AddInternetObject(pv0);					// vehicle is also wifi objet. add it to wifi
	Invalidate();
}
