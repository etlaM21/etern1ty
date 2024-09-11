#pragma once

#define NUMBEROFSTROKES 1

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

		float strokePositionVariation = 1;
		Stroke strokes[NUMBEROFSTROKES];
		// vector<Stroke> strokes;

		void resetBirthTime();
};
