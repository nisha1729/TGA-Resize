#include "halfsize.h"
#include <fstream>

void tga::resizeTGA(char *fileName, char *newFileName)
{
	std::ifstream tgaFile;
	tgaFile.open(fileName, std::ios::in | std::ios::binary);
	if (!tgaFile)
		printf("\nError : Could not open file %s\n", fileName);
	else{
        int width, height;
		int i,j;
		printf("\nReading '%s'...", fileName);
        tgaFile.seekg(0, std::ios::beg);
		tgaFile.read(&tgaHeader.idLength, sizeof(tgaHeader.idLength));
		tgaFile.read(&tgaHeader.colourMapType, sizeof(tgaHeader.colourMapType));
		tgaFile.read(&tgaHeader.imageType, sizeof(tgaHeader.imageType));

		// If colourMapType is 0 and these 3 fields below are not 0, something may have went wrong
		tgaFile.read((char*)(&tgaHeader.rangeStart), sizeof(tgaHeader.rangeStart));
		tgaFile.read((char*)(&tgaHeader.palletLength), sizeof(tgaHeader.palletLength));
		tgaFile.read(&tgaHeader.palletEntrySize, sizeof(tgaHeader.palletEntrySize));

		tgaFile.read((char*)(&tgaHeader.xOrigin), sizeof(tgaHeader.xOrigin));
		tgaFile.read((char*)(&tgaHeader.yOrigin), sizeof(tgaHeader.yOrigin));
		tgaFile.read((char*)(&tgaHeader.imageWidth), sizeof(tgaHeader.imageWidth));
		tgaFile.read((char*)(&tgaHeader.imageHeight), sizeof(tgaHeader.imageHeight));
		tgaFile.read(&tgaHeader.bitsperPixel, sizeof(tgaHeader.bitsperPixel));
		tgaFile.read(&tgaHeader.screenAttribute, sizeof(tgaHeader.screenAttribute));

        if ((tgaHeader.imageType == 2)){
			printf("\n\nImage Information:");
			printf("\nUnmapped %d bit uncompressed", tgaHeader.bitsperPixel);
			printf("\nOriginal size: %d x %d",tgaHeader.imageWidth,tgaHeader.imageHeight);

			width = tgaHeader.imageWidth;
			height = tgaHeader.imageHeight;

			char *skip = "";
			tgaFile.read(skip, tgaHeader.idLength);
			if (!(tgaHeader.colourMapType)){
				int colourMapSize = tgaHeader.colourMapType * tgaHeader.palletLength;
				tgaFile.read(skip, colourMapSize);
			}
						
			int imageDataSize = tgaHeader.imageWidth*tgaHeader.imageHeight;	
			TGAData tgaData[imageDataSize];

			for(i=0;i<imageDataSize;i++){
				tgaFile.read(&tgaData[i].r,sizeof(tgaData[i].r));
				tgaFile.read(&tgaData[i].g,sizeof(tgaData[i].r));
				tgaFile.read(&tgaData[i].b,sizeof(tgaData[i].r));
				if(tgaHeader.bitsperPixel==32)
					tgaFile.read(&tgaData[i].a,sizeof(tgaData[i].a));
			}

			// Rescaling the images
			printf("\n\nResizing to %d x %d...", width/2, height/2);
			TGAData newData[imageDataSize/4];

			for(i=0;i<imageDataSize/4;i++){
				if((2*i)%width==0)
					j = 4*i;
				else
					j = (i/(width/2))*2*width + 2*(i%(width/2));

				//  Going aheaed with max pooling as it is more asthetically pleasing
				newData[i].r = std::max(std::max(std::max(tgaData[j].r, tgaData[j+1].r), tgaData[j+width].r),tgaData[j+width+1].r);
				newData[i].g = std::max(std::max(std::max(tgaData[j].g, tgaData[j+1].g), tgaData[j+width].g), tgaData[j+width+1].g);
				newData[i].b = std::max(std::max(std::max(tgaData[j].b, tgaData[j+1].b), tgaData[j+width].b), tgaData[j+width+1].b);
				if(tgaHeader.bitsperPixel==32)
					newData[i].a = std::max(std::max(std::max(tgaData[j].a, tgaData[j+1].a), tgaData[j+width].a), tgaData[j+width+1].a);
			}

			tgaHeader.imageHeight/=2;
			tgaHeader.imageWidth/=2;

			// Saving the file to newFilName(.tga)
			printf("\nSaving '%s'...",newFileName);
			std::ofstream tgaNew (newFileName);
			if (!tgaNew.is_open())
				printf("\nUnable to open file\n");
			else{
				// tgaFile.seekg( 0, std::ios::beg );
				tgaNew.write(&tgaHeader.idLength, sizeof(tgaHeader.idLength));
				tgaNew.write(&tgaHeader.colourMapType,sizeof(tgaHeader.colourMapType));
				tgaNew.write(&tgaHeader.imageType,sizeof(tgaHeader.imageType));

				// If colourMapType is 0 and these 3 fields below are not 0, something may have went wrong
				tgaNew.write((char*)(&tgaHeader.rangeStart),sizeof(tgaHeader.rangeStart));
				tgaNew.write((char*)(&tgaHeader.palletLength), sizeof(tgaHeader.palletLength));
				tgaNew.write(&tgaHeader.palletEntrySize, sizeof(tgaHeader.palletEntrySize));


				tgaNew.write((char*)(&tgaHeader.xOrigin), sizeof(tgaHeader.xOrigin));
				tgaNew.write((char*)(&tgaHeader.yOrigin), sizeof(tgaHeader.yOrigin));
				tgaNew.write((char*)(&tgaHeader.imageWidth), sizeof(tgaHeader.imageWidth));
				tgaNew.write((char*)(&tgaHeader.imageHeight), sizeof(tgaHeader.imageHeight));
				tgaNew.write(&tgaHeader.bitsperPixel, sizeof(tgaHeader.bitsperPixel));
				tgaNew.write(&tgaHeader.screenAttribute, sizeof(tgaHeader.screenAttribute));

				for(i=0;i<imageDataSize/4;i++){
					tgaNew.write(&newData[i].r,sizeof(newData[i].r));
					tgaNew.write(&newData[i].g,sizeof(newData[i].g));
					tgaNew.write(&newData[i].b,sizeof(newData[i].b));
					if(tgaHeader.bitsperPixel==32)
						tgaNew.write(&newData[i].a,sizeof(newData[i].a));
				}
				printf("\nDone.\n");
				tgaNew.close();
			}				
		}	
	}	
	tgaFile.close();
}