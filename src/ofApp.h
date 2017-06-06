/**
*
* OFDevCon Example Code Sprint
* Camera Ribbon example
* This example generates ribbons along the mouse trail that descend in space
* When you click space bar, you can
*
* Created by James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
* Adapted during ofDevCon on 2/23/2012
*/

#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "lineWithColor.h"
#include "ofxGLWarper.h"
#include "ofxXmlSettings.h"
#include "ofxPiMapper.h"



#define NUM_WARPERS 4
#define APP_WIDTH 3200
#define APP_HEIGHT 1800

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	vector < lineWithColor > lines;
	ofVec3f center;

	ofCamera camera;
	ofFbo fbo;
	ofxLeapMotion leap;
	vector <ofxLeapMotionSimpleHand> simpleHands;
	vector <int> fingersFound;
	ofImage img;
	vector <ofImage> images;
	bool drawing;

	bool usecamera;
	bool fullscreen;

	int currentLine;
	ofColor currentColor;

	vector<ofxGLWarper> warpers;
	int activeWarper;
};
