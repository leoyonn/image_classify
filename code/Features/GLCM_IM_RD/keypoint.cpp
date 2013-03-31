/* -*-  Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */
/*
Author: Yan Ke
Dec 2003
*/
#include "stdafx.h"

#include <math.h>

#include "keypoint.h"
#include <assert.h>

#define PI 3.14159265358979323846


/**
   Keypoint window sample size is PatchMag * scale
   Smallest scale is typically around 2.0, so window size
   is at least 40.
*/
#define PatchMag 20


/**
   Sigma of base image -- See D.L.'s paper.
*/
#define INITSIGMA 0.5

/**
   Sigma of each octave -- See D.L.'s paper.
*/
#define SIGMA 1.6

/**
   Number of scales per octave.  See D.L.'s paper.
*/
#define SCALESPEROCTAVE 3
#define MAXOCTAVES 14


/**
   Double image size before looking searching for keypoints
   Doubling finds more keypoints, but takes longer. See
   D.L.'s paper.
*/
#define DOUBLE_BASE_IMAGE_SIZE 1


void Normvec(float * v, unsigned int len) {
	float total = 0;
	

	for (unsigned int i = 0; i < len; i++) {
		total += fabs(v[i]);
	}
	

	total /= len;

	
	for (unsigned int i = 0; i < len; i++) {
		v[i] = v[i] / total * 100.0;
	}	
}

KeypointDetector::KeypointDetector(char * fn) {
	assert(fn);

	FILE * pcaf = fopen(fn, "rb");

	printf("Reading averages\n");
 
        for (int i = 0; i < GPLEN; i++) {
                float val;
                if (fscanf(pcaf, "%f", &val) != 1) {
                       printf("Invalid pca vector file (avg).\n");
		       exit(1);

		}
                avgs[i] = val;
        }
 
        printf("Reading pca vector %dx%d\n", GPLEN, PCALEN);
 
        // read in vector, transposed
 
        for (int i = 0; i < GPLEN; i++) {
                for (int j = 0; j < PCALEN; j++) {
 
                        float val;
                        if (fscanf(pcaf, "%f", &val) != 1) {
                                printf("Invalid pca vector file (eig).\n");
				exit(1);
			}
                        
			if (j < EPCALEN)
				eigs[j][i] = val;
                }
        }
 
        fclose(pcaf);


}



void KeypointDetector::MakeKeypointPatch(Keypoint * key, Image * blur, float v[GPLEN])
{
	assert(key);
	assert(blur);

	int patchsize;
	int iradius;
	float  sine, cosine;
	float sizeratio;
	
	float scale = SIGMA * pow(2.0, key->fscale / (float) SCALESPEROCTAVE);


	// sampling window size
	patchsize = (int) (PatchMag * scale);
	
	// make odd
	patchsize /= 2;
	patchsize = patchsize * 2 + 1;
	
	if (patchsize < PatchSize)
		patchsize = PatchSize;
	
	sizeratio = (float) patchsize / (float) PatchSize;
	
	Image * win = new Image(patchsize, patchsize);
	
	sine = sin(key->ori);
	cosine = cos(key->ori);
	
	iradius = patchsize / 2;
	
	/* Examine all points from the gradient image that could lie within the
	   index square.
	*/
	
	//fprintf(stderr, "Scale %f  %d\n", scale, patchsize);
	
	//fprintf(stderr, "Key Patch of orientation %f\n", key->ori);
	for (int y = -iradius; y <= iradius; y++)
		for (int x = -iradius; x <= iradius; x++) {
			
			// calculate sample window coordinates (rotated along keypoint)
			float cpos = ((cosine * x + sine * (float) y) + key->sx);
			float rpos = ((-sine * x + cosine * (float) y) + key->sy);
			
			win->setPixel(x + iradius, y + iradius, blur->getPixelBI(cpos, rpos));
			
			//fprintf(stderr, "  (%d, %d) -> (%f, %f)\n", j, i, cpos, rpos);
		}
	
	int count = 0;

	for (int y = 1; y < PatchSize - 1; y++) {
		for (int x = 1; x < PatchSize - 1; x++) {
			float x1 = win->getPixelBI((float) (x+1) * sizeratio, (float) y * sizeratio);
			float x2 = win->getPixelBI((float) (x-1) * sizeratio, (float) y * sizeratio);
			
			float y1 = win->getPixelBI((float) x * sizeratio, (float) (y + 1) * sizeratio);
			float y2 = win->getPixelBI((float) x * sizeratio, (float) (y - 1) * sizeratio);
			
			// would need to divide by 2 (span 2 pixels), but we normalize anyway
			// so it's not necessary
			float gx = x1 - x2;
			float gy = y1 - y2;


			v[count] = gx;
			v[count + 1] = gy;

			count += 2;
		}
		//fprintf(stderr, "\n");
	}
	
}



