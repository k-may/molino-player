#pragma once
#include "ofxWMFVideoPlayer.h"
#include "ofMain.h"

// Struct for doing PingPong quickly and easy
//
// Because on GPU you can«t write over the texture that you are reading we are
// using to pair of ofFbo attached together on what we call pingPongBuffer 
// Learn more about Ping-Pong at:
//
// http://www.comp.nus.edu/~ashwinna/docs/PingPong_FBO.pdf
// http://www.seas.upenn.edu/~cis565/fbo.htm#setupgl4
//
struct pingPongBuffer {
public:
	void allocate(int _width, int _height, int _internalformat = GL_RGBA) {
		// Allocate
		for (int i = 0; i < 2; i++) {
			FBOs[i].allocate(_width, _height, _internalformat);
			FBOs[i].getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		}

		// Clean
		clear();
	}

	void swap() {
		std::swap(src, dst);
	}

	void clear() {
		for (int i = 0; i < 2; i++) {
			FBOs[i].begin();
			ofClear(0, 255);
			FBOs[i].end();
		}
	}

	ofFbo& operator[](int n) { return FBOs[n]; }
	ofFbo   *src = &FBOs[0];       // Source       ->  Ping
	ofFbo   *dst = &FBOs[1];       // Destination  ->  Pong

private:
	ofFbo   FBOs[2];    // Real addresses of ping/pong FBO«s
};

struct doodleDrawer {

public:
	void setup(string path) {
		_path = path;
		_player = new ofxWMFVideoPlayer();
		_player->load(path);
		_startTime = ofRandom(5, 10);
		float w = _player->getWidth();
		float h = _player->getHeight();
		_buffer.allocate(w, h);
		_position = getRandomPosition();
		_isPlaying = false;
	}

	void update() {

		float time = ofGetElapsedTimef();

		float elapsed = time - _startTime;

		if (elapsed > 0) {
			if (_isPlaying) {
				_player->update();
				if (!_player->getIsMovieDone()) {
					if (_player->isFrameNew()) {
						_buffer.begin();
						_player->draw(0,0);
						_buffer.end();
					}
				}else{
					_isPlaying = false;
					_startTime = time + ofRandom(5, 10);
					ofLog() << "stop : " << _path << " : " << ofToString(_startTime);
					_player->stop();
					_position = getRandomPosition();
					_buffer.begin();
					ofClear(255);
					_buffer.end();
				}
			}
			else {
				//if (!_isPlaying) {
					_isPlaying = true;
					ofLog() << "play : " << _path;
					_player->play();
				//}
			}
		}
	}
	void draw() {
		_buffer.getTextureReference();
		_buffer.draw(_position.x, _position.y);
	}

	ofTexture& getTextureReference() {
		return _buffer.getTextureReference();
	}

private:

	ofVec2f getRandomPosition() {
		return ofVec2f(ofRandom(-_player->getWidth() * 0.5, ofGetWidth() + _player->getWidth() * 0.5),
			ofRandom(-_player->getHeight() * 0.5, ofGetHeight() + _player->getHeight() * 0.5));
	}

	bool _isPlaying;
	string _path;
	float _startTime;
	ofVec2f _position;
	ofFbo _buffer;
	ofxWMFVideoPlayer* _player;
};

class doodlesPlayer
{
public:
	doodlesPlayer();
	~doodlesPlayer();
	void setup();
	void update();
	void draw();

private:

	vector<doodleDrawer> doodles;
	ofShader shader;
	pingPongBuffer posPingPong;

};

