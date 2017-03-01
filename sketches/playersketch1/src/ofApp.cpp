#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	shader.load("shader/shader");

	int camWidth = 320;
	int camHeight = 240;


	doodlePlayer.setup();

	image.loadImage("face1.png");
	imageMask.loadImage("mask.jpg");

	videoFbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.allocate(ofGetWidth(), ofGetHeight());
	maskFbo.allocate(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update() {
	doodlePlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	videoFbo.begin();
	ofClear(255,255,255,255);
	doodlePlayer.draw();
	videoFbo.end();

	//------------------------------------------ draw to mask fbo.
	maskFbo.begin();

	ofClear(255, 255, 255, 255);

	float imageMaskX = mouseX / (float)ofGetWidth();
	imageMaskX = ofClamp(imageMaskX, 0, 1);
	imageMaskX = -(imageMask.getWidth() - maskFbo.getWidth()) * imageMaskX;
	imageMask.draw(imageMaskX, 0);

	maskFbo.end();

	//------------------------------------------- draw to final fbo.
	fbo.begin();
	ofClear(255,255,255, 255);

	shader.begin();
	shader.setUniformTexture("tex1", image, 2);
	shader.setUniformTexture("tex2", videoFbo.getTextureReference(), 3);
	shader.setUniformTexture("imageMask", maskFbo.getTextureReference(), 4);

	// we are drawing this fbo so it is used just as a frame.
	maskFbo.draw(0, 0);

	shader.end();
	fbo.end();

	//------------------------------------------- 
	ofSetColor(255);
	videoFbo.draw(0,0,ofGetWidth(), ofGetHeight());

	ofSetColor(0);
	ofDrawBitmapString("frameRate : " + ofToString(ofGetFrameRate()), 20, 20);
}
