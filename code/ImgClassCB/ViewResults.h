#if !defined(AFX_VIEWRESULTS_H__3863AF51_BC64_47D3_92D6_528DD7C0709B__INCLUDED_)
#define AFX_VIEWRESULTS_H__3863AF51_BC64_47D3_92D6_528DD7C0709B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewResults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewResults dialog

class CViewResults : public CDialog
{
// Construction
public:
	CViewResults(CWnd* pParent = NULL);   // standard constructor
	void ComputeConMat(char * strInput);
// Dialog Data
	//{{AFX_DATA(CViewResults)
	enum { IDD = IDD_DLG_ViewResult };
	CStatic	m_cPicture;
	CString	m_szInResultFile;
	int		m_iFeatureType;
	int		m_iClassType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewResults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewResults)
	afx_msg void OnBTNConMatText();
	afx_msg void OnBTNConMatImg();
	afx_msg void OnBTNInResultFileBro();
	virtual void OnOK();
	afx_msg void OnBTNLoadRRW();
	afx_msg void OnBTNViewResultTxt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWRESULTS_H__3863AF51_BC64_47D3_92D6_528DD7C0709B__INCLUDED_)
