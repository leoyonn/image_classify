#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* --------------------------------------------------------------------------------------
The GaborFilteredImg provides the outputs of the Gabor filter bank
-----------------------------------------------------------------------------------------*/
void GaborFilteredImg(Matrix *FilteredImg_real, Matrix *FilteredImg_imag, Matrix *img, int side, double Ul, double Uh, 
int scale, int orientation, int flag)
{
	int h, w, xs, ys, border, r1, r2, r3, r4, hei, wid, s, n;
	Matrix *IMG, *IMG_imag, *Gr, *Gi, *Tmp_1, *Tmp_2, *F_1, *F_2, *G_real, *G_imag, *F_real, *F_imag;

	void Gabor(Matrix *Gr, Matrix *Gi, int s, int n, double Ul, double Uh, int scale, int orientation, int flag);

	border = side;
	hei = img->height;
	wid = img->width;

	/* FFT2 */
	xs = (int) pow(2.0, ceil(log2((double)(img->height+2.0*border))));
	ys = (int) pow(2.0, ceil(log2((double)(img->width+2.0*border))));

	CreateMatrix(&IMG, xs, ys);

	r1 = img->width+border;
	r2 = img->width+2*border;
	for (h=0;h<border;h++) {
		for (w=0;w<border;w++)
			IMG->data[h][w] = img->data[border-1-h][border-1-w];
		for (w=border;w<r1;w++)
			IMG->data[h][w] = img->data[border-1-h][w-border];
		for (w=r1;w<r2;w++)
			IMG->data[h][w] = img->data[border-1-h][2*img->width-w+border-1];
	}

	r1 = img->height+border;
	r2 = img->width+border;
	r3 = img->width+2*border;
	for (h=border;h<r1;h++) {
		for (w=0;w<border;w++)
			IMG->data[h][w] = img->data[h-border][border-1-w];
		for (w=border;w<r2;w++)
			IMG->data[h][w] = img->data[h-border][w-border];
		for (w=r2;w<r3;w++)
			IMG->data[h][w] = img->data[h-border][2*img->width-w+border-1];
	}

	r1 = img->height+border;
	r2 = img->height+2*border;
	r3 = img->width+border;
	r4 = img->width+2*border;
	for (h=r1;h<r2;h++) {
		for (w=0;w<border;w++)
			IMG->data[h][w] = img->data[2*img->height-h+border-1][border-1-w];
		for (w=border;w<r3;w++)
			IMG->data[h][w] = img->data[2*img->height-h+border-1][w-border];
		for (w=r3;w<r4;w++)
			IMG->data[h][w] = img->data[2*img->height-h+border-1][2*img->width-w+border-1];
	}

	CreateMatrix(&F_real, xs, ys);
	CreateMatrix(&F_imag, xs, ys);
	CreateMatrix(&IMG_imag, xs, ys);

	Mat_FFT2(F_real, F_imag, IMG, IMG_imag);

	/* ----------- compute the Gabor filtered output ------------- */

	CreateMatrix(&Gr, 2*side+1, 2*side+1);
	CreateMatrix(&Gi, 2*side+1, 2*side+1);
	CreateMatrix(&Tmp_1, xs, ys);
	CreateMatrix(&Tmp_2, xs, ys);
	CreateMatrix(&F_1, xs, ys);
	CreateMatrix(&F_2, xs, ys);
	CreateMatrix(&G_real, xs, ys);
	CreateMatrix(&G_imag, xs, ys);

	for (s=0;s<scale;s++) {
		for (n=0;n<orientation;n++) {
			Gabor(Gr, Gi, s+1, n+1, Ul, Uh, scale, orientation, flag);
			Mat_Copy(F_1, Gr, 0, 0, 0, 0, 2*side, 2*side);
			Mat_Copy(F_2, Gi, 0, 0, 0, 0, 2*side, 2*side);
			Mat_FFT2(G_real, G_imag, F_1, F_2);
			
			Mat_Product(Tmp_1, G_real, F_real);
			Mat_Product(Tmp_2, G_imag, F_imag);
			Mat_Substract(IMG, Tmp_1, Tmp_2);
			
			Mat_Product(Tmp_1, G_real, F_imag);
			Mat_Product(Tmp_2, G_imag, F_real);
			Mat_Sum(IMG_imag, Tmp_1, Tmp_2);
			
			Mat_IFFT2(Tmp_1, Tmp_2, IMG, IMG_imag);
			
			Mat_Copy(FilteredImg_real, Tmp_1, s*hei, n*wid, 2*side, 2*side, hei+2*side-1, wid+2*side-1);
			Mat_Copy(FilteredImg_imag, Tmp_2, s*hei, n*wid, 2*side, 2*side, hei+2*side-1, wid+2*side-1);
		}
	}
	
	FreeMatrix(Gr);
	FreeMatrix(Gi);
	FreeMatrix(Tmp_1);
	FreeMatrix(Tmp_2);
	FreeMatrix(F_1);
	FreeMatrix(F_2);
	FreeMatrix(G_real);
	FreeMatrix(G_imag);
	FreeMatrix(F_real);
	FreeMatrix(F_imag);
	FreeMatrix(IMG);
	FreeMatrix(IMG_imag);
}

