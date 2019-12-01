// #include <iostream>
// #include <fstream>

// using namespace std;
// int main()
// {
//     ifstream img;
//     string line;
//     img.open("original.tga");

//     if (img.is_open()) {
// 		img.close();
// 		cout<<"Opening .tga file\n";
//         while(getline(img,line)){
//             cout<<line<<'\n';
//         }
// 	} 
//     else {
// 		cout<<"unable to open file";
// 	}
    
//     return 0;
// }


#include "halfsize.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <vector>
// using namespace TGA;

void tga::resizeTGA(char *fileName, char *newFileName)
{
	std::ifstream tgaFile;
	tgaFile.open( fileName, std::ios::in | std::ios::binary );
	if ( !tgaFile ){
		printf( "Error : Could not open file %s\n", fileName );

	}
	else{
        int width, height;
		int i,j;
		// unsigned char *pixels;
		printf( "\nOpened file %s succesfully", fileName );
        tgaFile.seekg( 0, std::ios::beg );
		tgaFile.read(&tgaHeader.idLength, sizeof(tgaHeader.idLength));
		tgaFile.read(&tgaHeader.colourMapType, sizeof( tgaHeader.colourMapType ) );
		tgaFile.read(&tgaHeader.imageType, sizeof( tgaHeader.imageType ) );

		// If colourMapType is 0 and these 3 fields below are not 0, something may have went wrong
		tgaFile.read( ( char* )( &tgaHeader.rangeStart ),	sizeof( tgaHeader.rangeStart ) );
		tgaFile.read( ( char* )( &tgaHeader.palletLength ),	sizeof( tgaHeader.palletLength ) );
		tgaFile.read(			 &tgaHeader.palletEntrySize,	sizeof( tgaHeader.palletEntrySize ) );


		tgaFile.read( ( char* )( &tgaHeader.xOrigin ),		sizeof( tgaHeader.xOrigin ) );
		tgaFile.read( ( char* )( &tgaHeader.yOrigin ),		sizeof( tgaHeader.yOrigin ) );
		tgaFile.read( ( char* )( &tgaHeader.imageWidth ),	sizeof( tgaHeader.imageWidth ) );
		tgaFile.read( ( char* )( &tgaHeader.imageHeight ),	sizeof( tgaHeader.imageHeight ) );
		tgaFile.read(			 &tgaHeader.bitsperPixel,	sizeof( tgaHeader.bitsperPixel ) );
		tgaFile.read(			 &tgaHeader.screenAttribute,sizeof( tgaHeader.screenAttribute ) );

        if(( tgaHeader.imageType == 2)){
			std::cout<<"\nRGB (24 or 32 bit) uncompressed";
			std::cout<<"\nHeader size: "<<sizeof(tgaHeader);	
			printf("\nID lenght: %d",tgaHeader.idLength);
			printf("\nColour map type: %d",tgaHeader.colourMapType);
			printf("\nType: %d",tgaHeader.imageType);
			printf("\nSize: %d",tgaHeader.bitsperPixel);
			width = tgaHeader.imageWidth;
			height = tgaHeader.imageHeight;

			printf("\nWidth = %d",tgaHeader.imageWidth);
			printf("\nHeight = %d",tgaHeader.imageHeight);

			// char *skip = "";
			// tgaFile.read(skip, tgaHeader.idLength);
			// // if (!( tgaDesc & TGA_MAP)){
			// int colourMapSize = tgaHeader.colourMapType * tgaHeader.palletLength;
			// tgaFile.read(skip, colourMapSize);
			// }
						
			int imageDataSize = tgaHeader.imageWidth*tgaHeader.imageHeight;	
			// char pixels[imageDataSize];
			// char newPixels[imageDataSize/4];

			// int originalPosition = ( int )tgaFile.tellg(  );
			// tgaFile.read(pixels, imageDataSize);
			
			std::cout<<"\nBits per pixel: "<<(int)tgaHeader.bitsperPixel;
			TGAData tgaData[imageDataSize];
			std::cout<<"\nImageDataSize: "<<imageDataSize;

			//TODO: tgaData[i] is being updated only at multiples of 3, fix it

			for(i=0;i<imageDataSize;i++){
				tgaFile.read(&tgaData[i].r,sizeof(tgaData[i].r));
				tgaFile.read(&tgaData[i].g,sizeof(tgaData[i].r));
				tgaFile.read(&tgaData[i].b,sizeof(tgaData[i].r));

				// printf("\n%d ",pixels[i]);
				// if (((i)%3)==0){
				// 	tgaData[i].r = pixels[i-3];
				// 	tgaData[i].g = pixels[i-2];
				// 	tgaData[i].b = pixels[i-1];
					// std::cout<<"\n "<<(int)tgaData[i].r<<" "<<(int)tgaData[i].g<<" "<<(int)tgaData[i].b;
					// exit(0);
				// }
			}
			// std::cout<<"\nhello";

			// Rescaling the images, taking the 
			// average of four neighbouring pixels
			int j = 0;
			TGAData newData[imageDataSize/4];
			for(i=0;i<imageDataSize/4;i++){
				if((2*i)%width==0)
					int j = 4*i;
				else	
					int j = (i%(width/2)+i%(height/2))*(2*i/width)*width;
				newData[i].r = (tgaData[j + 2*i].r + tgaData[j+2*i+1].r + tgaData[j+width+2*i].r + tgaData[j+width+2*i+1].r)/4;
				newData[i].g = (tgaData[j + 2*i].g + tgaData[j+2*i+1].g + tgaData[j+width+2*i].g + tgaData[j+width+2*i+1].g)/4;
				newData[i].b = (tgaData[j + 2*i].b + tgaData[j+2*i+1].b + tgaData[j+width+2*i].b + tgaData[j+width+2*i+1].b)/4;
				// std::cout<<"\n "<<(int)newData[i].r<<" "<<(int)newData[i].g<<" "<<(int)newData[i].b;
				// std::cout<<i<<' ';

				//JUST NEED TO FIGURE OUT THE FORMULA
			}

			// for(i=0;i<imageDataSize/4;i++){
			// 	if (((i+3)%3)==0){
			// 		newPixels[i] = tgaData[i].r;
			// 		newPixels[i+1] = tgaData[i].g;
			// 		newPixels[i+2] = tgaData[i].b;
			// 	}
			// }


			tgaHeader.imageHeight/=2;
			tgaHeader.imageWidth/=2;

			// Saving the file to newFilName(.tga)
			std::ofstream tgaNew (newFileName);
			if (tgaNew.is_open()){
				// tgaFile.seekg( 0, std::ios::beg );
				tgaNew.write(			 &tgaHeader.idLength,		sizeof( tgaHeader.idLength ) );
				tgaNew.write(			 &tgaHeader.colourMapType,	sizeof( tgaHeader.colourMapType ) );
				tgaNew.write(			 &tgaHeader.imageType,		sizeof( tgaHeader.imageType ) );

				// If colourMapType is 0 and these 3 fields below are not 0, something may have went wrong
				tgaNew.write( ( char* )( &tgaHeader.rangeStart ),	sizeof( tgaHeader.rangeStart ) );
				tgaNew.write( ( char* )( &tgaHeader.palletLength ),	sizeof( tgaHeader.palletLength ) );
				tgaNew.write(			 &tgaHeader.palletEntrySize,	sizeof( tgaHeader.palletEntrySize ) );


				tgaNew.write( ( char* )( &tgaHeader.xOrigin ),		sizeof( tgaHeader.xOrigin ) );
				tgaNew.write( ( char* )( &tgaHeader.yOrigin ),		sizeof( tgaHeader.yOrigin ) );
				tgaNew.write( ( char* )( &tgaHeader.imageWidth ),	sizeof( tgaHeader.imageWidth ) );
				tgaNew.write( ( char* )( &tgaHeader.imageHeight ),	sizeof( tgaHeader.imageHeight ) );
				tgaNew.write(			 &tgaHeader.bitsperPixel,	sizeof( tgaHeader.bitsperPixel ) );
				tgaNew.write(			 &tgaHeader.screenAttribute,sizeof( tgaHeader.screenAttribute ) );
				// tgaNew.write( newPixels, imageDataSize/4);
				for(i=0;i<imageDataSize/4;i++){
					tgaNew.write(&newData[i].r,sizeof(newData[i].r));
					tgaNew.write(&newData[i].g,sizeof(newData[i].g));
					tgaNew.write(&newData[i].b,sizeof(newData[i].b));
				}
				printf("\nFile saved");
				tgaNew.close();
			}
			else std::cout<<"Unable to open file";

			// printf("\nHeight: ");
			// for(i=0;i<2;i++){
			// 	printf("%d",tgaHeader.imageHeight[i]);
			// }

			// newHeight = (int) (tgaHeader.imageHeight[0] + tgaHeader.imageHeight[1])/2;
			// printf("\nNewHeight: %d", newHeight);


			printf("\n");
		}	
	}
	
	
	// else if( ( tgaHeader.imageType == 10 ) ){
	// 	LoadCompressedTexture( &tgaHeader, &file );
	// }
	
	tgaFile.close();
}



// void LoadTexture::LoadUncompressedTexture( TGAHeader *tgaHeader, std::fstream *file )
// {
// 	printf( "Loading uncompressed tga image\n" );
// }

// void LoadTexture::LoadCompressedTexture( TGAHeader *tgaHeader, std::fstream *file )
// {
// 	printf( "Loading compressed tga image\n" );
// }