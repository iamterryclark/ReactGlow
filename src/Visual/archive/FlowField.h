#pragma once

#include "ofMain.h"

class FlowField
{
public:
	FlowField(int r, ofVec3f _screen, ofVec3f _screenPos);
	~FlowField();
	void display();
	void update();
	void drawVector(ofVec2f v, float x, float y, float scayl);
	ofVec2f lookup(ofVec2f lookup);
	float heading2d(ofVec3f _vel);
	int cols, rows;
	int resolution;
	ofVec3f screen, screenPos;
	float zoff = 0.0;
	vector<vector<ofVec2f>> field;
};

