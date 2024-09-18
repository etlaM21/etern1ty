#include "ofApp.h"
#include "Painter.h"

Painter userPainter;

//--------------------------------------------------------------
void ofApp::setup(){
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader"); // this is used
	}else{
		shader.load("shadersGL2/shader");
	}
	ofBackground(255,255,255);
	// Christel
	
	std::vector<ofColor> christelPalette = {
		ofColor(234.45833333333331, 199.15499999999997, 190.995),
		ofColor(34.70833333333333, 216.495, 175.43999999999997),
		ofColor(186.29166666666666, 54.56999999999999, 42.074999999999996),
		ofColor(186.29166666666666, 54.56999999999999, 42.074999999999996),
		ofColor(186.29166666666666, 54.56999999999999, 42.074999999999996),
		ofColor(34.70833333333333, 24.734999999999996, 56.60999999999999),
		ofColor(34.70833333333333, 24.734999999999996, 56.60999999999999),
		ofColor(34.70833333333333, 24.734999999999996, 56.60999999999999)

	};
	userPainter = Painter(
		// Behaviour
		30, // _slowDownThreshhold
		1.75f, // _noiseInfluence
		10, // _hitRadius
		8.5f, // _maxSpeed
		0.4f, // _maxForce
		// Paint Style
		christelPalette,  // _palette
		75, // _alpha
		180.0f, // _lifeTime
		15.0f, // _decayTime
		1.5f, // _strokePositionVariation
		2.0f, // _lineSize
		3.5f, // _lineSizeVariation
		1.66f // _simplificationFactor
	);

	// Heinrich
	/*
	std::vector<ofColor> heinrichPalette = {
		ofColor(85.70833333333334, 254.99999999999997, 42.074999999999996),
		ofColor(89.25, 179.77499999999998, 30.599999999999998),
		ofColor(70.125, 140.25, 56.1),
		ofColor(87.8, 160.65, 56.1),
		ofColor(4.25, 254.99999999999997, 82.61999999999999),
		ofColor(69.41666666666666, 73.94999999999999, 69.105),
		ofColor(20.541666666666668, 190.48499999999999, 98.93999999999998),
		ofColor(104.125, 98.93999999999998, 67.065)
	};
	userPainter = Painter(
		// Behaviour
		175, // _slowDownThreshhold
		20.0f, // _noiseInfluence
		40, // _hitRadius
		3.8f, // _maxSpeed
		1.5f, // _maxForce
		// Paint Style
		heinrichPalette,  // _palette
		50, // _alpha
		180.0f, // _lifeTime
		15.0f, // _decayTime
		25.0f, // _strokePositionVariation
		20.0f, // _lineSize
		10.0f, // _lineSizeVariation
		1.12f // _simplificationFactor
	);*/
	// drawPath.setFilled(true);
	userPainter.initalize();
}

//--------------------------------------------------------------
void ofApp::update(){
	userPainter.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	
	shader.begin();

	/* drawPath.draw();

	for( int i = 0; i < allPaths.size(); i++){
		allPaths[i].draw();
	} */

	userPainter.displayCanvas();

	shader.end();
	// userPainter.displayDebugCanvas();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	userPainter.moveBrush(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	userPainter.startNewStroke();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	userPainter.endStroke();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
