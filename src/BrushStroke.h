#pragma once

#define NUMBEROFSTROKES 10

#include "ofMain.h"
#include "Stroke.h"

class BrushStroke : public ofBaseApp{
	public:
		BrushStroke();
		BrushStroke(float zHeight, ofColor& paintColor);
		BrushStroke(float zHeight, ofColor& paintColor, int& _alpha, float& _lifeTime, float& _decayTime, float& _strokePositionVariation,
		// For Stroke CLass
		float& _lineSize, float& _lineSizeVariation, float& _simplificationFactor
		);


		void draw();
        
		void addStrokePosition(int x, int y);

		float decay();

		int getStrokeVertices();

    private:
		float zPosition;
		float birthtime;

		int alpha = 75;

		float lifeTime = 90.0;
		float lifeTimeLeft = lifeTime;
		float decayTime = 15.0;
		float decayStepLinear = alpha / decayTime;

		float strokePositionVariation = 1.5;

		Stroke strokes[NUMBEROFSTROKES];
		int currentStrokeVertices;
		// vector<Stroke> strokes;

		void resetBirthTime();
};
