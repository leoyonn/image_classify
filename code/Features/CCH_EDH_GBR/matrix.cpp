#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "matrix.h"

void nrerror(char *error_text)
{
	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"...now exiting to system...\n");
	exit(1);
}

double *dvector(int nl, int nh)
{
	double *v;

	v = (double *) calloc((unsigned) (nh-nl+1), sizeof(double));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl;
}

float *vector(int nl, int nh)
{
	float *v;

	v = (float *) calloc((unsigned) (nh-nl+1), sizeof(float));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl;
}

void free_dvector(double *v, int nl, int nh)
{
	free((char*) (v+nl));
}

void free_vector(float *v, int nl, int nh)
{
	free((char*) (v+nl));
}

float **matrix(int nrl,int nrh,int ncl,int nch)
{
	int i;
	float **m;

	m=(float **) malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(float *) malloc((unsigned) (nch-ncl+1)*sizeof(float));
		if (!m[i]) nrerror("allocation failure 2 in matrix()");
		m[i] -= ncl;
	}
	return m;
}

void free_matrix(float **m,int nrl,int nrh,int ncl,int nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

double **dmatrix(int nrl, int nrh, int ncl, int nch)
{
	int i;
	double **m;

	m = (double **) calloc((unsigned) (nrh-nrl+1), sizeof(double*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i] = (double *) calloc((unsigned) (nch-ncl+1), sizeof(double));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] -= ncl;
	}
	return m;
}

void free_dmatrix(double **m, int nrl, int nrh, int ncl, int nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}


double log2(double a)
{
	return log10(a)/log10(2.0);
}

void sort(double *Y, int *I, double *A, int length)
{
	int i, j;
	double max, *tmp;

	tmp = (double *) calloc(length, sizeof(double));

	for (i=0;i<length;i++) 
		tmp[i] = A[i];

	max = tmp[0];
	for (i=1;i<length;i++) {
		if (tmp[i] > max) 
			max = tmp[i];
	}

	max = fabs(10*max);

	for (i=0;i<length;i++) {
		Y[i] = tmp[0];
		I[i] = 0;
		for (j=1;j<length;j++) {
			if (tmp[j] < Y[i]) {
				Y[i] = tmp[j];
				I[i] = j;
			}
		}

		tmp[I[i]] = max;
	}

	free(tmp);
}

void minimun(double *Y, int *I, double *A, int length)
{
	int i, index;
	double min;

	min = A[0];
	index = 0;
	for (i=1;i<length;i++) 
		if (A[i] < min) {
			min = A[i];
			index = i;
		}

	*Y = min;
	*I = index;
}

void Mat_Abs(Matrix *A)
{
	int h, w;

	for (h=0;h<A->height;h++)
		for (w=0;w<A->width;w++) {
			if (A->data[h][w] < 0)
			    A->data[h][w] = -1.0*(A->data[h][w]);
		}
}

void Mat_Mean(double *mean, Matrix *A)
{
	int h, w;
	double tmp;

	tmp = 0.0;
	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			tmp += A->data[h][w];
		}
	}

	*mean = tmp/(double) (A->height*A->width);
}

void Mat_Vector(Matrix *A, float *a)
{
	int h, w;

	for (h=0;h<A->height;h++)
		for (w=0;w<A->width;w++)
			a[h*A->width+w] = (float) A->data[h][w];
}

void Mat_Shift(Matrix *A, Matrix *B, int side)
{
	int h, w;

	for (h=side;h<B->height;h++)
		for (w=side;w<B->width;w++)
			A->data[h-side][w-side] = B->data[h][w];
		
	for (h=side;h<B->height;h++)
		for (w=0;w<side;w++)
			A->data[h-side][B->width-side+w] = B->data[h][w];

	for (h=0;h<side;h++)
		for (w=side;w<B->width;w++)
			A->data[B->height-side+h][w-side] = B->data[h][w];

	for (h=0;h<side;h++)
		for (w=0;w<side;w++)
			A->data[B->height-side+h][B->width-side+w] = B->data[h][w];
}

void Mat_Zeros(Matrix *A)
{
	int h, w;

	for (h=0;h<A->height;h++)
		for (w=0;w<A->width;w++)
			A->data[h][w] = 0;
}

void Mat_Zeros_uc(uc_Matrix *A)
{
	int h, w;

	for (h=0;h<A->height;h++)
		for (w=0;w<A->width;w++)
			A->data[h][w] = 0;
}

