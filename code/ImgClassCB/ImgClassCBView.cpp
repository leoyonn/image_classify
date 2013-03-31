// ImgClassCBView.cpp : implementation of the CImgClassCBView class
//

#include "stdafx.h"
#include "ImgClassCB.h"

#include "MainFrm.h"
#include "ImgClassCBDoc.h"
#include "ImgClassCBView.h"
#include "memdc.h"

#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgClassCBView

IMPLEMENT_DYNCREATE(CImgClassCBView, CListView)

BEGIN_MESSAGE_MAP(CImgClassCBView, CListView)
	//{{AFX_MSG_MAP(CImgClassCBView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgClassCBView construction/destruction

CImgClassCBView::CImgClassCBView()
{
	// TODO: add construction code here
}

CImgClassCBView::~CImgClassCBView()
{
}

BOOL CImgClassCBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImgClassCBView drawing

void CImgClassCBView::OnDraw(CDC* pDC)
{
	CImgClassCBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CImgClassCBView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& ListCtrl=GetListCtrl();

	// Initialize Imaget List and Attach it to ListCtrl
	m_ImageListThumb.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
	ListCtrl.SetImageList(&m_ImageListThumb, LVSIL_NORMAL);
    
// 	m_ImageListThumb1.Create(THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT, ILC_COLOR24, 0, 1);
// 	ListCtrl.SetImageList(&m_ImageListThumb1, LVSIL_NORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CImgClassCBView printing

BOOL CImgClassCBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImgClassCBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImgClassCBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImgClassCBView diagnostics

#ifdef _DEBUG
void CImgClassCBView::AssertValid() const
{
	CListView::AssertValid();
}

void CImgClassCBView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CImgClassCBDoc* CImgClassCBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgClassCBDoc)));
	return (CImgClassCBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgClassCBView message handlers

BOOL CImgClassCBView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CListView::Create(lpszClassName, _T("ListView"),
		dwStyle|LVS_SHOWSELALWAYS|LVS_ALIGNTOP|LVS_ICON|LVS_SINGLESEL|LVS_AUTOARRANGE   , rect, pParentWnd, nID, pContext);
}

void CImgClassCBView::LoadThumbNail()
{
	CImgClassCBView* pView=this;
	CImgClassCBDoc* pDoc=pView->GetDocument();
	m_iViewNo = 2;
// 	pFrame->m_pTrainView->m_iViewNo = 2;
// 	pFrame->m_pTestView->m_iViewNo = 2;
	CListCtrl& ListCtrl=pView->GetListCtrl();
	CImageList* pImgList=&pView->m_ImageListThumb;

	// reset our image list
	for(int i=0; i<pImgList->GetImageCount(); i++)
		pImgList->Remove(i);	

	// remove all items from list view
	ListCtrl.DeleteAllItems();

	pImgList->SetImageCount(pDoc->m_vFileName.size());

	TCHAR path[MAX_PATH];
	vector<CString>::iterator iter;
	
	// Set redraw to FALSE to avoid flickering during adding new items
	ListCtrl.SetRedraw(FALSE);
	int nIndex=0;
	for(iter=pDoc->m_vFileName.begin(); iter!=pDoc->m_vFileName.end(); iter++, nIndex++)
	{
		ListCtrl.InsertItem(nIndex, *iter, nIndex);
	}

	ListCtrl.SetRedraw(TRUE);
	ListCtrl.Invalidate();

	// Create Brushes for Border and BackGround
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));

	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=THUMBNAIL_WIDTH;
	rcBorder.bottom=THUMBNAIL_HEIGHT;

	const float fRatio=(float)THUMBNAIL_HEIGHT/THUMBNAIL_WIDTH;

	int XDest, YDest, nDestWidth, nDestHeight;
	nIndex=0;
	for(iter=pDoc->m_vFileName.begin(); iter!=pDoc->m_vFileName.end(); iter++, nIndex++)
	{
		// Load Image File
		_stprintf(path, _T("%s\\%s"), pDoc->m_strCurrentDirectory, *iter);

		int nImageType=pDoc->GetTypeFromFileName(path);
		if(nImageType==CXIMAGE_FORMAT_UNKNOWN)
			continue;

		CxImage image(path, nImageType);

		if(image.IsValid()==false)
			continue;

		// Calculate Rect to fit to canvas
		const float fImgRatio=(float)image.GetHeight()/image.GetWidth();
		if(fImgRatio > fRatio)
		{
			nDestWidth=THUMBNAIL_HEIGHT/fImgRatio;
			XDest=(THUMBNAIL_WIDTH-nDestWidth)/2;
			YDest=0;
			nDestHeight=THUMBNAIL_HEIGHT;
		}
		else
		{
			XDest=0;
			nDestWidth=THUMBNAIL_WIDTH;
			nDestHeight=THUMBNAIL_WIDTH*fImgRatio;
			YDest=(THUMBNAIL_HEIGHT-nDestHeight)/2;
		}

		CClientDC cdc(pView);
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
		HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);
		// Draw Background
		::FillRect(hDC, &rcBorder, hBrushBk);

		// Draw Image
		image.Stretch(hDC, XDest, YDest, nDestWidth, nDestHeight);

		// Draw Border
		::FrameRect(hDC, &rcBorder, hBrushBorder);

		SelectObject(hDC, pOldBitmapImage);

		// Attach to Bitmap and Replace image in CImageList
		CBitmap bitmap;
		bitmap.Attach(bm);
		pImgList->Replace(nIndex, &bitmap, NULL);

		// Redraw only a current item for removing flickering and fast speed.
		ListCtrl.RedrawItems(nIndex, nIndex);

		// Release used DC and Object
		DeleteDC(hDC);
		DeleteObject(bm);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);

	ListCtrl.Invalidate();
}

