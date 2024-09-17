#include "ofApp.h"
#include "Stroke.h"


Stroke::Stroke(){
	zPosition = 0;
}

Stroke::Stroke(float zHeight, ofColor& paintColor){
	zPosition = zHeight;
	drawColor = paintColor;
}
//--------------------------------------------------------------
void Stroke::draw(){
    
    drawMesh.draw();
    
}


void Stroke::addStrokePosition(int x, int y){
	linePoints.push_back(glm::vec2(x, y));
	linePath = getLineFromPoints(linePoints);
	addWidthToLine(linePath);
	drawPath = createPathFromVertices(createVertsFromPath(linePath, linePathWidth));
	// drawMesh = createMeshFromVertices(createVertsFromPath(linePath, linePathWidth));
    drawMesh = drawPath.getTessellation();
    colorMesh(drawMesh);
}

//--------------------------------------------------------------
void Stroke::startNewPath(){
	linePoints.clear();
}

//--------------------------------------------------------------
void Stroke::endNewPath(){
	// allPaths.push_back(drawPath);
    // allMeshes.push_back(drawMesh);
}

ofPolyline Stroke::getLineFromPoints(const vector<glm::vec2>& points) {
	ofPolyline pointLine;
	for( int i = 0; i < points.size(); i++){
		if(points.size() >= 4) {
			pointLine.curveTo(points[i].x, points[i].y, zPosition, 100);
		}
		else {
			pointLine.addVertex(points[i].x, points[i].y, zPosition);
		}
	}
	// pointLine.close();
	pointLine.simplify(simplificationFactor);
	return pointLine;
}

void Stroke::addWidthToLine(const ofPolyline& pointLine){

	const vector<glm::vec3>& vertices = pointLine.getVertices();

	for (int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++) {
		if(linePathWidth.size() <= vertexIndex) {
			// linePathWidth.push_back(glm::vec2(lineSize * ofRandom(1 - lineSizeVariation, 1), lineSize * ofRandom(1 - lineSizeVariation, 1)));
			// float variation = ofRandom(1 - lineSizeVariation, 1);
			float variation = (ofNoise(vertices[vertexIndex].x, vertices[vertexIndex].y, ofGetElapsedTimef()) * + 1) * lineSizeVariation;
			linePathWidth.push_back(glm::vec2(lineSize + variation, lineSize + variation));
		}
	}
	
}

vector<glm::vec3> Stroke::createVertsFromPath(const ofPolyline& pointLine, const vector<glm::vec2>& width){
	vector<glm::vec3> thickLinePoints;
	if(!width.empty()) {
		vector<glm::vec3> vertices = pointLine.getVertices();

		for (int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++) {
			glm::vec3 vertex = vertices[vertexIndex];  // glm::vec3 is like ofVec2f, but with a third dimension, z
			glm::vec3 normal = pointLine.getNormalAtIndex(vertexIndex);
			glm::vec3 negativeVert = vertex - normal * width[vertexIndex].x;
			glm::vec3 positiveVert = vertex + normal * width[vertexIndex].y;
			if(thickLinePoints.size() < 2) {
				thickLinePoints.push_back(negativeVert);
				thickLinePoints.push_back(positiveVert);
			}
			else {
				int insertIndex = (int) ceil(thickLinePoints.size() / 2);
				thickLinePoints.insert(thickLinePoints.begin() + insertIndex, positiveVert);
				thickLinePoints.insert(thickLinePoints.begin() +  insertIndex, negativeVert);
			}
		}
		
	}

	return thickLinePoints;
}

ofPath Stroke::createPathFromVertices(const vector<glm::vec3>& vertices) {
	ofPath path;
	if (vertices.size() >= 2) {
		path.moveTo(vertices[0]);
		for (int i = 1; i < vertices.size(); i++) {
			path.curveTo(vertices[i]);
		}
		path.close();
	}
    path.simplify(simplificationFactor);
	return path;
}

void Stroke::colorMesh(ofMesh& meshToColor) {
	int index = 0;
	if(meshToColor.hasColors()){
		index = meshToColor.getColors().size() - 1;
	} 
    for (int i = index; i < meshToColor.getNumVertices(); i++) {
		meshToColor.addColor(ofColor::fromHsb(
			drawColor[0] * ofRandom(1, 0.95),
			drawColor[1] * ofRandom(1, 0.85),
			drawColor[2] * ofRandom(1, 0.75),
			drawColor[3])
		); // VALUES: 0 -> 255
    }
}

void Stroke::setAlphaColor(float newAlpha) {
	ofMesh& meshToColor = drawMesh;
	if (meshToColor.hasColors()) {
		for (int i = 0; i < meshToColor.getColors().size(); i++) {
			ofColor colorToSet = meshToColor.getColor(i);
			colorToSet.a = newAlpha;
			meshToColor.setColor(i, colorToSet);
			// meshToColor.addColor(ofColor::fromHsb(0, 0, ofRandom(0, 75))); // VALUES: 0 -> 255
		}
	}
}