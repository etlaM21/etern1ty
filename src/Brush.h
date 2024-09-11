#pragma once

#define MAXIMUMSTROKES 10

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
};