void CImgClassCBView::LoadThumbNail0()
{
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	CImgClassCBView* pView0;
	CImgClassCBDoc* pDoc0;
	pView0 = pFrame->m_pTrainView;
	pDoc0 = pView0->GetDocument();

	CListCtrl& ListCtrl0=pView0->GetListCtrl();
	CImageList* pImgList0 = &pView0->m_ImageListThumb;
	
	int i;
	// reset our image list
	for(i=0; i<pImgList0->GetImageCount(); i++)
		pImgList0->Remove(i);	

	// remove all items from list view
	ListCtrl0.DeleteAllItems();

	pImgList0->SetImageCount(pDoc0->m_vImgNameTrain.size());

	TCHAR path0[MAX_PATH];
	vector<CString>::iterator iter0;
	
	// Set redraw to FALSE to avoid flickering during adding new items
	ListCtrl0.SetRedraw(FALSE);

	int nIndex0 = 0;
	for(iter0=pDoc0->m_vImgNameTrain.begin(); 
		iter0 != pDoc0->m_vImgNameTrain.end(); 
		iter0 ++, nIndex0 ++)
	{
		ListCtrl0.InsertItem(nIndex0, *iter0, nIndex0);
	}

	ListCtrl0.SetRedraw(TRUE);
	ListCtrl0.Invalidate();
	// Create Brushes for Border and BackGround
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));

	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=THUMBNAIL_WIDTH;
	rcBorder.bottom=THUMBNAIL_HEIGHT;

	const float fRatio=(float)THUMBNAIL_HEIGHT/THUMBNAIL_WIDTH;

	int XDest, YDest, nDestWidth, nDestHeight;
	nIndex0=0;
	for(iter0=pDoc0->m_vImgNameTrain.begin();
		iter0!=pDoc0->m_vImgNameTrain.end();
		iter0++, nIndex0++)
	{
		// Load Image File
		_stprintf(path0, _T("%s\\%s"), pDoc0->m_strCurrentDirectory, *iter0);
		
		int nImageType=pDoc0->GetTypeFromFileName(path0);
		if(nImageType==CXIMAGE_FORMAT_UNKNOWN)
			continue;
		
		CxImage image(path0, nImageType);
		
		if(image.IsValid()==false)
			continue;
		
		// Calculate Rect to fit to canvas
		const float fImgRatio=(float)image.GetHeight()/image.GetWidth();
		if(fImgRatio > fRatio)
		{
			nDestWidth=THUMBNAIL_HEIGHT/fImgRatio;
			XDest=(THUMBNAIL_WIDTH-nDestWidth)/2;
			YDest=0;
			nDestHeight=THUMBNAIL_HEIGHT;
		}
		else
		{
			XDest=0;
			nDestWidth=THUMBNAIL_WIDTH;
			nDestHeight=THUMBNAIL_WIDTH*fImgRatio;
			YDest=(THUMBNAIL_HEIGHT-nDestHeight)/2;
		}
		
		CClientDC cdc(pView0);
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
		HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);
		// Draw Background
		::FillRect(hDC, &rcBorder, hBrushBk);
		
		// Draw Image
		image.Stretch(hDC, XDest, YDest, nDestWidth, nDestHeight);
		
		// Draw Border
		::FrameRect(hDC, &rcBorder, hBrushBorder);
		
		SelectObject(hDC, pOldBitmapImage);
		
		// Attach to Bitmap and Replace image in CImageList
		CBitmap bitmap;
		bitmap.Attach(bm);
		pImgList0->Replace(nIndex0, &bitmap, NULL);
		
		// Redraw only a current item for removing flickering and fast speed.
		ListCtrl0.RedrawItems(nIndex0, nIndex0);
		
		// Release used DC and Object
		DeleteDC(hDC);
		DeleteObject(bm);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);
	
	ListCtrl0.Invalidate();
}
void CImgClassCBView::LoadThumbNail1(int iCls, bool bCorrect[], int iImgs_per_Cls[])
{
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	CImgClassCBView* pView1;
	CImgClassCBDoc* pDoc1;
	pView1 = pFrame->m_pTestView;
	pDoc1 = pView1->GetDocument();
	CListCtrl& ListCtrl1=pView1->GetListCtrl();
	CImageList* pImgList1 = &pView1->m_ImageListThumb;
	int i;
	for(i=0; i<pImgList1->GetImageCount(); i++)
		pImgList1->Remove(i);	
	ListCtrl1.DeleteAllItems();
	pImgList1->SetImageCount(pDoc1->m_vImgNameTest.size());
	TCHAR path1[MAX_PATH];
	vector<CString>::iterator iter1;
	ListCtrl1.SetRedraw(FALSE);
	int nIndex1 = 0;
	for(iter1=pDoc1->m_vImgNameTest.begin(); 
			iter1!=pDoc1->m_vImgNameTest.end();
			iter1++, nIndex1++)
	{
		ListCtrl1.InsertItem(nIndex1, *iter1, nIndex1);
	}
	ListCtrl1.SetRedraw(TRUE);
	ListCtrl1.Invalidate();
	
	//Load Error Tag Img:
	CString szErrTag = "res\\err.png";
	CString szCorTag = "res\\cor.png";
	TCHAR path[MAX_PATH]={0};
	_stprintf(path, _T("%s"),szErrTag.GetBuffer(0));
	int nImageTypeErr=pDoc1->GetTypeFromFileName(path);
	CxImage imageErr(path, nImageTypeErr);
	_stprintf(path, _T("%s"),szCorTag.GetBuffer(0));
	nImageTypeErr=pDoc1->GetTypeFromFileName(path);
	CxImage imageCor(path, nImageTypeErr);
	if(imageErr.IsValid()==false || imageErr.IsValid()==false )
	{
		return;
	}
	////////////////////

	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));
	
	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=THUMBNAIL_WIDTH;
	rcBorder.bottom=THUMBNAIL_HEIGHT;
	
	const float fRatio=(float)THUMBNAIL_HEIGHT/THUMBNAIL_WIDTH;
	
	int XDest, YDest, nDestWidth, nDestHeight;
	
	nIndex1=0;

	for(iter1 = pDoc1->m_vImgNameTest.begin();
		iter1 != pDoc1->m_vImgNameTest.end(); 
		iter1 ++, nIndex1 ++)
	{
		// Load Image File
		_stprintf(path1, _T("%s\\%s"), pDoc1->m_strCurrentDirectory, *iter1);
		
		int nImageType=pDoc1->GetTypeFromFileName(path1);
		if(nImageType==CXIMAGE_FORMAT_UNKNOWN)
			continue;
		
		CxImage image(path1, nImageType);
		
		if(image.IsValid()==false)
			continue;
		
		// Calculate Rect to fit to canvas
		const float fImgRatio=(float)image.GetHeight()/image.GetWidth();
		if(fImgRatio > fRatio)
		{
			nDestWidth=THUMBNAIL_HEIGHT/fImgRatio;
			XDest=(THUMBNAIL_WIDTH-nDestWidth)/2;
			YDest=0;
			nDestHeight=THUMBNAIL_HEIGHT;
		}
		else
		{
			XDest=0;
			nDestWidth=THUMBNAIL_WIDTH;
			nDestHeight=THUMBNAIL_WIDTH*fImgRatio;
			YDest=(THUMBNAIL_HEIGHT-nDestHeight)/2;
		}
		
		//HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 1, 192));
		//HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH hBrushBkErr=::CreateSolidBrush(RGB(155, 0, 0));
		HBRUSH hBrushBkCor=::CreateSolidBrush(RGB(0, 190, 0));
		CClientDC cdc(pView1);
		HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
        //建立与pView显示设备兼容的位图
		HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH, THUMBNAIL_HEIGHT);
        //HBITMAP bm2 = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH_MASK, THUMBNAIL_HEIGHT_MASK);
		HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);
		// Draw Background

		::FillRect(hDC, &rcBorder, hBrushBk);
		//::FillRect(hDC, &rcBorderInside, hBrushBk);
		
		// Draw Image
		image.Stretch(hDC, XDest + 2, YDest + 2, nDestWidth - 4, nDestHeight - 4);
		
		// Draw Border
		//::FrameRect(hDC, &rcBorderInside, hBrushBorder);
		
		SelectObject(hDC, pOldBitmapImage);
		
		// Attach to Bitmap and Replace image in CImageList
		CBitmap bitmap;
		bitmap.Attach(bm);
		pImgList1->Replace(nIndex1, &bitmap, NULL);
		
		// Redraw only a current item for removing flickering and fast speed.
		ListCtrl1.RedrawItems(nIndex1, nIndex1);
		
		///////////////////////////////////////////////////////////////////////////
		//对标号不对的图片进行标记（正确的打对号）
		CxImage *pImg;
		int iImgNo = iImgs_per_Cls[nIndex1];
		if(!bCorrect[iImgNo / 100 * 50 + iImgNo % 50])
			pImg = &imageErr;
		else pImg = &imageCor;
		HBITMAP bmErr = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH_MASK, THUMBNAIL_HEIGHT_MASK);
		HBITMAP pOldBitmapImageErr = (HBITMAP)SelectObject(hDC,bmErr);
		::FillRect(hDC, &rcBorder, hBrushBk);
		pImg->AlphaSet(100); 
		pImg->Stretch(hDC, 0, 0, THUMBNAIL_WIDTH_MASK, THUMBNAIL_HEIGHT_MASK);
		SelectObject(hDC, pOldBitmapImage);
		CBitmap bitmapErr;
		bitmapErr.Attach(bmErr);//将位图贴到ImageList控件上
		pImgList1->Replace(nIndex1, &bitmapErr, NULL);
		pImgList1->SetOverlayImage(nIndex1,1);
		CPoint myPoint(XDest,YDest);
		pImgList1->Draw((CDC*)&hDC, 0, myPoint, INDEXTOOVERLAYMASK(1));
		ListCtrl1.RedrawItems(nIndex1, nIndex1);
		DeleteObject(bmErr);

