#include "ofApp.h"

/*
	React Glow: An Interactive Dance Performance

	Please see README.md and Class Definition Sheet to see structure of code.
*/


//--------------------------------------------------------------
void ofApp::setup() {
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update() {		
	sceneController.update();

}
    
//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);
	sceneController.display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	sceneController.keyPressed(key);
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
