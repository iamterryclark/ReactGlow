//
//  Path.hpp
//  flockingTest
//
//  Created by Terry Clark on 29/04/2017.
//
//

#ifndef Path_hpp
#define Path_hpp

#include "ofMain.h"

class Path {
public:
    Path();
    ~Path();
    
    void addPoint(float x, float y, float z);
    void addPoint(ofVec3f point);
    void display();
    
    ofVec3f getStart();
    ofVec3f getEnd();
    
    vector <ofVec3f> points;
    float radius;

};

#endif /* Path_hpp */
