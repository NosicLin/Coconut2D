﻿/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ***** END LICENSE BLOCK ***** */

// ==================================================================================================================================
//	    ____     ______            __  ______
//	   / __/  __/ ____/___  ____  / /_/ ____/___ _________
//	  / /_| |/_/ /_  / __ \/ __ \/ __/ /_  / __ `/ ___/ _ \
//	 / __/>  </ __/ / /_/ / / / / /_/ __/ / /_/ / /__/  __/
//	/_/ /_/|_/_/    \____/_/ /_/\__/_/    \__,_/\___/\___/
//
// ==================================================================================================================================

#ifndef _fxFontFace_h
#define _fxFontFace_h

#include "AssetFile.h"

#ifdef ENABLE_FREETYPE_SUPPORT

class fxFontFace
{
public:
	enum FONT_STYLE {
		None,
		Normal,
		Oblique,
		Bold,
		BoldOblique
	};
private:
    static FT_Library ftLibrary;
    static std::map<fxFontFace, FT_Face, fxFontFace> fonts;
protected:
	std::string name;
	FONT_STYLE style;
public:
	bool operator()(const fxFontFace& a, const fxFontFace& b) const
	{
		if(a.name < b.name) return true;
		if(a.style < b.style) return true;
		return false;
	}
    static void add(std::string name, FONT_STYLE style, const char* filename)
    {
		fxFontFace ff(name, style);
		if(fonts.find(ff) != fonts.end()) return;
		AssetFile* file = AssetFile::open(filename);
		if(!file) return;
		switch(file->mime)
		{
			case AssetFile::MIME::FONT_TTF:
			{
				FT_Face ftFace;
				int er = 0;
				if((er = FT_New_Memory_Face(ftLibrary, (const FT_Byte*)file->getData(), file->getLength(), 0, &ftFace)))
				{
					trace("Could not load FreeType Face(%d)!", er);
				}
				fonts.insert(std::pair<fxFontFace, FT_Face>(ff, ftFace));
				break;
			}
			default:
				trace("Unsupported font type!");
				return;
		}

        //trace("@font-face %s loaded", name);
    }
    static FT_Face get(std::string name, FONT_STYLE style)
    {
		fxFontFace ff(name, style);
        std::map<fxFontFace, FT_Face, fxFontFace>::iterator it = fonts.find(ff);
        if(it != fonts.end()) return it->second;
        return nullptr;
    }
    static void init()
    {
        if(FT_Init_FreeType(&ftLibrary)) { trace("Could not initialize FreeType library!"); }
        else { trace("FreeType OK!"); }
    }
    static void quit()
    {
        std::map<fxFontFace, FT_Face, fxFontFace>::iterator it = fonts.begin();
        while(it != fonts.end()) FT_Done_Face((it++)->second);
        fonts.clear();
        FT_Done_FreeType(ftLibrary);
    }

	fxFontFace(std::string i_name, FONT_STYLE i_style) : name(i_name), style(i_style) {}
	fxFontFace() : name(""), style(FONT_STYLE::None) {}
};
#else

class fxFontFace : public AssetFile
{
public:
    static void add(const char* name, FONT_STYLE style, const char* filename) { trace("Fonts not supported!"); }
    static const FT_Face* get(const char* name, FONT_STYLE style) { trace("Fonts not supported!"); return nullptr; }
    static void init() { trace("Fonts not supported!"); }
    static void quit(){ trace("Fonts not supported!"); }

	fxFontFace(const char* i_name, FONT_STYLE i_style) : name(i_name), style(i_style) {}
    inline void getFace() const { trace("Fonts not supported!"); }
    inline bool hasKerning() const { trace("Fonts not supported!"); return false; }
};

#endif /* ENABLE_FREETYPE_SUPPORT */

#endif


