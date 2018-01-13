#include "LightController.h"



LightController::LightController(ofVec3f _lLightPos, ofVec3f _rLightPos, ofVec3f &_target) :
lLightPos(_lLightPos),
rLightPos(_rLightPos),
target(_target)
{
	if (usingDMX) { //Change to true when Entec box connected
		dmx.connect("COM3", 150); //Serial Port Number
		dmx.update(true); //Resets the lights to 0 position in all channels
	}	
}


LightController::~LightController()
{
	//When object is destoryed dmx will clear all messages and then reset to 0
	if (usingDMX) {
		dmx.clear(); 
		dmx.update(true);
	}
}

void LightController::update() {
		leftLight();
		rightLight();

		if (dmx.isConnected()) {
			dmx.update(); // Gets next dmx message
		}
}

void LightController::leftLight() {

	//Left Light
	ofVec3f lDist = target - lLightPos;

	lPan = ofMap(abs(ofRadToDeg(atan(lDist.x / lDist.z))), 0, 540, 0, 255);
	lTilt = ofMap(abs(ofRadToDeg(atan(lDist.y / lDist.x))), 0, 180, 0, 255);

	if (usingDMX) {
		dmx.setLevel(70, 255);  //Shutter Open
		dmx.setLevel(71, 255);  //Dimmer
		dmx.setLevel(72, lPan);  //Pan
		dmx.setLevel(74, lTilt); //Tilt
		dmx.setLevel(81, ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255));  //White Light
	}

	/*if (ofGetFrameNum() % 10 == 0) {
	float panInDeg = ofMap(pan, 0, 255, 0, 540);
	float tiltInDeg = ofMap(tilt, 0, 255, 0, 180);
	cout << "Pan : " << panInDeg << endl;
	cout << "Tilt : " << tiltInDeg << endl;
	}*/


}

void LightController::rightLight() {
	//Right Light
	ofVec3f rDist = target - rLightPos;

	rPan = ofMap(abs(ofRadToDeg(atan(rDist.z / rDist.x))), 0, 540, 0, 255);
	rTilt = ofMap(abs(ofRadToDeg(atan(rDist.y / rDist.x))), 0, 180, 0, 255);

	if (usingDMX) {
		dmx.setLevel(110, 255);  //Shutter Open
		dmx.setLevel(111, 255);  //Dimmer
		dmx.setLevel(112, rPan); //Pan
		dmx.setLevel(114, rTilt); //Tilt
		dmx.setLevel(121, ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255));  //White Light
	}

	//pan = ofMap(pan, 0, 255, 0, 540);
	//tilt = ofMap(tilt, 0, 255, 0, 180);
	//cout << "Pan : " <<  pan << endl;
	//cout << "Tilt : " <<  tilt << endl;
}


void LightController::display() {

	//LeftLight
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(lLightPos);

	//Convert 255 to degrees 360 in order to display the lights rotation correctly
	float lPanToDeg = ofMap(lPan, 0, 255, 0, 540);
	float lTiltToDeg = ofMap(lTilt, 0, 255, 0, 180);
	
	ofRotate(-lPanToDeg, 0, 1, 0);
	ofRotate(lTiltToDeg, 1, 0, 0);

	//Axis
	ofSetColor(ofColor::rosyBrown);
	ofDrawLine(0, 0, 0, 0, 0, 4);
	ofSetColor(ofColor::blue);
	ofDrawLine(0, 0, 0, 1, 0, 0);
	ofSetColor(ofColor::green);
	ofDrawLine(0, 0, 0, 0, 1, 0);

	//LightPos
	ofSetColor(ofColor::red);
	ofFill();
	ofDrawCircle(0, 0, 0, 0.2);
	ofPopStyle();
	ofPopMatrix();

	//RightLight
	ofPushMatrix();
	ofPushStyle();
	ofTranslate(rLightPos);

	//Convert 255 to degrees 360 in order to display the lights rotation correctly
	float rPanToDeg = ofMap(rPan, 0, 255, 0, 540);
	float rTiltToDeg = ofMap(rTilt, 0, 255, 0, 180);

	ofRotate(-rPanToDeg + 90, 0, 1, 0);
	ofRotate(rTiltToDeg, 1, 0, 0);

	//Axis
	ofSetColor(ofColor::rosyBrown);
	ofDrawLine(0, 0, 0, 0, 0, 4);
	ofSetColor(ofColor::blue);
	ofDrawLine(0, 0, 0, 1, 0, 0);
	ofSetColor(ofColor::green);
	ofDrawLine(0, 0, 0, 0, 1, 0);

	//LightPos
	ofSetColor(ofColor::red);
	ofFill();
	ofDrawCircle(0, 0, 0, 0.2);
	ofPopStyle();
	ofPopMatrix();

	/*if (ofGetFrameNum() % 20 == 0) {
	cout << "Joint Middle" << joints.middle << endl;
	cout << "Left Light Dist : " << leftLightDist << endl;
	cout << "Left Light Pan  : " << leftLightPan << endl;
	cout << "Left Light Tilt : " << leftLightTilt << endl;

	//cout << "Right Light Dist : " << rightLightDist << endl;
	//cout << "Right Light Pan  : " << rightLightPan << endl;
	//cout << "Right Light Tilt : " << rightLightTilt << endl;
	}*/

}

