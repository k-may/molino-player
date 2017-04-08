#pragma once

#include "ofMain.h"
#include "player.h"

class starsPlayer : public player
{
public:
	starsPlayer();
	~starsPlayer();

	void setup() override;
	void update() override;
	void draw() override;
	void play() override;
	void pause() override;
	void setValue(float value) override;
	bool isPlaying;
	float opacity = 0;
	
	ofImage texture;
	ofVec2f particles;
};

