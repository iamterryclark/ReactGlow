#pragma once
#include "ofMain.h"
#include "ofMath.h"
#include "Joints.h"
#include "ofxDmx.h"

class LightController
{
public:
	LightController(ofVec3f _lLightPos, ofVec3f _rLightPos, ofVec3f &_target);
	~LightController();

	void update();
	void leftLight();
	void rightLight();
	void display();

	ofVec3f lLightPos, rLightPos, &target;

	float rPan, rTilt, lPan, lTilt;
	
	bool usingDMX = false;

	ofxDmx dmx;

	Joints joints;
};

