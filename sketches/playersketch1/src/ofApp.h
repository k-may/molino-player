#pragma once

#define WEBCAM

#include "ofMain.h"
#include "doodlesPlayer.h"


class ofApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();


	ofShader shader;

	ofImage image;
	ofImage imageMask;

	doodlesPlayer doodlePlayer;


	ofFbo videoFbo;
	ofFbo fbo;
	ofFbo maskFbo;
};
