#include "sift.h"
#include "imgfeatures.h"
#include "utils.h"
#include "image.h"
#include "keypoint.h"

#include <highgui.h>

#include <stdio.h>
#include <conio.h>

#define MAX_PTFS	128
#define NFEATURES	128
#define NPCAFTURES	40

#define FEATURE_PER_POINT	40
#define MAX_POINTS			128

struct SPcaSiftFeature
{
	int		iPointNum;									//每张图片中特征点的个数
	int		iFeatureNum;								//每个点的特征维数
	float	fFeatures[MAX_POINTS][FEATURE_PER_POINT];	//特征数组	
};

SPcaSiftFeature gFeatures[10];

struct SFeatureOri
{
	int		nPts;
	int		nFeatures;
	double	fFeatures[MAX_PTFS][NFEATURES];
};
/******************************** Globals ************************************/

// char* img_file_name = "G:\\50.jpg";
// char* out_file_name  = "G:\\sift2_50.txt";
char* out_img_name = NULL;
int display = 1;
int intvls = SIFT_INTVLS;
double sigma = SIFT_SIGMA;
double contr_thr = SIFT_CONTR_THR;
int curv_thr = SIFT_CURV_THR;
int img_dbl = SIFT_IMG_DBL;
int descr_width = SIFT_DESCR_WIDTH;
int descr_hist_bins = SIFT_DESCR_HIST_BINS;

// void test2000();
/********************************** Main *************************************/
void ComputeImgPCASift(char *szImgDir, int iImgNum, FILE *foutTrain, FILE *foutTest);
void ComputeImgnPCASift(char *szImgDir, int iImgNum, FILE *foutTrain, FILE *foutTest);
void ComputeImgSift(char *szImgDir, int iImgNum, FILE *foutTrain, FILE *foutTest);


int main( int argc, char** argv )
{
//	test2000();
	//参数格式：p/s ..\\pic\\ ..\\data\\Sift_Train_ori.txt ..\\data\\Sift_Test_ori.txt /

	char *cType = argv[1];
	int divi = 1, iImgNum, iKmeans = 40;
	char szImgDir[MAX_PATH] ; 
	char szOutTrainOri[MAX_PATH] = "..\\data\\Sift_Train_ori.txt";
	char szOutTestOri[MAX_PATH] = "..\\data\\Sift_Test_ori.txt";
	char szParam[MAX_PATH] = "";
	if(argc < 5)
	{
		printf("usage: p/s szImgDir szTrainOut szTestOut\n");
		getch();
		return 0;
	}
	sprintf(szImgDir, "%s", argv[2]);
	sprintf(szParam, "%s %s %s %s -c %d", szOutTrainOri, argv[3], szOutTestOri, argv[4], iKmeans);

	FILE *foutTrain;
	FILE *foutTest;
	if(strcmp(cType, "p") == 0)	//pcasift
	{
		sprintf(szOutTrainOri, "..\\data\\PCASift_Train_ori.txt");
		sprintf(szOutTestOri, "..\\data\\PCASift_Test_ori.txt");
		foutTrain = fopen(szOutTrainOri, "w");
		foutTest = fopen(szOutTestOri, "w");

		if(!foutTrain || !foutTest)
		{
			printf("open file error!\n");
			exit(1);
		}
		
		for(iImgNum = 0; iImgNum < 2000; iImgNum ++)
		{
			ComputeImgPCASift(szImgDir, iImgNum, foutTrain, foutTest);
		}

	}
	else if(strcmp(cType, "s") == 0)	//sift
	{
		sprintf(szOutTrainOri, "..\\data\\Sift_Train_ori.txt");
		sprintf(szOutTestOri, "..\\data\\Sift_Test_ori.txt");
		foutTrain = fopen(szOutTrainOri, "w");
		foutTest = fopen(szOutTestOri, "w");
	
		if(!foutTrain || !foutTest)
		{
			printf("open file error!\n");
			exit(1);
		}
		
		for(iImgNum = 0; iImgNum < 2000; iImgNum ++)
		{
			ComputeImgSift(szImgDir, iImgNum, foutTrain, foutTest);
		}
	}
	else
	{
		printf("error parameter type!\n");
		return 0;
	}

	// 调用k-means聚类，把维数统一
	// convert的格式：pcasift训练 pcasift训练输出 pcasift测试 pcasift测试输出 -c 分类数目
	//sprintf()
	ShellExecute(NULL, "open", "..\\bin\\kmeans.exe", szParam, "", SW_SHOW );

	fclose(foutTrain);
	fclose(foutTest);
	return 0;
}


