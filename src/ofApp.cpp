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
	/*
	std::vector<ofColor> myPalette = { 
		ofColor(331, 78.1, 74.9),
		ofColor(49, 84.9, 68.8),
		ofColor(263, 21.4, 16.5),
		ofColor(263, 21.4, 16.5),
		ofColor(263, 21.4, 16.5),
		ofColor(49, 9.7, 22.2),
		ofColor(49, 9.7, 22.2),
		ofColor(49, 9.7, 22.2)

	};
	userPainter = Painter(
		// Behaviour
		30, // _slowDownThreshhold
		1.75f, // _noiseInfluence
		10, // _hitRadius
		8.5f, // _maxSpeed
		0.4f, // _maxForce
		// Paint Style
		myPalette,  // _palette
		75, // _alpha
		180.0f, // _lifeTime
		15.0f, // _decayTime
		1.5f, // _strokePositionVariation
		2.0f, // _lineSize
		1.0f, // _lineSizeVariation
		1.66f // _simplificationFactor
	); */

	// Heinrich
	std::vector<ofColor> myPalette = {
		ofColor(121, 100.0, 16.5),
		ofColor(126, 70.5, 12.0),
		ofColor(6, 100.0, 32.4),
		ofColor(98, 29.0, 27.1),
		ofColor(29, 74.7, 38.8),
		ofColor(147, 38.8, 26.3)
	};
	userPainter = Painter(
		// Behaviour
		175, // _slowDownThreshhold
		2.0f, // _noiseInfluence
		40, // _hitRadius
		4.1f, // _maxSpeed
		1.5f, // _maxForce
		// Paint Style
		myPalette,  // _palette
		50, // _alpha
		180.0f, // _lifeTime
		15.0f, // _decayTime
		50.0f, // _strokePositionVariation
		20.0f, // _lineSize
		5.0f, // _lineSizeVariation
		1.12f // _simplificationFactor
	);
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
