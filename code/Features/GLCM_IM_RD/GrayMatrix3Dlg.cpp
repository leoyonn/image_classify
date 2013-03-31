// GrayMatrix3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GrayMatrix3.h"
#include "GrayMatrix3Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrayMatrix3Dlg dialog

CGrayMatrix3Dlg::CGrayMatrix3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGrayMatrix3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrayMatrix3Dlg)
	m_szInImg = _T("..\\pic\\");
	m_szOutTrain = _T("..\\data\\*_Train.txt");
	m_szOutTest = _T("..\\data\\*_Test.txt");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGrayMatrix3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrayMatrix3Dlg)
	DDX_Control(pDX, IDC_ImgNum, m_cImgNum);
	DDX_Text(pDX, IDC_EDIT1, m_szInImg);
	DDX_Text(pDX, IDC_EDIT2, m_szOutTrain);
	DDX_Text(pDX, IDC_EDIT3, m_szOutTest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGrayMatrix3Dlg, CDialog)
	//{{AFX_MSG_MAP(CGrayMatrix3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Exit, OnBTNExit)
	ON_BN_CLICKED(IDC_BTN_LoadJpg, OnBTNLoadJpg)
	ON_BN_CLICKED(IDC_BTN_HuConMatrix, OnBTNHuConMatrix)
	ON_BN_CLICKED(IDC_BTN_RANDOM, OnBtnRandom)
	ON_BN_CLICKED(IDC_BTN_Make, OnBTNMake)
	ON_BN_CLICKED(IDC_BTN_LoadJpg2, OnBTNCoMX5)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BTN_SIFT, OnBtnSift)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrayMatrix3Dlg message handlers

BOOL CGrayMatrix3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGrayMatrix3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGrayMatrix3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGrayMatrix3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGrayMatrix3Dlg::OnBTNExit() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CGrayMatrix3Dlg::OnBTNGenGrayCoMatrix() 
{
	// TODO: Add your control notification handler code here
	MessageBox("Start to Compute!", "", MB_OK | MB_ICONINFORMATION);
}

