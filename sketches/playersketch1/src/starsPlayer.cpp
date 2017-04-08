#include "starsPlayer.h"



starsPlayer::starsPlayer()
{
}


starsPlayer::~starsPlayer()
{
}

void starsPlayer::setup()
{
	isPlaying = false;
}

void starsPlayer::update()
{
}

void starsPlayer::draw()
{
	float destOpacity = isPlaying ? 255 : 0;
	opacity += (destOpacity - opacity) * 0.01;
	ofSetColor(255, 255, 255, opacity);

}

void starsPlayer::play()
{
	isPlaying = true;
}

void starsPlayer::pause()
{
	isPlaying = false;
}

void starsPlayer::setValue(float value)
{
	
}
