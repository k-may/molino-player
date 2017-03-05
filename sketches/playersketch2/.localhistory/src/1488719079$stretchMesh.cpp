#include "stretchMesh.h"



stretchMesh::stretchMesh()
{
}


stretchMesh::~stretchMesh()
{
}

void stretchMesh::update()
{
	updateHead();
	updateBody();
	updateVerts();
}

void stretchMesh::draw()
{
	//draw verts
}

ofVec2f stretchMesh::checkCollisions()
{
	ofVec2f desired(0,0);

	if (headPos.x <= 25) {
		desired.x = 20;
	}
	else if (headPos.x >= ofGetWidth() -25) {
		desired.x = -20;
	}

	if (headPos.y <= 0) {
		desired.y = 20;
	}
	else if (headPos.y >= buffer.height - 25) {
		desired.y = -20;
	}
	return desired;
}

void stretchMesh::updateHead()
{
	ofVec2f targetPos = checkCollisions();

	if (headPos.x <= 25) {
		targetPos.x = 20;
	}
	else if(headPos.x > ofGetWidth() - 25){
		targetPos.x = -20;
	}
}
