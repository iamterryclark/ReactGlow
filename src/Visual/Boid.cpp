//
//  Boid.cpp
//  flockingTest
//
//  Created by Terry Clark on 04/02/2017.
//
//

#include "Boid.h"


Boid::Boid(ofVec3f _pos) : pos(_pos)
{
	r = 0.04;
	maxspeed = 0.05;
	maxforce = 0.09;
}

Boid ::~Boid() {

}

void Boid::run(vector<Boid *> boids, float desiredSep, float neighborDistAli, float neighborDistCoh) {
	flock(boids, desiredSep, neighborDistAli, neighborDistCoh);
	update();
	borders();
	render();
}

void Boid::applyForce(ofVec3f force) {
	// We could add mass here if we want A = F / M
	acc += force;
}

void Boid::flock(vector<Boid *> boids, float desiredSep, float neighborDistAli, float neighborDistCoh) {

	//Settup position taking into account the three ideas fo flocking
	ofVec3f sep = seperate(boids, desiredSep);
	ofVec3f ali = align(boids, neighborDistAli);
	ofVec3f coh = cohesion(boids, neighborDistCoh);

	sep *= 1.5;
	ali *= 1.0;
	coh *= 1.0;

	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void Boid::update() {
	vel += acc;
	vel.limit(maxspeed);
	pos += vel;
	acc *= ofVec3f(0, 0, 0); // Reset for every cycle
}

void Boid::borders() {
	if (pos.x <  0.0)  vel.x =  0.05;
	if (pos.x >  6.0)  vel.x = -0.05;
	if (pos.y <  0.0)  vel.y =  0.05;
	if (pos.y >  6.0)  vel.y = -0.05;
	if (pos.z < -6.0)  vel.z =  0.05;
	if (pos.z >  6.0)  vel.z = -0.05;
}

void Boid::render() {
	//possible issue here as direction is needed also.
	float angle = (float)atan2(-vel.y, vel.x);
	float theta = -1.0 * angle;
	float heading2D = ofRadToDeg(theta) + 90;

	ofSetColor(255, 100);
	ofFill();

	ofPushMatrix();
	ofTranslate(pos);
	ofRotateZ(heading2D);
	ofBeginShape();
	ofVertex(0, -r * 2, r);
	ofVertex(-r, r * 2, -r);
	ofVertex(r, r * 2, 0);
	ofEndShape(true);
	ofPopMatrix();
}

void Boid::follow(Path p) {

	// Predict position 50 (arbitrary choice) frames ahead
	// This could be based on speed
	ofVec3f predict = vel;
	predict.normalize();
	predict *= 50;
	ofVec3f predictpos = pos + predict;

	// Now we must find the normal to the path from the predicted position
	// We look at the normal for each line segment and pick out the closest one

	ofVec3f normal = ofVec3f(0, 0, 0);
	ofVec3f target = ofVec3f(0, 0, 0);

	float worldRecord = 1000000;  // Start with a very high record distance that can easily be beaten

								  // Loop through all points of the path
	for (int i = 0; i < p.points.size() - 1; i++) {

		// Look at a line segment
		//Re - center the flock so that (0,0,0) is in the middle of the screen (Terry) 
		ofVec3f a = p.points[i] + ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
		ofVec3f b = p.points[i + 1] + ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);


		// Get the normal point to that line
		ofVec3f normalPoint = getNormalPoint(predictpos, a, b);

		// This only works because we know our path goes from left to right
		// We could have a more sophisticated test to tell if the point is in the line segment or not
		if (normalPoint.x < a.x || normalPoint.x > b.x) {
			// This is something of a hacky solution, but if it's not within the line segment
			// consider the normal to just be the end of the line segment (point b)
			normalPoint = b;
		}

		// How far away are we from the path?
		ofVec3f diffVec = predictpos - normalPoint;
		float distance = sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2) + pow(diffVec.z, 2));

		// Did we beat the record and find the closest line segment?
		if (distance < worldRecord) {
			worldRecord = distance;
			// If so the target we want to steer towards is the normal
			normal = normalPoint;

			// Look at the direction of the line segment so we can seek a little bit ahead of the normal
			ofVec3f dir = b - a;
			dir.normalize();

			// This is an oversimplification
			// Should be based on distance to path & velocity
			dir *= 10.0f;
			target = normalPoint;
			target += dir;
		}
	}

	// Only if the distance is greater than the path's radius do we bother to steer
	if (worldRecord > p.radius) {
		applyForce(seek(target));
	}

	// Draw the debugging stuff
	if (debug) {
		// Draw predicted future position
		ofSetColor(0);
		ofFill();
		ofDrawLine(pos, predictpos);
		ofDrawEllipse(predictpos, 4, 4);

		// Draw normal position
		ofSetColor(0);
		ofFill();
		ofDrawEllipse(normal, 4, 4);

		// Draw actual target (red if steering towards it)
		ofDrawLine(predictpos, normal);

		if (worldRecord > p.radius) {
			ofSetColor(255, 0, 0);
			ofFill();
		}

		ofSetLineWidth(0);
		ofDrawEllipse(target, 8, 8);
	}
}

