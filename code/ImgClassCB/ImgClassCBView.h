// ImgClassCBView.h : interface of the CImgClassCBView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ImgClassCBVIEW_H__CA5ED4AC_832E_4B39_B538_0E76AAC95ED9__INCLUDED_)
#define AFX_ImgClassCBVIEW_H__CA5ED4AC_832E_4B39_B538_0E76AAC95ED9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	THUMBNAIL_WIDTH		100
#define	THUMBNAIL_HEIGHT	90
#define THUMBNAIL_WIDTH_MASK	32
#define THUMBNAIL_HEIGHT_MASK	32

class CImgClassCBView;
class CImgClassCBDoc;

class CImgClassCBView : public CListView
{
protected: // create from serialization only
	CImgClassCBView();
	DECLARE_DYNCREATE(CImgClassCBView)

// Attributes
public:
	CImgClassCBDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgClassCBView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadThumbImages(int iCls, bool bCorrect[], int iImg_per_Cls[]);
	void LoadThumbImages();
	void SetErrorImgTag(int nIndex);
// 	BOOL IsClassRight(int, int[]);
	virtual ~CImgClassCBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	int		m_iViewNo;
protected:
// 	static unsigned __stdcall	LoadThumbNail(LPVOID lpParam);
	void	LoadThumbNail();
	void	LoadThumbNail0();
	void	LoadThumbNail1(int iCls, bool bCorrect[], int iImgs_per_Cls[]);
	CImageList				m_ImageListThumb;		// image list holding the thumbnails
// Generated message map functions
protected:
	//{{AFX_MSG(CImgClassCBView)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImgClassCBView.cpp
inline CImgClassCBDoc* CImgClassCBView::GetDocument()
   { return (CImgClassCBDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ImgClassCBVIEW_H__CA5ED4AC_832E_4B39_B538_0E76AAC95ED9__INCLUDED_)
