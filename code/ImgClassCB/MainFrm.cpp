// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ImgClassCB.h"

#include "MainFrm.h"
#include "ImgClassCBDoc.h"
#include "ImgClassCBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_DIRECTORY_BAR, OnViewDirectoryBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DIRECTORY_BAR, OnUpdateViewDirectoryBar)
	ON_COMMAND(ID_VIEW_PREVIEW_BAR, OnViewPreviewBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIEW_BAR, OnUpdateViewPreviewBar)
	ON_WM_CLOSE()
	ON_COMMAND(ID_STOP_THREAD, OnStopThread)
	ON_UPDATE_COMMAND_UI(ID_STOP_THREAD, OnUpdateStopThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bShowPreviewBar=m_bShowDirectoryBar=TRUE;
	int i, j;
	for(i = 0; i < 1000; i ++)
	{
		m_resultData.bCorrect[0] = true;
		m_resultData.iClasses[i] = 0;
	}
	for(i = 0; i < 20; i ++)
	{
		m_resultData.dImgCorRate[i] = 0;
		m_resultData.iImgCorNo_per_Cls[i] = 0;
		m_resultData.iImgNo_per_Cls[i] = 0;
		for(j = 0; j < 20; j ++)
			m_resultData.dImgConMat[i][j] = 0;
		for(j = 0; j < 1000; j ++)
			m_resultData.iImgs_per_Cls[i][j] = 0;
	}
	m_resultData.dEveCorRate = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
/*
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
*/


	if (!m_wndCCBar.Create(_T("图像类别浏览"), this, CSize(150, 100),
				    TRUE , AFX_IDW_CONTROLBAR_FIRST + 33))
	{
		return -1;
		// fail to create
	}
	m_wndCCBar.SetBarStyle(m_wndCCBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	m_wndCCBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	
	EnableDocking(CBRS_ALIGN_ANY);
	
#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif


	if (!m_wndPreviewBar.Create(_T("选定图像大图浏览"), this, CSize(150, 400),
				    TRUE , AFX_IDW_CONTROLBAR_FIRST + 33))
	{
		return -1;
		// fail to create
	}
	m_wndPreviewBar.SetBarStyle(m_wndPreviewBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	m_wndPreviewBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	
	EnableDocking(CBRS_ALIGN_ANY);
	
#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif
	
	
	if (!m_wndDirTreeBar.Create(_T("我的电脑"), this, CSize(300, 200),
				    TRUE , AFX_IDW_CONTROLBAR_FIRST + 33))
	{
		return -1;
		// fail to create
	}
	m_wndDirTreeBar.SetBarStyle(m_wndDirTreeBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	
	m_wndDirTreeBar.EnableDocking(CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT);
	
	EnableDocking(CBRS_ALIGN_ANY);
	
#ifdef _SCB_REPLACE_MINIFRAME
    m_pFloatingFrameClass = RUNTIME_CLASS(CSCBMiniDockFrameWnd);
#endif
	
	
	DockControlBar(&m_wndCCBar, AFX_IDW_DOCKBAR_LEFT);

	RecalcLayout();
	CRect rBar;
	m_wndCCBar.GetWindowRect(rBar);
	rBar.OffsetRect(0, 1);
	DockControlBar(&m_wndPreviewBar, AFX_IDW_DOCKBAR_LEFT, rBar);
	
	RecalcLayout();
	CRect rBar2;
	m_wndPreviewBar.GetWindowRect(rBar2);
	rBar2.OffsetRect(0, 1);
	DockControlBar(&m_wndDirTreeBar, AFX_IDW_DOCKBAR_LEFT, rBar2);
	
	
	MoveWindow(10, 50, 1040, 720);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewDirectoryBar() 
{
	// TODO: Add your command handler code here
	if(m_bShowDirectoryBar)
	{
		::ShowWindow(m_wndDirTreeBar.m_hWnd,SW_HIDE);			
		DockControlBar(&m_wndDirTreeBar,AFX_IDW_DOCKBAR_LEFT);				
		m_bShowDirectoryBar=FALSE;

		RecalcLayout(TRUE);
	}
	else
	{
		::ShowWindow(m_wndDirTreeBar.m_hWnd,SW_SHOW);
		DockControlBar(&m_wndDirTreeBar,AFX_IDW_DOCKBAR_LEFT);
		RecalcLayout(TRUE);
		m_bShowDirectoryBar=TRUE;
	}
}

void CMainFrame::OnUpdateViewDirectoryBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShowDirectoryBar);
}

void CMainFrame::OnViewPreviewBar() 
{
	// TODO: Add your command handler code here
	if(m_bShowPreviewBar)
	{
		::ShowWindow(m_wndPreviewBar.m_hWnd,SW_HIDE);			
		DockControlBar(&m_wndPreviewBar,AFX_IDW_DOCKBAR_LEFT);				
		m_bShowPreviewBar=FALSE;

		RecalcLayout(TRUE);
	}
	else
	{
		::ShowWindow(m_wndPreviewBar.m_hWnd,SW_SHOW);
		DockControlBar(&m_wndPreviewBar,AFX_IDW_DOCKBAR_LEFT);
		RecalcLayout(TRUE);
		m_bShowPreviewBar=TRUE;
	}
}

void CMainFrame::OnUpdateViewPreviewBar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bShowPreviewBar);	
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CFrameWnd::OnClose();
}

