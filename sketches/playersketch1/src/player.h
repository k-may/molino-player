#pragma once
class player
{
public:
	player();
	~player();
	virtual void draw();
	virtual void update();
	virtual void setup();
	virtual void play();
	virtual void pause();
	virtual void setValue(float value);
};