void Mat_Zeros_i(i_Matrix *A)
{
	int h, w;

	for (h=0;h<A->height;h++)
		for (w=0;w<A->width;w++)
			A->data[h][w] = 0;
}


void CreateMatrix(Matrix **M, int hei, int wid)
{
	int h;

	Matrix *tmp;

	tmp = (Matrix *) calloc(1, sizeof(Matrix)); 
	tmp->data = (double **) calloc(hei, sizeof(double *));

	if (!(tmp->data)) {
		nrerror("allocation failure in CreateMatrix()");
		exit(1);
	}

	for (h=0; h<hei; h++) {
		tmp->data[h] = (double *) calloc(wid, sizeof(double));
		if (!(tmp->data[h])) {
			nrerror("allocation failure in CreateMatrix()");
			exit(1);
		}
	}

	tmp->height = hei;
	tmp->width = wid;
	
	*M = tmp;
}


void FreeMatrix(Matrix *M)
{
	int h, hei = M->height;

	for (h=0; h<hei; h++) {
	     free(M->data[h]);
	}
	free(M->data);
	free(M);
}

void Create_i_Matrix(i_Matrix **M, int hei, int wid)
{
	int h;

	i_Matrix *tmp;

	tmp = (i_Matrix *) calloc(1, sizeof(i_Matrix));
	tmp->data = (int **) calloc(hei, sizeof(int *));
	if (!(tmp->data)) {
		nrerror("allocation failure in Create_i_Matrix()");
		exit(1);
	}

	for (h=0; h<hei; h++) {
		tmp->data[h] = (int *) calloc(wid, sizeof(int));
		if (!(tmp->data[h])) {
			nrerror("allocation failure in Create_i_Matrix()");
			exit(1);
		}
	}

	tmp->height = hei;
	tmp->width = wid;
	
	*M = tmp;
}

void Free_i_Matrix(i_Matrix *M)
{
	int h;

	for (h=0; h<M->height; h++) 
	     free(M->data[h]);
	free(M->data);
	free(M);
}

void Create_uc_Matrix(uc_Matrix **M, int hei, int wid)
{
	int h;

	uc_Matrix *tmp;

	tmp = (uc_Matrix *) calloc(1, sizeof(uc_Matrix));
	tmp->data = (unsigned char **) calloc(hei, sizeof(unsigned char *));
	if (!(tmp->data)) {
		nrerror("allocation failure in Create_uc_Matrix()");
		exit(1);
	}

	for (h=0; h<hei; h++) {
		tmp->data[h] = (unsigned char *) calloc(wid, sizeof(unsigned char));
		if (!(tmp->data[h])) {
			nrerror("allocation failure in Create_uc_Matrix()");
			exit(1);
		}
	}

	tmp->height = hei;
	tmp->width = wid;
	
	*M = tmp;
}

void Free_uc_Matrix(uc_Matrix *M)
{
	int h;

	for (h=0; h<M->height; h++) 
	     free(M->data[h]);
	free(M->data);
	free(M);
}


void Mat_FFT2(Matrix *Output_real, Matrix *Output_imag, Matrix *Input_real, Matrix *Input_imag)
{
	int xs, ys, i, j;
	double **R, **I, **Fr, **Fi;

	xs = Input_real->height;
	ys = Input_real->width;

        R  = dmatrix(1,xs,1,ys);
        I  = dmatrix(1,xs,1,ys);
        Fr = dmatrix(1,xs,1,ys);
        Fi = dmatrix(1,xs,1,ys);
			
        for (i=1;i<=Input_real->height;i++) 
            for (j=1;j<=Input_real->width;j++) {
                R[i][j] = Input_real->data[i-1][j-1];
                I[i][j] = Input_imag->data[i-1][j-1];
            }

        four2(Fr, Fi, R, I, xs, ys, 1);         /* 2-D FFT */

        for (i=1;i<=Input_real->height;i++) 
            for (j=1;j<=Input_real->width;j++) {
                Output_real->data[i-1][j-1] = Fr[i][j];
                Output_imag->data[i-1][j-1] = Fi[i][j];
            }

        free_dmatrix(R,1,xs,1,ys);
        free_dmatrix(I,1,xs,1,ys);   
        free_dmatrix(Fr,1,xs,1,ys);
        free_dmatrix(Fi,1,xs,1,ys);   
}

