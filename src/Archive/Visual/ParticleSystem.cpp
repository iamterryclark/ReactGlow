#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

	cout << "ParticleSystem Init" << endl;
}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::addParticle(string _tweetCol) {
	particles.push_back(Particle(_tweetCol));
}

void ParticleSystem::run(int _coordNum) {
	for (Particle& p : particles) {
		p.update(_coordNum);
	}
}

void ParticleSystem::display(int _avgRms) {	
	for (int i = 0; i < particles.size(); i++){
		particles[i].display(_avgRms);
	}
}