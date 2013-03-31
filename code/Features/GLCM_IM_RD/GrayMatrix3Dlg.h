// GrayMatrix3Dlg.h : header file
//

#if !defined(AFX_GRAYMATRIX3DLG_H__5CC4D943_6FCD_473D_8E6D_4CA101444E04__INCLUDED_)
#define AFX_GRAYMATRIX3DLG_H__5CC4D943_6FCD_473D_8E6D_4CA101444E04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GrayComatrix.h"
#include "InvariantMoment.h"
/////////////////////////////////////////////////////////////////////////////
// CGrayMatrix3Dlg dialog

class CGrayMatrix3Dlg : public CDialog
{
// Construction
public:
	CGrayMatrix3Dlg(CWnd* pParent = NULL);	// standard constructor

	
	
	
	CGrayComatrix		m_cGrayComatrix;
	CInvariantMoment	m_cInvMoment;
// Dialog Data
	//{{AFX_DATA(CGrayMatrix3Dlg)
	enum { IDD = IDD_GRAYMATRIX3_DIALOG };
	CStatic	m_cImgNum;
	CString	m_szInImg;
	CString	m_szOutTrain;
	CString	m_szOutTest;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrayMatrix3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGrayMatrix3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBTNExit();
	afx_msg void OnBTNGenGrayCoMatrix();
	afx_msg void OnBTNLoadJpg();
	afx_msg void OnBTNHuConMatrix();
	afx_msg void OnBtnRandom();
	afx_msg void OnBTNMake();
	afx_msg void OnBTNCoMX5();
	afx_msg void OnButton1();
	afx_msg void OnBtnSift();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAYMATRIX3DLG_H__5CC4D943_6FCD_473D_8E6D_4CA101444E04__INCLUDED_)
