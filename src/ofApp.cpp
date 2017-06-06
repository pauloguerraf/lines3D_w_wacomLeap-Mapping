#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//just set up the openFrameworks stuff
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	fullscreen = false;
	drawing = false;

	//camera setup
	usecamera = false;

	currentLine = 0;
	currentColor = ofColor(255, 255, 255);

	//leap motion stuff
	leap.open();
	fbo.allocate(ofGetWidth(), ofGetHeight());
	
	//projection mapping
	for (int i = 0; i<NUM_WARPERS; i++) {
		warpers.push_back(ofxGLWarper());
		warpers.back().setup((APP_WIDTH/NUM_WARPERS)*i, 0, (APP_WIDTH / NUM_WARPERS), APP_HEIGHT);
		//warpers.back().activate();
	}

	activeWarper = -1;
}

//--------------------------------------------------------------
void ofApp::update() {
	fingersFound.clear();
	simpleHands = leap.getSimpleHands();
	if (leap.isFrameNew() && simpleHands.size()) {
		leap.setMappingX(-230, 230, 0, ofGetWidth());
		leap.setMappingY(490, 90, 0, ofGetHeight());
		leap.setMappingZ(-150, 150, -200, 200);
	}
	if (simpleHands.size() == 1) {
		usecamera = true;
	}
	else {
		usecamera = false;
	}
	///
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines[i].update();
	}


	fbo.begin();
	ofClear(0, 0, 0, 255);
	ofSetColor(200);
	if (usecamera) {
		ofPushMatrix();
		ofTranslate(0, 0, -simpleHands[0].handPos.z*10.0f);
	}

	for (unsigned int i = 0; i < lines.size(); i++) {
		if (usecamera) {
			lines[i].initRotateCenter(ofMap(simpleHands[0].roll, 1.5, -2.5, -90, 90));
		}

		lines[i].draw();
		if (usecamera)lines[i].endRotateCenter();
	}

	if (usecamera) {
		ofPopMatrix();
	}
	fbo.end();
	ofPixels pixels;
	fbo.readToPixels(pixels);
	img.setFromPixels(pixels);
	img.update();
	
	//spout.sendTexture(fbo.getTexture(), "composition");
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofSetColor(255);
	ofClear(0, 0, 0, 255);
	for (int i = 0; i<NUM_WARPERS; i++) {
		warpers[i].begin();
		warpers[i].draw();
		img.drawSubsection((APP_WIDTH / 4)*i, 0, 800, APP_HEIGHT, (APP_WIDTH/4)*i, 0);
		warpers[i].draw();
		warpers[i].end();
	}
	//img.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'f') {
		fullscreen = !fullscreen;
		ofSetFullscreen(fullscreen);
	}
	if (!drawing) {
		bool bDeactivateOthers = false;
		switch (key) {
		case '1':
			activeWarper = 0;
			warpers[0].toogleActive();
			bDeactivateOthers = true;
			break;
			//*
		case '2':
			activeWarper = 1;
			warpers[1].toogleActive();
			bDeactivateOthers = true;
			break;
		case '3':
			activeWarper = 2;
			bDeactivateOthers = true;
			warpers[2].toogleActive();
			break;
		case '4':
			activeWarper = 3;
			bDeactivateOthers = true;
			warpers[3].toogleActive();
			break;
		case ' ':
			activeWarper = -1;
			bDeactivateOthers = true;
			//*/
		default:
			break;
		}

		if (bDeactivateOthers) {
			for (int i = 0; i < NUM_WARPERS; i++) {
				if (i != activeWarper) {
					warpers[i].deactivate();
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (activeWarper == -1) {
		lines[lines.size() - 1].addVertex(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	lineWithColor l;
	l.setColor(currentColor);
	lines.push_back(l);
	drawing = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (activeWarper == -1) {
		lines[lines.size() - 1].finishDrawing();
		currentLine = currentLine + 1;
		drawing = false;
		ofLog(OF_LOG_NOTICE, "adding line");
	}
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