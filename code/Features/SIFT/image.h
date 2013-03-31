/* -*-  Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */

/*

Author: Yan Ke
Dec 2003

*/

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
using namespace std;
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define round(a) ((int)((a) + 0.5))
typedef unsigned int gray;


/**
 * Image class
 */
class Image {
private:
	/**
	 * Allocates memory for new image
	 *
	 * @param width width in pixels of new image
	 * @param height height in pixels of new image
	 */

	void newImage(int width, int height);

public:
	
	int width; ///< Width of image in pixels
	int height; ///< Height of image in pixels
	float ** pix; ///< Storage of image


	/**
	 * Constructs new black image.
	 * 
	 * @param width width in pixels of new image
	 * @param height height in pixels of new image
	 */
	Image(int width, int height);

	/** 
	 * Constructs new image with existing data.
	 * Copies new_data into own data structure.
	 * 
	 * @param width width in pixels of new image
	 * @param height height in pixels of new image
	 * @param new_data image data to copy.
	 */
	Image(int width, int height, float * new_data);

	/**
	 * Constructs new image from file (PGM only).
	 */
	Image(const char * filename);

	~Image();

	/**
	 * Clones a copy of the image.
	 * @return Cloned copy.
	 */
	Image * clone();

	/**
	 * Returns a new image that's half the size of the current image.
	 * Rounds image sizes down.  Does not antialiase in any way.
	 * @return New half sized image
	 */
	Image * halfSizeImage();

	/**
	 * Returns a new image that's double the size of the current image.
	 * Does not antialiase in any way.
	 * @return New double sized image
	 */
	Image * doubleSizeImage();

	/**
	 * Returns a new image that's almost double the size of the current image.
	 * Bilinear interpolate between pixels
	 * @return New double sized image
	 */
	Image * doubleSizeImage2();

	/**
	 * Subtracts two images.
	 * dst = this_image - im2.
	 * 
	 * @param im2 Image to subtract
	 * @param dst Destination image.
	 */
	void sub(Image * im2, Image * dst);

	/**
	 * Write image to a file (PGM only).
	 *
	 * @param filename File name for output.
	 */
	void write(const char * filename);

	/**
	 * Sets pixel to a value.
	 * Does NOT check for bounds.
	 *
	 * @param x x pixel location
	 * @param y y pixel location
	 * @param val Value to set.
	 */
	void setPixel(int x, int y, float val);
	
	/**
	 * Gets the value of a pixel at a location.
	 * Does NOT check for bounds.
	 *
	 * @param x x pixel location
	 * @param y y pixel location
	 * @return pixel value
	 */
	float getPixel(int x, int y);

	/** Gets the value of a pixel at a location with bilinear interpolation.
	 * If location is out of bounds, then return value of closest pixel.
	 *
	 * @param x x pixel location
	 * @param y y pixel location
	 * @return pixel value
	 */
	float getPixelBI(float x, float y);
};

/**
 * Does Gaussian smoothing of an image.
 * 
 * @param src Source image
 * @param dst Destination image
 * @param sigma Sigma of Gaussian weighting function.
 */
void BlurImage(Image * src, Image * dst, float sigma);

/**
 * Calculates a 2D Gaussian kernel
 * 
 * @param sigma Sigma of Gaussian weighting function.
 * @return 2D matrix of kernel.
 */

vector<vector<float> > GaussianKernel2D(float sigma);

void GaussianBlur(Image * image, float sigma);

#endif
