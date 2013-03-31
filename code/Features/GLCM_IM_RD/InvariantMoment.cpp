// InvariantMoment.cpp: implementation of the CInvariantMoment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InvariantMoment.h"
#include "math.h"
#include "windows.h"
#include "Canny.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CInvariantMoment::CInvariantMoment()
{
	//7个不变矩值
	Fi1=0;                                  
	Fi2=0;
	Fi3=0;
	Fi4=0;
	Fi5=0;
	Fi6=0;
	Fi7=0;
	
	//7个不变矩重用到的yita值
	yita20=0;                             
	yita02=0;
	yita11=0;
	yita30=0;
	yita03=0;
	yita12=0;
	yita21=0;
		
	//x,y重心坐标
	m_mx=0;           
	m_my=0;  
}

CInvariantMoment::CInvariantMoment(LPSTR lpBits,LONG Width,LONG Height)
{
         
         //图像数据区指针，宽度，高度
	// m_pImageData=lpBits;
	 m_iImgWidth=Width;
	 m_iImgHeight=Height;

         //7个不变矩值
	 int i;
	 for(i = 0; i < 7; i ++)
	 {
		 m_dIM[i] = 0;
		 m_dIM_Norm[i] = 0;
	 }

         //7个不变矩重用到的yita值
	 yita20=0;                             
     yita02=0;
     yita11=0;
     yita30=0;
     yita03=0;
     yita12=0;
     yita21=0;

         //图像每行字实际节数
	 LineBytes=(((Width) + 31) / 32 * 4); 

     //x,y重心坐标
     m_mx=0;           
     m_my=0;  

}

CInvariantMoment::~CInvariantMoment()
{

}

void CInvariantMoment::SetImgData(BYTE **pImage, BYTE *pEdge, int w, int h)
{
	m_iImgWidth = w;
	m_iImgHeight = h;
	m_pImageData = pImage;
	m_pImageEdge = pEdge;

}
double CInvariantMoment::ComputeM(int p, int q)
{

    int i=0;     //计数
	int j=0;
	double m=0;  //重心坐标


	for (i = 0; i < m_iImgHeight; i ++)
		for (j = 0; j < m_iImgWidth; j ++)
		{  
			if(m_pImageData[i][j] == 255)
				m += m_pImageData[i][j]*pow(j,p)*pow(i,q);
		}
	return m;
}

double CInvariantMoment::Miu(int p,int q)
{
	double dMiu=0;
	int i, j;
	for (i=0;i<m_iImgHeight;i++)
		for (j=0;j<m_iImgWidth;j++)
		{
			dMiu += m_pImageData[i][j]*pow((j-m_mx),p)*pow((i-m_my),q);
		}
 	return dMiu;
}

double CInvariantMoment::YT(int p,int q)
{
    double YiTa=0;
	double r=0;
	// 	r=(p+q)/2+1;
	r=(p + q) / 2 + 1;
    YiTa=Miu(p , q) / pow(m_lMui00, r);

	return YiTa;
}


void CInvariantMoment::ComputeFi(double dIM[], double dExIM[])
{
	int i;
    m_mx = (int) (ComputeM(1,0) / ComputeM(0,0));
	m_my = (int) (ComputeM(0,1) / ComputeM(0,0));
	m_lMui00 = (LONG) Miu(0, 0);
    
	//首先计算6个yita值
	yita20=YT(2,0);
	yita02=YT(0,2);
	yita30=YT(3,0);
	yita03=YT(0,3);
	yita21=YT(2,1);
	yita12=YT(1,2);
	yita11=YT(1,1);
	//计算不变矩1
	m_dIM[0] = yita20+yita02;
    
	//计算不变矩2
	m_dIM[1]=pow((yita20-yita02),2)+4*pow(yita11,2);

	//计算不变矩3
	m_dIM[2]=pow((yita30-3*yita12),2)+pow((3*yita21-yita03),2);
    
	//计算不变矩4
	m_dIM[3]=pow((yita30+yita12),2)+pow((yita21+yita03),2);

	//计算不变矩5
	m_dIM[4]=(yita30-3*yita12)*(yita30+yita12)*(pow((yita30+yita12),2)-3*pow((yita21+yita03),2))
		   +(3*yita21-yita03)*(yita21+yita03)*(3*pow(yita30+yita12,2)-pow((yita21+yita03),2));
   
	//计算不变矩6
    m_dIM[5]=(yita20-yita02)*(pow((yita30+yita12),2)-pow((yita21+yita03),2))+4*yita11
		  *(yita30+yita12)*(yita21+yita03);
    
	//计算不变矩7
	m_dIM[6]=(3*yita21-yita03)*(yita30+yita12)*(pow((yita30+yita12),2)-3*pow((yita21+yita03),2))
		  +(3*yita12-yita30)*(yita21+yita03)*(pow((3*yita30+yita12),2)-pow((yita21+yita03),2));

	for(i = 0; i < 7; i ++)
		dIM[i] = m_dIM_Norm[i] = m_dIM[i] * 1000;

	//计算不变矩扩展变种（10个）
	m_dExIM[0] = sqrt(fabs(m_dIM[1])) / m_dIM[0];
	m_dExIM[1] = (m_dIM[0] + sqrt(fabs(m_dIM[1]))) / (m_dIM[0] - sqrt(fabs(m_dIM[1]))) ;
	m_dExIM[2] = sqrt(fabs(m_dIM[2])) / sqrt(fabs(m_dIM[3]));
	m_dExIM[3] = sqrt(fabs(m_dIM[2])) / sqrt(fabs(m_dIM[4]));
	m_dExIM[4] = sqrt(fabs(m_dIM[3])) / sqrt(fabs(m_dIM[4]));
	m_dExIM[5] = m_dIM[5] / (m_dIM[0] * m_dIM[2]);
	m_dExIM[6] = sqrt(fabs(m_dIM[5])) / (m_dIM[0] * sqrt(fabs(m_dIM[4])));
	m_dExIM[7] = sqrt(fabs(m_dIM[5])) / (m_dIM[2] * sqrt(fabs(m_dIM[1])));
	m_dExIM[8] = sqrt(fabs(m_dIM[5])) / sqrt(fabs(m_dIM[1]) * (fabs(m_dIM[4])));
	m_dExIM[9] = fabs(m_dIM[4]) / m_dIM[2] * m_dIM[3];
	
	for(i = 0; i < 10; i ++)
		dExIM[i] = m_dExIM[i];
	
}

void CInvariantMoment::OnCanny()
{
	//0.4, 0.4, 0.79, double sigma,	double dRatioLow, double dRatioHigh, 
	BYTE *pImgData = new BYTE[m_iImgWidth * m_iImgHeight];
// 	memcpy(pImgData, m_pImageData, sizeof(BYTE) * m_iImgHeight * m_iImgWidth);
	int i, j;
	for(i = 0; i < m_iImgHeight; i ++)
		for(j = 0; j < m_iImgWidth; j ++)
			pImgData[i * m_iImgWidth + j] = m_pImageData[i][j];
	Canny(pImgData, m_iImgWidth, m_iImgHeight, 0.4, 0.4, 0.79, m_pImageEdge);
	delete pImgData;
}