#include "doodlesPlayer.h"



doodlesPlayer::doodlesPlayer()
{
}


doodlesPlayer::~doodlesPlayer()
{
}

void doodlesPlayer::setup()
{

	string doodlePaths[] = {
		"doodle1.mp4",
		"doodle2.mp4",
		"doodle3.mp4",
		"doodle4.mp4",
		"doodle5.mp4",
		"doodle6.mp4",
		"doodle7.mp4",
		"doodle8.mp4",
		"doodle9.mp4",
		"doodle10.mp4",
		"doodle11.mp4",
		"doodle12.mp4",
		"doodle13.mp4",
		"blob1.mp4",
		"blob2.mp4",
		"blob3.mp4",
		"blob4.mp4",
		"blob5.mp4"
	};

	int num = sizeof(doodlePaths) / sizeof(doodlePaths[0]);

	for (int i = 0; i < num; i++) {
		doodleDrawer drawer;
		drawer.setup(doodlePaths[i]);
		doodles.push_back(drawer);
	}
	
	//posPingPong.allocate(ofGetWidth(), ofGetHeight());
	buffer.allocate(ofGetWidth(), ofGetHeight());
	fadeAmount = 255;
	shader.load("shader/doodle");

}

void doodlesPlayer::update()
{
	shader.load("shader/doodle");

	int counter = 0;
	float time = ofGetElapsedTimeMillis();

	ofSetColor(255);
	for (int i = 0; i < doodles.size(); i++) {
		doodles[i].update();
	}
}

void doodlesPlayer::draw()
{
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	float destOpacity = isPlaying ? 255 : 0;
	opacity += (destOpacity - opacity) * 0.01;
	ofSetColor(255, 255, 255, opacity);

	ofClear(255, 255, 255, fadeAmount);

	for (int i = 0; i < doodles.size(); i++) {
		shader.begin();
		shader.setUniformTexture("tex0", doodles[i].getTextureReference(), 0);
		doodles[i].draw();
		shader.end();
	}

}

void doodlesPlayer::play()
{
	isPlaying = true;
}

void doodlesPlayer::pause()
{
	isPlaying = false;
}

void doodlesPlayer::setValue(float value)
{
	fadeAmount = (1 - value) * 255;
}
