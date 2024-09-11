#include "ofApp.h"
#include "Brush.h"
#include "BrushStroke.h"


Brush::Brush(){
    
}
//--------------------------------------------------------------
void Brush::draw(){
    
    drawStroke.draw();

	for( int i = 0; i < allStrokes.size(); i++){
		allStrokes[i].draw();
	} 
    
}


void Brush::moveBrush(int x, int y){
	drawStroke.addStrokePosition(x, y);
}

//--------------------------------------------------------------
void Brush::startNewStroke(){
	drawStroke = BrushStroke(allStrokes.size() / 10);
    // delete drawStroke;
}

//--------------------------------------------------------------
void Brush::endStroke(){
	allStrokes.push_back(drawStroke);
}

void Brush::decayStrokes() {
	for (int i = 0; i < allStrokes.size(); i++) {
		float timeLeft = allStrokes[i].decay(); // returns lifeTimeLeft;
		if (timeLeft <= 0.0) {
			allStrokes.erase(allStrokes.begin() + i);
		}
	}
}