//////////////////////////////////////////////////////////////////////
// GrayShow.cpp: implementation of the CGrayComatrix class.
// 灰度共现矩阵算法实现
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Texture.h"
#include "GrayComatrix.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrayComatrix::CGrayComatrix()
{
	m_iFeatureNum = FEATURE_NUM;
	PMatrixRD = NULL;	//45度方向上的灰度共现矩阵
	PMatrixLD = NULL;	//135度方向上的灰度共现矩阵
	PMatrixV = NULL;		//90度方向上的灰度共现矩阵
	PMatrixH = NULL;		//0度方向上的灰度共现矩阵
	ImageArray = NULL;	//原始的图像数据数组

	m_tOriPixelArray = NULL;//原始位图数据
	m_tResPixelArray = NULL;//参考位图数据
	//m_dib = new CDib();

	distance = 1;
	FilterWindowWidth = 16;
	GrayLayerNum = 16; //初始化设为8个灰度层，可以修改
	//这样共现矩阵均为GrayLayerNum×GrayLayerNum
	int i;
	PMatrixH = new int*[GrayLayerNum];
	PMatrixLD= new int*[GrayLayerNum];
	PMatrixRD= new int*[GrayLayerNum];
	PMatrixV = new int*[GrayLayerNum];
	for(i=0; i<GrayLayerNum; i++)
	{
		PMatrixH[i] = new int[GrayLayerNum];
		PMatrixLD[i]= new int[GrayLayerNum];
		PMatrixRD[i]= new int[GrayLayerNum];
		PMatrixV[i] = new int[GrayLayerNum];
	}

}

CGrayComatrix::~CGrayComatrix()
{

}

