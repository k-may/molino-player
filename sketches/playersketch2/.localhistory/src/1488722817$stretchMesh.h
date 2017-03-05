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
	
	void drawVerts();
	void drawTriangle(ofVec2f p1, ofVec2f p2, ofVec2f p3);

	void updateHead();
	void updateBody();
	void updateVerts();

	void limit(ofVec2f & vec, float max);
	vector<ofVec2f> vertices;
	
	vector<ofVec2f> body;
	ofVec2f headPos;

	ofVec2f speed;
	ofVec2f target;
	ofVec2f acceleration;

};

