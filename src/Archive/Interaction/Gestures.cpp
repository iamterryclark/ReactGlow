#include "Gestures.h"

Gestures::Gestures(Joints& _joints) : 
joints(_joints) 
{
	//Load the vectors with blanks
	for (int i = 0; i < joints.skelJoints.size(); i++) {
		storedPose1.push_back(ofVec3f(0, 0, 0));
		storedPose2.push_back(ofVec3f(0, 0, 0));
		storedPose3.push_back(ofVec3f(0, 0, 0));
		storedPose4.push_back(ofVec3f(0, 0, 0));
		storedPose5.push_back(ofVec3f(0, 0, 0));
	}

	gestureOnFont.load("open-sans/OpenSans-Light.ttf", 5);
	poseDistFont.load("open-sans/OpenSans-Bold.ttf", 3);

	cout << "Gestures Init" << endl;
}


Gestures::~Gestures() 
{	
}

void Gestures::poseChecker() 
{
	poseDist1 = euclideanDistance(joints.skelJoints, storedPose1);
	poseDist2 = euclideanDistance(joints.skelJoints, storedPose2);
	poseDist3 = euclideanDistance(joints.skelJoints, storedPose2);
	poseDist4 = euclideanDistance(joints.skelJoints, storedPose2);
	poseDist5 = euclideanDistance(joints.skelJoints, storedPose2);

	ofPushMatrix();
	ofPushStyle();
	ofSetColor(255);
	ofRotate(180, 0, 1, 0);

	if (poseDist1 < euclidThreshold) {
		bool pose1On = true;
		gestureOnFont.drawStringCentered("Gesture 1 Activated", 1, -1);
	}
	else if (poseDist2 < euclidThreshold) {
		pose2On = true;
		gestureOnFont.drawStringCentered("Gesture 2 Activated", 1, -1);
	}
	else if (poseDist3 < euclidThreshold) {
		pose2On = true;
		gestureOnFont.drawStringCentered("Gesture 3 Activated", 1, -1);
	}
	else if (poseDist4 < euclidThreshold) {
		pose2On = true;
		gestureOnFont.drawStringCentered("Gesture 4 Activated", 1, -1);
	}
	else if (poseDist5 < euclidThreshold) {
		pose2On = true;
		gestureOnFont.drawStringCentered("Gesture 5 Activated", 1, -1);
	}
	else {
		pose1On = pose2On = pose3On = pose4On = pose5On = false;
		gestureOnFont.drawStringCentered("No Gestures Activated", ofGetWidth() / 2, ofGetHeight() - 40);

	}

	poseDistFont.drawStringCentered("Pose 1: " + to_string(poseDist1), 6, 6);
	poseDistFont.drawStringCentered("Pose 2: " + to_string(poseDist2), 6, 5.5);
	poseDistFont.drawStringCentered("Pose 3: " + to_string(poseDist3), 6, 5);
	poseDistFont.drawStringCentered("Pose 4: " + to_string(poseDist4), 6, 4.5);
	poseDistFont.drawStringCentered("Pose 5: " + to_string(poseDist5), 6, 4);
	ofPopStyle();
	ofPopMatrix();
}

//Euclidean Distance algorithm to detect which pose is activated, this was disucssed in our Perception and Multimedia Computing Lecutre
double Gestures::euclideanDistance(vector<ofVec3f*> _current, vector<ofVec3f> _stored) 
{
	//Set this always to 0 at the beginning to reset the euclidean distance value
	//If we don't do this the value will only accumulate 
	double sum = 0.0;

	for (int i = 0; i < _current.size(); i++) { //Assuming the vectors are the same size (which they are)
		
		//Adding the euclidenan formula to sum
		sum += pow(_current[i]->x - _stored[i].x, 2) +
			pow(_current[i]->y - _stored[i].y, 2) +
			pow(_current[i]->z - _stored[i].z, 2);
	}

	//Don't forget to square root the absolute value to make sure its positive.
	return sqrt(abs(sum));
}
