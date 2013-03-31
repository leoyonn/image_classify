// FeatureExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImgClassCB.h"
#include "FeatureExDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFeatureExDlg dialog


CFeatureExDlg::CFeatureExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFeatureExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFeatureExDlg)
	m_szInTest = _T("..\\pic\\");
	m_szInTrain = _T("..\\pic\\");
	m_szOutTest = _T("..\\data\\test.txt");
	m_szOutTrain = _T("..\\data\\train.txt");
	m_iFeatureType = 2;
	//}}AFX_DATA_INIT
}


void CFeatureExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeatureExDlg)
	DDX_Text(pDX, IDC_EDT_INTEST, m_szInTest);
	DDX_Text(pDX, IDC_EDT_INTRAIN, m_szInTrain);
	DDX_Text(pDX, IDC_EDT_OUTTEST, m_szOutTest);
	DDX_Text(pDX, IDC_EDT_OUTTRAIN, m_szOutTrain);
	DDX_Radio(pDX, IDC_RAD_0, m_iFeatureType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFeatureExDlg, CDialog)
	//{{AFX_MSG_MAP(CFeatureExDlg)
	ON_BN_CLICKED(IDC_BTN_INTRAINBRO, OnBtnIntrainbro)
	ON_BN_CLICKED(IDC_BTN_INTESTBRO, OnBtnIntestbro)
	ON_BN_CLICKED(IDC_BTN_OUTTRAINBRO, OnBtnOuttrainbro)
	ON_BN_CLICKED(IDC_BTN_OUTTESTBRO, OnBtnOuttestbro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFeatureExDlg message handlers

void CFeatureExDlg::OnOK() 
{
	// TODO: Add extra validation here
	char str[MAX_PATH] = "";
	GetCurrentDirectory(MAX_PATH, str);
	char szParam[256] = "";
	char szExe[256] = "";
	
	UpdateData(TRUE);

	switch(m_iFeatureType)
	{
	case 0:
		sprintf(szExe,		"..\\bin\\FE_EDH.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\EDH_Train.txt ..\\data\\EDH_Test.txt");
		break;
	case 1:
		sprintf(szExe,		"..\\bin\\FE_CCH.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\CCH_Train.txt ..\\data\\CCH_Test.txt");
		break;
	case 2:
		sprintf(szExe,		"..\\bin\\FE_GBR.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\GBR_Train.txt ..\\data\\GBR_Test.txt");
		break;
	case 3:
		sprintf(szExe,		"..\\bin\\FE_GLCM_IM.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\IM_Train.txt ..\\data\\IM_Test.txt");
		break;
	case 4:
		sprintf(szExe,		"..\\bin\\FE_GLCM_IM.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\ImEx_Train.txt ..\\data\\ImEx_Test.txt");
		break;
/*
	case 5:
		sprintf(szExe,		"..\\bin\\FE_Hough.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\Hough_Train.txt ..\\data\\Hough_Test.txt");
		break;
*/
	case 6:
		sprintf(szExe,		"..\\bin\\FE_GLCM_IM.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\GLCM_Train.txt ..\\data\\GLCM_Test.txt");
		break;
	case 7:
		sprintf(szExe,		"..\\bin\\FE_GLCM_IM.exe");	
		sprintf(szParam,	"..\\pic\\ ..\\data\\GLCMX_Train.txt ..\\data\\GLCMX_Test.txt");
		break;
	case 8:
		sprintf(szExe,		"..\\bin\\FE_SIFT.exe");	
		sprintf(szParam,	"s ..\\pic\\ ..\\data\\SIFT_Train.txt ..\\data\\SIFT_Test.txt");
		break;
	case 9:
		sprintf(szExe,		"..\\bin\\FE_SIFT.exe");	
		sprintf(szParam,	"p ..\\pic\\ ..\\data\\PCASIFT_Train.txt ..\\data\\PCASIFT_Test.txt");
		break;
	}
	ShellExecute(this->m_hWnd, "open", szExe, szParam, "", SW_SHOW );

	CDialog::OnOK();
}

void CFeatureExDlg::OnBtnIntrainbro() 
{
	char pBuffer[MAX_PATH] = "";
    BROWSEINFO   bf;   
    LPITEMIDLIST   lpitem;   
    memset(&bf,0,sizeof   BROWSEINFO);   
    bf.hwndOwner=GetSafeHwnd();   
    bf.lpszTitle="选择路径";   
    bf.ulFlags=BIF_RETURNONLYFSDIRS;     //属性你可自己选择   
    lpitem=SHBrowseForFolder(&bf);   
    if(lpitem==NULL)     //如果没有选择路径则返回   0   
        return;   
    
    //如果选择了路径则复制路径,返回路径长度   
    
    SHGetPathFromIDList(lpitem,pBuffer);   

}

void CFeatureExDlg::OnBtnIntestbro() 
{
	char pBuffer[MAX_PATH] = "";
    BROWSEINFO   bf;   
    LPITEMIDLIST   lpitem;   
    memset(&bf,0,sizeof   BROWSEINFO);   
    bf.hwndOwner=GetSafeHwnd();   
    bf.lpszTitle="选择路径";   
    bf.ulFlags=BIF_RETURNONLYFSDIRS;     //属性你可自己选择   
    lpitem=SHBrowseForFolder(&bf);   
    if(lpitem==NULL)     //如果没有选择路径则返回   0   
        return;   
    
    //如果选择了路径则复制路径,返回路径长度   
    
    SHGetPathFromIDList(lpitem,pBuffer);   
}

void CFeatureExDlg::OnBtnOuttrainbro() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(FALSE, "Text Files(*.txt)|*.* ", "Train.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files(*.txt)|*.*||"); 
	const int c_cMaxFiles = 100; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1; 
	
	dlgFile.DoModal(); 
	m_szOutTrain = dlgFile.GetPathName();
	UpdateData(FALSE);
	
}

void CFeatureExDlg::OnBtnOuttestbro() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(FALSE, "Text Files(*.txt)|*.* ", "Text.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files(*.txt)|*.*||"); 
	const int c_cMaxFiles = 100; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1; 
	
	dlgFile.DoModal(); 
	m_szOutTest = dlgFile.GetPathName();
	UpdateData(FALSE);
}
