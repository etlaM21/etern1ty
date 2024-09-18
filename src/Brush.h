#pragma once

#define MAXIMUMSTROKES 500
#define MAXIMUMSTROKEVERTICES 50

#include "ofMain.h"
#include "BrushStroke.h"

class Brush : public ofBaseApp{
	public:
		Brush();
		Brush(
			// For BrushStroke Class
			int& _alpha, float& _lifeTime, float& _decayTime, float& _strokePositionVariation,
			// For Stroke CLass
			float& _lineSize, float& _lineSizeVariation, float& _simplificationFactor
		);
		void draw();

		void setColor(ofColor& newColor);

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();

		void decayStrokes();

    private:
		// For BrushStroke Class
		int BrushStroke_alpha;
		float BrushStroke_lifeTime;
		float BrushStroke_decayTime;
		float BrushStroke_strokePositionVariation;
		// For Stroke CLass
		float Stroke_lineSize;
		float Stroke_lineSizeVariation;
		float Stroke_simplificationFactor;

		BrushStroke drawStroke;
		int currentAllStrokeCount = 0;
		BrushStroke allStrokes[MAXIMUMSTROKES];

		ofColor currentColor;


		int fourthLastX = 0;
		int fourthLastY = 0;
		int thirdLastX = 0;
		int thirdLastY = 0;
		int secondLastX = 0;
		int secondLastY = 0;
		int lastX = 0;
		int lastY = 0;
};
