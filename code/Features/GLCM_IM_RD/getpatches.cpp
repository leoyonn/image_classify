
/* -*-  Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */

/*

Author: Yan Ke
Dec 2003

*/

#include <stdio.h>

#include "config.h"
#include "image.h"
#include "keypoint.h"

int main(int argc, char* argv[])
{
	if (argc != 5) {
                printf("Usage: %s image.pgm in.keys out.keys patchsize\n", argv[0]);
                return -1;
        }

	char * imagefn = argv[1];
	char * inkeysfn = argv[2];
	char * outkeysfn = argv[3];
	int patchsize = atoi(argv[4]);

	if (patchsize % 2 == 0) {
		printf("Error: Patch size must be odd.\n");
		return -1;
	}

	Image * im = new Image(imagefn);

	printf("%d %d\n", im->width, im->height);
	
	vector<Keypoint *> keys = KeypointDetector::readKeysFromFile(inkeysfn);
	
	printf("Read %d keys\n", keys.size());
	
	KeypointDetector::getPatches(im, keys, patchsize);

	KeypointDetector::writePatchesToFile(keys, outkeysfn, patchsize);

	delete(im);
	
	return 0;
}
