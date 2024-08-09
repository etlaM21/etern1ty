#include "ofApp.h"

ofPath drawPath;
vector<glm::vec2> linePoints;

//--------------------------------------------------------------
void ofApp::setup(){
	if(ofIsGLProgrammableRenderer()){
		shader.load("shadersGL3/shader"); // this is used
	}else{
		shader.load("shadersGL2/shader");
	}
	ofBackground(255,255,255);
	
	drawPath.setFilled(true);
	
	// drawPath = createPathFromVertices(addWidthToLine(getLineFromPoints(linePoints)));
}

ofPolyline ofApp::getLineFromPoints(vector<glm::vec2> points) {
	ofPolyline pointLine;
	for( int i = 0; i < points.size(); i++){
		if(points.size() >= 4) {
			pointLine.curveTo(points[i].x, points[i].y, 0, 100);
		}
		else {
			pointLine.addVertex(points[i].x, points[i].y);
		}
	}
	pointLine.close();
	pointLine.simplify(2.0);
	return pointLine;
}

vector<glm::vec3> ofApp::addWidthToLine(ofPolyline pointLine){
	vector<glm::vec3> thickLinePoints;
	float size = 25;
	vector<glm::vec3> vertices = pointLine.getVertices();
	for (int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++) {
		glm::vec3 vertex = vertices[vertexIndex];  // glm::vec3 is like ofVec2f, but with a third dimension, z
		glm::vec3 normal = pointLine.getNormalAtIndex(vertexIndex);
		if(thickLinePoints.size() < 2) {
			thickLinePoints.push_back(glm::vec3(vertex - normal * size * ofRandom(0.75, 1)));
			thickLinePoints.push_back(glm::vec3(vertex - normal / 2 * size * ofRandom(0.75, 1)));
			thickLinePoints.push_back(glm::vec3(vertex + normal * size * ofRandom(0.75, 1)));
			thickLinePoints.push_back(glm::vec3(vertex + normal / 2 * size * ofRandom(0.75, 1)));
		}
		else {
			int insertIndex = (int) ceil(thickLinePoints.size() / 2);
			thickLinePoints.insert(thickLinePoints.begin() + insertIndex, glm::vec3(vertex + normal * size * ofRandom(1)));
			thickLinePoints.insert(thickLinePoints.begin() +  insertIndex, glm::vec3(vertex - normal * size * ofRandom(1)));
		}
	}
	return thickLinePoints;
}

ofPath ofApp::createPathFromVertices(vector<glm::vec3> vertices) {
	ofPath path;
	path.moveTo(vertices[0]);
	for( int i = 1; i < vertices.size(); i++){
		path.curveTo(vertices[i]);
	}
	path.close();
	return path;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	
	shader.begin();

	drawPath.draw();

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
	linePoints.push_back(glm::vec2(x, y));

	if(!linePoints.empty()) {
		drawPath = createPathFromVertices(addWidthToLine(getLineFromPoints(linePoints)));
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	drawPath.clear();
	linePoints.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