#define PIC_NUM 2000

void ComputeImgSift(char *szImgDir, int iImgNum, FILE *foutTrain, FILE * foutTest)
{
	int iLabel, iClass;
	char str[100];
	sprintf(str, "%s%d.jpg", szImgDir, iImgNum);
	struct feature* features;
	IplImage *cOrigImg	= cvLoadImage(str, 1); 
	if( ! cOrigImg)
	{
		fprintf( stderr, "unable to load image from %s", str );
		exit( 1 );
	}
	
	int i, j;
	
	int n = _sift_features( cOrigImg, &features, intvls, sigma, contr_thr, curv_thr,
								img_dbl, descr_width, descr_hist_bins );
	n = n < 128 ? n : 128;
	int d = features[0].d;
	
	cvReleaseImage(&cOrigImg);
	
	printf("%d ", iImgNum);
	
	iLabel = iImgNum / 50;
	iClass = iImgNum / 100;
	if(iLabel % 2 == 0)
	{
		fprintf(foutTrain, "%d %d %d %d\n", iImgNum, iClass, n, d + 4);			
		for (i = 0; i < n; i++)
		{
			fprintf(foutTrain, "%4.4f %4.4f %4.4f %4.4f",
				features[i].y, features[i].x, features[i].scl, features[i].ori);
			
			for (j = 0; j < d; j ++)
			{
				fprintf(foutTrain, " %d", (int)(features[i].descr[j]));
			}
			fprintf(foutTrain, "\n");
			fflush(foutTrain);
		}
		//if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
	}
	else
	{
		fprintf(foutTest, "%d %d %d %d\n", iImgNum, iClass, n, d + 4);			
		for (i = 0; i < n; i++)
		{
			fprintf(foutTest, "%4.4f %4.4f %4.4f %4.4f",
				features[i].y, features[i].x, features[i].scl, features[i].ori);
			
			for (j = 0; j < d; j ++)
			{
				fprintf(foutTest, " %d", (int)(features[i].descr[j]));
			}
			fprintf(foutTest, "\n");
			fflush(foutTest);
		}
		//if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
	}
}

