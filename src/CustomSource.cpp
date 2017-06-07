#include "CustomSource.h"

void CustomSource::setup() {
	name = "Custom FBO Source";
	allocate(ofGetWidth(), ofGetHeight());
	usecamera = false;
}

void CustomSource::update(){
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines[i].update();
	}
}

void CustomSource::addVertex(int x_, int y_) {
	lines[lines.size() - 1].addVertex(x_, y_);
}

void CustomSource::addLine(lineWithColor l_) {
	lines.push_back(l_);
}

void CustomSource::finishDrawing() {
	lines[lines.size() - 1].finishDrawing();
}
void CustomSource::draw(){
	ofClear(0, 255, 0, 255);
	ofSetColor(200);
	if (usecamera) {
		ofPushMatrix();
		ofTranslate(0, 0, -zTranslation*10.0f);
	}

	for (unsigned int i = 0; i < lines.size(); i++) {
		if (usecamera) {
			lines[i].initRotateCenter(ofMap(handRoll, 1.5, -2.5, -90, 90));
		}
		lines[i].draw();
		if (usecamera)lines[i].endRotateCenter();
	}

	if (usecamera) {
		ofPopMatrix();
	}
}