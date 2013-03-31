/* -*-  Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */

/*

Author: Yan Ke
Dec 2003

*/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
extern "C" {
     #include <pgm.h>
}*/

//#include "config.h"
#include "image.h"

#define GAUSSKERN 4
#define PI 3.14159265358979323846

Image::Image(int width, int height) {
	newImage(width, height);
}

Image::Image(int width, int height, float * new_data) {
	assert(width > 0 && height > 0);

	this->width = width;
	this->height = height;
	
	pix = (float **) malloc(height * sizeof(float *));
	float * data = (float *) malloc(height * width * sizeof(float));

	for (int i = 0; i < height; i++) {
		pix[i] = data;
		data += width;
	}

	memcpy(*pix, new_data, width * height * sizeof(float));
}

Image::Image(const char * filename) {
/*	assert(filename);

	FILE* fp = fopen(filename, "rb");
	assert(fp);
	
	gray maxval;
	gray ** pixels;

	pixels = pgm_readpgm(fp, &width, &height, &maxval);
	
	fclose(fp);

	assert(pixels);
	
	newImage(width, height);
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
			pix[y][x] = pixels[y][x] / 255.0;
	}

	pgm_freearray(pixels, height);
	*/
}

Image::~Image() {
	free(*pix);
	free(pix);
}

void Image::newImage(int width, int height) {
	assert(width > 0 && height > 0);

	this->width = width;
	this->height = height;
	
	pix = (float **) malloc(height * sizeof(float *));
	float * data = (float *) calloc(height * width, sizeof(float));

	for (int i = 0; i < height; i++) {
		pix[i] = data;
		data += width;
	}	
}

Image * Image::clone() {
	Image * im = new Image(width, height, *pix);
	return im;
}

Image * Image::halfSizeImage() {
	int w = width/2;
	int h = height/2;

	Image * im = new Image(w, h);
	
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			im->setPixel(i, j, getPixel(i*2, j*2));
		}
	}

	return im;
}


Image * Image::doubleSizeImage() {
	int w = width*2;
	int h = height*2;

	Image * im = new Image(w, h);
	
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			im->setPixel(i, j, getPixel(i/2, j/2));
		}
	}

	return im;
}


Image * Image::doubleSizeImage2() {
	int w = width*2;
	int h = height*2;
	int i, j;
	Image * im = new Image(w, h);
	
	// fill every pixel so we don't have to worry about skipping pixels later
	for ( j = 0; j < h; j++) {
		for ( i = 0; i < w; i++) {
			im->setPixel(i, j, getPixel(i/2, j/2));
		}
	}

	/*
	  A B C
	  E F G
	  H I J

	  pixels A C H J are pixels from original image
	  pixels B E G I F are interpolated pixels

	*/

	// interpolate pixels B and I
	for ( j = 0; j < h; j += 2)
		for ( i = 1; i < w - 1; i += 2)
			im->setPixel(i, j, (getPixel(i/2, j/2) + getPixel(i/2 + 1, j/2)) / 2.0);

       
	// interpolate pixels E and G
	for ( j = 1; j < h - 1; j += 2)
		for ( i = 0; i < w; i += 2)
			im->setPixel(i, j, (getPixel(i/2, j/2) + getPixel(i/2, j/2 + 1)) / 2.0);

       
	// interpolate pixel F
	// interpolate pixels E and G
	for ( j = 1; j < h - 1; j += 2)
		for ( i = 1; i < w - 1; i += 2)
			im->setPixel(i, j, (getPixel(i/2, j/2) + getPixel(i/2, j/2 + 1)
					    + getPixel(i/2 + 1, j/2) + getPixel(i/2 + 1, j/2 + 1))
				     / 4.0);



	return im;
}


void Image::sub(Image * im2, Image * dst) {
	assert(im2);
	assert(dst);
	
	assert(width == im2->width && width == dst->width);
	assert(height == im2->height && height == dst->height);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			dst->setPixel(i, j, getPixel(i, j) - im2->getPixel(i, j));
		}
	}
	
}


