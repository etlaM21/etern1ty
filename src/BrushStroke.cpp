#include "ofApp.h"
#include "BrushStroke.h"
#include "Stroke.h"


BrushStroke::BrushStroke(){
	zPosition = 0;
	for (int i = 0; i < nStrokes; i++) {
		strokes.push_back(Stroke());
	}
}

BrushStroke::BrushStroke(float zHeight){
	zPosition = zHeight;
	for (int i = 0; i < nStrokes; i++) {
		strokes.push_back(Stroke(zHeight + i / 100));
	}
}
//--------------------------------------------------------------
void BrushStroke::draw(){
  
	for (int i = 0; i < strokes.size(); i++) {
		strokes[i].draw();
	}
    
}


void BrushStroke::addStrokePosition(int x, int y){
	for (int i = 0; i < strokes.size(); i++) {
		strokes[i].addStrokePosition(x + ofRandom(-strokePositionVariation, strokePositionVariation), y + ofRandom(-strokePositionVariation, strokePositionVariation));
	}
}