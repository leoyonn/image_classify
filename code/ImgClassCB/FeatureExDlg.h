#if !defined(AFX_FEATUREEXDLG_H__6F339A07_A807_4A97_AC12_FBD638DA83FD__INCLUDED_)
#define AFX_FEATUREEXDLG_H__6F339A07_A807_4A97_AC12_FBD638DA83FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FeatureExDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFeatureExDlg dialog

class CFeatureExDlg : public CDialog
{
// Construction
public:
	CFeatureExDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFeatureExDlg)
	enum { IDD = IDD_DLG_FeatureEx };
	CString	m_szInTest;
	CString	m_szInTrain;
	CString	m_szOutTest;
	CString	m_szOutTrain;
	int		m_iFeatureType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeatureExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFeatureExDlg)
	virtual void OnOK();
	afx_msg void OnBtnIntrainbro();
	afx_msg void OnBtnIntestbro();
	afx_msg void OnBtnOuttrainbro();
	afx_msg void OnBtnOuttestbro();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATUREEXDLG_H__6F339A07_A807_4A97_AC12_FBD638DA83FD__INCLUDED_)
