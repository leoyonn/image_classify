// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "test.h"
#include "matrix.h"
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

//==============================================================EHD==========================================
/*
const int NUMOFANGLE = 5;
const int SUBWIDTH = 4;
const int SUBHEIGHT = 4;
CWinApp theApp;

using namespace std;

void main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("usage: %s <image_path> <train_data_file_name> <test_data_file_name>\n", argv[0]);
		getch();
		exit(0);
	}
	
	ofstream fVector_train;
	ofstream fVector_test;
	int nHistogram[SUBHEIGHT * SUBWIDTH * NUMOFANGLE];

	for(int nFileNum = 0; nFileNum < 2000; nFileNum++)
	{
		CxImage* image = new CxImage;
		char filename[4];
		for(int i=0; i<4; i++)
			filename[i] = 0;
		sprintf(filename, "%d", nFileNum);
		string filepath(argv[1]);
		filepath += "\\";
		filepath += filename;
		filepath +=".jpg";
		image->Load(filepath.c_str(), CXIMAGE_FORMAT_JPG);
		int width = image->GetWidth();
		int height = image->GetHeight();
		BYTE** pImage = new BYTE*[height];
		float** fAngle = new float*[height];
		for(i=0; i<height; i++)
		{
			pImage[i] = new BYTE[width];
			fAngle[i] = new float[width];
		}
		for(i=0; i<SUBHEIGHT * SUBWIDTH * NUMOFANGLE; i++)
			nHistogram[i] = 0;

		RGBQUAD rgb;
		for(i = 0;i < width * height;i++){
			rgb = image->GetPixelColor(i%width,i/width,true);
			pImage[i/width][i%width] = (rgb.rgbRed + rgb.rgbGreen + rgb.rgbBlue)/3;
		}

		for(i=0; i<height; i++)
		{
			for(int j=0; j<width; j++)
			{
					if(i == 0 || i == height-1)
						fAngle[i][j] = 0;
					else if(j == 0 || j == width-1)
						fAngle[i][j] = (float)PI/2;
					else
					{
						float fGy = pImage[i-1][j-1] + 2* pImage[i-1][j] + pImage[i-1][j+1] - pImage[i+1][j-1] - 2* pImage[i+1][j] - pImage[i+1][j+1];
						float fGx = pImage[i-1][j+1] + 2* pImage[i][j+1] + pImage[i+1][j+1] - pImage[i-1][j-1] - 2* pImage[i][j-1] - pImage[i+1][j-1];
						if(fGx == 0)
							if(fGy == 0)
								fAngle[i][j] = 0;
							else
								fAngle[i][j] = (float)PI/2;
						else
							fAngle[i][j] = atan(fGy/fGx);
						if(fAngle[i][j] < 0)
							fAngle[i][j] += (float)PI;
					}
			}
		}
	
		for(i=0; i<height; i++)
			for(int j=0; j<width; j++)
			{
				for(int k=0; k<=NUMOFANGLE-1; k++)
				{
					if(fAngle[i][j] <= PI/(NUMOFANGLE-1) * k)
						break;
				}
				if(fAngle[i][j] - PI/(NUMOFANGLE-1) * (k-1) < PI/(NUMOFANGLE-1) * k - fAngle[i][j])
					fAngle[i][j] = k-1;
				else
					fAngle[i][j] = k;
			}



		for(i=1; i<height-1; i++)
			for(int j=1; j<width-1; j++)
			{
				int m = j/(width/SUBWIDTH);
				int n = i/(height/SUBHEIGHT);
				int k = n * SUBWIDTH + m;
				
				nHistogram[NUMOFANGLE * k + (int)fAngle[i][j]]++;
			}


		int label = nFileNum/50;
		if(label % 2 == 0)
		{
			fVector_train.open(argv[2], ios::app);
			fVector_train<<label/2<<" ";
			for(i=0; i<NUMOFANGLE * SUBWIDTH * SUBHEIGHT; i++)
			{
				fVector_train<<i+1<<":"<<nHistogram[i]<<" ";
			}
			fVector_train<<endl;
			fVector_train.close();
		}
		else
		{
			fVector_test.open(argv[3], ios::app);
			fVector_test<<label/2<<" ";
			for(i=0; i<NUMOFANGLE * SUBWIDTH * SUBHEIGHT; i++)
			{
				fVector_test<<i+1<<":"<<nHistogram[i]<<" ";
			}
			fVector_test<<endl;
			fVector_test.close();
		}

		delete image;
		for(i=0; i<height; i++)
		{
			delete pImage[i];
			delete fAngle[i];
		}
		delete pImage;
		delete fAngle;
	}
}

*/
// ======================================================HSV=======================================================