///////////////////////////////////////////////////////////////////////////

		// Release used DC and Object
		DeleteDC(hDC);
		DeleteObject(bm);
		DeleteObject(hBrushBkErr);
		DeleteObject(hBrushBkCor);
	}
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);

	ListCtrl1.Invalidate();

	return;
}
void CImgClassCBView::LoadThumbImages()
{
	LoadThumbNail();
}
void CImgClassCBView::LoadThumbImages(int iCls, bool bCorrect[], int iImgs_per_Cls[])
{
	CImgClassCBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	LoadThumbNail0();
	LoadThumbNail1(iCls, bCorrect, iImgs_per_Cls);
}

void CImgClassCBView::OnFileNew() 
{
	// TODO: Add your command handler code here
	CListCtrl& ListCtrl=GetListCtrl();
	ListCtrl.DeleteAllItems();

	// reset our image list
	for(int i=0; i<m_ImageListThumb.GetImageCount(); i++)
		m_ImageListThumb.Remove(i);
	m_ImageListThumb.SetImageCount(0);
	for(int i=0; i<m_ImageListThumb.GetImageCount(); i++)
		m_ImageListThumb.Remove(i);
	m_ImageListThumb.SetImageCount(0);

	CImgClassCBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Delete Selected Image and clear Image File Name
	pDoc->m_vFileName.clear();
	if(pDoc->m_pSelectedImage!=NULL)
	{
		delete pDoc->m_pSelectedImage;
		pDoc->m_pSelectedImage=NULL;
	}
	// Redraw Selected Image in PreviewBar
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndPreviewBar.SendMessage(WM_SIZE);
}

