#include "ofMain.h"
#include "ofApp.h"

#ifdef USE_PROGRAMMABLE_GL
#include "ofGLProgrammableRenderer.h"
#endif


//========================================================================
int main( ){
    
#ifdef 	USE_PROGRAMMABLE_GL
    ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(false));
    ofSetCurrentRenderer(renderer, false);
    //	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
#endif

    
	ofSetupOpenGL(640,480,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
