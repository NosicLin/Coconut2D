﻿/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
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

#include "CocoFont.hpp"

#ifdef ENABLE_FREETYPE_SUPPORT

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoFont::CocoFont(String fontName, float fontSize, bool bold, bool italic) : height(fontSize)
{
	CocoFontsCache::FONT_STYLE style;
	if(bold)
	{
		if(italic) style = CocoFontsCache::FONT_STYLE::BoldItalic;
		else style = CocoFontsCache::FONT_STYLE::Bold;
	}
	else
	{
		if(italic) style = CocoFontsCache::FONT_STYLE::Italic;
		else style = CocoFontsCache::FONT_STYLE::Regular;
	}
	face = CocoFontsCache::get(fontName, style);

	if(!face)
	{
		trace("ERROR(CocoFont.cpp): Invalid font");
	}
}

CocoFont::~CocoFont()
{
	while(chars.size())
		chars.erase(chars.begin());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoFont::fillText(ArrayBuffer* imageDataBuffer, int width, String text, int x, int y, float R, float G, float B, float A)
{   // We only use the ArrayBuffer of an Int32Array with byteOffset = 0 (BYTES_PER_ELEMENT = 4) in RGBA format
	if(FT_Set_Pixel_Sizes(face, 0, height))
	{
		trace("ERROR(CocoFont.cpp): Freetype could not set font char size");
	}
    else
    {
		std::map<uint16_t, CocoFontChar>::iterator it;
		CocoFontChar* c = nullptr;
		for(size_t i = 0; i < text.size(); i++)
		{
			if((it = chars.find(text[i])) == chars.end())
			{
				CocoFontChar c;
				c.charIndex = FT_Get_Char_Index(face, (FT_ULong)(text[i]));
	            if(FT_Load_Glyph(face, c.charIndex, FT_LOAD_RENDER))
	            {
	            	trace("ERROR(CocoFont.cpp): Freetype could not load glyph");
	            }
	            else
	            {
	                if(face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY)
	                {
	                	trace("ERROR(CocoFont.cpp): Wrong FT_Pixel_Mode");
	                }
	                else
	                {
	                    c.rect.pos.x = face->glyph->metrics.horiBearingX >> 6;
	                    c.rect.pos.y = (face->size->metrics.ascender - face->glyph->metrics.horiBearingY) >> 6;
	                    c.rect.size.x = face->glyph->bitmap.width;
	                    c.rect.size.y = face->glyph->bitmap.rows;
	                    c.horiAdvance = face->glyph->advance.x >> 6;
	                    c.data = new uint8_t[c.rect.size.x * c.rect.size.y];
	                    memcpy(c.data, face->glyph->bitmap.buffer, c.rect.size.x * c.rect.size.y);
	                    it = chars.insert(std::pair<uint16_t, CocoFontChar>(text[i], c)).first;
	                }
	            }
			}
			if(c && FT_HAS_KERNING(face))
			{
				std::map<uint16_t, int>::iterator kit = c->horiKernings.find(it->second.charIndex);
				if(kit == c->horiKernings.end())
				{
					FT_Vector tk;
	                FT_Get_Kerning(face, c->charIndex, it->second.charIndex, FT_KERNING_DEFAULT, &tk);
	                kit = c->horiKernings.insert(std::pair<uint16_t, int>(it->second.charIndex, tk.x)).first;
				}
				x += kit->second >> 6;
			}
			c = &(it->second);
			for(size_t ix = c->rect.size.x; ix--;)
			{
				for(size_t iy = c->rect.size.y; iy--;)
				{
					uint8_t* cp = (uint8_t*)((*imageDataBuffer)[((y + c->rect.pos.y + iy) * width + (x + c->rect.pos.x + ix)) * 4]);
					if(cp && c->data[iy * c->rect.size.x + ix])
					{
						cp[0] = R;
						cp[1] = G;
						cp[2] = B;
						cp[3] = c->data[iy * c->rect.size.x + ix];
					}
				}
			}
			x += c->horiAdvance;
		}
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoFont::measureText(String text)
{
	size_t ret = 0;
	if(FT_Set_Pixel_Sizes(face, 0, height))
	{
		trace("ERROR(CocoFont.cpp): Freetype could not set font char size");
	}
    else
    {
		std::map<uint16_t, CocoFontChar>::iterator it;
		CocoFontChar* c = nullptr;
		for(size_t i = 0; i < text.size(); i++)
		{
			if((it = chars.find(text[i])) == chars.end())
			{
				CocoFontChar c;
				c.charIndex = FT_Get_Char_Index(face, (FT_ULong)(text[i]));
	            if(FT_Load_Glyph(face, c.charIndex, FT_LOAD_RENDER))
	            {
	            	trace("ERROR(CocoFont.cpp): Freetype could not load glyph");
	            }
	            else
	            {
	                if(face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY)
	                {
						trace("ERROR(CocoFont.cpp): Wrong FT_Pixel_Mode");
	                }
	                else
	                {
	                    c.rect.pos.x = face->glyph->metrics.horiBearingX >> 6;
	                    c.rect.pos.y = -(face->glyph->metrics.horiBearingY >> 6);//(face->size->metrics.ascender - face->glyph->metrics.horiBearingY) >> 6;
	                    c.rect.size.x = face->glyph->bitmap.width;
	                    c.rect.size.y = face->glyph->bitmap.rows;
	                    c.horiAdvance = face->glyph->advance.x >> 6;
	                    c.data = new uint8_t[c.rect.size.x * c.rect.size.y];
	                    memcpy(c.data, face->glyph->bitmap.buffer, c.rect.size.x * c.rect.size.y);
	                    it = chars.insert(std::pair<uint16_t, CocoFontChar>(text[i], c)).first;
	                }
	            }
			}
			if(c && FT_HAS_KERNING(face))
			{
				std::map<uint16_t, int>::iterator kit = c->horiKernings.find(it->second.charIndex);
				if(kit == c->horiKernings.end())
				{
					FT_Vector tk;
	                FT_Get_Kerning(face, c->charIndex, it->second.charIndex, FT_KERNING_DEFAULT, &tk);
	                kit = c->horiKernings.insert(std::pair<uint16_t, int>(it->second.charIndex, tk.x)).first;
				}
				ret += kit->second >> 6;
			}
			c = &(it->second);
			ret += c->horiAdvance;
		}
    }
    return ret;
}

#else
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoFont::CocoFont(float fontSize, String fontName)
{
	trace("ERROR(CocoFont.cpp): Fonts not supported");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoFont::fillText(ArrayBuffer* imageDataBuffer, int width, String text, float x, float y)
{
	trace("ERROR(CocoFont.cpp): Fonts not supported");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoFont::measureText(String text)
{
	trace("ERROR(CocoFont.cpp): Fonts not supported");
	return 0.0f;
}
#endif
