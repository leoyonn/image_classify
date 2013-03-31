// ImgClassCB.h : main header file for the ImgClassCB application
//

#if !defined(AFX_ImgClassCB_H__71E2C240_CCFB_4DFD_836E_EECD986C32A8__INCLUDED_)
#define AFX_ImgClassCB_H__71E2C240_CCFB_4DFD_836E_EECD986C32A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "MainFrm.h"
#include "FeatureExDlg.h"
#include "TrainDlg.h"
#include "TestDlg.h"
#include "ViewResults.h"
/////////////////////////////////////////////////////////////////////////////
// CImgClassCBApp:
// See ImgClassCB.cpp for the implementation of this class
//

class CImgClassCBApp : public CWinApp
{
public:
	CImgClassCBApp();
	CFeatureExDlg	m_cFeatureExDlg;
	CTrainDlg		m_cTrainExDlg;
	CTestDlg		m_cTestExDlg;
	CViewResults	m_cViewResultDlg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgClassCBApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImgClassCBApp)
	afx_msg void OnAppAbout();
	afx_msg void OnMENUFeatureExtract();
	afx_msg void OnMENUTest();
	afx_msg void OnMENUTrain();
	afx_msg void OnMENUViewResult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CMainFrame* GetMainFrame();
CImgClassCBDoc* GetActDoc();
CImgClassCBView* GetActView();
CImgClassCBApp* GetMainApp();

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ImgClassCB_H__71E2C240_CCFB_4DFD_836E_EECD986C32A8__INCLUDED_)
