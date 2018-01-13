#include "ofApp.h"

//Reference https://github.com/elliotwoods/ofxKinectForWindows2/blob/master/exampleDepthToCameraTable/src/ofApp.cpp#L57
//--------------------------------------------------------------
void ofApp::setup() {
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	//Audio Input from Soundcard
	soundStream.printDeviceList();
	soundStream.setDeviceID(3); //Get Soudcard Info
	//setInput(soundStream);
	// 0 output channels,
    // 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)
	soundStream.setup(this, 0, 2, 44100, BUFFER_SIZE, 4);

	//Set to be an array of float pointers to the buffer size
	left = new float[BUFFER_SIZE];

	for (int i = 0; i < NUM_WINDOWS; i++)
	{
		for (int j = 0; j < BUFFER_SIZE / 2; j++)
		{
			freq[i][j] = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {		
	sceneController.update();

}
    
//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);
	sceneController.display(avgRms);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	sceneController.keyPressed(key);
}

//--------------------------------------------------------------

//Reference: https://forum.openframeworks.cc/t/audio-input-fft-example/186 example code found in one of the last posts by 'grimus'
void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i * 2];
		inputSignal = left[i] * 10;
	}
	bufferCounter++;

	sumOutput = 0;

	for (int i = 0; i < BUFFER_SIZE - 1; i++) {
		outputValue = inputSignal;
		sumOutput += outputValue * outputValue;
	}

	rms = sqrt(sumOutput);

	avgRms *= smoothness;
	avgRms += ((1 - smoothness) * rms); //We minus smoothness from 1 as we always want a value under 1;
	//cout << inputSignal << endl;	
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