void CImgClassCBView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CImgClassCBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->SelectItem(pNMListView->iItem);
	*pResult = 0;
}

void CImgClassCBView::SetErrorImgTag(int nIndex)
{
    //从CImageList中恢复图片
	CMainFrame* pFrame=(CMainFrame*)AfxGetMainWnd();
	CImgClassCBView* pView = pFrame->m_pTestView;
	CImgClassCBDoc*  pDoc = pView->GetDocument();
    
	CListCtrl& ListCtrl=pView->GetListCtrl();
	CImageList* pImgList=&pView->m_ImageListThumb;
	
	
	//vector<CString>::iterator iter;
	
	// Create Brushes for Border and BackGround
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));//背景是黑色
	
	// Border Size
	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right=THUMBNAIL_WIDTH_MASK;
	rcBorder.bottom=THUMBNAIL_HEIGHT_MASK;
	
	const float fRatio=(float)THUMBNAIL_HEIGHT_MASK/THUMBNAIL_WIDTH_MASK;
	
	int XDest, YDest, nDestWidth, nDestHeight;
	//Set redraw to FALSE to avoid flickering during adding new items
	//ListCtrl.SetRedraw(FALSE);
	// Load Image File
	//_stprintf(path, _T("%s"),PATH_REMOVE_BMP);
	//这里要写函数得到当前目录
	CString szErrTag = "G:\\err.png";
	
	TCHAR path[MAX_PATH]={0};
	_stprintf(path, _T("%s"),szErrTag.GetBuffer(0));
	
	int nImageType=pDoc->GetTypeFromFileName(path);
	CxImage image(path, nImageType);
	if(image.IsValid()==false)
	{
		return ;
	}
	//Calculate Rect to fit to canvas
	const float fImgRatio=(float)image.GetHeight()/image.GetWidth();
	if(fImgRatio > fRatio)
	{
		nDestWidth=THUMBNAIL_HEIGHT_MASK/fImgRatio;
		XDest=(THUMBNAIL_WIDTH_MASK-nDestWidth)/2;
		YDest=0;
		nDestHeight=THUMBNAIL_HEIGHT_MASK;
	}
	else
	{
		XDest=0;
		nDestWidth=THUMBNAIL_WIDTH_MASK;
		nDestHeight=THUMBNAIL_WIDTH_MASK*fImgRatio;
		YDest=(THUMBNAIL_HEIGHT_MASK-nDestHeight)/2;
	}
	
	
