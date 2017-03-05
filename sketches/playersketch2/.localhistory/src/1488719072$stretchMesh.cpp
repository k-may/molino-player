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