/* ------------------------------------------------------------------------------------------------------
The Gabor function generates a Gabor filter with the selected index 's' and 'n' (scale and orientation, 
respectively) from a Gabor filter bank. This filter bank is designed by giving the range of spatial 
frequency (Uh and Ul) and the total number of scales and orientations used to partition the spectrum. 

  The returned filter is stored in 'Gr' (real part) and 'Gi' (imaginary part).
--------------------------------------------------------------------------------------------------------*/
void Gabor(Matrix *Gr, Matrix *Gi, int s, int n, double Ul, double Uh, int scale, int orientation, int flag)
{
	 double base, a, u0, z, Uvar, Vvar, Xvar, Yvar, X, Y, G, t1, t2, m;
	 int x, y, side;
	  
	 base = Uh/Ul;
	 a = pow(base, 1.0/(double)(scale-1));
	 
	 u0 = Uh/pow(a, (double) scale-s);
	  
	 Uvar = (a-1.0)*u0/((a+1.0)*sqrt(2.0*log(2.0)));  
	 z = -2.0*log(2.0)*(Uvar*Uvar)/u0;
	 Vvar = tan(PI/(2*orientation))*(u0+z)/sqrt(2.0*log(2.0)-z*z/(Uvar*Uvar));
	  
	 Xvar = 1.0/(2.0*PI*Uvar);
	 Yvar = 1.0/(2.0*PI*Vvar);
	  
	 t1 = cos(PI/orientation*(n-1.0));
	 t2 = sin(PI/orientation*(n-1.0));
	  
	 side = (int) (Gr->height-1)/2;
	  
	 for (x=0;x<2*side+1;x++) {
		 for (y=0;y<2*side+1;y++) {
			 X = (double) (x-side)*t1+ (double) (y-side)*t2;
			 Y = (double) -(x-side)*t2+ (double) (y-side)*t1;
			 G = 1.0/(2.0*PI*Xvar*Yvar)*pow(a, (double) scale-s)*exp(-0.5*((X*X)/(Xvar*Xvar)+(Y*Y)/(Yvar*Yvar)));
			 Gr->data[x][y] = G*cos(2.0*PI*u0*X);
			 Gi->data[x][y] = G*sin(2.0*PI*u0*X);
		 }
	 }
	  
	 /* if flag = 1, then remove the DC from the filter */
	 if (flag == 1) {
		 m = 0;
		 for (x=0;x<2*side+1;x++)
			 for (y=0;y<2*side+1;y++)
				 m += Gr->data[x][y];
			  
			 m /= pow((double) 2.0*side+1, 2.0);
			  
			 for (x=0;x<2*side+1;x++)
				 for (y=0;y<2*side+1;y++)
					 Gr->data[x][y] -= m;
	 }	
}