////////////////////////////////////////////////////////////////////
//功能：装载图像
//参数：FilePathName－图像文件路径名
void CGrayComatrix::LoadImage(CString &FilePathName)
{
/*	int i,j;
	//检测是否为空，不为空则要释放内存
	if(m_tOriPixelArray !=NULL)
	{
		for(i=0; i<ImageHeight; i++)
		{
			delete m_tOriPixelArray[i];
			delete m_tResPixelArray[i];
			delete ImageArray[i];
		}
	}

	m_dib->Open(FilePathName);
	ImageWidth = m_dib->GetWidth();
	ImageHeight = m_dib->GetHeight();

	BYTE	*colorTable;
	colorTable = (BYTE *)m_dib->m_pDibBits;
	int byteBitCount  = m_dib->GetBiBitCount()/8;

	m_tOriPixelArray  = new RGBQUAD*[ImageHeight];
	m_tResPixelArray  = new RGBQUAD*[ImageHeight];
	ImageArray = new BYTE*[ImageHeight];
	for(int l=0 ; l<ImageHeight; l++)
	{
		m_tOriPixelArray[l] = new RGBQUAD[ImageWidth];
		m_tResPixelArray[l] = new RGBQUAD[ImageWidth];
		ImageArray[l] = new BYTE[ImageWidth];
	}

	int count = 0;
	for(i=ImageHeight-1; i>=0; i--)
	{
		for(j=0; j<ImageWidth; j++)
		{
			m_tOriPixelArray[i][j].rgbBlue =colorTable[count++];
			m_tOriPixelArray[i][j].rgbGreen=colorTable[count++];
			m_tOriPixelArray[i][j].rgbRed  =colorTable[count++];
			m_tOriPixelArray[i][j].rgbReserved = 0;
			m_tResPixelArray[i][j]=m_tOriPixelArray[i][j];
			ImageArray[i][j] = (BYTE)(((unsigned int)m_tOriPixelArray[i][j].rgbBlue
								+(unsigned int)m_tOriPixelArray[i][j].rgbGreen
								+(unsigned int)m_tOriPixelArray[i][j].rgbRed)/3);
			count += byteBitCount-3;
		}
		count += (4-(ImageWidth*byteBitCount)%4)%4;
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////
//功能：计算共现矩阵
//参数：LocalImage－用来计算的局部纹理区域图像
//      LocalImageWidth－局部纹理区域宽度
////////////////////////////////////////////////////////////////////////////////////
void CGrayComatrix::ComputeMatrix(BYTE **LocalImage, int LocalImageWidth, int LocalImageHeight)
{
	BYTE **NewImage;
	NewImage = new BYTE*[LocalImageHeight];
	
	int i,j;
	for(i=0; i<LocalImageHeight; i++)
		NewImage[i] = new BYTE[LocalImageWidth];
	
	for(i=0; i<LocalImageHeight; i++)
	{
		for(j=0; j<LocalImageWidth; j++)
		{
			//分成GrayLayerNum个灰度级
			NewImage[i][j] = LocalImage[i][j] / (256/GrayLayerNum);
		}
	}
	for(i=0; i<GrayLayerNum; i++)
	{
		//
		for(j=0; j<GrayLayerNum; j++)
		{
			PMatrixH[i][j]  = 0;
			PMatrixLD[i][j] = 0;
			PMatrixRD[i][j] = 0;
			PMatrixV[i][j]  = 0;
		}
	}
	
	// 	dx=0．dy=1：横向纹理：0°
	// 	dx=1．dy=0：纵向纹理：90°
	// 	dx=1．dy=1：向上倾斜对角纹理：45°
	// 	dx=1，dy=-1：向下倾斜对角纹理：135°
	
	//计算0度的灰度共现阵
	for(i=0; i<LocalImageHeight; i++)
	{
		for(j=0; j< LocalImageWidth - distance; j++)
		{
			PMatrixH[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[i][j + distance]] += 1;
			PMatrixH[(unsigned int)NewImage[i][j + distance]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
	
	//计算90度的灰度共现阵
	for(i=0; i<LocalImageHeight-distance; i++)
	{
		for(j=0; j<LocalImageWidth; j++)
		{
			PMatrixV[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[i+distance][j]] += 1;
			PMatrixV[(unsigned int)NewImage[i+distance][j]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
	
	//计算45度的灰度共现阵
	for(i=0; i<LocalImageHeight-distance; i++)
	{
		for(j=0; j<LocalImageWidth-distance; j++)
		{
			int newi, newj;
			newi = i+distance;
			newj = j+distance;
			PMatrixLD[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[newi][newj]] += 1;
			PMatrixLD[(unsigned int)NewImage[newi][newj]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
	
	//计算135度的灰度共现阵
	for(i=distance; i<LocalImageHeight; i++)
	{
		for(j=0; j<LocalImageWidth-distance; j++)
		{
			int newi, newj;
			newi = i-distance;
			newj = j+distance;
			PMatrixRD[(unsigned int)NewImage[i][j]][(unsigned int)NewImage[newi][newj]] += 1;
			PMatrixRD[(unsigned int)NewImage[newi][newj]][(unsigned int)NewImage[i][j]] += 1;
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////
//函数功能：计算纹理特征
//参数：iDir：现在是哪个方向的共生矩阵0~3.
//      pMatrix－共生矩阵
//      iDim－共现矩阵的维数
///////////////////////////////////////////////////////////////////////////////////
void CGrayComatrix::ComputeFeature(int nFeature, int **pMatrix, int iDir, int iDim)
{
	int i, j, k;
	double **pdMatrix;
	pdMatrix = new double*[iDim];
	for(i=0; i<iDim; i++)
		pdMatrix[i] = new double[iDim];

	int total = 0;
	for(i=0; i<iDim; i++)
	{
		for(j=0; j<iDim; j++)
		{
			total += pMatrix[i][j];
		}
	}

	for(i=0; i<iDim; i++)
	{
		for(j=0; j<iDim; j++)
		{
			pdMatrix[i][j] = (double)pMatrix[i][j]/(double)total;
		}
	}
	

	//计算ux
	double ux = 0.0;
	double localtotal = 0.0;
	for(i=0; i<iDim; i++)
	{
		localtotal = 0.0;
		for(j=0; j<iDim; j++)
		{
			localtotal += pdMatrix[i][j];
		}
		ux += (double)i * localtotal;
	}

	//计算uy
	double uy = 0.0;
	for(j=0; j<iDim; j++)
	{
		localtotal = 0.0;
		for(i=0; i<iDim; i++)
		{
			localtotal += pdMatrix[i][j];
		}
		uy += (double)j * localtotal;
	}
	

	//计算sigmax
	double sigmax = 0.0;
	for(i=0; i<iDim; i++)
	{
		localtotal = 0.0;
		for(j=0; j<iDim; j++)
		{
			localtotal += pdMatrix[i][j];
		}
		sigmax += (double)(i-ux) * (double)(i-ux) * localtotal;
	}

	//计算sigmay
	double sigmay = 0.0;
	for(j=0; j<iDim; j++)
	{
		localtotal = 0.0;
		for(i=0; i<iDim; i++)
		{
			localtotal += pdMatrix[i][j];
		}
		sigmay += (double)(j-uy) * (double)(j-uy) * localtotal;
	}


	for(i = 0; i < nFeature; i ++)
	{
		m_dFeatures[i][iDir] = 0;
	}
	
	
	/*特征依次指：
			0. 能量(角二阶矩)(E)
			1. 熵(H)		
			2. 相关性
			3. 逆差矩(局部平稳)（同质度HOM）(L)
			4. 惯性（对比度）（惯性矩）(CON)(I)
			5. 灰度熵(Hf)
			6. 梯度熵(hg)
			7. 梯度分布不均匀性(Ug)
			8. 小梯度优势Tmin、
			9. 大梯度优势Tmax、
			10. 方差
			11. 均值和
	*/
	double	dTmpFeature5, dTmpFeature6, dTmpFeature7, dTmpFeature11, dSumIJ = 0;
	double	dMean = total / (iDim * iDim);
	for(i = 0; i < iDim; i ++)
	{
		dTmpFeature5 = 0; dTmpFeature6 = 0; dTmpFeature7 = 0;
		for(j = 0; j < iDim; j ++)
		{
			dSumIJ += pdMatrix[i][j];
			m_dFeatures[0][iDir] += pdMatrix[i][j]*pdMatrix[i][j];
			if(pdMatrix[i][j]>1e-12)
			{
				m_dFeatures[1][iDir] -= pdMatrix[i][j]*log(pdMatrix[i][j]);
			}
			m_dFeatures[2][iDir] += (double)(i-ux) * (double)(j-uy) * pdMatrix[i][j];
			m_dFeatures[3][iDir] += pdMatrix[i][j]/(1+(double)(i-j)*(double)(i-j));
			m_dFeatures[4][iDir] += (double)(i-j)*(double)(i-j)*pdMatrix[i][j];
			dTmpFeature5 += pdMatrix[i][j];
			dTmpFeature6 += pdMatrix[j][i];
			//dTmpFeature7 += pdMatrix[j][i];
			if(j > 0)
				m_dFeatures[8][iDir] += pdMatrix[i][j] / (j * j);
			m_dFeatures[9][iDir] += j * j * pdMatrix[i][j];
			m_dFeatures[10][iDir] += (i - dMean) * (i - dMean) * pdMatrix[i][j];

		}
		dTmpFeature7 = dTmpFeature5 * dTmpFeature5;
		if(dTmpFeature5 > 1e-12)
			m_dFeatures[5][iDir] -= dTmpFeature5 * log(dTmpFeature5);
		if(dTmpFeature6 > 1e-12)
		m_dFeatures[6][iDir] -= dTmpFeature6 * log(dTmpFeature6);
		m_dFeatures[7][iDir] += dTmpFeature7;
	}
	
	for(k = 0; k < iDim; k ++)
	{
		dTmpFeature11 = 0;
		for(i = 0; i <= k; i ++)
		{
			for(j = 0; j <= k; j ++)
				dTmpFeature11 += pdMatrix[i][j];
		}
		m_dFeatures[11][iDir] += 2 * k * dTmpFeature11;
	}
	m_dFeatures[2][iDir] /= sigmax;
	m_dFeatures[2][iDir] /= sigmay;
	m_dFeatures[7][iDir] /= dSumIJ;
	m_dFeatures[8][iDir] /= dSumIJ;
	m_dFeatures[9][iDir] /= dSumIJ;
}


