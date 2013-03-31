#if !defined(AFX_TRAINDLG_H__BBB36233_BE54_48E9_B393_D4197E76D934__INCLUDED_)
#define AFX_TRAINDLG_H__BBB36233_BE54_48E9_B393_D4197E76D934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrainDlg dialog

class CTrainDlg : public CDialog
{
// Construction
public:
	CTrainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTrainDlg)
	enum { IDD = IDD_DLG_TrainDlg };
	CString	m_szInFeatTrain;
	CString	m_szOutFeatTrain;
	int		m_iFeatureType;
	int		m_iClasserType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrainDlg)
	virtual void OnOK();
	afx_msg void OnBTNInFeatTrainBro();
	afx_msg void OnBTNOutFeatTrainBro();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAINDLG_H__BBB36233_BE54_48E9_B393_D4197E76D934__INCLUDED_)
