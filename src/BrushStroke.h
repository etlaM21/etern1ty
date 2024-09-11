#pragma once

#include "ofMain.h"
#include "Stroke.h"

class BrushStroke : public ofBaseApp{
	public:
		BrushStroke();
		BrushStroke(float zHeight);
		void draw();
        
		void addStrokePosition(int x, int y);

		float BrushStroke::decay();

    private:
		float zPosition;
		float birthtime;

		float lifeTime = 5.0;
		float lifeTimeLeft = lifeTime;
		float decayTime = 1.0;
		float decayStepLinear = 255 / decayTime;

		int nStrokes = 1;
		float strokePositionVariation = 1;
		vector<Stroke> strokes;

		void resetBirthTime();
};