void ComputeImgPCASift(char *szImgDir, int iImgNum, FILE *foutTrain, FILE * foutTest)
{
	int iLabel, iClass;
	char * gpcafn = "..\\code\\Features\\SIFT\\gpcavects.txt";
	KeypointDetector kpd(gpcafn);
	char str[100];
	sprintf(str, "%s%d.jpg", szImgDir, iImgNum);
	struct feature* features;
	IplImage *cOrigImg	= cvLoadImage(str, 1); 
	IplImage *cGrayImg	= cvCreateImage( cvSize(cOrigImg->width,cOrigImg->height), IPL_DEPTH_8U , 1 );
	cvCvtColor( cOrigImg, cGrayImg, CV_RGB2GRAY);
	if( ! cOrigImg )
	{
		fprintf( stderr, "unable to load image from %s", str );
		exit( 1 );
	}
	
	int i, j;
	int widthStep = cGrayImg->widthStep;
	int height = cGrayImg->height;
	int width = cGrayImg->width;
	const uchar *iplImagePtr = (const uchar *) cGrayImg->imageData;
	float *qImageBuffer = (float *) malloc(width*height*sizeof(float));
	float *QImagePtr = qImageBuffer;
	
	for(i = 0; i < height; i ++)
	{
		for(int j = 0; j < cGrayImg->width; j ++)
			QImagePtr[i * width + j] = (float)cvGetReal2D(cGrayImg, i, j) / 255.0;
	}
	
	int n = _sift_features( cOrigImg, &features, intvls, sigma, contr_thr, curv_thr,
								img_dbl, descr_width, descr_hist_bins );
	n = n < 128 ? n : 128;
	int d = features[0].d;
	
	vector<Keypoint *> keys;
	for (i = 0; i < n; i++)
	{
		Keypoint * key = new Keypoint(d);
		
		key->y		= features[i].y; 
		key->x		= features[i].x; 
		key->gscale	= features[i].scl; 
		key->ori	= features[i].ori; 
		
		for (int j = 0; j < d; j ++) 
			key->ld[j] = features[i].descr[j];
		
		keys.push_back(key);
	}
	
	Image * im = new Image(width, height, QImagePtr);
	kpd.RecalcKeys(im, keys);
	delete(im);
	free(qImageBuffer);
	cvReleaseImage(&cOrigImg);
	cvReleaseImage(&cGrayImg);
	
	printf("%d ", iImgNum);
	
	iLabel = iImgNum / 50;
	iClass = iImgNum / 100;
	if(iLabel % 2 == 0)
	{
		fprintf(foutTrain, "%d %d %d %d\n", iImgNum, iClass, n, NPCAFTURES);			
		for (i = 0; i < n; i++)
		{
			fprintf(foutTrain, "%4.4f %4.4f %4.4f %4.4f",
				keys[i]->y/2.0, keys[i]->x/2.0, keys[i]->gscale, keys[i]->ori);
			
			for (j = 0; j < 36; j ++)
			{
				fprintf(foutTrain, " %.4f", keys[i]->ld[j]);
			}
			fprintf(foutTrain, "\n");
			fflush(foutTrain);
		}
		//if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
	}
	else
	{
		fprintf(foutTest, "%d %d %d %d\n", iImgNum, iClass, n, NPCAFTURES);			
		for (i = 0; i < n; i++)
		{
			fprintf(foutTest, "%4.4f %4.4f %4.4f %4.4f",
				keys[i]->y/2.0, keys[i]->x/2.0, keys[i]->gscale, keys[i]->ori);
			
			for (j = 0; j < 36; j ++)
			{
				fprintf(foutTest, " %.4f", keys[i]->ld[j]);
			}
			fprintf(foutTest, "\n");
			fflush(foutTest);
		}
		//if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
	}
	for (i = 0; i < n; i++)
	{
		delete (keys[i]);
	}

}

int nFs = 16;

