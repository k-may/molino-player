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
	else if (headPos.y >= ofGetHeight() - 25) {
		desired.y = -20;
	}

	return desired;
}

void stretchMesh::updateHead()
{
	float time = ofGetElapsedTimef();
	ofVec2f desiredVelocity = checkCollisions().normalize() * 5.0;
	ofVec2f noise = ofVec2f(sin(time * 0.0001), cos(time * 0.0001)) *  0.001;
	acceleration = noise + desiredVelocity;
	//limit force
	this.limit(this.acceleration, 0.1);

	this.speed.add(this.acceleration);
	//limit speed
	this.limit(this.speed, 14);

	this.headPos.add(this.speed);
}

void stretchMesh::limit(ofVec2f & vec)
{
	if (vec.length > max)
		vec = vec.normalize() * max;
}
