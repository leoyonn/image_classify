// ClassChooseBar.cpp : implementation file
//

#include "stdafx.h"
#include "ImgClassCB.h"
#include "ClassChooseBar.h"

#include "MainFrm.h"
#include "ImgClassCBDoc.h"

#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClassChooseBar

CClassChooseBar::CClassChooseBar()
{
}

CClassChooseBar::~CClassChooseBar()
{
}


BEGIN_MESSAGE_MAP(CClassChooseBar, CSizingControlBarG)
	//{{AFX_MSG_MAP(CClassChooseBar)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LST_CCC, OnNM_LBtnDown)   
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CClassChooseBar message handlers
/*
int		iClasses[1000] = {0, };
bool	bCorrect[1000];
int		iImgNo_per_Cls[20] = {0, };
int		iImgs_per_Cls[20][1000] = {0, };
int		iImgCorNo_per_Cls[20] = {0, };
*/

int CClassChooseBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CSizingControlBarG::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect	rect;
	GetClientRect( &rect );
// 	m_wndEdit.Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,   
// 						CRect(10,   10,   100,   100),   this,   1);   
	//	m_wndEdit.Create(_T("Image Preview Canvas"), WS_VISIBLE|WS_CHILD, rect, this);
	m_wndCCList.Create( WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_BORDER|
						LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|WS_EX_CLIENTEDGE,   
						CRect(10, 10, 280,   280), this, IDC_LST_CCC);   
	m_wndCCList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);      
    m_wndCCList.SetBkColor(RGB(0,119,129));
    m_wndCCList.SetTextColor(RGB(240,220,230));
	m_wndCCList.SetTextBkColor(RGB(0,119,129));



	//---------Insert Column-------------------------------   
	m_wndCCList.InsertColumn( 0, "类别号", LVCFMT_LEFT, 56 );		//插入列
	m_wndCCList.InsertColumn( 1, "训练图片数", LVCFMT_LEFT, 76 );
	m_wndCCList.InsertColumn( 2, "测试图片数", LVCFMT_LEFT, 76 );
	m_wndCCList.InsertColumn( 3, "正确率", LVCFMT_LEFT, 56 );

	//LoadResult("G:\\resultraw.txt");
	return 0;
}

void CClassChooseBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	// 傈眉甫 弊妨具 且版快
	if(lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
	{
		CRect rect;
		GetClientRect(rect);
		HBRUSH hBrush=::CreateSolidBrush(RGB(55, 255, 255));
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

void CClassChooseBar::OnSize(UINT nType, int cx, int cy) 
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
// 		m_wndEdit.MoveWindow(rc);
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
// 		m_wndEdit.MoveWindow(rect);
// 		m_wndEdit.Invalidate();
	}
}

// Not closing window, just hiding
void CClassChooseBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( OnNcHitTest(point) == HTCLOSE )
	{
		CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
		pFrame->SendMessage(WM_COMMAND, ID_VIEW_DIRECTORY_BAR);
	}
	CSizingControlBarG::OnLButtonUp(nFlags, point);
}

void CClassChooseBar::InsertClass(int iClass, int iImg1Num, int iImg2CorNum, int iImg2Num, double dCorRate)
{
	CString str;
	int iRow = 0;
	if(iClass == -1)
	{
		str.Format("  平均");
		iRow = m_wndCCList.GetItemCount();
		m_wndCCList.InsertItem(iRow, str);//插入行
		str.Format("  -- ", iImg1Num);
		m_wndCCList.SetItemText(iRow, 1, str);//设置数据
		str.Format("  -- / --", iImg2CorNum, iImg2Num);
		m_wndCCList.SetItemText(iRow, 2, str);//设置数据
		str.Format(" %.2f", dCorRate);
		m_wndCCList.SetItemText(iRow, 3, str);//设置数据
	}
	else
	{
		str.Format("  %d", iClass);
		iRow = m_wndCCList.GetItemCount();
		m_wndCCList.InsertItem(iRow, str);//插入行
		str.Format("  %2d", iImg1Num);
		m_wndCCList.SetItemText(iRow, 1, str);//设置数据
		str.Format("  %2d / %2d", iImg2CorNum, iImg2Num);
		m_wndCCList.SetItemText(iRow, 2, str);//设置数据
		str.Format(" %.2f", dCorRate);
		m_wndCCList.SetItemText(iRow, 3, str);//设置数据
	}
}

void CClassChooseBar::OnNM_LBtnDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem > -1 && pNMListView->iItem < 20)
	{
		int j = pNMListView->iItem, i = pNMListView->iSubItem;
		CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
		CImgClassCBDoc* pDoc=(CImgClassCBDoc*)pFrame->GetActiveDocument();
		//pDoc->SelectDirectory("G:\\pic\\");
		pDoc->ShowTrainImgs(j, 50, "..\\pic\\");
		pDoc->ShowTestImgs(j, pFrame->m_resultData.bCorrect, 
				pFrame->m_resultData.iImgs_per_Cls[j], pFrame->m_resultData.iImgNo_per_Cls[j], "G:\\pic\\");
//		p
	}
	*pResult = 0;
}

void CClassChooseBar::LoadResult()
{
	CMainFrame*pFrame = GetMainFrame();
	int i;
	
	for(i = 0; i < 20; i ++)
		InsertClass(i, 50, pFrame->m_resultData.iImgCorNo_per_Cls[i], 
					pFrame->m_resultData.iImgNo_per_Cls[i], pFrame->m_resultData.dImgCorRate[i]);
	InsertClass(-1, -1, -1, -1, pFrame->m_resultData.dEveCorRate);
	// 	InsertClass(1, 50, 50);
}