void CGrayComatrix::OnComputeFeature(int nFeature, double *duFeatures, double *dsFeatures)
{
	ComputeFeature(nFeature, PMatrixH, 0, GrayLayerNum);
	ComputeFeature(nFeature, PMatrixV, 1, GrayLayerNum);
	ComputeFeature(nFeature, PMatrixLD, 2, GrayLayerNum);
	ComputeFeature(nFeature, PMatrixRD, 3, GrayLayerNum);
	int i, j;
	for(j = 0; j < nFeature; j ++)
	{	
		m_duFeatures[j] = 0;
		for(i = 0; i < 4; i ++)
		{
			m_duFeatures[j] += m_dFeatures[j][i];
		}
		m_duFeatures[j] /= 4;
	}
	
	for(j = 0; j < nFeature; j ++)
	{	
		m_dsFeatures[j] = 0;
		for(i = 0; i < 4; i ++)
		{
			m_dsFeatures[j] += (m_dFeatures[j][i] - m_duFeatures[j]) * (m_dFeatures[j][i] - m_duFeatures[j]);
		}
		m_dsFeatures[j] /= 4;
		m_dsFeatures[j] = sqrt(m_dsFeatures[j]);
	}
	for(j = 0; j < nFeature; j ++)
	{
		duFeatures[j] = m_duFeatures[j];
		dsFeatures[j] = m_dsFeatures[j];
	}
}
