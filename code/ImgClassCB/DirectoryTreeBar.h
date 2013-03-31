#if !defined(AFX_DIRECTORYTREEBAR_H__BC4FAB7E_B856_46D4_A218_E427DCDF7117__INCLUDED_)
#define AFX_DIRECTORYTREEBAR_H__BC4FAB7E_B856_46D4_A218_E427DCDF7117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectoryTreeBar.h : header file
//
#include "DirTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CDirectoryTreeBar window

class CDirectoryTreeBar : public CSizingControlBarCF
{
// Construction
public:
	CDirectoryTreeBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectoryTreeBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDirectoryTreeBar();

	// Generated message map functions
protected:
	CDirTreeCtrl m_TreeCtrl;
	//{{AFX_MSG(CDirectoryTreeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORYTREEBAR_H__BC4FAB7E_B856_46D4_A218_E427DCDF7117__INCLUDED_)