void Image::write(const char * filename) {
	FILE * fp;
 
	assert(filename);
	fp = fopen(filename, "wb");
	assert(fp);

/*	gray ** pixels = pgm_allocarray(width, height);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			pixels[j][i] = (unsigned int) (getPixel(i, j) * 255.0);
		//unsigned int val = (unsigned int) (fabs(getPixel(i, j) * 255.0 * 20));
		//if (val > 255)
		//	val = 255;
		//pixels[j][i] = val;
		}
	}

	pgm_writepgm(fp, pixels, width, height, 255, 0);

	pgm_freearray(pixels, height);
*/
	fclose(fp);

}

void Image::setPixel(int x, int y, float val) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);
	//assert(val >= 0 && val <= 1);

	pix[y][x] = val;
}


float Image::getPixel(int x, int y) {
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);

	return pix[y][x];
}

float Image::getPixelBI(float col, float row) {

	int irow, icol;
	float rfrac, cfrac;
	float row1 = 0, row2 = 0;
	
	irow = (int) row;
	icol = (int) col;
	
	if (irow < 0 || irow >= height
	    || icol < 0 || icol >= width)
		return 0;
	
	if (row > height - 1)
		row = height - 1;
	
	if (col > width - 1)
		col = width - 1;
	
	rfrac = 1.0 - (row - (float) irow);
	cfrac = 1.0 - (col - (float) icol);
	
	
	if (cfrac < 1) {
		row1 = cfrac * pix[irow][icol] + (1.0 - cfrac) * pix[irow][icol + 1];
	} else {
		row1 = pix[irow][icol];
	}
	
	if (rfrac < 1) {
		if (cfrac < 1) {
			row2 = cfrac * pix[irow+1][icol] + (1.0 - cfrac) * pix[irow+1][icol + 1];
		} else {
			row2 = pix[irow+1][icol];
		}
	}
	
	return rfrac * row1 + (1.0 - rfrac) * row2;
	

}

/**
 * Normalizes a matrix to unit length.
 * 
 * @param mat Matrix to normalize
 */

void normalizeMat(vector<vector<float> > & mat) {

	float sum = 0;
	unsigned int i, j;
	for (j = 0; j < mat.size(); j++) {
		for (i = 0; i < mat[j].size(); i++) {
			assert(mat[j].size() == mat[0].size());
			sum += mat[j][i];
		}
	}

	for (j = 0; j < mat.size(); j++) {
		for (i = 0; i < mat[j].size(); i++) {
			mat[j][i] /= sum;
		}
	}

}

/**
 * Normalizes a vector to unit length.
 * 
 * @param vec vector to normalize
 */
void normalizeVec(vector<float> & vec) {

	float sum = 0;
	int i;
	for (i = 0; i < vec.size(); i++)
		sum += vec[i];

	for (i = 0; i < vec.size(); i++)
		vec[i] /= sum;
}

/**
 * Creates a 1D Gaussian kernel.
 * Kernel is always odd.
 *
 * @param sigma Sigma of Gaussian weighting function.
 * @return 1D Gaussian kernel
 */

vector<float> GaussianKernel1D(float sigma) {

	assert (sigma > 0);

	int dim = (int) max(3.0f, 2 * GAUSSKERN * sigma + 1.0f);

	// make dim odd
	if (dim % 2 == 0)
		dim++;

	//printf("GaussianKernel1D(): Creating 1x%d vector for sigma=%.3f gaussian kernel\n", dim, sigma);

	vector<float> kern(dim);

	float s2 = sigma * sigma;

	int c = dim / 2;
  
	for (int i = 0; i < (dim + 1) / 2; i++) {
		float v = 1 / (2 * PI * s2) * exp(-(i*i) / (2 * s2));
		kern[c+i] = v;
		kern[c-i] = v;
		
	}
	
	normalizeVec(kern);
	
	//for (unsigned int i = 0; i < kern.size(); i++)
	//	printf("%f\n", kern[i]);

	return kern;
}

/**
 * Convolve an image along the X direction at a particular pixel location.
 *
 * @param kernel Kernel to convolve with.
 * @param src Source image
 * @param x x pixel location
 * @param y y pixel location
 * @return Convolved value at location (x, y)
 */
