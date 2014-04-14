﻿#ifndef __COCOTEXT_HPP__
#define __COCOTEXT_HPP__

#include "Coconut2D.hpp"

class CocoTextStyle
{
public:
	String fontFamily;
	int fontSizePixels;
	String fontStyle;
	String fontWeight;
	bool underline;
	Array<int>* color;
	Array<int>* bgcolor;
	CocoTextStyle(String ff, int fsp, String fs, String fw, bool u, int r, int g, int b, int a, int br, int bg, int bb, int ba);
	~CocoTextStyle();
};

class CocoText
{
public:
	static CanvasRenderingContext2D* c2d;
	String str;
	Array<CocoTextStyle*>* styles;
	Array<int>* indices;
	Array<int>* mappings;
	Array<int>* lineBreaks;
	Array<int>* lineWidths;
	Array<int>* lineHeights;
	int totalHeight;
	static int npo2(int i);
	static void init(int width, int height);
	CocoText();
	~CocoText();
	void wrap(int width);
	String draw(float width, float height, float halign, float valign, int bgR, int bgG, int bgB, int bgA);
};

#endif
