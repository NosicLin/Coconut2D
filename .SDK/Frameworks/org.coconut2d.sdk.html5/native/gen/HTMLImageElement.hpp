/* Generated by Coconut2D C++ Compiler from file HTMLImageElement.jspp */

#ifndef __HTMLIMAGEELEMENT_HPP__
#define __HTMLIMAGEELEMENT_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"
#include "ImageData.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Image
{
public:
	ImageData* __imageData;
	String src;
	int width;
	int height;
	int naturalWidth;
	int naturalHeight;
	bool __complete;
	const String __className = String("Image");
	Image();
	virtual ~Image();
	void load(String url);
	bool __get_complete();
};

#endif // __HTMLIMAGEELEMENT_HPP__