// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F46372F6_ED98_4BD5_8334_0F6DB1F3F910__INCLUDED_)
#define AFX_MAINFRM_H__F46372F6_ED98_4BD5_8334_0F6DB1F3F910__INCLUDED_

#include "DirectoryTreeBar.h"
#include "PreviewBar.h"
#include "ClassChooseBar.h"
#include "ImgClassCBView.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct ResultDataType
{
	int		iClasses[1000];
	bool	bCorrect[1000];
	int		iImgNo_per_Cls[20];
	int		iImgs_per_Cls[20][1000];
	int		iImgCorNo_per_Cls[20];
	double	dImgCorRate[20];
	double	dImgConMat[20][20];
	double	dEveCorRate;
};
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	ResultDataType m_resultData;
	CSplitterWnd m_wndSplitter;
// Operations
public:
// Overrides
	double LoadResult(char *szRrwFile);
	void ShowResult();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDirectoryTreeBar	m_wndDirTreeBar;
	CPreviewBar			m_wndPreviewBar;
	CClassChooseBar		m_wndCCBar;
	CImgClassCBView		*m_pTrainView;
	CImgClassCBView		*m_pTestView;
	int					m_iViewNo;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	BOOL m_bShowPreviewBar, m_bShowDirectoryBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewDirectoryBar();
	afx_msg void OnUpdateViewDirectoryBar(CCmdUI* pCmdUI);
	afx_msg void OnViewPreviewBar();
	afx_msg void OnUpdateViewPreviewBar(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnStopThread();
	afx_msg void OnUpdateStopThread(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F46372F6_ED98_4BD5_8334_0F6DB1F3F910__INCLUDED_)
