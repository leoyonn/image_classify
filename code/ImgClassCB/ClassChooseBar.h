#if !defined(AFX_ClassChooseBar_H__426DCEB6_0A8E_4609_B433_2675C303E9DA__INCLUDED_)
#define AFX_ClassChooseBar_H__426DCEB6_0A8E_4609_B433_2675C303E9DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClassChooseBar.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CClassChooseBar window

class CClassChooseBar : public CSizingControlBarCF
{
// Construction
public:
	CClassChooseBar();

// Attributes
public:
	CEdit		m_wndEdit;
	CListCtrl	m_wndCCList;
// Operations
public:
	void InsertClass(int iClass, int iImg1Num, int iImg2Num, int iImg2CorNum, double dCorRate);
	void LoadResult();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClassChooseBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClassChooseBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClassChooseBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNM_LBtnDown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ClassChooseBar_H__426DCEB6_0A8E_4609_B433_2675C303E9DA__INCLUDED_)
