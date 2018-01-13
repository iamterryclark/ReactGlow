#pragma once
#include "ofMain.h"
#include "ofMath.h"
#include "KinectCam.h"

#define bodies 6
#define kinectDepth -200;

class Joints {
private:

protected:
public:
	Joints();
	~Joints();
	void update();
	void draw();
	vector <ofVec3f*> skelJoints;

	//Do I need to delete kinectCam?
	KinectCam *kinectCam = &KinectCam::get_kinectInstance();
	
	ofVec3f normalisedHead, head;
	ofVec3f middle; //No need for normalised middle it will always be 0
	ofVec3f normalisedLeftHand, leftHand;
	ofVec3f normalisedLeftElbow, leftElbow;
	ofVec3f normalisedLeftShoulder, leftShoulder;
	ofVec3f normalisedRightHand, rightHand;
	ofVec3f normalisedRightElbow, rightElbow;
	ofVec3f normalisedRightShoulder, rightShoulder;
};