void CGrayMatrix3Dlg::OnBTNLoadJpg() 
{
	// TODO: Add your control notification handler code here
	FILE *foutTrain = fopen("..\\data\\GLCM_Train.txt", "w");
	FILE *foutTest = fopen("..\\data\\GLCM_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}

	int iImgNum, i, iImgWidth, iImgHeight, iLabel, iClass, iFeatureNum = m_cGrayComatrix.m_iFeatureNum;
	for(iImgNum = 0; iImgNum < PIC_NUM; iImgNum ++)
	{
		CString ss;
		ss.Format("%d", iImgNum);
		m_cImgNum.SetWindowText(ss);
		UpdateData(FALSE);
		CxImage* cImg = new CxImage;
		CString szImgName = "";
		szImgName.Format("..\\pic\\%d.jpg", iImgNum);
		if(!cImg->Load(szImgName, CXIMAGE_FORMAT_JPG))
		{
			AfxMessageBox("Load Jpg Failed!");
			return;
		}

		iImgWidth = cImg->GetWidth();
		iImgHeight = cImg->GetHeight();
		BYTE** pImage = new BYTE*[iImgHeight];
		for(i = 0; i < iImgHeight; i ++)
		{
			pImage[i] = new BYTE[iImgWidth];
			memset(pImage[i], 0, iImgWidth * sizeof(BYTE));
		}
		
		RGBQUAD rgb;
		for(i = 0; i < iImgWidth * iImgHeight; i ++)
		{
			rgb = cImg->GetPixelColor(i % iImgWidth,i / iImgWidth, true);
				//I = O.299 * R + O.587 * G + 0.114 * B ：更精确
			pImage[i / iImgWidth][i % iImgWidth] = BYTE(0.299 * rgb.rgbRed + 0.587 * rgb.rgbGreen + 0.114 * rgb.rgbBlue);
		}
		
		double duFeatures[16]		= {0.0, };
		double dsFeatures[16]		= {0.0, };
		
		m_cGrayComatrix.ComputeMatrix(pImage, iImgWidth, iImgHeight);
		m_cGrayComatrix.OnComputeFeature(m_cGrayComatrix.m_iFeatureNum, duFeatures, dsFeatures);

		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			fprintf(foutTrain, "%d", iClass);
			for(i = 0; i < 10; i ++)
				fprintf(foutTrain, " %d:%.4f", i + 1, duFeatures[i]);
			for(i = 0; i < 10; i ++)
				fprintf(foutTrain, " %d:%.4f", i + 10 + 1, dsFeatures[i]);
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			fprintf(foutTest, "%d", iClass);
			for(i = 0; i < 10; i ++)
				fprintf(foutTest, " %d:%.4f", i + 1, duFeatures[i]);
			for(i = 0; i < 10; i ++)
				fprintf(foutTest, " %d:%.4f", i + 10 + 1, dsFeatures[i]);
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}
		//fprintf(fout, "\n\n");
		for(i = 0; i < iImgHeight; i ++)
			delete pImage[i];
		delete pImage;
		delete cImg;
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");
// 	myXimage->Load("G:\\pic\\1.jpg", CXIMAGE_FORMAT_JPG);
// 	myXimage->Save("G:\\z.bmp", CXIMAGE_FORMAT_BMP);
}

void CGrayMatrix3Dlg::OnBTNHuConMatrix() 
{
	FILE *foutTrain = fopen("..\\data\\ImEx_Train.txt", "w");
	FILE *foutTest = fopen("..\\data\\ImEx_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}

	int iImgNum, i, iImgWidth, iImgHeight, iLabel, iClass;
	for(iImgNum = 0; iImgNum < 2000; iImgNum ++)
	{
		CString ss;
		ss.Format("%d", iImgNum);
		m_cImgNum.SetWindowText(ss);
		UpdateData(FALSE);
		CxImage* cImg = new CxImage;
		CString szImgName = "";
		szImgName.Format("..\\pic\\%d.jpg", iImgNum);
		UpdateData(FALSE);
		if(!cImg->Load(szImgName, CXIMAGE_FORMAT_JPG))
		{
			AfxMessageBox("Load Jpg Failed!");
			return;
		}

		iImgWidth = cImg->GetWidth();
		iImgHeight = cImg->GetHeight();
		BYTE** pImage = new BYTE*[iImgHeight];
		BYTE*pEdge  = new BYTE[iImgWidth * iImgHeight];
		memset(pEdge, 0, iImgWidth * iImgHeight * sizeof(BYTE));
		for(i = 0; i < iImgHeight; i ++)
		{
			pImage[i] = new BYTE[iImgWidth];
			memset(pImage[i], 0, iImgWidth * sizeof(BYTE));
		}
		
		RGBQUAD rgb;
		for(i = i; i < iImgWidth * iImgHeight; i ++)
		{
			rgb = cImg->GetPixelColor(i % iImgWidth,i / iImgWidth, true);
				//I = O.299 * R + O.587 * G + 0.114 * B ：更精确
			pImage[i / iImgWidth][i % iImgWidth] = BYTE(0.299 * rgb.rgbRed + 0.587 * rgb.rgbGreen + 0.114 * rgb.rgbBlue);
		}
		
////////////////////////
		double dIM[7] = {0, }, dExIM[10] = {0, };
		m_cInvMoment.SetImgData(pImage, pEdge, iImgWidth, iImgHeight);

/*
		//Canny边缘检测，检测后复制
		m_cInvMoment.OnCanny();
// 		memcpy(pImage, pEdge, sizeof(BYTE) * iImgHeight * iImgWidth);
		int i, j;
		for(i = 0; i < iImgHeight; i ++)
			for(j = 0; j < iImgWidth; j ++)
				pImage[i][j] = pEdge[i * iImgWidth + j];
// 		CxImage *imgtemp2 = new CxImage((BYTE*)pEdge,iImgWidth * iImgHeight, CXIMAGE_FORMAT_BMP);
// 		imgtemp2->Save("G:\\temp.bmp", CXIMAGE_FORMAT_BMP);
// 		delete imgtemp2;
*/
		m_cInvMoment.ComputeFi(dIM, dExIM);
/////////////////////////////////////////////////////////
		
		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			fprintf(foutTrain, "%d", iClass);
// 			for(i = 0; i < 7; i ++)
// 				fprintf(foutTrain, " %d:%.4f", i + 1, dIM[i]);
			for(i = 0; i < 10; i ++)
				fprintf(foutTrain, " %d:%.4f", i + 1, dExIM[i]);
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			fprintf(foutTest, "%d", iClass);
// 			for(i = 0; i < 7; i ++)
// 				fprintf(foutTest, " %d:%.4f", i + 1, dIM[i]);
			for(i = 0; i < 10; i ++)
				fprintf(foutTest, " %d:%.4f", i + 1, dExIM[i]);
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}

		//fprintf(fout, "\n\n");
		for(i = 0; i < iImgHeight; i ++)
			delete pImage[i];
		delete pImage;
		delete cImg;
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");	
}

void CGrayMatrix3Dlg::OnBtnRandom() 
{
	// TODO: Add your control notification handler code here
	FILE *foutTrain = fopen("..\\data\\RDM_Train.txt", "w");
	FILE *foutTest = fopen("..\\data\\RDM_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}
	srand(time(0));
	int iImgNum, i, iLabel, iClass;
	for(iImgNum = 0; iImgNum < 2000; iImgNum ++)
	{
		CString ss;
		ss.Format("%d", iImgNum);
		double dParam[5] = {0, };

		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			fprintf(foutTrain, "%d", iClass);
			for(i = 0; i < 5; i ++)
			{
				dParam[i] = (double)(rand() % 1000) + ((double)(rand() % 1000) / 1000);
				fprintf(foutTrain, " %d:%.4f", i + 1, dParam[i]);
			}
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			fprintf(foutTest, "%d", iClass);
			for(i = 0; i < 5; i ++)
			{
				dParam[i] = (double)(rand() % 1000) + ((double)(rand() % 1000) / 1000);
				fprintf(foutTest, " %d:%.4f", i + 1, dParam[i]);
			}
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");		
}

void CGrayMatrix3Dlg::OnBTNMake() 
{
	// TODO: Add your control notification handler code here
	FILE *foutTrain = fopen("..\\data\\MK_Train.txt", "w");
	FILE *foutTest = fopen("..\\data\\MK_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}
	srand(time(0));
	int iImgNum, i, iLabel, iClass;
	for(iImgNum = 0; iImgNum < 2000; iImgNum ++)
	{
		CString ss;
		ss.Format("%d", iImgNum);
		double dParam[5] = {0, };
		
		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			fprintf(foutTrain, "%d", iClass);
			for(i = 0; i < 5; i ++)
			{
				dParam[i] = iClass + i * 100 + ((double)(rand() % 1000) / 1000);
				fprintf(foutTrain, " %d:%.4f", i + 1, dParam[i]);
			}
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			fprintf(foutTest, "%d", iClass);
			for(i = 0; i < 5; i ++)
			{
				dParam[i] = iClass + i * 100 + ((double)(rand() % 1000) / 1000);
				fprintf(foutTest, " %d:%.4f", i + 1, dParam[i]);
			}
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");		
}

void CGrayMatrix3Dlg::OnBTNCoMX5() 
{
	FILE *foutTrain = fopen("..\\data\\GLCMX_Train.txt", "w");
	FILE *foutTest = fopen("..\\data\\GLCMX_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}
	
	int iImgNum, i, j, iImgWidth, iImgHeight, iLabel, iClass, iFeatureNum = m_cGrayComatrix.m_iFeatureNum;
	int iblkH, iblkW, igridH, igridW;
	for(iImgNum = 0; iImgNum < PIC_NUM; iImgNum ++)
	{
		CString ss;
		ss.Format("%d", iImgNum);
		m_cImgNum.SetWindowText(ss);
		UpdateData(FALSE);
		CxImage* cImg = new CxImage;
		CString szImgName = "";
		szImgName.Format("..\\pic\\%d.jpg", iImgNum);
		if(!cImg->Load(szImgName, CXIMAGE_FORMAT_JPG))
		{
			AfxMessageBox("Load Jpg Failed!");
			return;
		}
		
		iImgWidth = cImg->GetWidth();
		iImgHeight = cImg->GetHeight();
		BYTE** pImage = new BYTE*[iImgHeight];
		for(i = 0; i < iImgHeight; i ++)
		{
			pImage[i] = new BYTE[iImgWidth];
			memset(pImage[i], 0, iImgWidth * sizeof(BYTE));
		}
		
		RGBQUAD rgb;
		for(i = 0; i < iImgWidth * iImgHeight; i ++)
		{
			rgb = cImg->GetPixelColor(i % iImgWidth,i / iImgWidth, true);
			//I = O.299 * R + O.587 * G + 0.114 * B ：更精确
			pImage[i / iImgWidth][i % iImgWidth] = BYTE(0.299 * rgb.rgbRed + 0.587 * rgb.rgbGreen + 0.114 * rgb.rgbBlue);
		}


		///////////////////////////////////////////////////
		//这里开始分块：
		///////////////////////////////////////////////////
		igridW = iImgWidth / 8; igridH = iImgHeight / 8;
		iblkW = igridW * 5; iblkH = igridH * 5;

		BYTE **pImgBlks[5];
		for(i = 0; i < 5; i ++)
		{
			pImgBlks[i] = new BYTE*[iblkH];
			for(j = 0; j < iblkH; j ++)
			{
				pImgBlks[i][j] = new BYTE[iblkW];
				for(int k = 0; k < iblkW; k ++)
					pImgBlks[i][j][k] = 0;
			}
		}
		
		int iW0 = iImgWidth - iblkW, iH0 = iImgHeight - iblkH;
		int iMidW0 = igridW * 2, iMidH0 = igridH * 2;
		//中间的分块：
		for(i = 0; i < igridH * 4; i ++)
		{
			for(j = 0; j < igridW * 4; j ++)
			{
				pImgBlks[0][i][j] = pImage[i + iMidH0][j + iMidW0];
			}
		}
		
		//左上角的分块：
		for(i = 0; i < iblkH; i ++)
		{
			for(j = 0; j < iblkW; j ++)
			{
				pImgBlks[1][i][j] = pImage[i][j];
			}
		}
		
		//右上角的分块：
		for(i = 0; i < iblkH; i ++)
		{
			for(j = 0; j < iblkW; j ++)
			{
				pImgBlks[2][i][j] = pImage[i][j + iW0];
			}
		}
		//左下角的分块：
		for(i = 0; i < iblkH; i ++)
		{
			for(j = 0; j < iblkW; j ++)
			{
				pImgBlks[3][i][j] = pImage[i + iH0][j];
			}
		}
		//右下角的分块：
		for(i = 0; i < iblkH; i ++)
		{
			for(j = 0; j < iblkW; j ++)
			{
				pImgBlks[4][i][j] = pImage[i + iH0][j + iW0];
			}
		}
		double duFeatures[5][16]		= {0.0, };
		double dsFeatures[5][16]		= {0.0, };
		
		m_cGrayComatrix.ComputeMatrix(pImgBlks[0], igridW * 4, igridH * 4);
		m_cGrayComatrix.OnComputeFeature(iFeatureNum, duFeatures[0], dsFeatures[0]);
		for(i = 1; i < 5; i ++)
		{
			m_cGrayComatrix.ComputeMatrix(pImgBlks[i], iblkW, iblkH);
			m_cGrayComatrix.OnComputeFeature(iFeatureNum, duFeatures[i], dsFeatures[i]);
		}
		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			fprintf(foutTrain, "%d", iClass);
			for(j = 0; j < 5; j ++)
			{
				for(i = 0; i < 10; i ++)
					fprintf(foutTrain, " %d:%.4f", j * 15 + i + 1, duFeatures[j][i]);
				for(i = 0; i < 5; i ++)
					fprintf(foutTrain, " %d:%.4f", j * 15 + i + 10 + 1, dsFeatures[j][i]);
			}
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			fprintf(foutTest, "%d", iClass);
			for(j = 0; j < 5; j ++)
			{
				for(i = 0; i < 10; i ++)
					fprintf(foutTest, " %d:%.4f", j * 15 + i + 1, duFeatures[j][i]);
				for(i = 0; i < 5; i ++)
					fprintf(foutTest, " %d:%.4f", j * 15 + i + 10 + 1, dsFeatures[j][i]);
			}
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}

		for(i = 0; i < 5; i ++)
		{
			for(j = 0; j < iblkH; j ++)
				delete []pImgBlks[i][j];
			delete []pImgBlks[i];
		}
		//delete []pImgBlks; 不用delete了
		for(i = 0; i < iImgHeight; i ++)
			delete []pImage[i];
		delete []pImage;
		delete cImg;
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");
}

void CGrayMatrix3Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here

	FILE *foutTrain = fopen("G:\\adaMK_Train.txt", "w");
	FILE *foutTest = fopen("G:\\adaMK_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}
	srand(time(0));
	int iImgNum, i, iLabel, iClass;
	for(iImgNum = 0; iImgNum < 2000; iImgNum ++)
	{
		double dParam[5] = {0, };
		
		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			//fprintf(foutTrain, "%d", iClass);
			for(i = 0; i < 5; i ++)
			{
				dParam[i] = iClass + i * 100 + ((double)(rand() % 1000) / 1000);
				fprintf(foutTrain, " %.4f", dParam[i]);
			}
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			//fprintf(foutTest, "%d", iClass);
			for(i = 0; i < 5; i ++)
			{
				dParam[i] = iClass + i * 100 + ((double)(rand() % 1000) / 1000);
				fprintf(foutTest, " %.4f", dParam[i]);
			}
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");		
		
}

void CGrayMatrix3Dlg::OnBtnSift() 
{
	FILE *foutTrain = fopen("G:\\SIFT_Train.txt", "w");
	FILE *foutTest = fopen("G:\\SIFT_Ex_Test.txt", "w");
	if(!foutTrain || !foutTest)
	{
		AfxMessageBox("open file error!");
		return;
	}

	int iImgNum, i, iImgWidth, iImgHeight, iLabel, iClass;
	for(iImgNum = 0; iImgNum < 1; iImgNum ++)
	{
		CxImage* cImg = new CxImage;
		CString szImgName = "";
		szImgName.Format("G:\\pic\\%d.jpg", iImgNum);
		if(!cImg->Load(szImgName, CXIMAGE_FORMAT_JPG))
		{
			AfxMessageBox("Load Jpg Failed!");
			return;
		}

		iImgWidth = cImg->GetWidth();
		iImgHeight = cImg->GetHeight();
		BYTE** pImage = new BYTE*[iImgHeight];
		BYTE*pEdge  = new BYTE[iImgWidth * iImgHeight];
		memset(pEdge, 0, iImgWidth * iImgHeight * sizeof(BYTE));
		for(i = 0; i < iImgHeight; i ++)
		{
			pImage[i] = new BYTE[iImgWidth];
			memset(pImage[i], 0, iImgWidth * sizeof(BYTE));
		}
		
		RGBQUAD rgb;
		for(i = i; i < iImgWidth * iImgHeight; i ++)
		{
			rgb = cImg->GetPixelColor(i % iImgWidth,i / iImgWidth, true);
				//I = O.299 * R + O.587 * G + 0.114 * B ：更精确
			pImage[i / iImgWidth][i % iImgWidth] = BYTE(0.299 * rgb.rgbRed + 0.587 * rgb.rgbGreen + 0.114 * rgb.rgbBlue);
		}
		
////////////////////////
		double dIM[7] = {0, }, dExIM[10] = {0, };
		m_cInvMoment.SetImgData(pImage, pEdge, iImgWidth, iImgHeight);

/*
		//Canny边缘检测，检测后复制
		m_cInvMoment.OnCanny();
// 		memcpy(pImage, pEdge, sizeof(BYTE) * iImgHeight * iImgWidth);
		int i, j;
		for(i = 0; i < iImgHeight; i ++)
			for(j = 0; j < iImgWidth; j ++)
				pImage[i][j] = pEdge[i * iImgWidth + j];
// 		CxImage *imgtemp2 = new CxImage((BYTE*)pEdge,iImgWidth * iImgHeight, CXIMAGE_FORMAT_BMP);
// 		imgtemp2->Save("G:\\temp.bmp", CXIMAGE_FORMAT_BMP);
// 		delete imgtemp2;
*/
		m_cInvMoment.ComputeFi(dIM, dExIM);
/////////////////////////////////////////////////////////
		
		iLabel = iImgNum / 50;
		iClass = iImgNum / 100;
		if(iLabel % 2 == 0)
		{
			fprintf(foutTrain, "%d", iClass);
// 			for(i = 0; i < 7; i ++)
// 				fprintf(foutTrain, " %d:%.4f", i + 1, dIM[i]);
			for(i = 0; i < 10; i ++)
				fprintf(foutTrain, " %d:%.4f", i + 1, dExIM[i]);
			if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
		}
		else
		{
			fprintf(foutTest, "%d", iClass);
// 			for(i = 0; i < 7; i ++)
// 				fprintf(foutTest, " %d:%.4f", i + 1, dIM[i]);
			for(i = 0; i < 10; i ++)
				fprintf(foutTest, " %d:%.4f", i + 1, dExIM[i]);
			if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
		}

		//fprintf(fout, "\n\n");
		for(i = 0; i < iImgHeight; i ++)
			delete pImage[i];
		delete pImage;
		delete cImg;
	}
	fclose(foutTrain);
	fclose(foutTest);
	MessageBox("OK!");		
}
