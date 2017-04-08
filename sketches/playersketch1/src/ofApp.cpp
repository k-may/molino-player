#include "ofApp.h"


enum STATE {
	DOODLES= 0,
	STARS = 1
};

//--------------------------------------------------------------
void ofApp::setup() {
	
	ofSetFrameRate(60);

	players.push_back(&doodlePlayer);
	players.push_back(&starsPlayer);

	for (auto & p : players)
		p->setup();

	posPingPong.allocate(ofGetWidth(), ofGetHeight());
	buffer.allocate(ofGetWidth(), ofGetHeight());

	myGlitch.setup(&buffer);
	//myGlitch.setFx(ofxPostGlitchType::OFXPOSTGLITCH_CONVERGENCE, true);

	vidRecorder.setVideoCodec("mpeg4");
	vidRecorder.setVideoBitrate("800k");
	fileName = "testMovie";
	fileExt = ".mp4";

	isRecording = false;
	isDebug = false;

	ofEnableAlphaBlending();

	showControls = false;
	_nanoKontrol.setup();

	ofAddListener(_nanoKontrol.onMarkerLeft, this, &ofApp::onSelectPrevious);
	ofAddListener(_nanoKontrol.onMarkerRight,this, &ofApp::onSelectNext);
	ofAddListener(_nanoKontrol.onRecord, this, &ofApp::onRecord);

	players[0]->play();

	lenna.loadImage("lenna.png");
	shader.load("Shaders/convergence");
}

//--------------------------------------------------------------
void ofApp::update() {
	
	_nanoKontrol.update();

	for (int i = 0; i < players.size(); i ++) {
		float value = _nanoKontrol.sliders[i] / 127.0;
		players[i]->setValue(value);
		players[i]->update();
	}

	if (isRecording) {
		ofPixels pix;
		pix.allocate(buffer.getWidth(), buffer.getHeight(), OF_PIXELS_RGB);
		buffer.readToPixels(pix);
		bool success = vidRecorder.addFrame(pix);
		if (!success) {
			ofLogWarning("This frame was not added!");
		}
	}

	shader.load("Shaders/convergence");
}

//--------------------------------------------------------------
void ofApp::draw() {

	//------------------ render -----------------
	buffer.begin();

	posPingPong.swap();
	posPingPong.src->begin();
	
	ofClear(255,255,255,255);
	
	for (auto & p : players)
		p->draw();

	float value = _nanoKontrol.knobs[0] * 2;
	if (value > 0) {

		ofPushMatrix();
		ofTranslate(ofGetWidth(), 0, 0);
		ofScale(-1, 1, 0);
		ofSetColor(255, 255, 255, _nanoKontrol.knobs[0] * 2);
		posPingPong.dst->draw(0, 0);
		ofPopMatrix();
	}
	posPingPong.src->end();

	ofSetColor(255, 255, 255, 255);
	posPingPong.src->draw(0, 0);

	buffer.end();

	//--------------- effects ----------------- 
	
	ofSetColor(255);
	

	/* Apply effects */
	myGlitch.generateFx();

	buffer.draw(0, 0, ofGetWidth(), ofGetHeight());

	if (isDebug) {
		ofSetColor(0);
		ofDrawBitmapString("frameRate : " + ofToString(ofGetFrameRate()), 20, 20);
	}

	if(isRecording){
		stringstream ss;
		ss << "video queue size: " << vidRecorder.getVideoQueueSize() << endl
			<< "audio queue size: " << vidRecorder.getAudioQueueSize() << endl
			<< "FPS: " << ofGetFrameRate() << endl
			<< (isRecording ? "pause" : "start") << " recording: r" << endl
			<< (isRecording ? "close current video file: c" : "") << endl;

		ofSetColor(0, 0, 0, 100);
		ofRect(0, 0, 260, 75);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(ss.str(), 15, 15);
	}

	if (showControls)
		_nanoKontrol.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW, true);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER, true);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST, true);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE, true);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE, true);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, true);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL, true);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT, true);

	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, true);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, true);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, true);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, true);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, true);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, true);

}

void ofApp::keyReleased(int key) {
	if (key == 'n')
		showControls = !showControls;

	if (key == 'd')
		isDebug = !isDebug;

	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW, false);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER, false);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST, false);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE, false);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE, false);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN, false);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL, false);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT, false);

	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, false);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, false);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, false);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, false);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, false);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, false);
}

void ofApp::onSelectNext()
{
	ofLog() << "select next";
	state = (state + 1) % players.size();

	for (auto & p : players)
		p->pause();

	players[state]->play();
}

void ofApp::onSelectPrevious()
{
	ofLog() << "select previous";

	state = (state - 1) % players.size();

	for (auto & p : players)
		p->pause();

	players[state]->play();
}

void ofApp::onRecord()
{
	isRecording = !isRecording;
	if (isRecording && !vidRecorder.isInitialized()) {
		vidRecorder.setup(fileName + ofGetTimestampString() + fileExt, buffer.getWidth(), buffer.getHeight(), 30);
		// Start recording
		vidRecorder.start();
	}
	else if (!isRecording && vidRecorder.isInitialized()) {
		vidRecorder.close();
	}
}
