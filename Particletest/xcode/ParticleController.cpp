#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "ParticleController.h"
#include "cinder/gl/Fbo.h"

using namespace ci;
using std::list;


ParticleController::ParticleController()
{
}

void ParticleController::update()
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->update();
	}
}

void ParticleController::draw()
{
    
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}

}

void ParticleController::addParticle( int xi, int yi, float radius ) {
    float x = ( xi + 0.5f ) * 10.0f;
    float y = ( yi + 0.5f ) * 10.0f;
    mParticles.push_back( Particle( Vec2f( x, y ), radius ) );
}

void ParticleController::addParticles(int w, int h,  int amt )
{
	for( int i=0; i<amt; i++ )
	{
		float x = Rand::randFloat( w );
		float y = Rand::randFloat( h );
		mParticles.push_back( Particle( Vec2f( x, y ),10 ) );
	}
}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}

