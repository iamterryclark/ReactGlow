#pragma once

#include "ofMain.h"
#include "PointCloud.h"
#include "Particle.h"

class ParticleSystem {
private:

protected:
public:
	ParticleSystem();
	~ParticleSystem();
	void addParticle(string _tweetCol);
	void run(int _coordNum);
	void display(int _avgRms);

	//Grab pointcloud to attach each point to the pointcloud positions
	//PointCloud *pointcloud = &PointCloud::get_pCloudInstance();

	vector<Particle> particles;

};