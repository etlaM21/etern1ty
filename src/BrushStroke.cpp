#include "ofApp.h"
#include "BrushStroke.h"
#include "Stroke.h"


BrushStroke::BrushStroke(){
	zPosition = 0;
	birthtime = ofGetElapsedTimef();
	currentStrokeVertices = 0;
	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		strokes[i] = Stroke();
	}
}

BrushStroke::BrushStroke(float zHeight, ofColor& paintColor){
	zPosition = zHeight;
	birthtime = ofGetElapsedTimef();
	currentStrokeVertices = 0;
	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		ofColor strokeColor = paintColor;
		strokeColor.a = alpha;
		strokes[i] = Stroke(zHeight + i / 100, strokeColor);
	}
}
//--------------------------------------------------------------
void BrushStroke::draw(){
  
	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		strokes[i].draw();
	}
    
}

float BrushStroke::decay() {
	lifeTimeLeft = lifeTime - (ofGetElapsedTimef() - birthtime);
	if (lifeTimeLeft <= decayTime && lifeTimeLeft > 0.0) {
		for (int i = 0; i < NUMBEROFSTROKES; i++) {
			strokes[i].setAlphaColor(alpha * (lifeTimeLeft / decayTime));
		}
	}
	return lifeTimeLeft;
}

void BrushStroke::addStrokePosition(int x, int y){
	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		strokes[i].addStrokePosition(
			x + ofRandom(-strokePositionVariation, strokePositionVariation),
			y + ofRandom(-strokePositionVariation, strokePositionVariation)
		);
	}
	resetBirthTime();
}

int BrushStroke::getStrokeVertices() {

	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		int nVertices = strokes[i].getStrokeVertices();
		if (nVertices > currentStrokeVertices) {
			currentStrokeVertices = nVertices;
		}
	}

	return currentStrokeVertices;
}


void BrushStroke::resetBirthTime() {
	birthtime = ofGetElapsedTimef();
}