/* Generated by Coconut2D C++ Compiler from file DeviceMessage.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DeviceMessage.hpp"
#include "IEventTarget.hpp"
#include "HTMLWindow.hpp"
#include "DeviceTouches.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceMessage::DeviceMessage()
{
	type = String("");
	target = nullptr;
	currentTarget = nullptr;
	bubbles = true;
	cancelable = true;
	timeStamp = 0;
	defaultPrevented = false;
	scale = 0.0;
	rotation = 0.0;
	__clientX = 0;
	__clientY = 0;
	touches = new TouchList();
	targetTouches = new TouchList();
	changedTouches = new TouchList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceMessage::~DeviceMessage()
{
	if(touches)
	{
		touches = (delete touches, nullptr);
	}
	if(targetTouches)
	{
		targetTouches = (delete targetTouches, nullptr);
	}
	if(changedTouches)
	{
		changedTouches = (delete changedTouches, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceMessage::stopPropagation()
{
	bubbles = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceMessage::preventDefault()
{
	defaultPrevented = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceMessage::initEvent(String type, bool canBubble, bool cancelable)
{
	this->type = type;
	this->bubbles = canBubble;
	this->cancelable = cancelable;
	this->timeStamp = (new Date())->getTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceMessage::initUIEvent(String type, bool canBubble, bool cancelable, HTMLWindow* view, int detail)
{
	this->initEvent(type, canBubble, cancelable);
	this->view = view;
	this->detail = detail;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceMessage::initTouchEvent(String type, bool canBubble, bool cancelable, HTMLWindow* view, int detail, int screenX, int screenY, int clientX, int clientY, bool ctrlKey, bool altKey, bool shiftKey, bool metaKey, TouchList* touches, TouchList* targetTouches, TouchList* changedTouches, float scale, float rotation)
{
	this->initUIEvent(type, canBubble, cancelable, view, detail);
	this->scale = scale;
	this->rotation = rotation;
	this->touches = touches;
	this->targetTouches = targetTouches;
	this->changedTouches = changedTouches;
}
