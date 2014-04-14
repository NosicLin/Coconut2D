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

#include "fxFontFace.h"

#include "AssetFile.h"

#ifdef ENABLE_FREETYPE_SUPPORT
FT_Library fxFontFace::ftLibrary;
std::map<fxFontFace, FT_Face> fxFontFace::fonts;

bool fxFontFace::operator<(const fxFontFace& b) const
{
	if(name < b.name) return true;
	if(style < b.style) return true;
	return false;
}
void fxFontFace::add(std::string name, FONT_STYLE style, const char* filename)
{
	trace("fxFontFace::add(%s)", name.c_str());
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
			trace("Unsupported font type!\n");
			return;
	}

    //LOGI("@font-face %s loaded\n", name);
}
FT_Face fxFontFace::get(std::string name, FONT_STYLE style)
{
	fxFontFace ff(name, style);
    std::map<fxFontFace, FT_Face, fxFontFace>::iterator it = fonts.find(ff);
    if(it != fonts.end()) return it->second;
    return nullptr;
}
void fxFontFace::init()
{
    if(FT_Init_FreeType(&ftLibrary)) { trace("Could not initialize FreeType library!\n"); }
    else { trace("FreeType OK!\n"); }
}
void fxFontFace::quit()
{
    std::map<fxFontFace, FT_Face, fxFontFace>::iterator it = fonts.begin();
    while(it != fonts.end()) FT_Done_Face((it++)->second);
    fonts.clear();
    FT_Done_FreeType(ftLibrary);
}

fxFontFace::fxFontFace(std::string i_name, FONT_STYLE i_style) : name(i_name), style(i_style) {}
fxFontFace::fxFontFace() : name(""), style(FONT_STYLE::None) {}

#endif /* ENABLE_FREETYPE_SUPPORT */

