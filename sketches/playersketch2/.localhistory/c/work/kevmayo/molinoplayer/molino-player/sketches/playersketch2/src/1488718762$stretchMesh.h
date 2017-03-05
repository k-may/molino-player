#pragma once

#include "ofMain.h"

class stretchMesh
{
public:
	stretchMesh();
	~stretchMesh();
	void update();
	void draw();
private:

	vector<ofVec2f> vertices;
	vector<ofVec2f> body;
	ofVec2f headPos;

	float speed;
	ofVec2f acceleration;

};