/*
void main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("usage: %s <image_path> <train_data_file_name> <test_data_file_name>\n", argv[0]);
		getch();
		exit(0);
	}
	const int HLEVEL = 16;
	const int SLEVEL = 4;
	const int VLEVEL = 4;
	const double COEFFICIENT = 0.2;

	int nHistogram[SLEVEL][VLEVEL][HLEVEL];
	ofstream fHSV_train;
	ofstream fHSV_test;

	for (int nFileNum = 0; nFileNum < 2000; nFileNum++) 
	{
		for(int i=0; i<SLEVEL; i++)
			for(int j=0; j<VLEVEL; j++)
				for(int k=0; k<HLEVEL; k++)
					nHistogram[i][j][k] = 0;
				
		CxImage* image = new CxImage;
		string filepath(argv[1]);
		filepath += "\\";
		char filename[4];
		for(i=0; i<4; i++)
			filename[i] = 0;
		sprintf(filename, "%d", nFileNum);
		filepath += filename;
		filepath +=".jpg";
		image->Load(filepath.c_str(), CXIMAGE_FORMAT_JPG);
		int width = image->GetWidth();
		int height = image->GetHeight();

		float s, v, h;
		for(i=0; i<width; i++)
		{
			for(int j=0; j<height; j++)
			{
				RGBQUAD rgb = image->GetPixelColor(i, j);
				float max = max(max(rgb.rgbBlue, rgb.rgbGreen), rgb.rgbRed);
				float min = min(min(rgb.rgbBlue, rgb.rgbGreen), rgb.rgbRed);

				v = max/255;
				s = (max - min)/max;

				if(max == min)
					h = 0;
				else if(max == rgb.rgbRed)
					h = (rgb.rgbGreen - rgb.rgbBlue)/(max - min);
				else if(max == rgb.rgbGreen)
					h = 2 + (rgb.rgbBlue - rgb.rgbRed)/(max - min);
				else
					h = 4 + (rgb.rgbRed - rgb.rgbGreen)/(max - min);

				h *= 60;
				if(h < 0)
					h =+ 360;
				
				int x = (int)(s*SLEVEL);
				int y = (int)(v*VLEVEL);
				int z = (int)(h/360*HLEVEL);
				if(x >= SLEVEL)
					x = SLEVEL-1;
				if(y >= VLEVEL)
					y = VLEVEL-1;
				if(z >= HLEVEL)
					z = HLEVEL-1;
				nHistogram[x][y][z]++;
			}
		}

		int nHistogram2[SLEVEL * VLEVEL * HLEVEL];
		for(i=1; i<SLEVEL * VLEVEL * HLEVEL -1; i++)
		{
			nHistogram2[i] = *((int*)nHistogram + i) + (*((int*)nHistogram + i - 1) + *((int*)nHistogram + i + 1))*COEFFICIENT;
			nHistogram2[i] /= 1 + 2*COEFFICIENT;
		}
		nHistogram2[0] = *(int*)nHistogram + *((int*)nHistogram + 1) * COEFFICIENT;
		nHistogram2[SLEVEL * VLEVEL * HLEVEL - 1] = nHistogram[SLEVEL-1][VLEVEL-1][HLEVEL-1] + nHistogram[SLEVEL-1][VLEVEL-1][HLEVEL-2] * COEFFICIENT;
		nHistogram2[0] /= 1 + COEFFICIENT;
		nHistogram2[SLEVEL * VLEVEL * HLEVEL - 1] /= 1 + COEFFICIENT;

		int label = nFileNum/50;
		if(label % 2 == 0)
		{
			fHSV_train.open(argv[2], ios::app);
			fHSV_train<<label/2<<" ";
			int num1 = 0;
			for(i=0; i<SLEVEL * VLEVEL * HLEVEL; i++)
			{
				num1++;
				fHSV_train<<num1<<":"<<nHistogram2[i]<<" ";
			}
			fHSV_train<<endl;
			fHSV_train.close();
		}
		else
		{
			fHSV_test.open(argv[3], ios::app);
			fHSV_test<<label/2<<" ";
			int num2 = 0;
			for(i=0; i<SLEVEL * VLEVEL * HLEVEL; i++)
			{
				num2++;
				fHSV_test<<num2<<":"<<nHistogram2[i]<<" ";
			}
			fHSV_test<<endl;
			fHSV_test.close();
		}

		delete image;
	}
}
*/