// This function could be optimized to make fewer new Vector objects
ofVec3f Boid::getNormalPoint(ofVec3f
	p, ofVec3f a, ofVec3f b) {

	// Vector from a to p
	ofVec3f ap = p - a;

	// Vector from a to b
	ofVec3f ab = b - a;

	ab.normalize(); // Normalize the line

					// Project vector "diff" onto line by using the dot product
	ab *= ap.dot(ab);

	ofVec3f normalPoint = a + ab;
	return normalPoint;
}


ofVec3f Boid::seek(ofVec3f target) {
	ofVec3f desired = target - pos;
	desired.normalize();
	desired = desired * maxspeed;

	ofVec3f steer = desired - vel;
	steer.limit(maxforce);
	return steer;
}

//Serperation
ofVec3f Boid::seperate(vector <Boid *> boids, float desiredSep) {
	ofVec3f steer = ofVec3f(0, 0, 0);
	int count = 0;

	for (Boid * other : boids) {

		ofVec3f diffVec = pos - other->pos;
		float distFloat = sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2) + pow(diffVec.z, 2));

		if ((distFloat > 0) && (distFloat < desiredSep)) {
			ofVec3f diff = pos - other->pos;

			diff.normalize();
			diff /= distFloat;
			steer += diff;
			count++;
		}
	}

	//Average -- divde by how many
	if (count > 0) steer /= (float)count;

	//Calculate magnitude of vector
	float mag = sqrt((pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2)));

	if (mag > 0) {
		//Reynolds Algorithmn:
		steer.normalize();
		steer *= maxspeed;
		steer -= vel;
		steer.limit(maxforce);
	}

	return steer;
}

//Alignment
ofVec3f Boid::align(vector<Boid *> boids, float neighborDistAli) {
	ofVec3f sum = ofVec3f(0, 0, 0);
	int count = 0;
	for (Boid * other : boids) {

		ofVec3f diffVec = pos - other->pos;
		float distFloat = sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2) + pow(diffVec.z, 2));

		if ((distFloat > 0) && (distFloat < neighborDistAli)) {
			sum += other->vel;
			count++;
		}
	}

	if (count > 0) {
		sum /= (float)count;
		sum.normalize();
		sum *= maxspeed;
		ofVec3f steer = sum - vel;
		steer.limit(maxforce);
		return steer;
	}
	else {
		return ofVec3f(0, 0, 0);
	}
}

//Cohesion
ofVec3f Boid::cohesion(vector<Boid *> boids, float neighborDistCoh) {
	ofVec3f sum = ofVec3f(0, 0, 0);
	int count = 0;

	for (Boid * other : boids) {
		ofVec3f diffVec = this->pos - other->pos;
		float distFloat = sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2) + pow(diffVec.z, 2));
		if ((distFloat > 0) && (distFloat < neighborDistCoh)) {
			sum += other->pos;
			count++;
		}
	}

	if (count > 0) {
		sum /= count;
		return seek(sum);
	}
	else {
		return ofVec3f(0, 0, 0);
	}

}