void KeypointDetector::MakeKeypointPCA(Keypoint * key, Image * blur) {
	assert(key);
	assert(blur);

	float v[GPLEN];
	MakeKeypointPatch(key, blur, v);

	Normvec(v, GPLEN);

	
	for (unsigned int i = 0; i < GPLEN; i++) {
		v[i] -= avgs[i];
	}

	for (int ldi = 0; ldi < EPCALEN; ldi++) {
		key->ld[ldi] = 0;

		for (int x = 0; x < GPLEN; x++)
			key->ld[ldi] += eigs[ldi][x] * v[x];
	}
}

void KeypointDetector::ComputeLocalDescr(vector<Keypoint *> & kps, vector<vector<Image *> > & LOctaves) {
	printf("ComputeLocalDescr(): Computing local descriptors.\n");

	for (unsigned int i = 0; i < kps.size(); i++) {
                MakeKeypointPCA(kps[i], LOctaves[kps[i]->octave][kps[i]->scale]);
	}
}


vector<vector<Image *> > KeypointDetector::BuildGaussianOctaves(Image * image) {
	assert(image);

	vector<vector<Image *> > octaves;
	
	printf("BuildGaussianOctaves(): Base image dimension is %dx%d\n", image->width, image->height);
	int dim = min(image->height, image->width);
	int numoctaves = int (log((double) dim) / log(2.0)) - 2;
	
	numoctaves = min(numoctaves, MAXOCTAVES);
	
	printf("BuildGaussianOctaves(): Building %d octaves\n", numoctaves);

        // start with initial source image
	Image * timage = image->clone();

	for (int i = 0; i < numoctaves; i++) {
		printf("Building octave %d of dimesion (%d, %d)\n", i, timage->width, timage->height);
		vector<Image *> scales = BuildGaussianScales(timage);
		octaves.push_back(scales);

		// halve the image size for next iteration
		Image * simage  = scales[SCALESPEROCTAVE]->halfSizeImage();
		delete timage;
		timage = simage;

	}

	delete timage;

	return octaves;
}

vector<Image *> KeypointDetector::BuildGaussianScales(Image * image) {
	assert(image);

	vector<Image *> GScales;

	//printf("Building scales of dimension (%d, %d)\n", image->width, image->height);

	double k = pow(2, 1.0/(float)SCALESPEROCTAVE);
	
	GScales.push_back(image->clone());

	for (int i =  1; i < SCALESPEROCTAVE + 3; i++) {
		Image * dst = new Image(image->width, image->height);
		//Image * dst = GScales[GScales.size() - 1]->clone();

		// 2 passes of 1D on original
		float sigma1 = pow(k, i - 1) * SIGMA;
		float sigma2 = pow(k, i) * SIGMA;
		float sigma = sqrt(sigma2*sigma2 - sigma1*sigma1);
		
		//printf("Blur %f\n", sigma);
		BlurImage(GScales[GScales.size() - 1], dst, sigma);
		

		GScales.push_back(dst);
	}

	return GScales;
}



Image * KeypointDetector::ScaleInitImage(Image * image) {
	assert(image);

	Image * dst;

	if (DOUBLE_BASE_IMAGE_SIZE) {
		Image * im = image->doubleSizeImage2();
		dst = new Image(im->width, im->height);
		//dst = im->clone();
		double sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA * 4);
		//printf("Init Sigma: %f\n", sigma);
		BlurImage(im, dst, sigma);
		
		delete im;
	} else {
		dst = new Image(image->width, image->height);
		double sigma = sqrt(SIGMA * SIGMA - INITSIGMA * INITSIGMA);
		//printf("Init Sigma: %f\n", sigma);
		BlurImage(image, dst, sigma);
	}

	return dst;
}




void KeypointDetector::RecalcKeyIndices(vector <Keypoint *> & keys) {
	float log2 = log(2);

	for (unsigned int i = 0; i < keys.size(); i++) {
		
		Keypoint * k = keys[i];

		/* need to recalc:
		   sx, sy, octave, scale, fscale
		*/
		//printf("gscale %f\n", k->gscale);
		
		float tmp = log(k->gscale/SIGMA) / log2 + 1.0;
		//printf("  tmp %f\n", tmp);

		k->octave = (int) tmp;

		//printf("  octave %d\n", k->octave);
		k->fscale = (tmp - k->octave) * (float) SCALESPEROCTAVE;
		//printf("  fscale %f\n", k->fscale);

		k->scale = (int) round(k->fscale);

		if (k->scale == 0 && k->octave > 0) {
			k->scale = SCALESPEROCTAVE;
			k->octave--;
			k->fscale += SCALESPEROCTAVE;
		}
			
		//printf("  scale %d\n", k->scale);

		k->sx = k->x / pow(2.0, k->octave);
		k->sy = k->y / pow(2.0, k->octave);

		if (DOUBLE_BASE_IMAGE_SIZE) {
			k->sx *= 2.0;
			k->sy *= 2.0;
			k->x *= 2.0;
			k->y *= 2.0;
		}
		
		//printf("(%f, %f) -> (%f, %f)\n", k->x, k->y, k->sx, k->sy);
	}
}

