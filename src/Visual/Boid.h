//
//  Boid.hpp
//  flockingTest
//
//  Created by Terry Clark on 04/02/2017.
//
//

#ifndef Boid_hpp
#define Boid_hpp

//Reference https://processing.org/examples/flocking.html

#include "ofMain.h"
#include "Path.h"
#include "math.h"

class Path;

class Boid {

public:
	Boid(ofVec3f _pos);
	~Boid();

	void run(vector<Boid *> boids, float desiredSep, float neighborDistAli, float neighborDistCoh);
	void applyForce(ofVec3f force);
	void flock(vector<Boid *> boids, float desiredSep, float neighborDistAli, float neighborDistCoh);

	void update();
	void borders();
	void render();
	void follow(Path path);

	ofVec3f getNormalPoint(ofVec3f p, ofVec3f a, ofVec3f b);
	ofVec3f seek(ofVec3f target);
	ofVec3f seperate(vector<Boid *> boids, float desiredSep);
	ofVec3f align(vector<Boid *> boids, float neighborDistAli);
	ofVec3f cohesion(vector<Boid *> boids, float neighborDistCoh);

	ofVec3f pos, vel, acc = ofVec3f(0, 0, 0);

	float r;
	float maxforce;
	float maxspeed;

	bool debug = true;
};

#endif /* Boid_hpp */
