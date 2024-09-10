#pragma once

#include "ofMain.h"
#include "Stroke.h"

class BrushStroke : public ofBaseApp{
	public:
		BrushStroke();
		BrushStroke(float zHeight);
		void draw();
        
		void addStrokePosition(int x, int y);

    private:
		float zPosition;

		int nStrokes = 1;
		float strokePositionVariation = 1;
		vector<Stroke> strokes;
};
