#include "stretchMesh.h"



stretchMesh::stretchMesh()
{
	headPos.x = ofRandom(ofGetWidth(), ofGetHeight());

	mesh.setMode(OF_PRIMITIVE_LINE_LOOP);

	body.push_back(headPos);

	for (int i = 0; i < 50; i++) {
		body.push_back(headPos);
		vertices.push_back(ofVec2f(0, 0));
		vertices.push_back(ofVec2f(0, 0));

		_mesh.addVertex(ofPoint(0, 0));
		_mesh.addVertex(ofPoint(0, 0));
		_mesh.addVertex(ofPoint(0, 0));
	}
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
	ofLog() << "head : " << headPos.x << " : " << headPos.y;
	ofFill();
	ofSetColor(0);
	for (auto pos : body)
		ofEllipse(pos.x, pos.y, 10, 10);

	ofSetColor(255, 0, 0);

	ofEllipse(headPos.x, headPos.y, 10, 10);
	
	ofSetColor(0, 0, 255);
	//draw verts
	drawVerts();
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
	ofNoFill();
	ofSetLineWidth(1);
	ofSetColor(0);

	int width = 40;
	ofVec2f a1, a2, b1, b2;
	int vertCount = 0;

	while (vertCount < vertices.size()) {

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

		ofVec2f triangle1[3] = { a1, a2, b2 };
		drawTriangle(triangle1);

		ofVec2f triangle2[3] = { a1, b2, b1 };
		drawTriangle(triangle2);

	}
}

void stretchMesh::drawTriangle(ofVec2f triangle[])
{
	ofPath path;
	path.setFilled(false);
	path.setColor(0);
	path.setStrokeWidth(1);
	path.setStrokeColor(0);
	
	bool first = true;
	ofVec2f v;
	for (int j = 0; j < 3; j++) {
		v = triangle[j];
		if (first) {
			first = false;
			path.moveTo((v.x + 1) * 0.5 * ofGetWidth(), (-v.y + 1) * 0.5 * ofGetHeight());
		}
		else {
			path.lineTo((v.x + 1) * 0.5 * ofGetWidth(), (-v.y + 1) * 0.5 * ofGetHeight());
		}
	}
	v = triangle[0];
	path.lineTo((v.x + 1) * 0.5 *  ofGetWidth(), (-v.y + 1) * 0.5 * ofGetHeight());
	path.close();
	path.draw();
}

void stretchMesh::updateHead()
{
	float time = ofGetElapsedTimef();
	ofVec2f desiredVelocity = checkCollisions().normalize() * 5.0;
	ofVec2f noise = ofVec2f(sin(time * 0.1), cos(time * 0.1)) *  0.001;
	acceleration = noise + desiredVelocity;
	//limit force
	limit(acceleration, 0.1);

	speed = speed + acceleration;
	//limit speed
	limit(speed, 14.0);

	headPos += speed;
}

void stretchMesh::updateBody()
{
	ofVec2f previous(headPos);

	for (int i = 0; i < body.size(); i++) {
		auto& node = body[i];
		node.interpolate(previous, 0.1);
		previous = node;
	}
}

void stretchMesh::updateVerts()
{
	int width = 40;
	ofVec2f perp;
	ofVec2f a1;
	int vertCount = 0;

	for (int i = 0; i < body.size() - 1; i++) {
		ofVec2f &node = body[i];
		ofVec2f &next = body[i + 1];

		perp = ofVec2f(node.y - next.y, -(node.x - next.x));
		perp.normalize();

		//update verts
		a1 = ofVec2f(node.x + perp.x * width, node.y + perp.y * width);
		ofVec2f &v1 = vertices[vertCount++];
		v1.x = (a1.x / ofGetWidth()) * 2 - 1;
		v1.y = (1 - a1.y / ofGetHeight()) * 2 - 1;

		a1 = ofVec2f(node.x + perp.x * -width, node.y + perp.y * -width);
		ofVec2f &v2 = vertices[vertCount++];
		v2.x = (a1.x / ofGetWidth()) * 2 - 1;
		v2.y = (1 - a1.y / ofGetHeight()) * 2 - 1;
	}
}

void stretchMesh::limit(ofVec2f & vec, float max)
{
	if (vec.length() > max)
		vec = vec.normalize() * max;
}
