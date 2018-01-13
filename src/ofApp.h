#pragma once

#include "ofMain.h"
#include "SceneController.h"

//#define BUFFER_SIZE 256
//#define NUM_WINDOWS 80

class ofApp : public ofBaseApp {
private:
	//All for Audio input (currently microphone)
	//float * left;
	//float * right; //Not using right channel just need a simple audio reaction to the orbs
	//int 	bufferCounter;

	//float magnitude[BUFFER_SIZE];
	//float phase[BUFFER_SIZE];
	//float power[BUFFER_SIZE];

	//float freq[NUM_WINDOWS][BUFFER_SIZE / 2];
	//float freq_phase[NUM_WINDOWS][BUFFER_SIZE / 2];

	//ofSoundStream soundStream; //From the soundcard

protected:

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	//Regular Classes
	SceneController sceneController;

	//Audio Variables
	float inputSignal = 0;
	float smoothedValue, deltaValue;
	float outputValue;
};