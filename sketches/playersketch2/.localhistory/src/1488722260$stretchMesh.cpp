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
	ofVec2f desired(0, 0);

	if (headPos.x <= 25) {
		desired.x = 20;
	}
	else if (headPos.x >= ofGetWidth() - 25) {
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

void stretchMesh::drawVerts()
{
	ofSetLineWidth(2);
	ofSetColor(0);

	int width = 40;
	ofVec2f a1, a2, b1, b2;
	int vertCount = 0;

	while (vertCount < vertices.size) {

		if (vertCount < 2) {
			a1 = vertices[vertCount++];
			a2 = vertices[vertCount++];
		}
		else {
			a1 = b1;
			a2 = b2;
		}

		b1 = vertices[vertCount++];
		b2 = vertices[vertCount++];

		drawTriangle({ a1, a2, b2 });
		//triangles.push(triangle);

		triangle = { a1, b2, b1 };
		this.drawTriangle(this.buffer.ctx, triangle);
		this.triangles.push(triangle);

	}
	this.buffer.ctx.stroke();
}

void stretchMesh::drawTriangle(ofVec2f triangle[])
{
}

void stretchMesh::drawTriangle()
{
	var first = true;
	var v;
	for (var j = 0; j < 3; j++) {
		v = triangle[j];
		if (first) {
			first = false;
			ctx.moveTo((v.x + 1) * 0.5 * this.buffer.width, (-v.y + 1) * 0.5 * this.buffer.height);
		}
		else {
			ctx.lineTo((v.x + 1) * 0.5 * this.buffer.width, (-v.y + 1) * 0.5 * this.buffer.height);
		}
	}
	v = triangle[0];
	ctx.lineTo((v.x + 1) * 0.5 * this.buffer.width, (-v.y + 1) * 0.5 * this.buffer.height);
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

	for (int i = 1; i < body.size; i++) {
		auto& node = body[i];
		node = node.getInterpolated(previous, 0.1);
		previous = node;
	}
}

void stretchMesh::updateVerts()
{
	int width = 40;
	ofVec2f perp;
	ofVec2f a1;
	int vertCount = 0;

	for (int i = 0; i < body.size - 1; i++) {
		ofVec2f &node = body[i];
		ofVec2f &next = body[i + 1];

		perp = ofVec2f(node.y - next.y, -(node.x - next.x));
		perp.normalize();

		//update verts
		a1 = ofVec2f(node.x + perp.x * width, node.y + perp.y * width);
		ofVec2f &v = vertices[vertCount++];
		v.x = (a1.x / ofGetWidth()) * 2 - 1;
		v.y = (1 - a1.y / ofGetHeight()) * 2 - 1;

		a1 = ofVec2f(node.x + perp.x * -width, node.y + perp.y * -width);
		ofVec2f &v = vertices[vertCount++];
		v.x = (a1.x / ofGetWidth()) * 2 - 1;
		v.y = (1 - a1.y / ofGetHeight()) * 2 - 1;
	}
}

void stretchMesh::limit(ofVec2f & vec, float max)
{
	if (vec.length > max)
		vec = vec.normalize() * max;
}
