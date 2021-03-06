#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


}

//--------------------------------------------------------------
void ofApp::update(){

	vector<ofVec3f> vertices = {
		ofVec3f(0, 0), ofVec3f(50, 0),
		ofVec3f(0, 50), ofVec3f(50, 50),
		ofVec3f(0, 100), ofVec3f(50, 100),
		ofVec3f(0, 150), ofVec3f(50, 150),
	};
	_mesh.addVertices(vertices);

	vector<ofIndexType> indices = {
		2,1,0,
		3,4,2,
		6,4,3,
		5,6,4,
		7,6,5,
		7,8,6
	};
	_mesh.addIndices(indices);

	_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofClear(0);
	
	_mesh.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
