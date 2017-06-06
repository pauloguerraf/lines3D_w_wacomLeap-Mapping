#pragma once
#include "ofMain.h"

class lineWithColor
{
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
		//do the same thing from the first example...
		ofMesh mesh;
		mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		for (unsigned int i = 1; i < points.size(); i++) {

			//find this point and the next point
			ofVec3f thisPoint = points[i - 1];
			ofVec3f nextPoint = points[i];

			//get the direction from one to the next.
			//the ribbon should fan out from this direction
			ofVec3f direction = (nextPoint - thisPoint);

			//get the distance from one point to the next
			float distance = direction.length();

			//get the normalized direction. normalized vectors always have a length of one
			//and are really useful for representing directions as opposed to something with length
			ofVec3f unitDirection = direction.getNormalized();

			//find both directions to the left and to the right
			ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0, 0, 1));
			ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0, 0, 1));

			//use the map function to determine the distance.
			//the longer the distance, the narrower the line.
			//this makes it look a bit like brush strokes
			float thickness = ofMap(distance, 0, 60, 5, 2, true);

			//calculate the points to the left and to the right
			//by extending the current point in the direction of left/right by the length
			ofVec3f leftPoint = thisPoint + toTheLeft*thickness;
			ofVec3f rightPoint = thisPoint + toTheRight*thickness;

			//add these points to the triangle strip
			mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
			mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
		}

		//end the shape
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