void ComputeImgnPCASift(char *szImgDir, int iImgNum, FILE *foutTrain, FILE * foutTest)
{
	int iLabel, iClass;
	char * gpcafn = "..\\code\\Features\\SIFT\\gpcavects.txt";
	KeypointDetector kpd(gpcafn);
	char str[100];
	sprintf(str, "%s%d.jpg", szImgDir, iImgNum);
	struct feature* features;
	IplImage *cOrigImg	= cvLoadImage(str, 1); 
	IplImage *cGrayImg	= cvCreateImage( cvSize(cOrigImg->width,cOrigImg->height), IPL_DEPTH_8U , 1 );
	cvCvtColor( cOrigImg, cGrayImg, CV_RGB2GRAY);
	if( ! cOrigImg )
	{
		fprintf( stderr, "unable to load image from %s", szImgDir );
		exit( 1 );
	}
	
	int i, j;
	int widthStep = cGrayImg->widthStep;
	int height = cGrayImg->height;
	int width = cGrayImg->width;
	const uchar *iplImagePtr = (const uchar *) cGrayImg->imageData;
	float *qImageBuffer = (float *) malloc(width*height*sizeof(float));
	float *QImagePtr = qImageBuffer;
	
	for(i = 0; i < height; i ++)
	{
		for(int j = 0; j < cGrayImg->width; j ++)
			QImagePtr[i * width + j] = (float)cvGetReal2D(cGrayImg, i, j) / 255.0;
	}
	
	int n = _sift_features( cOrigImg, &features, intvls, sigma, contr_thr, curv_thr,
								img_dbl, descr_width, descr_hist_bins );
	n = n < 128 ? n : 128;
	int d = features[0].d;
	
	vector<Keypoint *> keys;
	for (i = 0; i < n; i++)
	{
		Keypoint * key = new Keypoint(d);
		
		key->y		= features[i].y; 
		key->x		= features[i].x; 
		key->gscale	= features[i].scl; 
		key->ori	= features[i].ori; 
		
		for (int j = 0; j < d; j ++) 
			key->ld[j] = features[i].descr[j];
		
		keys.push_back(key);
	}
	
	Image * im = new Image(width, height, QImagePtr);
	kpd.RecalcKeys(im, keys);
	delete(im);
	free(qImageBuffer);
	cvReleaseImage(&cOrigImg);
	cvReleaseImage(&cGrayImg);
	
	printf("%d ", iImgNum);
	
	iLabel = iImgNum / 50;
	iClass = iImgNum / 100;
	if(iLabel % 2 == 0)
	{
		fprintf(foutTrain, "%d %d %d %d\n", iImgNum, iClass, nFs, NPCAFTURES);
		n = n < nFs ? n : nFs;
		for (i = 0; i < n; i++)
		{
			fprintf(foutTrain, "%4.4f %4.4f %4.4f %4.4f",
				keys[i]->y/2.0, keys[i]->x/2.0, keys[i]->gscale, keys[i]->ori);
			
			for (j = 0; j < 36; j ++)
			{
				fprintf(foutTrain, " %.4f", keys[i]->ld[j]);
			}
			fprintf(foutTrain, "\n");
			fflush(foutTrain);
		}
		
		for (i = n; i < nFs; i++)
		{
			fprintf(foutTrain, "%4.4f %4.4f %4.4f %4.4f",
				0, 0, 0, 0);
			
			for (j = 0; j < 36; j ++)
			{
				fprintf(foutTrain, " %.4f", 0);
			}
			fprintf(foutTrain, "\n");
			fflush(foutTrain);
		}
		
		//if(iImgNum < PIC_NUM - 51) fprintf(foutTrain, "\n");
	}
	else
	{
		fprintf(foutTest, "%d %d %d %d\n", iImgNum, iClass, nFs, NPCAFTURES);
		n = n < nFs ? n : nFs;
		for (i = 0; i < n; i++)
		{
			fprintf(foutTest, "%4.4f %4.4f %4.4f %4.4f",
				keys[i]->y/2.0, keys[i]->x/2.0, keys[i]->gscale, keys[i]->ori);
			
			for (j = 0; j < 36; j ++)
			{
				fprintf(foutTest, " %.4f", keys[i]->ld[j]);
			}
			fprintf(foutTest, "\n");
			fflush(foutTest);
		}
		
		for (i = n; i < nFs; i++)
		{
			fprintf(foutTest, "%4.4f %4.4f %4.4f %4.4f",
				0, 0, 0, 0);
			
			for (j = 0; j < 36; j ++)
			{
				fprintf(foutTest, " %.4f", 0);
			}
			fprintf(foutTest, "\n");
			fflush(foutTest);
		}
		//if(iImgNum < PIC_NUM - 1) fprintf(foutTest, "\n");
	}
	for (i = 0; i < n; i++)
	{
		delete (keys[i]);
	}

}

void test2000()
{
}



