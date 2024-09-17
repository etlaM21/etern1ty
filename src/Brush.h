#pragma once

#define MAXIMUMSTROKES 250
#define MAXIMUMSTROKEVERTICES 25

#include "ofMain.h"
#include "BrushStroke.h"

class Brush : public ofBaseApp{
	public:
		Brush();
		void draw();

		void setColor(ofColor& newColor);

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();

		void decayStrokes();

    private:
		BrushStroke drawStroke;
		int currentAllStrokeCount = 0;
		BrushStroke allStrokes[MAXIMUMSTROKES];

		ofColor currentColor;

		int fourthLastX;
		int fourthLastY;
		int thirdLastX;
		int thirdLastY;
		int secondLastX;
		int secondLastY;
		int lastX;
		int lastY;
};
