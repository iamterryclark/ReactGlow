#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Gestures.h"
#include "Vehicle.h"
#include "Joints.h"
#include "ofxGui.h"

#define HOST "localhost"
//#define HOST "10.100.15.21"
//#define HOST "192.168.0.100"
//#define HOST "192.168.0.31"
#define PORTLISTEN 12345
#define PORTSEND 9000

class OSCController {
private:
protected:
public:
	OSCController();
	~OSCController();
	void retreive(vector <Vehicle*> *_vehicles);
	void playScene(int scene);
	void play();
	void stop();
	void streamToInstrumentDevice(string address, int track, int device, int parameter, float value);
	ofxOscReceiver oscRetreive;
	ofxOscSender oscSender;

	string tweetCol;
	int currentTweetNum;
	const int timeDelay = 100;

	KinectCam *kinectCam = &KinectCam::get_kinectInstance();

	//This controls which part the performance is playing
	//Controlled by the saved poses on the dancer
	int scene = 0;
};

