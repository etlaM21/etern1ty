#include "ofApp.h"
#include "Brush.h"
#include "BrushStroke.h"


Brush::Brush(){
    
}

Brush::Brush(// For BrushStroke Class
	int& _alpha, float& _lifeTime, float& _decayTime, float& _strokePositionVariation,
	// For Stroke CLass
	float& _lineSize, float& _lineSizeVariation, float& _simplificationFactor
	) {
	// For BrushStroke Class
	BrushStroke_alpha = _alpha;
	BrushStroke_lifeTime = _lifeTime;
	BrushStroke_decayTime = _decayTime;
	BrushStroke_strokePositionVariation = _strokePositionVariation;
	// For Stroke CLass
	Stroke_lineSize = _lineSize;
	Stroke_lineSizeVariation = _lineSizeVariation;
	Stroke_simplificationFactor = _simplificationFactor;
}
//--------------------------------------------------------------
void Brush::draw(){

	for( int i = 0; i < currentAllStrokeCount; i++){
		allStrokes[i].draw();
	} 
	// REMOVED the "if (currentAllStrokeCount < MAXIMUMSTROKES)" check.
	// We ALWAYS want to see the active brush, even if the history is full.
	drawStroke.draw();
}

//--------------------------------------------------------------
void Brush::setColor(ofColor& newColor) {
	currentColor = newColor;
}

void Brush::moveBrush(int x, int y){
	drawStroke.addStrokePosition(x, y);
	if (drawStroke.getStrokeVertices() >= MAXIMUMSTROKEVERTICES) {
		endStroke();
		startNewStroke();
		// This is not elegant but works to properly start the new stroke IN the old one
		drawStroke.addStrokePosition(fourthLastX, fourthLastY);
		drawStroke.addStrokePosition(thirdLastX, thirdLastY);
		drawStroke.addStrokePosition(secondLastX, secondLastY);
		drawStroke.addStrokePosition(lastX, lastY);
		drawStroke.addStrokePosition(x, y);
	}
	// This is not elegant but works to properly start the new stroke IN the old one
	fourthLastX = thirdLastX;
	fourthLastY = thirdLastY;
	thirdLastX = secondLastX;
	thirdLastY = secondLastY;
	secondLastX = lastX;
	secondLastY = lastY;
	lastX = x;
	lastY = y;
}

//--------------------------------------------------------------
void Brush::startNewStroke(){
	drawStroke = BrushStroke(currentAllStrokeCount / 10, currentColor, BrushStroke_alpha, BrushStroke_lifeTime, BrushStroke_decayTime, BrushStroke_strokePositionVariation, Stroke_lineSize, Stroke_lineSizeVariation, Stroke_simplificationFactor);
}
//--------------------------------------------------------------
void Brush::endStroke() {
	if (currentAllStrokeCount < MAXIMUMSTROKES) {
		// Normal case: Buffer has space
		allStrokes[currentAllStrokeCount] = drawStroke;
		currentAllStrokeCount++;
	} else {
		// Full Case: Buffer is full!
		// We must DELETE the oldest stroke (index 0) to save the new one.
		// Shift everyone left by 1.
		for (int i = 0; i < MAXIMUMSTROKES - 1; i++) {
			allStrokes[i] = allStrokes[i + 1];
		}

		// Save the new stroke in the last slot
		allStrokes[MAXIMUMSTROKES - 1] = drawStroke;

		// Note: currentAllStrokeCount remains at MAXIMUMSTROKES
	}
}

void Brush::decayStrokes() {
	for (int i = 0; i < currentAllStrokeCount; i++) {
		float timeLeft = allStrokes[i].decay(); // returns lifeTimeLeft and sets new alpha value
		if (timeLeft <= 0.0) {
			// Shift all remaining strokes left by one position
			for (int j = i; j < currentAllStrokeCount - 1; j++) {
				allStrokes[j] = allStrokes[j + 1];
			}
			currentAllStrokeCount--;  // Decrease stroke count
			i--;  // Adjust loop index to account for the shift
		}
	}
}
