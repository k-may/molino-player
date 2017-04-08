#pragma once

#define WEBCAM

#include "ofMain.h"

#include "doodlesPlayer.h"
#include "starsPlayer.h"
#include "player.h"
#include "Nano.h"

#include "ofxPostGlitch.h"
#include "ofxVideoRecorder.h"

class ofApp : public ofBaseApp {
public:

	void setup();
	void update();
	void draw();
	void keyReleased(int key);
	void keyPressed(int key);

	void onSelectNext();
	void onSelectPrevious();
	void onRecord();

	vector<player*> players;
	doodlesPlayer doodlePlayer;
	starsPlayer starsPlayer;

	//ofFbo videoFbo;
	pingPongBuffer posPingPong;
	ofFbo buffer;

	ofShader shader;

	ofImage			lenna;
	//-----------------------------------RECORDING----------------------------
	ofxVideoRecorder    vidRecorder;
	string fileName;
	string fileExt;
	bool isRecording;
	bool isDebug;
	bool showControls;
	Nano _nanoKontrol;

	/*Addon instance*/
	ofxPostGlitch	myGlitch;

	int state;
};
