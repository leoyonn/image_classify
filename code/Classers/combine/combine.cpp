#include <stdio.h>
#include "svm.h"
#include "predict.h"
#include <conio.h>
#define SVM_NUM	3
#define DATA_NUM 1000
#define CLASS_NUM 20
int ** label;
struct svm_model * model_edh;
struct svm_model * model_HSV;
struct svm_model * model_GM;
struct svm_model * model_sift;

int main(int argc, char ** argv){
	if (argc < 8)
	{
		printf("usage: model1 test1 model2 test2 model3 test3 model4 test4 output\n");
		getch();
		return 1;
	}
	char * input_edh = argv[1];
	char * input_edh_test = argv[2];
	model_edh = svm_load_model(input_edh);
	FILE * finput_edh;
	finput_edh = fopen(input_edh_test,"r");

	char * input_HSV = argv[3];
	char * input_hsv_test = argv[4];
	model_HSV = svm_load_model(input_HSV);
	FILE * finput_hsv;
	finput_hsv = fopen(input_hsv_test,"r");

	char * input_GM = argv[5];
	char * input_GM_test = argv[6];
	model_GM = svm_load_model(input_GM);
	FILE * finput_GM;
	finput_GM = fopen(input_GM_test,"r");

	char * input_sift_test = argv[8];
	char * input_sift = argv[7];
	model_sift = svm_load_model(input_sift);
	FILE * finput_sift;	
	finput_sift = fopen(input_sift_test,"r");

	int i;
	label = new int*[DATA_NUM];
	for(i = 0; i < DATA_NUM; i ++){
		label[i] = new int[CLASS_NUM];
		for(int j = 0; j < CLASS_NUM; j ++)
			label[i][j] = 0;
	}
	predict(finput_edh,model_edh,label);
	predict(finput_hsv,model_HSV,label);
	predict(finput_GM,model_GM,label);
	predict(finput_sift,model_sift,label);
	FILE * foutput;
	foutput = fopen(argv[9],"w");
	int correct = 0;
	int index = 0;
	for(i = 0; i < DATA_NUM; i ++){
		for(int j = 1; j < CLASS_NUM; j++){
			if(label[i][j] > label[i][index])
				index = j;
		}	
		fprintf(foutput,"%d\n",index);
		if(index == i/50)
			correct++;
		index = 0;
	}

	printf("the accuracy is %f\n",correct * 1.0 / 1000);
	for(i = 0; i < SVM_NUM; i ++){
		delete label[i];
	}
	delete label;
	fclose(finput_sift);
	fclose(foutput);
	fclose(finput_GM);
	fclose(finput_edh);
	fclose(finput_hsv);
	return 1;
}
