#pragma once
#include "ofMain.h"
#include "FlowField.h"
class Vehicle
{
public:
	Vehicle(ofVec2f l, float ms, float mf);
	~Vehicle();
	void run();
	void follow(FlowField *_flow);
	void applyForce(ofVec2f force);
	void update();
	void display();
	void borders();

	ofVec2f position;
	ofVec2f velocity;
	ofVec2f acceleration;

	float r;
	float maxspeed;
	float maxforce;
};

