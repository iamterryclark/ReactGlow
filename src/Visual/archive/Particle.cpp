#include "Particle.h"

Particle::Particle(string _tweetCol) : tweetCol(_tweetCol) {
	ease = ofRandom(0.01, 0.05);
	speed = ofRandom(0.25, 0.6);
	size = (0.5, 0.9);
	angle = ofRandom(360);
	pos = ofVec2f(ofRandom(-6,6), ofRandom(-6,6));
	//cout << "Particle init" << endl;
}

Particle::~Particle() {

}

void Particle::update(int coordNum) {
	runCoords(coordNum);
	easing(ease);
	target = coords;
}

void Particle::display(float _avgRms) {
	if (tweetCol == "purple" || tweetCol == "Purple") {
		ofSetColor(100, 0, 100);
	}
	else if (tweetCol == "blue" || tweetCol == "Blue") {
		ofSetColor(0,0,255);
	}
	else if (tweetCol == "red" || tweetCol == "Red") {
		ofSetColor(255, 0, 0);
	}
	else if (tweetCol == "green" || tweetCol == "Green") {
		ofSetColor(0,255,0);
	}
	else {
		ofSetColor(255);
	}
	
	ofSetColor(255);
	ofFill();
	ofDrawCircle(pos, (size + (_avgRms / 1000)));
}

void Particle::runCoords(int coordNum) {
	angle += speed;
	
	switch (coordNum) {
	case 0:
		coords = ofVec2f(scalar * cos(ofDegToRad(angle)),
						 scalar * sin(ofDegToRad(angle)) * cos(ofDegToRad(angle)));
		break;
	case 1:
		coords = ofVec2f(scalar * cos(ofDegToRad(angle) + cos(ofDegToRad(angle))),
						 scalar * sin(ofDegToRad(angle) * cos(ofDegToRad(angle))));
		break;
	case 2:
		coords = ofVec2f(scalar * cos(ofDegToRad(angle)),
						 scalar * sin(ofDegToRad(angle)));
		break;
	case 3:
		coords = ofVec2f(scalar * cos(ofDegToRad(angle) + cos(ofDegToRad(angle))),
						 scalar * sin(ofDegToRad(angle)) + cos(ofDegToRad(angle)));
		break;
	}
}

void Particle::easing(float easing) {
	float dx = target.x - pos.x;
	pos.x += dx * easing;
	float dy = target.y - pos.y;
	pos.y += dy * easing;
}