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

// ==================================================================================================================================
//	    __  __________  _____ _       ___           __
//	   / / / /_  __/  |/  / /| |     / (_)___  ____/ /___ _      __
//	  / /_/ / / / / /|_/ / / | | /| / / / __ \/ __  / __ \ | /| / /
//	 / __  / / / / /  / / /__| |/ |/ / / / / / /_/ / /_/ / |/ |/ /
//	/_/ /_/ /_/ /_/  /_/_____/__/|__/_/_/ /_/\__,_/\____/|__/|__/
//
// ==================================================================================================================================

#include "HTMLWindow.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLWindow::HTMLWindow()
{
	touchstart = nullptr;
	touchmove = nullptr;
	touchend = nullptr;
	__uid = 0;
	document = new HTMLDocument();
	__deviceMessage = new DeviceMessage();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLWindow::~HTMLWindow()
{
	if(document)
	{
		document = (delete document, nullptr);
	}
	if(__deviceMessage)
	{
		__deviceMessage = (delete __deviceMessage, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::setScreen(fxScreen screen)
{
	innerWidth = screen.width;
	innerHeight = screen.height;
	devicePixelRatio = screen.pixelRatio;
	screenRotation = screen.rotation;

	switch(screenRotation)
	{
		case fxScreen::Rotation::NONE: deviceRotation = 0.0f; break;
		case fxScreen::Rotation::RCW: deviceRotation = M_PI_2; break;
		case fxScreen::Rotation::RCCW: deviceRotation = -M_PI_2; break;
		case fxScreen::Rotation::FULL: deviceRotation = M_PI; break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::addEventListener(String eventType, CocoEventAction listener, bool useCapture)
{
	if(eventType == "touchstart")
		touchstart = listener;
	else if(eventType == "touchmove")
		touchmove = listener;
	else if(eventType == "touchend")
		touchend = listener;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::removeEventListener(String eventType, CocoEventAction listener, bool useCapture)
{
	if(eventType == "touchstart")
		touchstart = nullptr;
	else if(eventType == "touchmove")
		touchmove = nullptr;
	else if(eventType == "touchend")
		touchend = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::dispatchEvent(int uid, String eventType)
{
	__deviceMessage->type = eventType;
	if(eventType == "touchstart")
		(engine->*touchstart)(__deviceMessage);
	else if(eventType == "touchmove")
		(engine->*touchmove)(__deviceMessage);
	else if(eventType == "touchend")
		(engine->*touchend)(__deviceMessage);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::handleEvent(fxObjectUID uid, fxEvent type, void* data)
{
	String eventType;

	switch(type)
	{
		case fxEvent::LOAD:
		{
			eventType = "load";
			break;
		}

		case fxEvent::FOCUS:
		{
			eventType = "focus";
			break;
		}

		case fxEvent::BLUR:
		{
			//saveStorage();
			eventType = "blur";
			break;
		}

		case fxEvent::UNLOAD:
		{
			//saveStorage();
			eventType = "unload";
			break;
		}

		case fxEvent::RESIZE:
		{
			eventType = "resize";
			break;
		}

		case fxEvent::CLICK:
		{
			eventType = "click";
			int x, y;
			switch(screenRotation)
			{
				case fxScreen::Rotation::NONE: x = fxAPIGetMouseEventX(data); y = fxAPIGetMouseEventY(data); break;
				case fxScreen::Rotation::FULL: x = -fxAPIGetMouseEventX(data); y = -fxAPIGetMouseEventY(data); break;
				case fxScreen::Rotation::RCW: x = -fxAPIGetMouseEventY(data); y = fxAPIGetMouseEventX(data); break;
				case fxScreen::Rotation::RCCW: x = fxAPIGetMouseEventY(data); y = -fxAPIGetMouseEventX(data); break;
			}
			__deviceMessage->__clientX = x;
			__deviceMessage->__clientY = y;
			break;
		}

		case fxEvent::KEYDOWN:
		{
			eventType = "keydown";
			//fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
			break;
		}

		case fxEvent::KEYPRESS:
		{
			eventType = "keypress";
			//fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
			break;
		}

		case fxEvent::KEYUP:
		{
			eventType = "keyup";
			//fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
			break;
		}

		case fxEvent::TOUCHSTART:
		case fxEvent::TOUCHMOVE:
		case fxEvent::TOUCHEND:
		case fxEvent::TOUCHCANCEL:
		{
			switch(type)
			{
				case fxEvent::TOUCHSTART: eventType = "touchstart"; break;
				case fxEvent::TOUCHMOVE: eventType = "touchmove"; break;
				case fxEvent::TOUCHEND: eventType = "touchend"; break;
				case fxEvent::TOUCHCANCEL: eventType = "touchcancel"; break;
				default: break;
			}
			int x, y;
			__deviceMessage->touches->length = fxAPIGetTouchesLength(data);
			for(size_t i = __deviceMessage->touches->length; i--;)
			{
				switch(screenRotation)
				{
						/*
						 case fxScreen::Rotation::NONE: x = fxAPIGetTouchEventX(data, i); y = fxAPIGetTouchEventY(data, i) - screen->top; break;
						 case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetTouchEventX(data, i); y = innerHeight - fxAPIGetTouchEventY(data, i); break;
						 case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetTouchEventY(data, i); y = fxAPIGetTouchEventX(data, i) - screen->top; break;
						 case fxScreen::Rotation::RCCW: x = fxAPIGetTouchEventY(data, i); y = innerHeight - fxAPIGetTouchEventX(data, i); break;
						 */
					case fxScreen::Rotation::NONE: x = fxAPIGetTouchEventX(data, i); y = fxAPIGetTouchEventY(data, i); break;
					case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetTouchEventX(data, i); y = innerHeight - fxAPIGetTouchEventY(data, i); break;
					case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetTouchEventY(data, i); y = fxAPIGetTouchEventX(data, i); break;
					case fxScreen::Rotation::RCCW: x = fxAPIGetTouchEventY(data, i); y = innerHeight - fxAPIGetTouchEventX(data, i); break;
				}
				__deviceMessage->touches->item(i)->clientX = x;
				__deviceMessage->touches->item(i)->clientY = y;
				__deviceMessage->touches->item(i)->screenX = x;
				__deviceMessage->touches->item(i)->screenY = y;
			}

			__deviceMessage->changedTouches->length = fxAPIGetChangedTouchesLength(data);
			for(size_t i = __deviceMessage->changedTouches->length; i--;)
			{
				switch(screenRotation)
				{
						/*
						 case fxScreen::Rotation::NONE: x = fxAPIGetChangedTouchEventX(data, i); y = fxAPIGetChangedTouchEventY(data, i) - screen->top; break;
						 case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetChangedTouchEventX(data, i); y = innerHeight - fxAPIGetChangedTouchEventY(data, i); break;
						 case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetChangedTouchEventY(data, i); y = fxAPIGetChangedTouchEventX(data, i) - screen->top; break;
						 case fxScreen::Rotation::RCCW: x = fxAPIGetChangedTouchEventY(data, i); y = innerHeight - fxAPIGetChangedTouchEventX(data, i); break;
						 */
					case fxScreen::Rotation::NONE: x = fxAPIGetChangedTouchEventX(data, i); y = fxAPIGetChangedTouchEventY(data, i); break;
					case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetChangedTouchEventX(data, i); y = innerHeight - fxAPIGetChangedTouchEventY(data, i); break;
					case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetChangedTouchEventY(data, i); y = fxAPIGetChangedTouchEventX(data, i); break;
					case fxScreen::Rotation::RCCW: x = fxAPIGetChangedTouchEventY(data, i); y = innerHeight - fxAPIGetChangedTouchEventX(data, i); break;
				}
				__deviceMessage->changedTouches->item(i)->clientX = x;
				__deviceMessage->changedTouches->item(i)->clientY = y;
				__deviceMessage->changedTouches->item(i)->screenX = x;
				__deviceMessage->changedTouches->item(i)->screenY = y;
			}
			break;
		}

		default:
			trace("Event not implemented");
	}

	if(__deviceMessage->touches->length)
	{
		trace("Event=%d, x=%d, y=%d", (int)type, __deviceMessage->touches->item(0)->clientX, __deviceMessage->touches->item(0)->clientY);
	}

	dispatchEvent(uid, eventType);
}