int amain( int argc, char** argv )
{
/*
	struct feature* features;
	int n = 0;
/ *
	IPL_DEPTH_8U
		IPL_DEPTH_8S
		IPL_DEPTH_8U
		IPL_DEPTH_8U
* /
	IplImage *cOrigImg	= cvLoadImage(img_file_name, 1); 
	IplImage *cGrayImg	= cvCreateImage( cvSize(cOrigImg->width,cOrigImg->height), IPL_DEPTH_8U , 1 );
	cvCvtColor( cOrigImg, cGrayImg, CV_RGB2GRAY);
	if( ! cOrigImg )
	{
		fprintf( stderr, "unable to load image from %s", img_file_name );
		exit( 1 );
	}
	int i;
	int widthStep = cGrayImg->widthStep;
	int height = cGrayImg->height;
	int width = cGrayImg->width;
	const uchar *iplImagePtr = (const uchar *) cGrayImg->imageData;
    float *qImageBuffer = (float *) malloc(width*height*sizeof(float));
	float *QImagePtr = qImageBuffer;

	fprintf( stderr, "Finding SIFT features...\n" );
	//img = cvLoadImage( img_file_name, 1 );
	printf("%d, %d, nchannel: %d, depth: %d\n", 
			cGrayImg->height, cGrayImg->width, cGrayImg->nChannels, cGrayImg->depth);
	cvSaveImage("G:\\test.jpg", cGrayImg);
	for(i = 0; i < cGrayImg->height; i ++)
	{
		for(int j = 0; j < cGrayImg->width; j ++)
		{
			QImagePtr[i * width + j] = (float)cvGetReal2D(cGrayImg, i, j) / 255.0;
			printf(" %f", (QImagePtr[i * width + j]));
		}
		printf("\n");
	}

	n = _sift_features( cOrigImg, &features, intvls, sigma, contr_thr, curv_thr,
						img_dbl, descr_width, descr_hist_bins );
	fprintf( stderr, "Found %d features.\n", n );

	if( display )
	{
		draw_features( cOrigImg, features, n );
		cvNamedWindow( img_file_name, 1 );
		cvShowImage( img_file_name, cOrigImg );
		cvWaitKey( 0 );
	}

	if( out_file_name != NULL )
		export_features( out_file_name, features, n );

	if( out_img_name != NULL )
		cvSaveImage( out_img_name, cOrigImg );

	gen(QImagePtr, width, height);
*/
//	test2000();
	return 0;
}




void Feature2KMeans(SPcaSiftFeature *arrFeatures, FILE *fpOut);

void _main_PCA2Kmeans()
{
	// 	char *szInSiftTrain		= "sift_train.txt";
	// 	char *szInSiftTest		= "sift_test.txt";
	
	char *szInPcaSiftTrain	= "G:\\pcasift_ori_train.txt";
	char *szInPcaSiftTest	= "G:\\pcasift_ori_test.txt";
	char *szOutPcaSiftTrain = "G:\\pcasift_train.txt";
	
	FILE * fpIn = fopen(szInPcaSiftTrain, "r");
	FILE * fpOut = fopen(szOutPcaSiftTrain, "w");
	
	int i, j, k;
	for(i = 0; i < 1000; i ++)
	{
		fscanf(fpIn, "%d %d\n", &gFeatures[i].iPointNum, &gFeatures[i].iFeatureNum);
		for(j = 0; j < gFeatures[i].iPointNum; j ++)
		{
			for(k = 0; k < gFeatures[i].iFeatureNum; k ++)
			{
				fscanf(fpIn, "%f ", &gFeatures[i].fFeatures[j][k]);
			}
		}
	}
	
	Feature2KMeans(gFeatures, fpOut);
	
	fclose(fpIn);
	fclose(fpOut);
}

void Feature2KMeans(SPcaSiftFeature *arrFeatures, FILE *fpOut)
{
	
	
	
}
