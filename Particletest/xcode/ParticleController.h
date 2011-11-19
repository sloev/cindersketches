#pragma once
#include "Particle.h"
#include <list>
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"

class ParticleController {
 public:
	ParticleController();
	void update();
	void draw();
	void addParticles( int w, int h, int amt);
    void addParticle( int xi, int yi,  float radius );
	void removeParticles( int amt );    
    
	
	std::list<Particle>	mParticles;
};