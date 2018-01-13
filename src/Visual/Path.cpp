//
//  Path.cpp
//  flockingTest
//
//  Created by Terry Clark on 29/04/2017.
//
//

#include "Path.h"


Path::Path(){
    radius = 20;
}

Path::~Path(){
    
}

void Path::addPoint(float x, float y, float z) {
    ofVec3f point = ofVec3f(x, y, z);
    points.push_back(point);
}

void Path::addPoint(ofVec3f point) {
    points.push_back(point);
}

// Draw the path
void Path::display() {
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    // Draw thick line for radius
    ofSetColor(255);
    ofSetLineWidth(radius);
    ofNoFill();
    ofBeginShape();
    for (ofVec3f v : points) {
        ofVertex(v.x, v.y, v.z);
    }
    ofEndShape();
    
    // Draw thin line for center of path
    ofSetColor(0);
    ofSetLineWidth(1);
    ofNoFill();
    ofBeginShape();
    for (ofVec3f v : points) {
        ofVertex(v.x, v.y, v.z);
    }
    ofEndShape();
    ofPopMatrix();
}

// Add a point to the path
ofVec3f Path::getStart() {
    return points.at(0);
}
    
ofVec3f Path::getEnd() {
    return points.at(points.size()-1);
}
