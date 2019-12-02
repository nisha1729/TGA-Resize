#ifndef HALFSIZE_H
#define HALFSIZE_H

class tga
{	
	typedef struct
	{
		char idLength;
		char colourMapType;
		char imageType;
		
        //Color Map Specification:
		short rangeStart;	//word
		short palletLength;	//word
		char palletEntrySize;
		
        //image specification
		short xOrigin;		//word
		short yOrigin;		//word
		short imageWidth;	//word
		short imageHeight;	//word

		char bitsperPixel;
		char screenAttribute;
	} TGAHeader;
	
	typedef struct
	{
		// Image Data: Pixel RBG(A) values
		char r,g,b,a;
	} TGAData;
	
	TGAHeader tgaHeader;	
	public: 
		void resizeTGA(char*,char*);
};

#endif	//HALFSIZE_H
