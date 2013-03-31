// PreviewBar.cpp : implementation file
//

#include "stdafx.h"
#include "ImgClassCB.h"
#include "PreviewBar.h"

#include "MainFrm.h"
#include "ImgClassCBDoc.h"

#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewBar

CPreviewBar::CPreviewBar()
{
}

CPreviewBar::~CPreviewBar()
{
}


BEGIN_MESSAGE_MAP(CPreviewBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CPreviewBar)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPreviewBar message handlers

int CPreviewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect	rect;
	GetClientRect( &rect );

	m_wndCanvas.Create(_T("Image Preview Canvas"), WS_VISIBLE|WS_CHILD|SS_OWNERDRAW , rect, this, IDC_IMAGEPREVIEW);
	return 0;
}

void CPreviewBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	// 전체를 그려야 할경우
	if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
	{
		CRect rect;
		GetClientRect(rect);
		HBRUSH hBrush=::CreateSolidBrush(RGB(255, 255, 255));
		::FillRect(lpDrawItemStruct->hDC, rect, hBrush);
		DeleteObject(hBrush);

		CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
		CImgClassCBDoc* pDoc=(CImgClassCBDoc*)pFrame->GetActiveDocument();

		if(pDoc->m_pSelectedImage!=NULL)
		{
			// Draw Image
			pDoc->m_pSelectedImage->Draw(lpDrawItemStruct->hDC, lpDrawItemStruct->rcItem);
		}
	}
//	CSizingControlBarG::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CPreviewBar::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControlBarG::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rc;
    GetClientRect(rc);

	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	if(pFrame==NULL)
		return;

	CImgClassCBDoc* pDoc=(CImgClassCBDoc*)pFrame->GetActiveDocument();
	if (pDoc == NULL)
	{
		return;
	}

	if(pDoc->m_pSelectedImage==NULL)
	{
		rc.SetRectEmpty();
		m_wndCanvas.MoveWindow(rc);
	}
	else
	{
		const int nWidth=rc.Width();
		const int nHeight=rc.Height();
		const float fRatio=(float)nHeight/nWidth;
		const float fImgRatio=(float)pDoc->m_pSelectedImage->GetHeight()/pDoc->m_pSelectedImage->GetWidth();

		int XDest, YDest, nDestWidth, nDestHeight;
		if(fImgRatio > fRatio)
		{
			nDestWidth=nHeight/fImgRatio;
			XDest=(nWidth-nDestWidth)/2;
			YDest=0;
			nDestHeight=nHeight;
		}
		else
		{
			XDest=0;
			nDestWidth=nWidth;
			nDestHeight=nWidth*fImgRatio;
			YDest=(nHeight-nDestHeight)/2;
		}
		CRect rect(XDest, YDest, XDest+nDestWidth, YDest+nDestHeight);
		m_wndCanvas.MoveWindow(rect);
		m_wndCanvas.Invalidate();
	}
}

// Not closing window, just hiding
void CPreviewBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( OnNcHitTest(point) == HTCLOSE )
	{
		CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
		pFrame->SendMessage(WM_COMMAND, ID_VIEW_DIRECTORY_BAR);
	}
	CSizingControlBarG::OnLButtonUp(nFlags, point);
}