void CMainFrame::OnStopThread() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnUpdateStopThread(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CImgClassCBView* pView=(CImgClassCBView*)GetActiveView();
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CRect rect;
	GetClientRect(&rect);
	//产生第一次静态切分
	if(!m_wndSplitter.CreateStatic(this,
							2,	// 切分的行数
							1,	// 切分的列数
							WS_CHILD|WS_VISIBLE))
	{   
		TRACE("Failed   to   CreateStaticSplitter\n");   
		return   FALSE;   
	}   

	//为第一个窗格产生视图
	m_wndSplitter.CreateView(0,	0, // 窗格的行、列序数
							RUNTIME_CLASS(CImgClassCBView),//视图类
							CSize(rect.Width(),rect.Height()-rect.Height()/5),//初始化大小
							pContext);//父窗口的创建参数
		//为第二个窗格产生视图
							m_wndSplitter.CreateView(1,0,
							RUNTIME_CLASS(CImgClassCBView),
							CSize(rect.Width(),rect.Height()/5),
							pContext);
		m_wndSplitter.SetRowInfo(0,300,0); 
		m_wndSplitter.SetRowInfo(1,360,0); 
		m_pTrainView = (CImgClassCBView*)m_wndSplitter.GetPane(0, 0);
		m_pTestView = (CImgClassCBView*)m_wndSplitter.GetPane(1, 0);
		m_pTrainView->m_iViewNo = 0;
		m_pTestView->m_iViewNo = 1;
		m_pTrainView->SetFocus();
		//m_pTestView->SetFocus();

	return TRUE;//不再调用基类的OnCreateClient函数	

// 	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

double CMainFrame::LoadResult(char *szRrwFile)
{
	int i, j;
	for(i = 0; i < 1000; i ++)
	{
		m_resultData.bCorrect[0] = true;
		m_resultData.iClasses[i] = 0;
	}
	for(i = 0; i < 20; i ++)
	{
		m_resultData.dImgCorRate[i] = 0;
		m_resultData.iImgCorNo_per_Cls[i] = 0;
		m_resultData.iImgNo_per_Cls[i] = 0;
		for(j = 0; j < 20; j ++)
			m_resultData.dImgConMat[i][j] = 0;
		for(j = 0; j < 1000; j ++)
			m_resultData.iImgs_per_Cls[i][j] = 0;
	}
	m_resultData.dEveCorRate = 0;

	FILE *fInput = fopen(szRrwFile, "r");
	FILE *fOutput1 = fopen("..\\data\\result.txt", "w");
	FILE *fOutput2 = fopen("..\\data\\ConMat.txt", "w");
	if(!fInput || !fOutput1 || !fOutput2)
	{
		MessageBox("计算Confusion Matrix时，加载分类结果失败！", "温馨提示", 
			MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	for(i = 0; i < 1000; i ++)
		m_resultData.bCorrect[i] = true;
	for(i = 0; i < 1000; i ++)
	{
		int iCls = 0;
		fscanf(fInput, "%d\n", &iCls);
		m_resultData.iClasses[i] = iCls;
		int iC = i / 50;
		if(iCls != iC)
			m_resultData.bCorrect[i] = false;
		else
			m_resultData.iImgCorNo_per_Cls[iCls] ++;
		m_resultData.iImgs_per_Cls[iCls][m_resultData.iImgNo_per_Cls[iCls]] = (i / 50) * 100 + i % 50 + 50, i / 50; 
		m_resultData.iImgNo_per_Cls[m_resultData.iClasses[i]] ++;
		m_resultData.dImgConMat[iC][iCls] ++;
	}
	for(i = 0; i < 20; i ++)
	{
		m_resultData.dImgCorRate[i] = (double)m_resultData.iImgCorNo_per_Cls[i]/(double)50;
		m_resultData.dEveCorRate += m_resultData.dImgCorRate[i];
		for(j =0; j < 20; j ++)
		{
			m_resultData.dImgConMat[i][j] /= 50;
			fprintf(fOutput2, "%1.2f ", m_resultData.dImgConMat[i][j]);
		}
		fprintf(fOutput2, "\n");
	}
	m_resultData.dEveCorRate /= 20;

	for(i = 0; i < 1000; i ++)
	{
		fprintf(fOutput1, "%5d  %3d %3d\n", (i / 50) * 100 + i % 50 + 50, i / 50 + 1, m_resultData.iClasses[i] + 1);
	}
	fclose(fInput);
	fclose(fOutput1);
	fclose(fOutput2);
	return m_resultData.dEveCorRate;
}


void CMainFrame::ShowResult()
{
	m_wndCCBar.LoadResult();
}