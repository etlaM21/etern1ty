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
	userPainter.displayDebugCanvas();
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