void Mat_IFFT2(Matrix *Output_real, Matrix *Output_imag, Matrix *Input_real, Matrix *Input_imag)
{
	int xs, ys, i, j;
	double **R, **I, **Fr, **Fi, NN;

	xs = Input_real->height;
	ys = Input_real->width;

        R  = dmatrix(1,xs,1,ys);
        I  = dmatrix(1,xs,1,ys);
        Fr = dmatrix(1,xs,1,ys);
        Fi = dmatrix(1,xs,1,ys);

        for (i=1;i<=Input_real->height;i++) 
            for (j=1;j<=Input_real->width;j++) {
                R[i][j] = Input_real->data[i-1][j-1];
                I[i][j] = Input_imag->data[i-1][j-1];
            }

        four2(Fr, Fi, R, I, xs, ys, -1);         /* 2-D IFFT */

	NN = (double) (xs*ys);

        for (i=1;i<=Input_real->height;i++) 
            for (j=1;j<=Input_real->width;j++) {
                Output_real->data[i-1][j-1] = Fr[i][j]/NN;
                Output_imag->data[i-1][j-1] = Fi[i][j]/NN;
            }

        free_dmatrix(R,1,xs,1,ys);
        free_dmatrix(I,1,xs,1,ys);   
        free_dmatrix(Fr,1,xs,1,ys);
        free_dmatrix(Fi,1,xs,1,ys);   
}

void four2(double **fftr, double **ffti, double **rdata, double **idata, int rs, int cs, int isign)
/************************************************************ 

   2-D fourier transform of data with real part stored in
   "rdata" and imaginary part in "idata" with size "rs" x
   "cs". The result is in "fftr" and "ffti". The isign is
   "isign" =  1 forward, and "isign" = -1 inverse 

*************************************************************/
{
        double **T, *tmp1, *tmp2;
        int i, j;

        tmp1 = dvector(1,2*cs);
        tmp2 = dvector(1,2*rs);
        T = dmatrix(1,2*rs,1,cs);

        for (i=1;i<=rs;i++) {
            for (j=1;j<=cs;j++) {
                tmp1[j*2-1] = rdata[i][j];
                tmp1[j*2] = idata[i][j];
            }
            four1(tmp1, cs, isign);
            for (j=1;j<=cs;j++) {
                T[i*2-1][j] = tmp1[j*2-1];
                T[i*2][j] = tmp1[j*2];
            }
        }

        for (i=1;i<=cs;i++) {
            for (j=1;j<=rs;j++) {
                tmp2[j*2-1] = T[j*2-1][i];
                tmp2[j*2] = T[j*2][i];
            }
            four1(tmp2,rs,isign);
            for (j=1;j<=rs;j++) {
                fftr[j][i] = tmp2[j*2-1];
                ffti[j][i] = tmp2[j*2];
            }
        }
        free_dvector(tmp1, 1, 2*cs);
        free_dvector(tmp2, 1, 2*rs);
        free_dmatrix(T, 1, 2*rs, 1, cs); 
}

void four1(double *data, int nn, int isign)
{
	int n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	n = nn << 1;
	j = 1;
	for (i=1;i<n;i+=2) {
		if (j > i) {
			SWAP(data[j],data[i]);
			SWAP(data[j+1],data[i+1]);
		}
		m = n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax = 2;
	while (n > mmax) {
		istep = 2*mmax;
		theta = 6.28318530717959/(isign*mmax);
		wtemp = sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=n;i+=istep) {
				j = i+mmax;
				tempr = wr*data[j]-wi*data[j+1];
				tempi = wr*data[j+1]+wi*data[j];
				data[j] = data[i]-tempr;
				data[j+1] = data[i+1]-tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr = (wtemp=wr)*wpr-wi*wpi+wr;
			wi = wi*wpr+wtemp*wpi+wi;
		}
		mmax = istep;
	}
}

void Mat_Copy(Matrix *A, Matrix *B, int h_target, int w_target, int h_begin, int w_begin, int h_end, int w_end)
{
	int i, j, h, w, h_done, w_done;

	if ((h_target >= 0)&&(h_target < A->height)&&(w_target >= 0)&&(w_target < A->width)) {
		if ((h_begin >= 0)&&(h_begin < B->height)&&(w_begin >= 0)&&(w_begin < B->width)) {
			h = h_end-h_begin+1;
			w = w_end-w_begin+1;
			if ((h >= 1)&&(w >= 1)) {
				h_done = h_target+h-1;
				w_done = w_target+w-1;
				if ((h_done < A->height)&&(w_done < A->width)) {
					for (i=0;i<h;i++) {
						for (j=0;j<w;j++) {
							A->data[i+h_target][j+w_target] = B->data[i+h_begin][j+w_begin];
						}
					}
				}
			}
		}
	}
	else {
		printf("matrix dimension error!\n");
		exit(1);
	}
}

