#pragma once

#include "ofMain.h"
#include "BrushStroke.h"

class Brush : public ofBaseApp{
	public:
		Brush();
		void draw();

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();

    private:
		BrushStroke drawStroke;
        vector<BrushStroke> allStrokes;
};
