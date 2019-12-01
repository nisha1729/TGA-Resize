#ifndef HALFSIZE_H
#define HALFSIZE_H

class tga
{
	// public:
	// tga();
	// ~tga();
	
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
		short xOrigin;	//2
		short yOrigin;	//2
		short imageWidth;	//2
		short imageHeight;	//2

		char bitsperPixel;
		char screenAttribute;
	} TGAHeader;
	
	typedef struct
	{
		// char *imageData;
		char r,g,b;
		// unsigned int  bitDepth;
		// unsigned int  width;
		// unsigned int  height;
		// unsigned int  texID;
		// unsigned int  type;
	} TGAData;
	
	TGAHeader tgaHeader;
	
	public: 
		void resizeTGA(char*,char*);
	// void LoadUncompressedTexture( TGAHeader *, std::fstream * );
	// void LoadCompressedTexture( TGAHeader *, std::fstream * );
};

// } // namespace TGA

#endif	//TARGA_H
