//
//  Flock.cpp
//  flockingTest
//
//  Created by Terry Clark on 04/02/2017.
//
//

#include "Flock.h"


Flock::Flock(){
    
    shader.load("shader/shader");
    
    ofSetColor(200,100,0);
    
    // flat vehicles array
    for (int i = 0 ; i < 60; i ++){
        boids.push_back(new Boid(ofVec3f(ofRandom(-6.0,6.0), ofRandom(-6.0,6.0), ofRandom(-6.0, 6.0))));
    }
    
    // pixels to set positions and other boid params to be passed shader
    positionsPix.allocate(10, 10, OF_PIXELS_RGBA);
    
    // texture to pass to shader which will take the above information and store it here
    positionsTex.allocate(positionsPix);
    positionsTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
	//Used to ativate the boids in the shader
    maxCount = 1;
}

Flock::~Flock(){
    for (Boid * b : boids){
        delete b;
        b = nullptr;
    }
}

void Flock::run(Path p, float desiredSep, float neighborDistAli, float neighborDistCoh){
   //Run the flock individually passing the flocking algorithm parameters 
    for (Boid * b : boids){
        b->run(boids, desiredSep, neighborDistAli, neighborDistCoh); //Ajusted in the gui
        b->follow(p);
    }
    
	//Store all boid positions depth and pulse rate in a texture.

    for (int y = 0; y < positionsPix.getHeight(); y++) {
        for (int x = 0; x < positionsPix.getWidth(); x++){
            int i = x + y * (int)positionsPix.getWidth();
            
            if (i > maxCount) {
                break;
            }
          
            ofFloatColor pos(
                             boids[i]->pos.x, // boids pos x
                             boids[i]->pos.y, // boids pos y
                             ofRandom(-0.05, 0.05), //Depth
                             ofRandom(0.001, 0.002) //Pulse rate
                             );
            
            positionsPix.setColor(x, y, pos);
        }
    }
    
    positionsTex.loadData(positionsPix);
}

void Flock::display(){
    {
        for (Boid * b : boids){
            b->render();
        }
       
        shader.begin();
        {
			//Pass uniforms the the shader
            shader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
            shader.setUniform1i("maxCount", maxCount);
            shader.setUniformTexture("positions", positionsTex, 0);
			
			//Draws/hides the shader
            if(shaderDraw) ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
        shader.end();
      
    }
}

void Flock::addBoid(Boid * b) {
    boids.push_back(b);
}


