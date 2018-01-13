#pragma once
#include "Joints.h"
#include "ofxCenteredTrueTypeFont.h"

class Gestures {
private:
protected:
public:
	Gestures(Joints& _joints);
	~Gestures();

	double euclideanDistance(vector<ofVec3f*> _current, vector<ofVec3f> _stored);
	void poseChecker();

	Joints& joints;

	vector<ofVec3f> storedPose1;
	vector<ofVec3f> storedPose2;
	vector<ofVec3f> storedPose3;
	vector<ofVec3f> storedPose4;
	vector<ofVec3f> storedPose5;

	double poseDist1, poseDist2, poseDist3, poseDist4, poseDist5;
	float euclidThreshold = 0.4;
	bool pose1On, pose2On, pose3On, pose4On, pose5On;

	ofxCenteredTrueTypeFont gestureOnFont, poseDistFont;
};

