#pragma once

#define MAXIMUMSTROKES 250

#include "ofMain.h"
#include "BrushStroke.h"

class Brush : public ofBaseApp{
	public:
		Brush();
		void draw();

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();

		void decayStrokes();

    private:
		BrushStroke drawStroke;
		int currentAllStrokeCount = 0;
		BrushStroke allStrokes[MAXIMUMSTROKES];
        // vector<BrushStroke> allStrokes;

		ofColor palette[10] = {
			ofColor(100, 255, 255),
			ofColor(100, 80, 255),
			ofColor(250, 125, 255),
			ofColor(250, 125, 186),
			ofColor(250, 225, 123),
			ofColor(125, 175, 186),
			ofColor(0, 0, 25),
			ofColor(0, 0, 25),
			ofColor(0, 0, 25),
			ofColor(0, 0, 25),
		};
};
