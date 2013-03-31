// DirectoryTreeBar.cpp : implementation file
//

#include "stdafx.h"
#include "ImgClassCB.h"
#include "DirectoryTreeBar.h"
#include "MainFrm.h"
#include "ImgClassCBDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectoryTreeBar

CDirectoryTreeBar::CDirectoryTreeBar()
{
}

CDirectoryTreeBar::~CDirectoryTreeBar()
{
}


BEGIN_MESSAGE_MAP(CDirectoryTreeBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CDirectoryTreeBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCLBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDirectoryTreeBar message handlers

int CDirectoryTreeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect	rect;
	GetClientRect( &rect );
	m_TreeCtrl.Create(WS_VISIBLE|WS_CHILD|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		rect, this, IDC_TREEDIR);
	m_TreeCtrl.Initialize();

	return 0;
}

void CDirectoryTreeBar::OnSize(UINT nType, int cx, int cy) 
{
	CSizingControlBarG::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rc;
    GetClientRect(rc);

	m_TreeCtrl.MoveWindow(rc);
}

// Not closing window, just hiding
void CDirectoryTreeBar::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	if( OnNcHitTest(point) == HTCLOSE )
	{
		pFrame->SendMessage(WM_COMMAND, ID_VIEW_DIRECTORY_BAR);
	}
	CSizingControlBarG::OnNcLButtonUp(nHitTest, point);
}
