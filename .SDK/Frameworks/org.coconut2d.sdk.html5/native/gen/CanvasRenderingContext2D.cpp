﻿#include "CanvasRenderingContext2D.hpp"
#include "HTMLImageElement.hpp"
#include "HTMLElement.hpp"
#include "HTMLTextMetrics.hpp"
#include "CocoFont.hpp"
#include "HTMLCanvasElement.hpp"
#include "TypedArray.hpp"
#include "HTMLWindow.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
PathLine::PathLine(float _x0, float _y0, float _x1, float _y1)
{
	x0 = _x0;
	y0 = _y0;
	x1 = _x1;
	y1 = _y1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CanvasRenderingContext2D::CanvasRenderingContext2D(HTMLCanvasElement* canvas)
{
	__curX = 0.0;
	__curY = 0.0;
	__fillColor = new Array<float> ();
	__fillColor->push(0.0);
	__fillColor->push(0.0);
	__fillColor->push(0.0);
	__fillColor->push(1.0);
	__strokeColor = new Array<float> ();
	__strokeColor->push(0.0);
	__strokeColor->push(0.0);
	__strokeColor->push(0.0);
	__strokeColor->push(1.0);
	__pathLines = new Array<PathLine*> ();
	this->canvas = canvas;
	canvas->__imageData = new ImageData((String(toString(canvas->width))), (String(toString(canvas->height))));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CanvasRenderingContext2D::~CanvasRenderingContext2D()
{
	if(__strokeColor)
	{
		__strokeColor = (delete __strokeColor, nullptr);
	}
	if(__fillColor)
	{
		__fillColor = (delete __fillColor, nullptr);
	}
	if(__pathLines)
	{
		__pathLines = (delete __pathLines, nullptr);
	}
	if(__font)
	{
		__font = (delete __font, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::arcTo(float x1, float y1, float x2, float y2, float radius)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::clip()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::closePath()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ImageData* CanvasRenderingContext2D::createImageData(float width, float height)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasGradient* CanvasRenderingContext2D::createLinearGradient(float x0, float y0, float x1, float y1)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasPattern* CanvasRenderingContext2D::createPattern(Image* image, String repetition)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasGradient* CanvasRenderingContext2D::createRadialGradient(float x0, float y0, float r0, float x1, float y1, float r1)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CanvasRenderingContext2D::drawCustomFocusRing(HTMLElement* element)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::drawSystemFocusRing(HTMLElement* element)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::fill()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
ImageData* CanvasRenderingContext2D::getImageData(float x, float y, float width, float height)
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::getLineDash()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CanvasRenderingContext2D::isPointInPath(float x, float y)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CanvasRenderingContext2D::isPointInStroke(float x, float y)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::quadraticCurveTo(float cpx, float cpy, float x, float y)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::rect(float x, float y, float width, float height)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::restore()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::rotate(float angle)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::save()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::scale(float x, float y)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::scrollPathIntoView()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::setLineDash(Array<float>* segments)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::setTransform(float m11, float m12, float m21, float m22, float dx, float dy)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::strokeRect(float x, float y, float w, float h)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::strokeText(String text, float x, float y, float maxWidth)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::transform(float m11, float m12, float m21, float m22, float dx, float dy)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::translate(float x, float y)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::drawImage(Image* image, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::putImageData(ImageData* imagedata, float dx, float dy, float dirtyX, float dirtyY, float dirtyWidth, float dirtyHeight)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::beginPath()
{
	__pathLines->clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::moveTo(float x, float y)
{
	__curX = x;
	__curY = y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::lineTo(float x, float y)
{
	__pathLines->push(new PathLine(__curX, __curY, x, y));
	moveTo(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::stroke()
{
	int l0 = floor(-0.5 * __get_lineWidth());
	int l1 = floor(0.5 * __get_lineWidth());
	for(int i = __pathLines->size(); i--;)
	{
		int x0 = floor(std::max(((float)0.0), std::min(canvas->width, (*__pathLines)[i]->x0)));
		int y0 = floor(std::max(((float)0.0), std::min(canvas->height, (*__pathLines)[i]->y0)));
		int x1 = floor(std::max(((float)0.0), std::min(canvas->width, (*__pathLines)[i]->x1)));
		int y1 = floor(std::max(((float)0.0), std::min(canvas->height, (*__pathLines)[i]->y1)));
		int t = 0;
		if(x0 > x1)
		{
			t = x0;
			x0 = x1;
			x1 = t;
		}
		if(y0 > y1)
		{
			t = y0;
			y0 = y1;
			y1 = t;
		}
		if(x0 == x1 && y0 == y1)
		{
		}
		else if(x0 == x1)
		{
			for(int y = y0; y < y1; y++)
			{
				for(int l = l0; l < l1; l++)
				{
					t = (y * ((int)canvas->width) + x0 + l) * 4;
					if(t < canvas->__imageData->data->length)
					{
						(*canvas->__imageData->data)[t + 0] += 255.0 * (*__strokeColor)[0] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 0] * (*__strokeColor)[3];
						(*canvas->__imageData->data)[t + 1] += 255.0 * (*__strokeColor)[1] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 1] * (*__strokeColor)[3];
						(*canvas->__imageData->data)[t + 2] += 255.0 * (*__strokeColor)[2] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 2] * (*__strokeColor)[3];
						(*canvas->__imageData->data)[t + 3] += 255.0 * (*__strokeColor)[3] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 3] * (*__strokeColor)[3];
					}
				}
			}
		}
		else if(y0 == y1)
		{
			for(int x = x0; x < x1; x++)
			{
				for(int l = l0; l < l1; l++)
				{
					t = ((y0 + l) * ((int)canvas->width) + x) * 4;
					if(t < canvas->__imageData->data->length)
					{
						(*canvas->__imageData->data)[t + 0] += 255.0 * (*__strokeColor)[0] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 0] * (*__strokeColor)[3];
						(*canvas->__imageData->data)[t + 1] += 255.0 * (*__strokeColor)[1] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 1] * (*__strokeColor)[3];
						(*canvas->__imageData->data)[t + 2] += 255.0 * (*__strokeColor)[2] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 2] * (*__strokeColor)[3];
						(*canvas->__imageData->data)[t + 3] += 255.0 * (*__strokeColor)[3] * (*__strokeColor)[3] - (*canvas->__imageData->data)[t + 3] * (*__strokeColor)[3];
					}
				}
			}
		}
		else
		{
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_fillStyle()
{
	return __fillStyle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_fillStyle(String v)
{
	if(v.indexOf(String("rgba")))
	{
		return;
	}
	String str = v.substr(v.indexOf(String("(")) + 1);
	str = str.substr(0, str.indexOf(String(")")));
	Array<String>* arr = str.split(String(","));
	if(arr->size() != 4)
	{
		return;
	}
	for(int i = 0; i < 4; i++)
	{
		(*__fillColor)[i] = (float)(parseFloat((*arr)[i])) / (float)(255.0);
	}
	__fillStyle = v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_strokeStyle()
{
	return __strokeStyle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_strokeStyle(String v)
{
	if(v.indexOf(String("rgba")))
	{
		return;
	}
	String str = v.substr(v.indexOf(String("(")) + 1);
	str = str.substr(0, str.indexOf(String(")")));
	Array<String>* arr = str.split(String(","));
	if(arr->size() != 4)
	{
		return;
	}
	for(int i = 0; i < 4; i++)
	{
		(*__strokeColor)[i] = (float)(parseFloat((*arr)[i])) / (float)(255.0);
	}
	__strokeStyle = v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float CanvasRenderingContext2D::__get_lineWidth()
{
	return __lineWidth;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_lineWidth(float v)
{
	if(v >= 1.0)
	{
		__lineWidth = v;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String CanvasRenderingContext2D::__get_font()
{
	return __fontSetting;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::__set_font(String v)
{
	Array<String>* spl = v.split(String(" "));
	String fontStyle = String("normal");
	String fontVariant = String("normal");
	String fontWeight = String("normal");
	String fontSize = String("medium");
	String lineHeight = String("normal");
	String fontFamily = String("Arial");
	int s = 0;
	String str = "";
	for(int i = 0; i < spl->size(); i++)
	{
		str = (*spl)[i];
		if(!str)
		{
			continue;
		}
		switch(s)
		{
			case 3:
			{
				{
					int idx = str.indexOf(String("/"));
					if(idx != -1)
					{
						fontSize = str.substr(0, idx);
						String lh = str.substr(idx + 1);
						if(lh)
						{
							lineHeight = lh;
							s++;
						}
					}
					else
					{
						fontSize = str;
					}
					s++;
					break;
				}
			}
			break;
			case 4:
			{
				{
					int idx = str.indexOf(String("/"));
					if(idx != -1)
					{
						String lh = str.substr(idx + 1);
						if(lh)
						{
							lineHeight = lh;
							s++;
						}
					}
					else
					{
						fontFamily = spl->slice(i)->join(String(""));
						i = spl->size();
					}
					s++;
					break;
				}
			}
			break;
			case 5:
			{
				{
					fontFamily = spl->slice(i + 1)->join(String(""));
					i = spl->size();
					break;
				}
			}
			break;
			default:
			{
				{
					if(str == String("inherit"))
					{
						return;
					}
					else if(str == String("normal"))
					{
						switch(s)
						{
							case 0:
							{
								s++;
								break;
							}
							break;
							case 1:
							{
								s++;
								break;
							}
							break;
							case 2:
							{
								s++;
								break;
							}
							break;
							case 4:
							{
								s++;
								break;
							}
							break;
							default:
							{
								return;
							}
							break;
						}
					}
					else if(str == String("italic") || str == String("oblique"))
					{
						switch(s)
						{
							case 0:
							{
								fontStyle = str;
								s = 1;
								break;
							}
							break;
							default:
							{
								return;
							}
							break;
						}
					}
					else if(str == String("small-caps"))
					{
						switch(s)
						{
							case 0:
							{
								fontVariant = str;
								s = 2;
								break;
							}
							break;
							case 1:
							{
								fontVariant = str;
								s = 2;
								break;
							}
							break;
							default:
							{
								return;
							}
							break;
						}
					}
					else if(str == String("bold") || str == String("bolder") || str == String("lighter") || str == String("100") || str == String("200") || str == String("300") || str == String("400") || str == String("500") || str == String("600") || str == String("700") || str == String("800") || str == String("900"))
					{
						switch(s)
						{
							case 1:
							{
								fontWeight = str;
								s = 3;
								break;
							}
							break;
							case 2:
							{
								fontWeight = str;
								s = 3;
								break;
							}
							break;
							default:
							{
								return;
							}
							break;
						}
					}
				}
			}
			break;
		}
	}
	float fontSizeInPixels = 0.0;
	if(fontSize == String("xx-small"))
	{
		fontSizeInPixels = 9;
	}
	else if(fontSize == String("x-small"))
	{
		fontSizeInPixels = 10;
	}
	else if(fontSize == String("small"))
	{
		fontSizeInPixels = 13;
	}
	else if(fontSize == String("medium"))
	{
		fontSizeInPixels = 16;
	}
	else if(fontSize == String("large"))
	{
		fontSizeInPixels = 18;
	}
	else if(fontSize == String("x-large"))
	{
		fontSizeInPixels = 24;
	}
	else if(fontSize == String("xx-large"))
	{
		fontSizeInPixels = 32;
	}
	else if(fontSize == String("smaller"))
	{
		fontSizeInPixels = 13;
	}
	else if(fontSize == String("larger"))
	{
		fontSizeInPixels = 18;
	}
	else
	{
		if(fontSize.indexOf(String("px")) != -1)
		{
			fontSizeInPixels = parseFloat(fontSize);
		}
		else if(fontSize.indexOf(String("in")) != -1)
		{
			fontSizeInPixels = parseFloat(fontSize) * window->devicePixelRatio * 160.0;
		}
		else if(fontSize.indexOf(String("cm")) != -1)
		{
			fontSizeInPixels = (float)(parseFloat(fontSize) * window->devicePixelRatio * 160.0) / (float)(2.54);
		}
		else
		{
			return;
		}
	}
	__fontSetting = v;
	__font = new CocoFont(fontSizeInPixels, fontFamily, fontWeight == String("bold"), fontStyle == String("italic") || fontStyle == String("oblique"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::fillText(String text, float x, float y, float maxWidth)
{
	if(__font)
	{
		__font->fillText(canvas->__imageData->data->buffer, canvas->__imageData->width, text, x, y, (*__fillColor)[0], (*__fillColor)[1], (*__fillColor)[2], (*__fillColor)[3]);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::fillRect(float x, float y, float width, float height)
{
	int _x = ((int)floor(x));
	int _y = ((int)floor(y));
	for(int ix = 0; ix < width; ix++)
		for(int iy = 0; iy < height; iy++)
		{
			int idx = ((_y + iy) * canvas->__imageData->width + _x + ix) * 4;
			if(idx < canvas->__imageData->data->length)
			{
				(*canvas->__imageData->data)[idx + 0] += 255.0 * (*__fillColor)[0] * (*__fillColor)[3] - (*canvas->__imageData->data)[idx + 0] * (*__fillColor)[3];
				(*canvas->__imageData->data)[idx + 1] += 255.0 * (*__fillColor)[1] * (*__fillColor)[3] - (*canvas->__imageData->data)[idx + 1] * (*__fillColor)[3];
				(*canvas->__imageData->data)[idx + 2] += 255.0 * (*__fillColor)[2] * (*__fillColor)[3] - (*canvas->__imageData->data)[idx + 2] * (*__fillColor)[3];
				(*canvas->__imageData->data)[idx + 3] += 255.0 * (*__fillColor)[3] * (*__fillColor)[3] - (*canvas->__imageData->data)[idx + 3] * (*__fillColor)[3];
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasRenderingContext2D::clearRect(float x, float y, float width, float height)
{
	int _x = ((int)floor(x));
	int _y = ((int)floor(y));
	for(int ix = 0; ix < width; ix++)
		for(int iy = 0; iy < height; iy++)
		{
			int idx = (_y + iy) * canvas->__imageData->width + _x + ix;
			if(idx < canvas->__imageData->data->length)
			{
				(*canvas->__imageData->data)[idx] = 0;
			}
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLTextMetrics* CanvasRenderingContext2D::measureText(String text)
{
	HTMLTextMetrics* ret = new HTMLTextMetrics();
	ret->width = __font->measureText(text);
	return ret;
}
