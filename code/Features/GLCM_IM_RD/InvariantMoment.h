// InvariantMoment.h: interface for the CInvariantMoment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INVARIANTMOMENT_H__41E859A2_FD08_41F5_80B3_117253940769__INCLUDED_)
#define AFX_INVARIANTMOMENT_H__41E859A2_FD08_41F5_80B3_117253940769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInvariantMoment : public CObject  
{
//Atrributes:
public:
	double Fi1;         //7个不变矩
	double Fi2;
	double Fi3;
	double Fi4;
	double Fi5;
	double Fi6;
	double Fi7;

	double	m_dIM[7];
	double	m_dIM_Norm[7];
	double	m_dExIM[10];

	double yita20;      //7个不变矩重用到的yita值
	double yita02;
	double yita11;
	double yita30;
	double yita03;
	double yita12;
	double yita21;

	LONG	m_lMui00;

	int		m_iImgWidth;        //图像宽度
	int		m_iImgHeight;       //图像高度
	BYTE	**m_pImageData;		//图像数据区指针
	BYTE	*m_pImageEdge;		//图像边界检测结果
	int		m_mx;				//图像重心x坐标
	int		m_my;				//图像重心y坐标
	LONG  LineBytes;			//图像行字节数
//Functions
public:
	CInvariantMoment();
	CInvariantMoment(LPSTR lpBits,LONG Width,LONG Height);
	virtual ~CInvariantMoment();
	double ComputeM(int p,int q);     //计算重心函数
	double Miu(int p,int q);          //计算Miu函数
	double YT(int p,int q);           //计算Fi函数
	void ComputeFi(double dIM[], double dExIM[]);      //计算7个不变矩
	void SetImgData(BYTE ** pImage, BYTE *pEdge, int w, int h);
	void OnCanny();
};

#endif // !defined(AFX_INVARIANTMOMENT_H__41E859A2_FD08_41F5_80B3_117253940769__INCLUDED_)
