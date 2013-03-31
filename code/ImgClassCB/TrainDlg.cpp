// TrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImgClassCB.h"
#include "TrainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrainDlg dialog


CTrainDlg::CTrainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrainDlg)
	m_szInFeatTrain = _T("..\\data\\Train.txt");
	m_szOutFeatTrain = _T("..\\data\\Train.txt.out");
	m_iFeatureType = 6;
	m_iClasserType = 0;
	//}}AFX_DATA_INIT
}


void CTrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrainDlg)
	DDX_Text(pDX, IDC_EDT_INFeatTrain, m_szInFeatTrain);
	DDX_Text(pDX, IDC_EDT_OutFeatTrain, m_szOutFeatTrain);
	DDX_Radio(pDX, IDC_RAD_0, m_iFeatureType);
	DDX_Radio(pDX, IDC_RAD_11, m_iClasserType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrainDlg, CDialog)
	//{{AFX_MSG_MAP(CTrainDlg)
	ON_BN_CLICKED(IDC_BTN_InFeatTrainBro, OnBTNInFeatTrainBro)
	ON_BN_CLICKED(IDC_BTN_OutFeatTrainBro, OnBTNOutFeatTrainBro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrainDlg message handlers

void CTrainDlg::OnOK() 
{
	UpdateData(TRUE);
	// TODO: Add extra validation here
	char szParam[256] = "";
	char szExe[256] = "";

		//分类器可执行程序
	if(m_iClasserType == 0)
	{
		sprintf(szExe, "..\\bin\\svm-train.exe");
		if(m_iFeatureType == 9)
		{
			MessageBox("特征的融合在测试时进行，相关说明请参见文档", "温馨提示", MB_OK | MB_ICONINFORMATION);
			return;
		}
		switch(m_iFeatureType)
		{
		case 0:	sprintf(szParam, "-c 1 -g 0.00001 ..\\data\\EDH_Train.txt ..\\data\\EDH_Train.mdl");			break;
		case 1:	sprintf(szParam, "-c 0.0000305 -g 0.00048828 ..\\data\\CCH_Train.txt ..\\data\\CCH_Train.mdl");	break;
		case 2:	sprintf(szParam, "-c 2 -g 0.00001 ..\\data\\GBR_Train.txt ..\\data\\GBR_Train.mdl");			break;
		case 3:	sprintf(szParam, "-c 4096 -g 0.00048828 ..\\data\\ImEx_Train.txt ..\\data\\ImEx_Train.mdl");	break;
		case 4:	sprintf(szParam, "-c 4096 -g 0.00048828 ..\\data\\ImEx_Train.txt ..\\data\\ImEx_Train.mdl");	break;
		case 5:	sprintf(szParam, "-c 16384 -g 0.000061 ..\\data\\GLCM_Train.txt ..\\data\\GLCM_Train.mdl");		break;
		case 6:	sprintf(szParam, "-c 16384 -g 0.000061 ..\\data\\GLCMX_Train.txt ..\\data\\GLCMX_Train.mdl");	break;
		case 7:	sprintf(szParam, "-c 32 -g 0.0012315 ..\\data\\SIFT_Train.txt ..\\data\\SIFT_Train.mdl");		break;
		case 8:	sprintf(szParam, "-c 32 -g 0.0012315 ..\\data\\PCASIFT_Train.txt ..\\data\\PCASIFT_Train.mdl");	break;
		//case 9: sprintf(szParam, "-c 1 -g 0.00001 ..\\data\\Merge_Train.txt ..\\data\\Merge_Train.mdl");		break;
		}
	}
	else if(m_iClasserType == 1)
	{
		sprintf(szExe, "..\\bin\\knn.exe");
		switch(m_iFeatureType)
		{
		case 0:	sprintf(szParam, "..\\data\\EDH_Train.txt ..\\data\\EDH_Test.txt ..\\data\\EDH_res.rrw");		break;
		case 1:	sprintf(szParam, "..\\data\\CCH_Train.txt ..\\data\\CCH_Test.txt ..\\data\\CCH_res.rrw");		break;
		case 2:	sprintf(szParam, "..\\data\\GBR_Train.txt ..\\data\\GBR_Test.txt ..\\data\\GBR_res.rrw");		break;
		case 3:	sprintf(szParam, "..\\data\\ImEx_Train.txt ..\\data\\ImEx_Test.txt ..\\data\\ImEx_res.rrw");		break;
		case 4:	sprintf(szParam, "..\\data\\ImEx_Train.txt ..\\data\\ImEx_Test.txt ..\\data\\ImEx_res.rrw");		break;
		case 5:	sprintf(szParam, "..\\data\\GLCM_Train.txt ..\\data\\GLCM_Test.txt ..\\data\\GLCM_res.rrw");		break;
		case 6:	sprintf(szParam, "..\\data\\GLCMX_Train.txt ..\\data\\GLCMX_Test.txt ..\\data\\GLCMX_res.rrw");	break;
		case 7:	sprintf(szParam, "..\\data\\SIFT_Train.txt ..\\data\\SIFT_Test.txt ..\\data\\SIFT_res.rrw");		break;
		case 8:	sprintf(szParam, "..\\data\\PCASIFT_Train.txt ..\\data\\PCASIFT_Test.txt ..\\data\\PCASIFT_res.rrw");break;
		//case 9: sprintf(szParam, "-c 1 -g 0.00001 ..\\data\\Merge_Train.txt ..\\data\\Merge_Test.txt ..\\data\\Merge_res.rrw");		break;
		}
		if(m_iFeatureType == 9)
		{
			MessageBox("knn未做有关特征融合的部分，相关说明请参见文档", "温馨提示", MB_OK | MB_ICONINFORMATION);
			return;
		}
	}
		
	ShellExecute(this->m_hWnd, "open", szExe, szParam, "", SW_SHOW );
	CDialog::OnOK();
}

void CTrainDlg::OnBTNInFeatTrainBro() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(TRUE, "Text Files(*.txt)|*.* ", "Train.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files(*.txt)|*.*||"); 
	const int c_cMaxFiles = 100; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1; 
	
	dlgFile.DoModal(); 
	m_szInFeatTrain = dlgFile.GetPathName();
	UpdateData(FALSE);
	
}

void CTrainDlg::OnBTNOutFeatTrainBro() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(FALSE, "Text Files(*.txt)|*.* ", "Train.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files(*.txt)|*.*"); 
	const int c_cMaxFiles = 100; 
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1; 
	
	dlgFile.DoModal(); 
	m_szOutFeatTrain = dlgFile.GetPathName();
	UpdateData(FALSE);
	
}
