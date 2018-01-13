#include "Vehicle.h"

Vehicle::Vehicle(ofVec2f l, float ms, float mf) :
	position(l),
	maxspeed(ms),
	maxforce(mf)
{
	r = ofRandom(3.0, 6.0);
	acceleration = ofVec2f(ofRandom(10, 30), ofRandom(10, 30));
	velocity = ofVec2f(10, 100);
}


Vehicle::~Vehicle()
{
}

void Vehicle::run() {
	update();
	borders();
	display();
}

void Vehicle::follow(FlowField *_flow) {
	ofVec2f desired = _flow->lookup(position);
	desired *= maxspeed;
	ofVec2f steer = desired -= velocity;
	steer.limit(maxforce);
	applyForce(steer);
}

void Vehicle::applyForce(ofVec2f force) {
	acceleration += (force);
}

void Vehicle::update() {
	velocity += acceleration;
	velocity.limit(maxspeed);
	position += velocity;
	acceleration *= 0;
}

void Vehicle::display() {
	// Draw a triangle rotated in the direction of velocity
	ofSetColor(255);
	ofFill();
	ofPushMatrix();
	ofTranslate(position.x, position.y);
	ofDrawCircle(0, 0, r);
	ofPopMatrix();
}

void Vehicle::borders() {
	// Wraparound
	if (position.x < -r) position.x = ofGetWidth() + r;
	if (position.y < -r) position.y = ofGetHeight() + r;
	if (position.x > ofGetWidth() + r) position.x = -r;
	if (position.y > ofGetHeight() + r) position.y = -r;
}