#pragma once

#define NUMBEROFSTROKES 10

#include "ofMain.h"
#include "Stroke.h"

class BrushStroke : public ofBaseApp{
	public:
		BrushStroke();
		BrushStroke(float zHeight, ofColor& paintColor);
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

		float strokePositionVariation = 1.5;
		Stroke strokes[NUMBEROFSTROKES];
		// vector<Stroke> strokes;

		void resetBirthTime();
};
