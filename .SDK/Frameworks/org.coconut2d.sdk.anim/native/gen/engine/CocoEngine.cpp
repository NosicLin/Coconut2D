/* Generated by Coconut2D C++ Compiler from file CocoEngine.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CocoEngine.hpp"
#include "DeviceMessage.hpp"
#include "CocoClip.hpp"
#include "ITickable.hpp"
#include "WebGLRenderingContext.hpp"
#include "DeviceTouches.hpp"
#include "HTMLWindow.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::CocoEngine()
{
	__clicked = new Array<CocoClip*> ();
	__currentState = nullptr;
	__deviceMessage = nullptr;
	__clock = 0;
	debugbreak = false;
	window->addEventListener(String("mouseup"), &CocoEngine::__setTouchEvent);
	window->addEventListener(String("touchstart"), &CocoEngine::__setTouchEvent);
	window->addEventListener(String("touchmove"), &CocoEngine::__setTouchEvent);
	window->addEventListener(String("touchend"), &CocoEngine::__setTouchEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::~CocoEngine()
{
	if(__clicked)
	{
		__clicked = (delete __clicked, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::addTickListener(ITickable* tickable)
{
	__tickables->push(tickable);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoEngine::getTickableIndex(ITickable* tickable)
{
	if(tickable)
	{
		for(int i = __tickables->size() - 1; i >= 0; i--)
		{
			if((*__tickables)[i] == tickable)
			{
				return i;
			}
		}
	}
	return  -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::removeTickListener(ITickable* tickable)
{
	int index = getTickableIndex(tickable);
	if(index != -1)
	{
		__tickables->splice(index, 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::setNextState(State* s)
{
	__nextState = s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::run(WebGLRenderingContext* gl, Time time)
{
	if(!__currentState && !__nextState)
	{
		return;
	}
	if(__nextState != nullptr)
	{
		if(__currentState)
		{
			__currentState->exit();
		}
		__currentState = __nextState;
		__nextState = nullptr;
		trace((String("\n@@STATE ") + __currentState->__name).c_str());
		__clicked->clear();
		if(__currentState)
		{
			__currentState->enter();
		}
	}
	if(__currentState)
	{
		int i = 0;
		for(i = 0; i < __clicked->size(); i++)
		{
			CocoClip* clip = (*__clicked)[i];
		}
		__currentState->tick(__clock);
	}
	__clicked->clear();
	if(__nextState == nullptr && __currentState != nullptr)
	{
		gl->clearColor(0, 0, 0, 1);
		gl->clear(gl->COLOR_BUFFER_BIT);
		__currentState->paint(gl, __clock);
	}
	__deviceMessage = nullptr;
	__clock += TICK_TIME;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::__setTouchEvent(DeviceMessage* e)
{
	__deviceMessage = e;
	__deviceMessage->__clientX = e->touches ? (*e->touches)[0]->clientX : e->clientX;
	__deviceMessage->__clientY = e->touches ? (*e->touches)[0]->clientY : e->clientY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceMessage* CocoEngine::getTouchEvent()
{
	return __deviceMessage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::pushTouched(CocoClip* clip)
{
	trace((String("click: ") + clip->__instanceName).c_str());
	__clicked->push(clip);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoEngine::isClicked(Array<CocoClip*>* check)
{
	for(int i = __clicked->size() - 1; i >= 0; i--)
		for(int r = check->size() - 1; r >= 0; r--)
			if((*check)[r] == (*__clicked)[i])
			{
				return r;
			}
	return  -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::__debug_trace(CocoScene* scene, CocoClip* clip, String message)
{
}
