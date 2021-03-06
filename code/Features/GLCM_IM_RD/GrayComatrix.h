//////////////////////////////////////////////////////////////////////
// GrayShow.h: interface for the CGrayComatrix class.
// 纹理分析－灰度共现矩阵算法实现
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAYMATRIX_H_INCLUDED_)
#define AFX_GRAYMATRIX_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define FEATURE_NUM 12

//#include "Dib.h"

class CGrayComatrix  
{
public:
	//变量
	double FeatureLocalCalmRD;	//局部平稳性－45度方向
	double FeatureLocalCalmLD;	//局部平稳性－135度方向
	double FeatureLocalCalmV;	//局部平稳性－90度方向度方向
	double FeatureLocalCalmH;	//局部平稳性－0度方向
	double FeatureCorrelationRD;	//相关性－45度方向
	double FeatureCorrelationLD;	//相关性－135度方向
	double FeatureCorrelationV;		//相关性－90度方向
	double FeatureCorrelationH;		//相关性－0度方向
	double FeatureInertiaQuadratureRD;	//惯性矩－45度方向
	double FeatureInertiaQuadratureLD;	//惯性矩－135度方向
	double FeatureInertiaQuadratureV;	//惯性矩－90度方向
	double FeatureInertiaQuadratureH;	//惯性矩－0度方向
	double FeatureEntropyRD;	//熵－45度方向
	double FeatureEntropyLD;	//熵－135度方向
	double FeatureEntropyV;		//熵－90度方向
	double FeatureEntropyH;		//熵－0度方向
	double FeatureEnergyRD;		//能量－45度方向
	double FeatureEnergyLD;		//能量－135度方向
	double FeatureEnergyV;		//能量－90度方向
	double FeatureEnergyH;		//能量－0度方向
	int FilterWindowWidth;	//纹理区域块的大小，通常将图像划分成若干个纹理块计算
	long ImageHeight;	//原图像的高度
	long ImageWidth;		//原图像的宽度
	int distance;	//距离，依据不同的应用选取	
	int GrayLayerNum;	//灰度分级
	int** PMatrixRD;	//45度方向上的灰度共现矩阵
	int** PMatrixLD;	//135度方向上的灰度共现矩阵
	int** PMatrixV;		//90度方向上的灰度共现矩阵
	int** PMatrixH;		//0度方向上的灰度共现矩阵
	BYTE** ImageArray;	//原始的图像数据数组－灰度
	
		//特征值：0、1、2、3分别指0°、90°、45°、135°
	/*特征依次指：
			1. 能量(角二阶矩)(E)
			2. 熵(H)		
			3. 相关性
			4. 逆差矩（同质度HOM）(L)
			5. 惯性（对比度）（惯性矩）(CON)(I)
			6. 灰度熵(Hf)
			7. 梯度熵(hg)
			8. 梯度分布不均匀性(Ug)
			9. 小梯度优势Tmin、
			10. 大梯度优势Tmax、
			11. 方差
			12. 均值和
	*/
	int		m_iFeatureNum;
	double	m_dFeatures[16][4];
	double	m_duFeatures[16];
	double	m_dsFeatures[16];
	RGBQUAD** m_tOriPixelArray;//原始位图数据
	RGBQUAD** m_tResPixelArray;//参考位图数据
	
//	CDib *m_dib;
	
	//操作
	void LoadImage(CString &FilePathName);
	void ComputeMatrix(BYTE** LocalImage, int LocalImageWidth, int LocalImageHeight);
	void ComputeFeature(int nFeature, int** pMatrix, int iDir, int iDim);
	void OnComputeFeature(int nFeature, double *duFeatures, double *dsFeatures);

	CGrayComatrix();
	virtual ~CGrayComatrix();
	
};

#define PIC_NUM 2000

#endif // !defined(AFX_GRAYMATRIX_H_INCLUDED_)
