/* Generated by Coconut2D C++ Compiler from file DeviceTouches.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "DeviceTouches.hpp"
#include "IEventTarget.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Touch::Touch()
{
	identifier = 0;
	target = nullptr;
	screenX = 0;
	screenY = 0;
	clientX = 0;
	clientY = 0;
	pageX = 0;
	pageY = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Touch::~Touch()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Touch::initTouch(int identifier, IEventTarget* target, int screenX, int screenY, int clientX, int clientY, int pageX, int pageY)
{
	this->identifier = identifier;
	this->target = target;
	this->screenX = screenX;
	this->screenY = screenY;
	this->clientX = clientX;
	this->clientY = clientY;
	this->pageX = pageX;
	this->pageY = pageY;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
TouchList::TouchList()
{
	for(int i = 0; i <= 5; i++)
	{
		Touch* touch = new Touch();
		touch->initTouch(i, ((IEventTarget*)(nullptr)), 0, 0, 0, 0, 0, 0);
		push(touch);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Touch* TouchList::item(int index)
{
	return (*this)[index];
}
