#pragma once

#include "ofMain.h"

class Particle
{
public:
	Particle(string _tweetCol);
	~Particle();
	
	void update(int coordNum);
	void display(float _avgRms);
	void runCoords(int coordNum);
	void easing(float _easing);

	int coordNum = 0;
	int size;
	
	float scalar = 4.0;
	float angle = 0.0, ease = 0.0, speed = 0.0;

	ofVec2f pos, target;
	ofVec2f coords;

	string tweetCol;
};

