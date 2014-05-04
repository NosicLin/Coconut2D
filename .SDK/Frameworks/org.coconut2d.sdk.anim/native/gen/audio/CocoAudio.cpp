/* Generated by Coconut2D C++ Compiler from file CocoAudio.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CocoAudio.hpp"
#include "HTMLAudioElement.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoAudio::CocoAudio(String url, bool autoplay, int loops)
{
	audio = new Audio(url);
	audio->autoplay = false;
	audio->loop = false;
	this->src = url;
	this->autoplay = autoplay;
	this->loops = loops;
	__firstPlayed = false;
	__loopCount = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoAudio::~CocoAudio()
{
	if(audio)
	{
		audio->pause();
		if(audio)
		{
			audio = (delete audio, nullptr);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudio::reset()
{
	if(!audio)
	{
		return;
	}
	audio->pause();
	audio->ended = false;
	audio->paused = true;
	setCurrentTime(0);
	__loopCount = 0;
	__firstPlayed = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudio::tick()
{
	if(!audio)
	{
		return;
	}
	if(!__firstPlayed && autoplay)
	{
		__firstPlayed = true;
		play();
		return;
	}
	if(loops >= 0 && audio->ended)
	{
		__loopCount++;
		if(loops == 0 || (loops > 0 && __loopCount < loops))
		{
			play();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudio::play()
{
	if(!audio)
	{
		return;
	}
	audio->ended = false;
	audio->paused = false;
	setCurrentTime(0);
	audio->play();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudio::pause()
{
	if(!audio)
	{
		return;
	}
	audio->pause();
	audio->ended = false;
	audio->paused = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudio::stop()
{
	if(!audio)
	{
		return;
	}
	audio->pause();
	audio->ended = false;
	audio->paused = true;
	__loopCount = 0;
	__firstPlayed = true;
	setCurrentTime(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoAudio::duration()
{
	return audio ? audio->duration : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoAudio::paused()
{
	return audio ? audio->paused : true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoAudio::ended()
{
	return audio ? audio->ended : true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoAudio::getCurrentTime()
{
	return audio ? audio->__get_currentTime() : 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudio::setCurrentTime(float t)
{
	if(audio && audio->__get_readyState() == 4)
	{
		audio->__set_currentTime(t);
	}
}
