#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {


}

//--------------------------------------------------------------
void ofApp::update() {

	_mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	vector<ofVec3f> vertices = {
		ofVec3f(0, 0), ofVec3f(50, 0),
		ofVec3f(0, 50), ofVec3f(50, 50),
		ofVec3f(0, 100), ofVec3f(50, 100),
		ofVec3f(0, 150), ofVec3f(50, 150),
	};
	_mesh.addVertices(vertices);

	_mesh.addColor(ofFloatColor(1.0, 0.0, 0.0));
	_mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
	_mesh.addColor(ofFloatColor(0.0, 0.0, 1.0));
	_mesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
	_mesh.addColor(ofFloatColor(1.0, 0.0, 1.0));
	_mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
	_mesh.addColor(ofFloatColor(1.0, 1.0, 1.0));
	_mesh.addColor(ofFloatColor(0.5, 0.5, 0.5));

	_mesh.addIndices(new ofIndexType[3]{ 2,1,0 }, 3);
	_mesh.addIndices(new ofIndexType[3]{ 2,3,1 }, 3);
	_mesh.addIndices(new ofIndexType[3]{ 4,3,2 }, 3);
	_mesh.addIndices(new ofIndexType[3]{ 4,5,3 }, 3);
	_mesh.addIndices(new ofIndexType[3]{ 6,5,4 }, 3);
	_mesh.addIndices(new ofIndexType[3]{ 6,7,5 }, 3);

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofClear(0);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	_mesh.drawWireframe();
	glPointSize(10);
	ofSetColor(255, 0, 0);

	_mesh.drawVertices();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
