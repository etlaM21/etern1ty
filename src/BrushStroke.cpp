#include "ofApp.h"
#include "BrushStroke.h"
#include "Stroke.h"


BrushStroke::BrushStroke(){
	zPosition = 0;
	birthtime = ofGetElapsedTimef();
	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		strokes[i] = Stroke();
	}
}

BrushStroke::BrushStroke(float zHeight, ofColor& paintColor){
	zPosition = zHeight;
	birthtime = ofGetElapsedTimef();
	for (int i = 0; i < NUMBEROFSTROKES; i++) {
		strokes[i] = Stroke(zHeight + i / 100, paintColor);
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
			strokes[i].setAlphaColor(255 * (lifeTimeLeft / decayTime));
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

void BrushStroke::resetBirthTime() {
	birthtime = ofGetElapsedTimef();
}