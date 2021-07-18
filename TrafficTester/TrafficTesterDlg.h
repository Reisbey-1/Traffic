
// TrafficTesterDlg.h : header file
//

#pragma once
#include "process.h"

// CTrafficTesterDlg dialog
class CTrafficTesterDlg : public CDialogEx
{
// Construction
public:
	CTrafficTesterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAFFICTESTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	static CTrafficTesterDlg * theObjectPtr;				// objet pointer to itself

// Implementation
protected:
	HICON m_hIcon;
//	CVehicleState m_vs0;
//	CVehicleState m_vs1;
//	CVehicleState m_vs2;
	

//	CTLightState m_tls;
//	CPLightState m_pls;
	//CList <CVehicle*> m_PVehicles;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedButtonBackward();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAdd2();
	afx_msg void OnBnClickedButtonAdd1();
};
