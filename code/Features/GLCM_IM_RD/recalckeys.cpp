
/* -*-  Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */

/*

Author: Yan Ke
Dec 2003

*/
#include "stdafx.h"

#include <stdio.h>

#include "config.h"
#include "image.h"
#include "keypoint.h"

int main(int argc, char* argv[])
{
	if (argc != 5 ) {
                printf("Usage: %s gpcavects.txt image.pgm in.keys out.keys\n", argv[0]);
                return -1;
        }

	char * gpcafn = argv[1];
	char * imagefn = argv[2];
	char * inkeysfn = argv[3];
	char * outkeysfn = argv[4];

	Image * im = new Image(imagefn);

	printf("%d %d\n", im->width, im->height);
	
	KeypointDetector kpd(gpcafn);

	vector<Keypoint *> keys = kpd.readKeysFromFile(inkeysfn);
	
	printf("Read %d keys\n", keys.size());
	
	kpd.RecalcKeys(im, keys);

	kpd.writeKeysToFile(keys, outkeysfn);

	delete(im);
	
	return 0;
}