//=================================GABOR================================================//
void GaborFilteredImg(Matrix *FilteredImg_real, Matrix *FilteredImg_imag, Matrix *img, int side, double Ul, double Uh, 
int scale, int orientation, int flag);
void Gabor(Matrix *Gr, Matrix *Gi, int s, int n, double Ul, double Uh, int scale, int orientation, int flag);

float ave_array(float* arr, int len);
float fangcha_array(float* arr, int len, float ave);

void main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("usage: %s <image_path> <train_data_file_name> <test_data_file_name>\n", argv[0]);
		getch();
		exit(0);
	}

	string filepath(argv[1]);
	filepath += "\\";
	ofstream fGabor_train;
	ofstream fGabor_test;
	
	for (int nFileNum = 0; nFileNum < 1; nFileNum++) 
	{
				
		CxImage* image = new CxImage;
		char filename[4];
		for(int i=0; i<4; i++)
			filename[i] = 0;
		sprintf(filename, "%d", nFileNum);
		filepath += filename;
		filepath +=".jpg";
		image->Load(filepath.c_str(), CXIMAGE_FORMAT_JPG);
		int wid = image->GetWidth();
		int hei = image->GetHeight();
		unsigned char* cImage = new unsigned char[wid * hei];
				
		for(i=0; i<hei; i++)
		{
			for(int j=0; j<wid; j++)
			{
				RGBQUAD rgb = image->GetPixelColor(j, i);
				cImage[i*wid+j] = (rgb.rgbBlue + rgb.rgbGreen + rgb.rgbRed)/3;
			}
		}

		int j, side, scale, orientation, flag, s, n;
		Matrix *Gabor_r, *Gabor_i, *Gr, *Gi, *img, *F_r, *F_i;
//		FILE *fp;
		float *output_r, *output_i, *output;
		double Ul, Uh;

		/* --------------------------- Example --------------------------------
		scale = 3, 
		orientation = 4, 
		Uh (highest spatial frequency) = 0.4, 
		Ul (lowest spatial frequency) = 0.1,
		flag (removing the DC term) = 0 (False),
		side (filter dimension = (2*side+1)*(2*side+1)) = 60
		----------------------------------------------------------------------- */
		scale = 5;
		orientation = 8;
		Ul = 0.1;
		Uh = 0.4;
		flag = 0;
		side = 60;

		CreateMatrix(&img, hei, wid);
		for (i=0;i<hei;i++)
			for (j=0;j<wid;j++) 
				img->data[i][j] = (double) (cImage[i*wid+j]);

		delete cImage;

		/* ------ print out the Gabor filters (intensity plot) ----------------- */
		CreateMatrix(&Gr, 2*side+1, 2*side+1);
		CreateMatrix(&Gi, 2*side+1, 2*side+1);
		CreateMatrix(&Gabor_r, (2*side+1)*scale, (2*side+1)*orientation);
		CreateMatrix(&Gabor_i, (2*side+1)*scale, (2*side+1)*orientation);

		for (s=0;s<scale;s++)
			for (n=0;n<orientation;n++) {
				Gabor(Gr, Gi, s+1, n+1, Ul, Uh, scale, orientation, flag);
				Mat_Copy(Gabor_r, Gr, s*(2*side+1), n*(2*side+1), 0, 0, 2*side, 2*side);
				Mat_Copy(Gabor_i, Gi, s*(2*side+1), n*(2*side+1), 0, 0, 2*side, 2*side);
			}

		output = (float *) calloc((2*side+1)*scale*(2*side+1)*orientation, sizeof(float));

		Mat_Vector(Gabor_r, output);

/*		fp = fopen("Gabor.R","wb");
		fwrite(output, sizeof(float), (2*side+1)*scale*(2*side+1)*orientation, fp);
		fclose(fp);

		Mat_Vector(Gabor_i, output);

		fp = fopen("Gabor.I","wb");
		fwrite(output, sizeof(float), (2*side+1)*scale*(2*side+1)*orientation, fp);
		fclose(fp);

		free(output);*/
/*		FreeMatrix(Gr);
		FreeMatrix(Gi);
		FreeMatrix(Gabor_r);
		FreeMatrix(Gabor_i);*/

		/* ------ Save the Gabor filtered outputs ----------------- */
		CreateMatrix(&F_r, hei*scale, wid*orientation);
		CreateMatrix(&F_i, hei*scale, wid*orientation);

		GaborFilteredImg(F_r, F_i, img, side, Ul, Uh, scale, orientation, flag);

		int len = F_r->height*F_r->width;
		output_r = (float *) calloc(len, sizeof(float));
		output_i = (float *) calloc(len, sizeof(float));
		output = (float *) calloc(len, sizeof(float));

		Mat_Vector(F_r, output_r);
		Mat_Vector(F_i, output_i);

		
		for(i=0; i<len; i++)
			output[i] = sqrt(pow(output_r[i], 2) + pow(output_i[i], 2));

		int k=0;
		float *fVector = new float[5*2*len/(wid*hei)];
		int s0, s1, s2, s3, s4;
		int len0 = (wid/2)*(hei/2);
		int len1 = (wid*hei)*3/16;
		float *sub_image0 = new float[len0];
		float *sub_image1 = new float[len1];
		float *sub_image2 = new float[len1];
		float *sub_image3 = new float[len1];
		float *sub_image4 = new float[len1];
		for(i=0; i<len/(wid*hei); i++)
		{
			s0 = s1 = s2 = s3 = s4 = 0;
			for(j=0; j<wid*hei; j++)
			{
				int m = j/wid;
				int n = j%wid;
				if(m>=hei/4 && m<hei*3/4 && n>=wid/4 && n<wid*3/4)
				{
					sub_image0[s0] = output[k];
					s0++;
				}
				else if(m<hei/2 && n<wid/2)
				{
					sub_image1[s1] = output[k];
					s1++;
				}
				else if(m<hei/2 && n>=wid/2)
				{
					sub_image2[s2] = output[k];
					s2++;
				}
				else if(m>=hei/2 && n<wid/2)
				{
					sub_image3[s3] = output[k];
					s3++;
				}
				else
				{
					sub_image4[s4] = output[k];
					s4++;
				}
				k++;
			}
			if(i==9)
				Sleep(100);
			fVector[10*i] = ave_array(sub_image0, len0);
			fVector[10*i+1] = fangcha_array(sub_image0, len0, fVector[10*i]);
			fVector[10*i+2] = ave_array(sub_image1, len1);
			fVector[10*i+3] = fangcha_array(sub_image1, len1, fVector[10*i+2]);
			fVector[10*i+4] = ave_array(sub_image2, len1);
			fVector[10*i+5] = fangcha_array(sub_image2, len1, fVector[10*i+4]);
			fVector[10*i+6] = ave_array(sub_image3, len1);
			fVector[10*i+7] = fangcha_array(sub_image3, len1, fVector[10*i+6]);
			fVector[10*i+8] = ave_array(sub_image4, len1);
			fVector[10*i+9] = fangcha_array(sub_image4, len1, fVector[10*i+8]);
		}

		int label = nFileNum/50;
		if(label % 2 == 0)
		{
			fGabor_train.open(argv[2], ios::app);
			fGabor_train<<label/2<<" ";
			int num1 = 0;
			for(i=0; i<5*2*len/(wid*hei); i++)
			{
				num1++;
				fGabor_train<<num1<<":"<<fVector[i]<<" ";
			}
			fGabor_train<<endl;
			fGabor_train.close();
		}
		else
		{
			fGabor_test.open("argv[3]", ios::app);
			fGabor_test<<label/2<<" ";
			int num2 = 0;
			for(i=0; i<5*2*len/(wid*hei); i++)
			{
				num2++;
				fGabor_test<<num2<<":"<<fVector[i]<<" ";
			}
			fGabor_test<<endl;
			fGabor_test.close();
		}

		delete sub_image0;
		delete sub_image1;
		delete sub_image2;
		delete sub_image3;
		delete sub_image4;
		free(output);
		free(output_i);
		free(output_r);
		delete fVector;
		FreeMatrix(F_r);
		FreeMatrix(F_i);
	}
}

float ave_array(float* arr, int len)
{
	float sum = 0;
	for(int i=0; i<len; i++)
		sum += arr[i];
	return sum/len;
}
float fangcha_array(float* arr, int len, float ave)
{
	float sum = 0;
	for(int i=0; i<len; i++)
		sum += pow(arr[i] - ave, 2);
	return sum/len;
}
