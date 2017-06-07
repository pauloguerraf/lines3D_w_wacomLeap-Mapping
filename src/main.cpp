#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, APP_WIDTH, APP_HEIGHT, OF_WINDOW);
	ofSetWindowPosition(1366, 0); 	// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
