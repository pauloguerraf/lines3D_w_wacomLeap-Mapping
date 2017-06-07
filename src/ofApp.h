#pragma once

#include "ofMain.h"
//#include "ofxLeapMotion2.h"
#include "CustomSource.h"
#include "lineWithColor.h"
#include "ofxXmlSettings.h"
#include "ofxPiMapper.h"

#define APP_WIDTH 5120
#define APP_HEIGHT 768

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

	ofVec3f center;
	int currentLine;
	ofColor currentColor;
	bool fullscreen;

	//leapmotion
	//ofxLeapMotion leap;
	//vector <ofxLeapMotionSimpleHand> simpleHands;
	//vector <int> fingersFound;

	//projection mapping
	ofxPiMapper piMapper;
	CustomSource * customSource;
};
