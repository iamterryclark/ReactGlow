#include "Joints.h"

Joints::Joints() {
	//I decide to make to push back the reference to the normalised vectors in order to then be able to update
	//and use the updated positions
	skelJoints.push_back(&normalisedHead);

	skelJoints.push_back(&normalisedLeftHand);
	skelJoints.push_back(&normalisedLeftElbow);
	skelJoints.push_back(&normalisedLeftShoulder);

	skelJoints.push_back(&normalisedRightHand);
	skelJoints.push_back(&normalisedRightElbow);
	skelJoints.push_back(&normalisedRightShoulder);
	cout << "Joints init" << endl;
}


Joints::~Joints() {
	/*for (auto it = skelJoints.begin(); it != skelJoints.end(); ++it) {
		delete *it;
	}

	skelJoints.clear();
	kinectCam->destroy_kinectInstance();*/
}

void Joints::update() {
	//Get all the useful joints data from the kinect, data returns back between -1 nd 1 which is actually good for shaders and coloring etc
	//I will remap these for ableton in the OSC class
	for (int i = 0; i < bodies; i++) {
		//Get the bodies tracked, although i am unable to just get one body index [0] at the moment
		auto b = this->kinectCam->kinect.getBodySource()->getBodies()[i];

		// check to see if a body is tracked...
		if (b.tracked) {

			//Check to see if hands are tracked, this was taken fro the oscHands example in the ofKinectforWindows2
			//Get  all the necessary 3d joint information to create poses.
			//Use the middle to normlise and create body mapped gestures
			middle = b.joints[JointType_SpineMid].getPositionInWorld();

			//Extra position for the pose
			head = b.joints[JointType_Head].getPositionInWorld();

			//Left Joints
			leftHand = b.joints[JointType_HandLeft].getPositionInWorld();
			leftElbow = b.joints[JointType_ElbowLeft].getPositionInWorld();
			leftShoulder = b.joints[JointType_ShoulderLeft].getPositionInWorld();

			//Right Joints
			rightHand = b.joints[JointType_HandRight].getPositionInWorld();
			rightElbow = b.joints[JointType_ElbowRight].getPositionInWorld();
			rightShoulder = b.joints[JointType_ShoulderRight].getPositionInWorld();

			//Normalise thejoint using the middle verticies for body mapped gestures
			normalisedHead = head - middle;

			normalisedLeftHand = leftHand - middle;
			normalisedLeftElbow = leftElbow - middle;
			normalisedLeftShoulder = leftShoulder - middle;

			normalisedRightHand = rightHand - middle;
			normalisedRightHand = rightElbow - middle;
			normalisedRightShoulder = rightShoulder - middle;
		}
	}
}


//Mainly this is only used for debugging and checking how well the skeleton tracks the body.
void Joints::draw() {
	ofPushStyle();
	//Draw everything to screen
	ofSetColor(150, 150, 50);
	ofFill();
	ofDrawCircle(head, 0.05);

	ofSetColor(255, 0, 0);
	ofDrawCircle(middle, 0.05);

	ofSetColor(0, 255, 0);
	ofDrawCircle(leftHand, 0.05);
	ofDrawCircle(leftElbow, 0.05);
	ofDrawCircle(leftShoulder, 0.05);

	ofSetColor(0, 0, 255);
	ofDrawCircle(rightHand, 0.05);
	ofDrawCircle(rightElbow, 0.05);
	ofDrawCircle(rightShoulder, 0.05);
	
	//Draw line betweeen all of the points
	ofSetColor(255);
	ofDrawLine(leftHand, leftElbow);
	ofDrawLine(leftElbow, leftShoulder);
	ofDrawLine(leftShoulder, rightShoulder);
	ofDrawLine(rightHand, rightElbow);
	ofDrawLine(rightElbow, rightShoulder);
	ofPopStyle();
}
