#pragma once
#include "ofMain.h"

class lineWithColor{
public:
	vector<ofVec3f> points;
	bool bAmDoneDrawing;
	ofColor color;
	ofVec3f center;

	lineWithColor() {
		bAmDoneDrawing = false;
		color = ofColor(255, 0, 0);
	}
	void addVertex(int x_, int y_) {
		ofVec3f mousePoint(x_, y_, 0);
		points.push_back(mousePoint);
	}
	void update() {
		if (!bAmDoneDrawing) {
			ofVec3f sumOfAllPoints(0, 0, 0);
			for (unsigned int i = 0; i < points.size(); i++) {
				points[i].z -= 2;
				sumOfAllPoints += points[i];
			}
			center = sumOfAllPoints / points.size();
		}
	}
	void initRotateCenter(float angle_) {
		ofPushMatrix();
		ofTranslate(center);
		ofRotateY(angle_);
		ofTranslate(-center);
	}
	void draw() {
		ofSetColor(color);
		ofMesh mesh;
		mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		for (unsigned int i = 1; i < points.size(); i++) {
			ofVec3f thisPoint = points[i - 1];
			ofVec3f nextPoint = points[i];
			ofVec3f direction = (nextPoint - thisPoint);
			float distance = direction.length();
			ofVec3f unitDirection = direction.getNormalized();

			ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0, 0, 1));
			ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0, 0, 1));
			float thickness = ofMap(distance, 0, 60, 5, 2, true);
			ofVec3f leftPoint = thisPoint + toTheLeft*thickness;
			ofVec3f rightPoint = thisPoint + toTheRight*thickness;
			mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
			mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
		}
		mesh.draw();
	}
	void endRotateCenter() {
		ofPopMatrix();
	}
	void finishDrawing() {
		bAmDoneDrawing = true;
	}
	void setColor(ofColor &c_) {
		color = c_;
	}
};

