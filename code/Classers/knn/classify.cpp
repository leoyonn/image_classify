#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <fstream.h>
#include <memory.h>
#include <conio.h>
//#define  NATTRS 5 //number of attributes
#define  MAXSZ  1700 //max size of training set
#define  MAXVALUE  10000.0 //the biggest attribute's value is below 10000(int)
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
static char *line = NULL;
struct vector {
	double * attributes;
	int classlabel;
};
struct item {
	double distance;
	int classlabel;
};
struct vector * trSet;//global variable,the training set
struct item * knn;//global variable,the k-neareast-neighbour set
int curTSize = 0; //current size of the training set
static int max_line_lenth;
int * label_y;
double ** sample;
double * element_x;
int class_num = 20;
int K_value = 10;
int lenth = 0;
int width = 0;
int max_line_len;
static char* readline(FILE *input);
void exit_input_error(int line_num)
{
	fprintf(stderr,"Wrong input format at line %d\n", line_num);
	exit(1);
}
int AddtoTSet(struct vector v)
{
	if(curTSize>=MAXSZ) {
		cout<<endl<<"The training set has "<<MAXSZ<<" examples!"<<endl<<endl; 
		return 0;
	}
	trSet[curTSize] = v;
	curTSize++;
	return 1;
}
double Distance(struct vector v1,struct vector v2)
{
	double d = 0.0;
	double tem = 0.0;
	for(int i = 0;i < width;i++)
		tem += (v1.attributes[i]-v2.attributes[i])*(v1.attributes[i]-v2.attributes[i]);
	d = sqrt(tem);
	return d;
}
int max(struct item knn[]) //return the no. of the item which has biggest distance(
//should be replaced) 
{
	int maxNo = 0;
	if(K_value > 1)
		for(int i = 1;i < K_value;i++)
			if(knn[i].distance>knn[maxNo].distance)
				maxNo = i;
			return maxNo;
}

int Classify(struct vector v)//decide which class label will be assigned to
//a given input vetor with the knn method
{
	double dd = 0;
	int maxn = 0;
	int *  freq = new int[K_value];
	int mfreqC = 0;//the class label appears most frequently 
	int i;
	for(i = 0;i < K_value;i++)
		knn[i].distance = MAXVALUE;
	for(i = 0;i < curTSize;i++)
	{
		dd = Distance(trSet[i],v);
		maxn = max(knn);//for every new state of the training set should update maxn
		if(dd < knn[maxn].distance) {
			knn[maxn].distance = dd;
			knn[maxn].classlabel = trSet[i].classlabel;
		}
	}
	for(i = 0;i < K_value;i++)//freq[i] represents knn[i].classlabel appears how many times 
		freq[i] = 1;
	for(i = 0;i < K_value;i++)  
		for(int j = 0;j < K_value;j++)
			if((i!=j)&&(knn[i].classlabel == knn[j].classlabel))
				freq[i]+=1;
			int mfreq = 1;
			mfreqC = knn[0].classlabel;
			for(i = 0;i < K_value;i++)
				if(freq[i] > mfreq)  {
					mfreq = freq[i];//mfreq represents the most frepuences
					mfreqC = knn[i].classlabel; //mfreqNo is the item no. with the most frequent
					//classlabel
				}
				return mfreqC;
}

