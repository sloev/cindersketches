#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc, float radius)
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();
	mVel	= Rand::randFloat( 5.0f );
	mRadius	= radius;
}

void Particle::update()
{
    //float time = app::getElapsedSeconds();
    //mRadius=((sin( cos( sin( mLoc.x*cos(time) ) + cos( mLoc.y *sin(time)) ) ) + 1.0f))*2;
	mLoc += mDir * mVel;
}

void Particle::draw()
{
	gl::drawSolidCircle( mLoc, mRadius );
}