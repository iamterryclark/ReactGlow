//
//  Flock.hpp
//  flockingTest
//
//  Created by Terry Clark on 04/02/2017.
//
//

#ifndef Flock_hpp
#define Flock_hpp

#include <stdio.h>
#include "Boid.h"

class Boid;

class Flock {
public:
    Flock();
    ~Flock();

    void run(Path p, float desiredSep, float neighborDistAli, float neighborDistCoh);
    void display();
    void addBoid(Boid * b);
    
    ofShader shader;

    // particles
    vector<Boid *> boids;
    ofFloatPixels positionsPix;     // cpu
    ofTexture positionsTex;    // gpu
    
    int maxCount;
    bool shaderDraw = true;
    

    
};
#endif /* Flock_hpp */