// 	AfxMessageBox("woat!");
	CClientDC cdc(pView);//定义pView为显示设备对象
	HDC hDC=::CreateCompatibleDC(cdc.m_hDC);//建立与pView显示设备兼容的内存显示设备
	//建立与pView显示设备兼容的位图
	HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, THUMBNAIL_WIDTH_MASK, THUMBNAIL_HEIGHT_MASK);
	//将位图选入到pView显示设备中
	HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);
	// Draw Background
	//使用背景色将位图清除干净
	::FillRect(hDC, &rcBorder, hBrushBk);
	// Draw Image
	//将图片画在pView内存显示设备上
	image.AlphaSet(100); 
	image.Stretch(hDC, XDest, YDest, nDestWidth, nDestHeight);
	// Draw Border
	//在内存显示设备上画边框
	::FrameRect(hDC, &rcBorder, hBrushBorder);
	//将位图图像显示到pView显示设备上
	SelectObject(hDC, pOldBitmapImage);
	// Attach to Bitmap and Replace image in CImageList
	CBitmap bitmap;
	bitmap.Attach(bm);//将位图贴到ImageList控件上
	pImgList->Replace(nIndex, &bitmap, NULL);
	//这里需要再贴一张透明的图片在原始的图片上...........
	//pImgList->SetOverlayImage(nIndex,1);
	//CPoint myPoint(XDest,YDest);
	//pImgList->Draw((CDC*)&hDC, 0, myPoint, INDEXTOOVERLAYMASK(1));
	// Redraw only a current item for removing flickering and fast speed.
	ListCtrl.RedrawItems(nIndex, nIndex);
	// Release used DC and Object
	DeleteDC(hDC);
	DeleteObject(bm);
	
	
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);
}