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
		"blob1.mp4",
		"doodle2.mp4",
		"doodle3.mp4",
		"doodle4.mp4",
		"doodle5.mp4",
		"doodle6.mp4",
		"blob2.mp4"
	};

	int num = sizeof(doodlePaths) / sizeof(doodlePaths[0]);

	for (int i = 0; i < num; i++) {
		doodleDrawer drawer;
		drawer.setup(doodlePaths[i]);
		doodles.push_back(drawer);
	}

	posPingPong.allocate(ofGetWidth(), ofGetHeight());

	shader.load("shader/doodle");

}

void doodlesPlayer::update()
{
	int counter = 0;
	float time = ofGetElapsedTimeMillis();

	ofSetColor(255);
	for (int i = 0; i < doodles.size(); i++) {
		doodles[i].update();
	}
}

void doodlesPlayer::draw()
{
	//posPingPong.dst->draw(0, 0);
	posPingPong.src->begin();
	ofClear(255);
	for (int i = 0; i < doodles.size(); i++) {
		shader.begin();
		shader.setUniformTexture("tex0", doodles[i].getTextureReference(), 0);
		doodles[i].draw();
		shader.end();
	}
	posPingPong.src->end();

	posPingPong.src->draw(0, 0);

}
