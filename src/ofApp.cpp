#include "ofApp.h"
#include "Brush.h"

Brush userBrush;

//--------------------------------------------------------------
void ofApp::setup(){
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader"); // this is used
	}else{
		shader.load("shadersGL2/shader");
	}
	ofBackground(255,255,255);
	
	// drawPath.setFilled(true);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	userBrush.decayStrokes();
	
	shader.begin();

	/* drawPath.draw();

	for( int i = 0; i < allPaths.size(); i++){
		allPaths[i].draw();
	} */

	userBrush.draw();

	shader.end();
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
	userBrush.moveBrush(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	userBrush.startNewStroke();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	userBrush.endStroke();
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
