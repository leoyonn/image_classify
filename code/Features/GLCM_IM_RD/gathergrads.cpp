
/* -*-  Mode:C++; c-basic-offset:8; tab-width:8; indent-tabs-mode:t -*- */

/*

Author: Yan Ke
Dec 2003

*/

#include <stdio.h>

#include "config.h"
#include "image.h"
#include "keypoint.h"


void writeGrads(vector<Keypoint *> & keys, FILE * fp) {
	
	for (unsigned int i = 0; i < keys.size(); i++) {
		int patchsize = keys[i]->patch->width;
		int gsize = (patchsize - 2) * (patchsize - 2) * 2;
		float v[gsize];
		int count = 0;

		for (int y = 1; y < patchsize - 1; y++) {
			for (int x = 1; x < patchsize - 1; x++) {
				float x1 = keys[i]->patch->getPixel(x + 1, y);
				float x2 = keys[i]->patch->getPixel(x - 1, y);
		
				float y1 = keys[i]->patch->getPixel(x, y + 1);
				float y2 = keys[i]->patch->getPixel(x, y - 1);
		
				// would normally divide by 2, but we normalize later
				float gx = x1 - x2;
				float gy = y1 - y2;

				v[count] = gx;
				v[count + 1] = gy;

				count += 2;
			}
			
		}

		Normvec(v, gsize);

		for (int j = 0; j < gsize; j++)
			fprintf(fp, "%4.2f ", v[j]);
		fprintf(fp, "\n");

	}
	
}

int main(int argc, char* argv[])
{
	if (argc != 3 ) {
                printf("Usage: %s patches.keys patches.txt\n", argv[0]);
                return -1;
        }


	char * inkeysfn = argv[1];
	char * outkeysfn = argv[2];

	vector<Keypoint *> keys = KeypointDetector::readPatchesFromFile(inkeysfn);
	
	printf("Read %d keys\n", keys.size());

	FILE * fp = fopen(outkeysfn, "wb+");
	writeGrads(keys, fp);
	fflush(fp);
	fclose(fp);


	return 0;
}
