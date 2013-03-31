#if !defined(AFX_TESTDLG_H__25059A83_0175_4818_9D3E_51E52A81CF2E__INCLUDED_)
#define AFX_TESTDLG_H__25059A83_0175_4818_9D3E_51E52A81CF2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_DLG_TestDlg };
	CString	m_szInFeatTest;
	CString	m_szOutFeatTest;
	int		m_iFeatureType;
	int		m_iClasserType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual void OnOK();
	afx_msg void OnBTNInFeatTestBro();
	afx_msg void OnBTNOutFeatTestBro();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__25059A83_0175_4818_9D3E_51E52A81CF2E__INCLUDED_)
