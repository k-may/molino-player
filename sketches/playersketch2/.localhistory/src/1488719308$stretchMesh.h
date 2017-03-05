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

	ofVec2f checkCollisions();
	void updateHead();
	void updateBody();
	void updateVerts();
	void limit(ofVec2f & vec, float max);
	vector<ofVec2f> vertices;
	
	vector<ofVec2f> body;
	ofVec2f headPos;

	float speed;
	ofVec2f target;
	ofVec2f acceleration;

};