void read_problem(const char *filename)
{
	int elements, max_index, inst_max_index, i, j;
	FILE *fp = fopen(filename,"r");
	char *endptr;
	char *idx, *val, *label;

	if(fp == NULL)
	{
		fprintf(stderr,"can't open input file %s\n",filename);
		exit(1);
	}

	lenth = 0;
	elements = 0;

	max_line_len = 1024;
	line = Malloc(char,max_line_len);
	while(readline(fp)!=NULL)
	{
		char *p = strtok(line," \t"); // label

		// features
		while(1)
		{
			p = strtok(NULL," \t");
			if(p == NULL || *p == '\n') // check '\n' as ' ' may be after the last feature
				break;
			++elements;
		}
		++lenth;
	}
	rewind(fp);

	label_y = new int[lenth];
	sample = new double * [lenth];
	element_x = new double [elements];
	width = elements / lenth;
	max_index = 0;
	j=0;
	for(i=0;i<lenth;i++)
	{
		inst_max_index = -1; // strtol gives 0 if wrong format, and precomputed kernel has <index> start from 0
		readline(fp);
		sample[i] = &element_x[j];
		label = strtok(line," \t");
		label_y[i] = strtol(label,&endptr,10);
		if(endptr == label)
			exit_input_error(i+1);

		while(1)
		{
			idx = strtok(NULL,":");
			val = strtok(NULL," \t");

			if(val == NULL)
				break;

			errno = 0;
			//x_space[j].index = (int) strtol(idx,&endptr,10);
			if(endptr == idx || errno != 0 || *endptr != '\0' )
				exit_input_error(i+1);
			else
//				inst_max_index = x_space[j].index;

			errno = 0;
			element_x[j] = strtod(val,&endptr);
	//		if(endptr == val || errno != 0 || (*endptr != '\0' && !((*endptr) == ' ')))
	//			exit_input_error(i+1);

			++j;
		}

		if(inst_max_index > max_index)
			max_index = inst_max_index;
		//x_space[j++].index = -1;
	}

//	if(param.gamma == 0 && max_index > 0)
//		param.gamma = 1.0/max_index;

//	if(param.kernel_type == PRECOMPUTED)
//		for(i=0;i<prob.l;i++)
//		{
//			if (prob.x[i][0].index != 0)
//			{
//				fprintf(stderr,"Wrong input format: first column must be 0:sample_serial_number\n");
//				exit(1);
//			}
//			if ((int)prob.x[i][0].value <= 0 || (int)prob.x[i][0].value > max_index)
//			{
//				fprintf(stderr,"Wrong input format: sample_serial_number out of range\n");
//				exit(1);
//			}
//		}
	element_x = NULL;
	fclose(fp);
}

static char* readline(FILE *input)
{
	int len;
	
	if(fgets(line,max_line_len,input) == NULL)
		return NULL;

	while(strrchr(line,'\n') == NULL)
	{
		max_line_len *= 2;
		line = (char *) realloc(line,max_line_len);
		len = (int) strlen(line);
		if(fgets(line+len,max_line_len-len,input) == NULL)
			break;
	}
	return line;
}

void main(int argc, char** argv)
{   
//	char input_file_name[1024] = "data1.txt";
//	char output_file_name[1024];
	if(argc < 4)
	{
		printf("usage: [traindata] [testdata] [output]\n");
		getch();
		return;
	}
	for(int k = 1; k< argc; k ++)
		if(strcmp(argv[k], "-k") == 0)
			K_value = atoi(argv[k+1]);
	knn = new struct item[K_value];
	double ** sample_train;
	double ** sample_test;
	int * label_train;
	int * label_test;
	int lenth_train,lenth_test;
	read_problem(argv[1]);
	sample_train = new double*[lenth];
	label_train = new int[lenth];
	memcpy(sample_train,sample,lenth * sizeof(double *));
	memcpy(label_train, label_y, lenth * sizeof(int));
	lenth_train = lenth;
	delete sample;
	delete label_y;
	delete element_x;
	read_problem(argv[2]);
	sample_test = new double*[lenth];
	label_test = new int[lenth];
	memcpy(sample_test,sample,lenth * sizeof(double *));
	memcpy(label_test, label_y, lenth * sizeof(int));
	lenth_test = lenth;
	delete sample;
	delete label_y;
	sample = NULL;
	label_y = NULL;
	FILE * output;
	output = fopen(argv[3], "w");

	int classlabel;
	int i;
	curTSize = lenth_train;
	trSet = new vector[lenth_train];
	vector * test_Set = new vector[lenth_test];
	for(i=0;i<lenth_train;i++){
		trSet[i].attributes = sample_train[i];
		trSet[i].classlabel = label_train[i];
	}
	struct vector testv;
	int num_match = 0;
	for(i=0; i<lenth_test; i++){
		testv.attributes = sample_test[i];
		classlabel = Classify(testv);
		fprintf(output,"%d\n",classlabel);
		if(classlabel == label_test[i])
			++num_match;
	}
	fclose(output);
	double accuracy = 0.0;
	accuracy = 1.0 * num_match / lenth_test;
	cout << "The accuracy equals to " << accuracy << endl;
	delete knn;
	delete sample_test;
	delete sample_train;
	delete label_test;
	delete label_train;
}