void Mat_uc_Copy(uc_Matrix *A, uc_Matrix *B, int h_target, int w_target, int h_begin, int w_begin, int h_end, int w_end)
{
	int i, j, h, w, h_done, w_done;

	if ((h_target >= 0)&&(h_target < A->height)&&(w_target >= 0)&&(w_target < A->width)) {
		if ((h_begin >= 0)&&(h_begin < B->height)&&(w_begin >= 0)&&(w_begin < B->width)) {
			h = h_end-h_begin+1;
			w = w_end-w_begin+1;
			if ((h >= 1)&&(w >= 1)) {
				h_done = h_target+h-1;
				w_done = w_target+w-1;
				if ((h_done < A->height)&&(w_done < A->width)) {
					for (i=0;i<h;i++) {
						for (j=0;j<w;j++) {
							A->data[i+h_target][j+w_target] = B->data[i+h_begin][j+w_begin];
						}
					}
				}
			}
		}
	}
	else {
		printf("matrix dimension error!\n");
		exit(1);
	}
}
	
void Mat_i_Copy(i_Matrix *A, i_Matrix *B, int h_target, int w_target, int h_begin, int w_begin, int h_end, int w_end)
{
	int i, j, h, w, h_done, w_done;

	if ((h_target >= 0)&&(h_target < A->height)&&(w_target >= 0)&&(w_target < A->width)) {
		if ((h_begin >= 0)&&(h_begin < B->height)&&(w_begin >= 0)&&(w_begin < B->width)) {
			h = h_end-h_begin+1;
			w = w_end-w_begin+1;
			if ((h >= 1)&&(w >= 1)) {
				h_done = h_target+h-1;
				w_done = w_target+w-1;
				if ((h_done < A->height)&&(w_done < A->width)) {
					for (i=0;i<h;i++) {
						for (j=0;j<w;j++) {
							A->data[i+h_target][j+w_target] = B->data[i+h_begin][j+w_begin];
						}
					}
				}
			}
		}
	}
	else {
		printf("matrix dimension error!\n");
		exit(1);
	}
}
				
void Mat_Product(Matrix *A, Matrix *B, Matrix *C)
{
	int h, w;

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = B->data[h][w]*C->data[h][w];
		}
	}
}

void Mat_Sum(Matrix *A, Matrix *B, Matrix *C)
{
	int h, w;

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = B->data[h][w]+C->data[h][w];
		}
	}
}

void Mat_Substract(Matrix *A, Matrix *B, Matrix *C)
{
	int h, w;

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = B->data[h][w]-C->data[h][w];
		}
	}
}

void Mat_Fliplr(Matrix *A)
{
	Matrix *tmp;
	int h, w;

	CreateMatrix(&tmp, A->height, A->width);
	
	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			tmp->data[h][w] = A->data[h][(A->width)-w-1];
		}
	}

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = tmp->data[h][w];
		}
	}

	FreeMatrix(tmp);
}

void Mat_Flipud(Matrix *A)
{
	Matrix *tmp;
	int h, w;

	CreateMatrix(&tmp, A->height, A->width);
	
	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			tmp->data[h][w] = A->data[(A->height)-h-1][w];
		}
	}

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = tmp->data[h][w];
		}
	}

	FreeMatrix(tmp);
}


void Mat_uc_Fliplr(uc_Matrix *A)
{
	uc_Matrix *tmp;
	int h, w;

	Create_uc_Matrix(&tmp, A->height, A->width);
	
	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			tmp->data[h][w] = A->data[h][(A->width)-w-1];
		}
	}

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = tmp->data[h][w];
		}
	}

	Free_uc_Matrix(tmp);
}

void Mat_uc_Flipud(uc_Matrix *A)
{
	uc_Matrix *tmp;
	int h, w;

	Create_uc_Matrix(&tmp, A->height, A->width);
	
	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			tmp->data[h][w] = A->data[(A->height)-h-1][w];
		}
	}

	for (h=0;h<A->height;h++) {
		for (w=0;w<A->width;w++) {
			A->data[h][w] = tmp->data[h][w];
		}
	}

	Free_uc_Matrix(tmp);
}





