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
	limit(acceleration, 0.1);

	speed += acceleration;
	//limit speed
	limit(speed, 14.0);

	headPos += speed;
}

void stretchMesh::updateBody()
{
	ofVec2f previous(headPos);

	for (int i = 1; i < this.body.length; i++) {
		var node = this.body[i];
		node = node.lerp(previous, 0.1);
		previous = node;
	}
}

void stretchMesh::limit(ofVec2f & vec, float max)
{
	if (vec.length > max)
		vec = vec.normalize() * max;
}
