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

	vector<ofVec2f> body;
};

