/*
 syphonImpApp.cpp
 Cinder Syphon Implementation Sample App
 
 Created by astellato on 2/6/11
 
 Copyright 2011 astellato, bangnoise (Tom Butterworth) & vade (Anton Marini).
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "cinderSyphon.h"
#include "Particle.h"
#include "ParticleController.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"



#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

#define WIDTH 300
#define HEIGHT 300

#define WIDTHFBO 1024
#define HEIGHTFBO 768


class syphonImpApp : public AppBasic {
public:
    void setup();

	void prepareSettings( Settings *settings );
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void update();
	void draw();
	
    void renderSceneToFbo();;
	 
	syphonServer mTextureSyphon;
	
    //particle to fbo init
    gl::Fbo myFbo;
    ParticleController mParticleController;
};

void syphonImpApp::renderSceneToFbo()
{
	// this will restore the old framebuffer binding when we leave this function
	// on non-OpenGL ES platforms, you can just call mFbo.unbindFramebuffer() at the end of the function
	// but this will restore the "screen" FBO on OpenGL ES, and does the right thing on both platforms
	gl::SaveFramebufferBinding bindingSaver;
	
	// bind the framebuffer - now everything we draw will go there
	myFbo.bindFramebuffer();
    gl::setViewport(myFbo.getBounds() );
    gl::setMatricesWindow( myFbo.getSize(), false );
	
	// clear out the FBO with blue
	gl::clear();
   mParticleController.update();
    mParticleController.draw();
    
}

void syphonImpApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize(WIDTH,HEIGHT);
	settings->setFrameRate(60.f);
}

void syphonImpApp::setup()
{
    gl::Fbo::Format format;
    //	format.setSamples( 4 ); // uncomment this to enable 4x antialiasing
	myFbo = gl::Fbo( WIDTHFBO,HEIGHTFBO, format );
    
    mParticleController.addParticles(WIDTHFBO,HEIGHTFBO,1000);

}

void syphonImpApp::update()
{

}

void syphonImpApp::draw()
{
	gl::enableAlphaBlending();
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );

    renderSceneToFbo();
    mTextureSyphon.publishTexture(&myFbo.getTexture()); //publish our texture

    Vec2f upperLeftCorner = Vec2f( 0, WIDTH );
    Vec2f lowerRightCorner = Vec2f(WIDTH,WIDTH-(WIDTH/1.33) );
    Rectf rect = Rectf( upperLeftCorner, lowerRightCorner );
    gl::draw( myFbo.getTexture(0),rect);


	

}


void syphonImpApp::keyDown( KeyEvent event )
{
	//
}

void syphonImpApp::mouseDown( MouseEvent event )
{
	//
}

void syphonImpApp::mouseUp( MouseEvent event )
{
	//
}

void syphonImpApp::mouseMove( MouseEvent event )
{
	//
}

void syphonImpApp::mouseDrag( MouseEvent event )
{
	//
}

CINDER_APP_BASIC( syphonImpApp, RendererGl )

