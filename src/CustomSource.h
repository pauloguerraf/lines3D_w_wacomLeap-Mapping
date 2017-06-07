#pragma once

#include "ofMain.h"
#include "FboSource.h"
#include "lineWithColor.h"

class CustomSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
		void addVertex(int x_, int y_);
		void addLine(lineWithColor l_);
		void finishDrawing();


		vector <lineWithColor> lines;
		bool usecamera;
		float zTranslation;
		float handRoll;
};