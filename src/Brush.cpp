#include "ofApp.h"
#include "Brush.h"
#include "BrushStroke.h"


Brush::Brush(){
    
}
//--------------------------------------------------------------
void Brush::draw(){
    
    drawStroke.draw();

	for( int i = 0; i < currentAllStrokeCount; i++){
		allStrokes[i].draw();
	} 
    
}


void Brush::moveBrush(int x, int y){
	drawStroke.addStrokePosition(x, y);
}

//--------------------------------------------------------------
void Brush::startNewStroke(){
	drawStroke = BrushStroke(currentAllStrokeCount / 10, palette[(int) ofRandom(10)]);
    // delete drawStroke;
}

//--------------------------------------------------------------
void Brush::endStroke(){
	if (currentAllStrokeCount < MAXIMUMSTROKES) {
		allStrokes[currentAllStrokeCount] = drawStroke;
		currentAllStrokeCount++;  // Increment the stroke count
	}
	// allStrokes.push_back(drawStroke);
}

void Brush::decayStrokes() {
	for (int i = 0; i < currentAllStrokeCount; i++) {
		float timeLeft = allStrokes[i].decay(); // returns lifeTimeLeft;
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