void KeypointDetector::RecalcKeys(Image * im, vector <Keypoint *> & keys) {
	assert(im);
	Image * image = ScaleInitImage(im);

	vector<vector<Image *> > GOctaves = BuildGaussianOctaves(image);
	//vector<vector<Image *> > DOctaves = BuildDOGOctaves(GOctaves);

	RecalcKeyIndices(keys);

        ComputeLocalDescr(keys, GOctaves);

	delete image;

}

void KeypointDetector::MakeLocalPatch(Keypoint * key, Image * blur, int windowsize)
{
        assert(key);
        assert(blur);
                                                                                                                       
        int patchsize;
        int iradius;
        float sine, cosine;
        float sizeratio;
                                                                                                                       
        float scale = SIGMA * pow(2.0, key->fscale / (float) SCALESPEROCTAVE);
                                                                                                                       
                                                                                                                       
        // sampling window size
        patchsize = (int) (PatchMag * scale);
                                                                                                                       
        // make odd
        patchsize /= 2;
        patchsize = patchsize * 2 + 1;
                                                                                                                       
        /* The following two lines are not entirely correct.
           In theory, patchsize should never be smaller than PatchSize.
           If it is, then PatchMag isn't set large enough, or PatchSize is set too small.
           It's kept here for compatibility, and is a bug.
           It should eventually be removed.
        */
        if (patchsize < PatchSize)
                patchsize = PatchSize;
                                                                                                                       
        sizeratio = (float) patchsize / (float) PatchSize;
                                                                                                                       
        key->patch = new Image(windowsize, windowsize);
                                                                                                                       
        sine = sin(key->ori);
        cosine = cos(key->ori);
                                                                                                                       
        iradius = windowsize / 2;
                                                                                                                       
                                                                                                                       
        //fprintf(stderr, "Scale %f  %d\n", scale, patchsize);
                                                                                                                       
        //fprintf(stderr, "Key Patch of orientation %f\n", key->ori);
        for (int y = -iradius; y <= iradius; y++) {
                for (int x = -iradius; x <= iradius; x++) {
                                                                                                                       
                        // calculate sample window coordinates (rotated along keypoint)
                        float cpos = ((cosine * x * sizeratio
                                       + sine * (float) y * sizeratio) + key->sx);
                        float rpos = ((-sine * x * sizeratio
                                       + cosine * (float) y * sizeratio) + key->sy);
                                                                                                                       
                        key->patch->setPixel(x + iradius, y + iradius, blur->getPixelBI(cpos, rpos));
                                                                                                                       
                        //fprintf(stderr, "  (%d, %d) -> (%f, %f)\n", j, i, cpos, rpos);
                }
        }
 
}
 


void KeypointDetector::ComputeLocalPatches(vector<Keypoint *> & kps, vector<vector<Image *> > & LOctaves, int patchsize) {
        printf("ComputeLocalDescr(): Computing local patches.\n");
 
        for (unsigned int i = 0; i < kps.size(); i++) {
                assert(kps[i]->octave >= 0 && kps[i]->octave < (int) LOctaves.size());
                assert(kps[i]->scale >= 0 && kps[i]->scale < (int) LOctaves[kps[i]->octave].size());
 
 
                MakeLocalPatch(kps[i], LOctaves[kps[i]->octave][kps[i]->scale], patchsize);
        }
}


void KeypointDetector::writeKeysToFile(vector<Keypoint *> & keys, char * fn) {
	assert(fn);

	printf("Writing to %s\n", fn);
                                                                                
        FILE * fp = fopen(fn, "wb");

	/* Output total number of keypoints and VecLength. */
        fprintf(fp, "%d %d\n", keys.size(), EPCALEN);
                                                                                
        for (unsigned int i = 0; i < keys.size(); i++) {

		
		if (DOUBLE_BASE_IMAGE_SIZE) {
			// don't divide gscale by 2 here because we already did.
			fprintf(fp, "%4.2f %4.2f %4.3f %4.4f", keys[i]->y/2.0, keys[i]->x/2.0, keys[i]->gscale,
				keys[i]->ori);
		} else
			fprintf(fp, "%4.2f %4.2f %4.3f %4.4f", keys[i]->y, keys[i]->x,
				keys[i]->gscale, keys[i]->ori);
                                                                                
                for (int j = 0; j < EPCALEN; j++) {
                        if (j % 12 == 0)
                                fprintf(fp, "\n");
                        fprintf(fp, " %d", (int) keys[i]->ld[j]);
                }
                                                                                
                                                                                
                fprintf(fp, "\n");
        }
                                                                                
                                                                                
        fflush(fp);
        fclose(fp);

}


