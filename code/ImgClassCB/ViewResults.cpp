// ViewResults.cpp : implementation file
//

#include "stdafx.h"
#include "MainFrm.h"
#include "ImgClassCB.h"
#include "ViewResults.h"
#include "ximage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewResults dialog

CViewResults::CViewResults(CWnd* pParent /*=NULL*/)
	: CDialog(CViewResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewResults)
	m_szInResultFile = _T("..\\data\\resultraw.rrw");
	m_iFeatureType = 6;
	m_iClassType = 0;
	//}}AFX_DATA_INIT
}


void CViewResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewResults)
	DDX_Control(pDX, IDC_PICTURE, m_cPicture);
	DDX_Text(pDX, IDC_EDT_INResultFile, m_szInResultFile);
	DDX_Radio(pDX, IDC_RAD_0, m_iFeatureType);
	DDX_Radio(pDX, IDC_RAD_11, m_iClassType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewResults, CDialog)
	//{{AFX_MSG_MAP(CViewResults)
	ON_BN_CLICKED(IDC_BTN_ConMatText, OnBTNConMatText)
	ON_BN_CLICKED(IDC_BTN_ConMatImg, OnBTNConMatImg)
	ON_BN_CLICKED(IDC_BTN_InResultFileBro, OnBTNInResultFileBro)
	ON_BN_CLICKED(IDC_BTN_LoadRRW, OnBTNLoadRRW)
	ON_BN_CLICKED(IDC_BTN_ViewResultTxt, OnBTNViewResultTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewResults message handlers

void CViewResults::OnBTNConMatText() 
{
	// TODO: Add your control notification handler code here
	//ComputeConMat(m_szInResultFile.GetBuffer(0));

	ShellExecute(this->m_hWnd, "open", "..\\data\\ConMat.txt","","", SW_SHOW );
}

void CViewResults::OnBTNConMatImg() 
{
	// TODO: Add your control notification handler code here
	// Invoke the standard Insert Object dialog box to obtain information
	
    //  for new COlecreateCntrItem object.
	
	HBITMAP m_bitmap = NULL;
	CxImage image("..\\data\\ConMat.jpg", CXIMAGE_FORMAT_PNG);
	CDC* hdc = m_cPicture.GetDC();
	m_bitmap = image.MakeBitmap(hdc->m_hDC);
	
	HBITMAP hOldBmp = m_cPicture.SetBitmap(m_bitmap);
	if (hOldBmp) DeleteObject(hOldBmp);
	if (hdc->m_hDC) m_cPicture.ReleaseDC(hdc);

	//if (m_bitmap) DeleteObject(m_bitmap);
	
}

void CViewResults::OnBTNInResultFileBro() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(TRUE, "Text Files(*.txt)|*.* ", "result.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "result Files(*.rrw)|*.*"); 
	const int c_cMaxFiles = 100; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1; 
	
	dlgFile.DoModal(); 
	m_szInResultFile = dlgFile.GetPathName();
	UpdateData(FALSE);
}


void CViewResults::ComputeConMat(char *szInput)
{
	FILE *fInput = fopen("..\\data\\resultraw.txt", "r");
	FILE *fOutput1 = fopen("..\\data\\result.txt", "w");
	FILE *fOutput2 = fopen("..\\data\\ConMat.txt", "w");
	if(!fInput || !fOutput1 || !fOutput2)
	{
		MessageBox("计算Confusion Matrix时，加载分类结果失败！", "温馨提示", 
			MB_OK | MB_ICONINFORMATION);
		return;
	}
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	int i;
	for(i = 0; i < 1000; i ++)
		pFrame->m_resultData.bCorrect[i] = true;
	for(i = 0; i < 1000; i ++)
	{
		fscanf(fInput, "%d\n", &pFrame->m_resultData.iClasses[i]);
		int iC = i / 100;
		if(pFrame->m_resultData.iClasses[i] != iC)
			pFrame->m_resultData.bCorrect[i] = false;
		else
			pFrame->m_resultData.iImgCorNo_per_Cls[pFrame->m_resultData.iClasses[i]] ++;
		pFrame->m_resultData.iImgs_per_Cls[pFrame->m_resultData.iClasses[i]][pFrame->m_resultData.iImgNo_per_Cls[pFrame->m_resultData.iClasses[i]]] = i; 
		pFrame->m_resultData.iImgNo_per_Cls[pFrame->m_resultData.iClasses[i]] ++;
	}
	for(i = 0; i < 20; i ++)
		pFrame->m_resultData.dImgCorRate[i] = (double)pFrame->m_resultData.iImgCorNo_per_Cls[i]/(double)50;
	for(i = 0; i < 1000; i ++)
	{
		fprintf(fOutput1, "%5d  %3d %3d", (i / 50) * 100 + i % 50 + 50, i / 100 + 1, pFrame->m_resultData.iClasses[i] + 1);
	}

	fclose(fInput);
	fclose(fOutput1);
	fclose(fOutput2);
	
}

void CViewResults::OnOK() 
{
	// TODO: Add extra validation here
	CMainFrame *pFrame = GetMainFrame();
	pFrame->ShowResult();
	CDialog::OnOK();
}

void CViewResults::OnBTNLoadRRW() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CMainFrame* pFrame = GetMainFrame();
	double dAveRate = pFrame->LoadResult(m_szInResultFile.GetBuffer(0));
	CString strOut;
	strOut.Format("结果导入成功，平均准确率%.2f%%.\n现在可以通过各种方式查询结果", dAveRate * 100);
	MessageBox(strOut, "温馨提示", MB_OK | MB_ICONINFORMATION);
}

void CViewResults::OnBTNViewResultTxt() 
{
	// TODO: Add your control notification handler code here
	ShellExecute(this->m_hWnd, "open", "..\\data\\result.txt","","", SW_SHOW );
}