float ConvolveLocWidth(vector<float> & kernel, Image * src, int x, int y) {
	float pixel = 0;

	int cen = kernel.size() / 2;

	//printf("ConvolveLoc(): Applying convoluation at location (%d, %d)\n", x, y);

	for (unsigned int i = 0; i < kernel.size(); i++) {
		int col = x + (i - cen);
		if (col < 0)
			col = 0;
		if (col >= src->width)
			col = src->width - 1;

		float tmp = src->getPixel(col, y);
		pixel += kernel[i] * tmp;
	}

	if (pixel > 1)
		pixel = 1;

	return pixel;
}

/* Convolves an entire image along the X direction.
 * 
 * @param kern Kernel to convolve with.
 * @param src Source image
 * @param dst Destination image
 */
void Convolve1DWidth(vector<float> & kern, Image * src, Image * dst) {
	for (int j = 0; j < src->height; j++) {
		for (int i = 0; i < src->width; i++) {
			//printf("%d, %d\n", i, j);
			dst->setPixel(i, j, ConvolveLocWidth(kern, src, i, j));
		}
	}
}

/**
 * Convolve an image along the Y direction at a particular pixel location.
 *
 * @param kernel Kernel to convolve with.
 * @param src Source image
 * @param x x pixel location
 * @param y y pixel location
 * @return Convolved value at location (x, y)
 */
float ConvolveLocHeight(vector<float> & kernel, Image * src, int x, int y) {
	float pixel = 0;

	int cen = kernel.size() / 2;

	//printf("ConvolveLoc(): Applying convoluation at location (%d, %d)\n", x, y);

	for (unsigned int j = 0; j < kernel.size(); j++) {
		int row = y + (j - cen);

		if (row < 0)
			row = 0;
		if (row >= src->height)
			row = src->height - 1;

		float tmp = src->getPixel(x, row);
		pixel += kernel[j] * tmp;
	}

	if (pixel > 1)
		pixel = 1;

	return pixel;
}

/* Convolves an entire image along the Y direction.
 * 
 * @param kern Kernel to convolve with.
 * @param src Source image
 * @param dst Destination image
 */
void Convolve1DHeight(vector<float> & kern, Image * src, Image * dst) {

	for (int j = 0; j < src->height; j++) {
		for (int i = 0; i < src->width; i++) {
			//printf("%d, %d\n", i, j);
			dst->setPixel(i, j, ConvolveLocHeight(kern, src, i, j));
		}
	}
}

void BlurImage(Image * src, Image * dst, float sigma) {
	assert (src && dst);

	assert(src->width == dst->width);
	assert(src->height == dst->height);

	Image * tmpImage = new Image(src->width, src->height);

	vector<float> convkernel = GaussianKernel1D(sigma);

	/*
	printf("Gauss Blur for sigma %f: ", sigma);
	for (unsigned int i = 0; i < convkernel.size(); i++) {
		printf("%f ", convkernel[i]);
	}
	printf("\n");
	*/

	Convolve1DWidth(convkernel, src, tmpImage);
	Convolve1DHeight(convkernel, tmpImage, dst);
}

vector<vector<float> > GaussianKernel2D(float sigma) {
	int dim = (int) max(3.0f, GAUSSKERN * sigma);
	int i, j;
	// make dim odd
	if (dim % 2 == 0)
		dim++;


	//printf("GaussianKernel(): Creating %dx%d matrix for sigma=%.3f gaussian\n", dim, dim, sigma);

	vector<vector<float> > mat;

	for (i = 0; i < dim; i++) {
		vector<float> row(dim);
		mat.push_back(row);
	}

	float s2 = sigma * sigma;

	int c = dim / 2;
  
	//printf("%d %d\n", mat.size(), mat[0].size());

	for (i = 0; i < (dim + 1) / 2; i++) {
		for (j = 0; j < (dim + 1) / 2; j++) {

			//printf("%d %d %d\n", c, i, j);

			float v = 1 / (2 * PI * s2) * exp(-(i*i + j*j) / (2 * s2));
			mat[c+i][c+j] = v;
			mat[c-i][c+j] = v;
			mat[c+i][c-j] = v;
			mat[c-i][c-j] = v;

			/*
			cvmSet(mat, c + i, c + j, v);
			cvmSet(mat, c - i, c + j, v);
			cvmSet(mat, c + i, c - j, v);
			cvmSet(mat, c - i, c - j, v);
			*/
		}
	}
	
	normalizeMat(mat);
	
	//printf("Done\n");
	//printmat(mat);

	return mat;
}




