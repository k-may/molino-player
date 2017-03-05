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


	void updateHead();
	void updateBody();
	void updateVerts();

	vector<ofVec2f> vertices;
	
	vector<ofVec2f> body;
	ofVec2f headPos;

	float speed;
	ofVec2f target;
	ofVec2f acceleration;

};

