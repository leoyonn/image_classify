#include <stdio.h>
#include <memory.h>
#include "KMeans.h"

#define PIC_NUM		1000
#define FEATURE_PER_POINT	40
#define MAX_POINTS			128
int CLUSTER_NUM = 40;

struct SPcaSiftFeature
{
	int		iPointNum;			//每张图片中特征点的个数
	int		iFeatureNum;		//每个点的特征维数
	double	fFeatures[MAX_POINTS][FEATURE_PER_POINT];	//特征数组	
};

SPcaSiftFeature gFeatures[1000];
SPcaSiftFeature gFeatures_test[1000];

void Feature2KMeans(SPcaSiftFeature *arrFeatures, FILE *fpOut, System * KMeans);

void main(int argc, char ** argv)
{
// 	char *szInSiftTrain		= "sift_train.txt";
// 	char *szInSiftTest		= "sift_test.txt";

	if(argc < 4){
		printf("usage:[traindata] [train_output] [testdata] [test_output] [-c classnumber]\n");
		getch();
		return;
	}
	char *szInPcaSiftTrain	= argv[1];
	char *szInPcaSiftTest	= argv[3];
	char *szOutPcaSiftTrain = argv[2];
	char *szOutPcaSiftTest = argv[4];
	for(int m = 0; m < argc; m++)
		if(strcmp(argv[m], "-c") == 0)
			CLUSTER_NUM = atoi(argv[m+1]);

	FILE * fpIn = fopen(szInPcaSiftTrain, "r");
	FILE * fpIn_test = fopen(szInPcaSiftTest,"r");
	FILE * fpOut = fopen(szOutPcaSiftTrain, "w");
	FILE * fpOut_test = fopen(szOutPcaSiftTest,"w");

	int i, j, k;
	int image_num = -1,class_label = -1;
	int image_num_test = -1,class_label_test = -1;
	int tmp = 0;
	for(i = 0; i < PIC_NUM; i ++)
	{
		fscanf(fpIn, "%d %d %d %d\n", &image_num, &class_label,&gFeatures[i].iPointNum, &gFeatures[i].iFeatureNum);
		for(j = 0; j < gFeatures[i].iPointNum; j ++)
		{
			for(k = 0; k < gFeatures[i].iFeatureNum; k ++)
			{
				float ftemp = 0;
				fscanf(fpIn, "%f ", &ftemp);
				gFeatures[i].fFeatures[j][k] = double(ftemp);
//				printf("%f ", gFeatures[i].fFeatures[j][k]);
			}
			tmp ++;
		}
	}
	tmp = 0;
	for(i = 0; i < PIC_NUM; i ++)
	{
		fscanf(fpIn_test, "%d %d %d %d\n", &image_num_test, &class_label_test,&gFeatures_test[i].iPointNum, &gFeatures_test[i].iFeatureNum);
		for(j = 0; j < gFeatures_test[i].iPointNum; j ++)
		{
			for(k = 0; k < gFeatures_test[i].iFeatureNum; k ++)
			{
				float ftemp = 0;
				fscanf(fpIn_test, "%f ", &ftemp);
				gFeatures_test[i].fFeatures[j][k] = double(ftemp);
				//				printf("%f ", gFeatures[i].fFeatures[j][k]);
			}
			tmp ++;
		}
	}
	int total_num = 0;
	for(i = 0; i < PIC_NUM; i ++){
		total_num += gFeatures[i].iPointNum;
	}
	double ** sample = new double*[total_num];
	int count = 0;
	for(i=0; i< PIC_NUM; i++){
		for(int j = 0; j < gFeatures[i].iPointNum; j++){
			sample[count] = new double[gFeatures[i].iFeatureNum];
			for(int k = 0; k < gFeatures[i].iFeatureNum; k ++){
				sample[count][k] = gFeatures[i].fFeatures[j][k];
			}
			count ++;
			//memcpy(sample[count], gFeatures[i].fFeatures[j],gFeatures[i].iFeatureNum * sizeof(double));
		}
	}
	System KMeans;
	KMeans.Load(sample,total_num,gFeatures[0].iFeatureNum, CLUSTER_NUM);//to add
	KMeans.InitClusters();
	KMeans.RunKMeans();

	Feature2KMeans(gFeatures, fpOut, &KMeans);
	Feature2KMeans(gFeatures_test,fpOut_test,&KMeans);
	KMeans.destroy();
	fclose(fpIn);
	fclose(fpIn_test);
	fclose(fpOut);
	fclose(fpOut_test);
}

void Feature2KMeans(SPcaSiftFeature *arrFeatures, FILE *fpOut, System * KMeans)
{
	int * dictionary = new int[CLUSTER_NUM];
	int class_label = -1;
	for(int s = 0; s < CLUSTER_NUM; s++)
		dictionary[s] = 0;
//	memset(dictionary,CLUSTER_NUM,0);
	int total_num = 0;
	for(int i = 0; i < PIC_NUM; i ++){
		fprintf(fpOut,"%d ",i/50);
		for(int j = 0; j < arrFeatures->iPointNum; j ++){
			class_label = KMeans->Classify(arrFeatures[i].fFeatures[j],arrFeatures[i].iFeatureNum);//to add
			dictionary[class_label]++;
			class_label = -1;
		}
		for(j = 0; j < CLUSTER_NUM; j ++){
			fprintf(fpOut, "%d:%d",j,dictionary[j]);
			if(j < CLUSTER_NUM - 1){
				fprintf(fpOut," ");
			}
			else fprintf(fpOut, "\n");
		}
		for(int s = 0; s < CLUSTER_NUM; s++)
		dictionary[s] = 0;
	}
}