vector<Keypoint *> KeypointDetector::readKeysFromFile(char * filename)
{
	assert(filename);
	
	int num, pcalen;
	
	FILE * fp;
	vector<Keypoint *> keys;
	
	fp = fopen (filename, "rb");
	
	if (! fp) {
		fprintf(stderr, "Could not open file: %s", filename);
		exit(1);
	}         
	
	fscanf(fp, "%d %d", &num, &pcalen);
	

	for (int i = 0; i < num; i++) {
		/* Allocate memory for the keypoint. */
		Keypoint * key = new Keypoint(pcalen);
		
		if (fscanf(fp, "%f %f %f %f", &(key->y), &(key->x), &(key->gscale),
			   &(key->ori)) != 4) {
			fprintf(stderr, "Invalid keypoint file format.");
			exit(1);
		}
                                                                                
		for (int j = 0; j < pcalen; j++) {
			float fval;
			fscanf(fp, "%f", &fval);
			key->ld[j] = fval;
		}
		
		keys.push_back(key);
		
	}
	
	fclose(fp);
	
	return keys;
}



vector<Keypoint *> KeypointDetector::readPatchesFromFile(char * filename)
{
	assert(filename);
	
	int num, pcalen;
	
	FILE * fp;
	vector<Keypoint *> keys;
	
	fp = fopen (filename, "rb");
	
	if (! fp) {
		fprintf(stderr, "Could not open file: %s", filename);
		exit(1);
	}         
	
	fscanf(fp, "%d %d", &num, &pcalen);
	
	int sqrtlen = (int) sqrt(pcalen);

	if (sqrtlen * sqrtlen != pcalen) {
		fprintf(stderr, "Invalid patch file - dimensions incorrect: %d\n", pcalen);
		exit(1);
	}

	for (int i = 0; i < num; i++) {
		/* Allocate memory for the keypoint. */
		Keypoint * key = new Keypoint(0);
		
		if (fscanf(fp, "%f %f %f %f", &(key->y), &(key->x), &(key->gscale),
			   &(key->ori)) != 4) {
			fprintf(stderr, "Invalid keypoint file format.");
			exit(1);
		}

		key->patch = new Image(sqrtlen, sqrtlen);

		for (int y = 0; y < sqrtlen; y++) {
			for (int x = 0; x < sqrtlen; x++) {
				float fval;
				fscanf(fp, "%f", &fval);
				key->patch->setPixel(x, y, fval);
			}
		}
		
		keys.push_back(key);
		
	}
	
	fclose(fp);
	
	return keys;
}


void KeypointDetector::getPatches(Image * im, vector <Keypoint *> & keys, int patchsize) {
        assert(im);
        Image * image = ScaleInitImage(im);
 
        vector<vector<Image *> > GOctaves = BuildGaussianOctaves(image);
 
        RecalcKeyIndices(keys);
 
        ComputeLocalPatches(keys, GOctaves, patchsize);
 
        delete image;
 
}

 
void KeypointDetector::writePatchesToFile(vector<Keypoint *> & keys, char * fn, int patchsize) {
        assert(fn);
 
        printf("Writing to %s\n", fn);
                                                                                 
        FILE * fp = fopen(fn, "wb");
 
        /* Output total number of keypoints and VecLength. */
        fprintf(fp, "%d %d\n", keys.size(), patchsize * patchsize);
                                                                                 
        for (unsigned int i = 0; i < keys.size(); i++) {
 
                 
                if (DOUBLE_BASE_IMAGE_SIZE) {
                        // don't divide gscale by 2 here because we already did.
                        fprintf(fp, "%4.2f %4.2f %4.2f %4.3f\n",
                                keys[i]->y/2.0, keys[i]->x/2.0, keys[i]->gscale,
                                keys[i]->ori);
                } else
                        fprintf(fp, "%4.2f %4.2f %4.2f %4.3f\n",
                                keys[i]->y, keys[i]->x,
                                keys[i]->gscale, keys[i]->ori);
                           
                for (int y = 0; y < patchsize; y++) {
                        for (int x = 0; x < patchsize; x++)
                                fprintf(fp, "%0.4f ", keys[i]->patch->getPixel(x, y));
                        fprintf(fp, "\n");
 
                }
                 
        }
                                                                                 
                                                                                 
        fflush(fp);
        fclose(fp);
 
}
