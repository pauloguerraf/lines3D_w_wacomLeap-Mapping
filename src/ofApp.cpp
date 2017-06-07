#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//general setup
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	currentLine = 0;
	isDrawing = false;
	//projection mapping
	customSource = new CustomSource();
	piMapper.registerFboSource(customSource);
	piMapper.setup();

	//leap motion stuff
	leap.open();
}

//--------------------------------------------------------------
void ofApp::update() {
	fingersFound.clear();
	simpleHands = leap.getSimpleHands();
	if (leap.isFrameNew() && simpleHands.size()) {
		leap.setMappingX(-230, 230, 0, ofGetWidth());
		leap.setMappingY(490, 90, 0, ofGetHeight());
		leap.setMappingZ(-150, 150, -200, 200);
		customSource -> zTranslation = simpleHands[0].handPos.z;
		customSource -> handRoll = simpleHands[0].roll;
	}
	if (simpleHands.size() == 1) {
		customSource -> usecamera = true;
	}
	else {
		customSource -> usecamera = false;
	}
	//projection mapping
	piMapper.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	piMapper.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	piMapper.keyPressed(key);
	if (key == ' ' && !isDrawing) {
		customSource->clearLines();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	piMapper.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (piMapper.getMode() == 0)customSource->addVertex(x, y);
	else piMapper.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	ofLog(OF_LOG_NOTICE, ofToString(piMapper.getMode()));
	if (piMapper.getMode() == 0) {
		lineWithColor l;
		currentColor = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		l.setColor(currentColor);
		customSource->addLine(l);
		isDrawing = true;
	}
	else piMapper.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (piMapper.getMode() == 0)
	{
		customSource->finishDrawing();
		currentLine = currentLine + 1;
		isDrawing = false;
	}
	else piMapper.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
//-----------------------------------color picker event
void ofApp::exit() {
	if (leap.isConnected()) {
		leap.close();
	}
}

