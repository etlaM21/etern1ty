#include "ofApp.h"

ofPath drawPath;
vector<ofPath> allPaths;
ofPolyline linePath;
vector<glm::vec2> linePathWidth;
float lineSize = 12.0;
float lineSizeVariation = 0.5;
vector<glm::vec3> pathVerts;
vector<glm::vec2> linePoints;

//--------------------------------------------------------------
Brush::Brush(){
	drawPath.setFilled(true);
}

ofPolyline Brush::getLineFromPoints(const vector<glm::vec2>& points) {
	ofPolyline pointLine;
	for( int i = 0; i < points.size(); i++){
		if(points.size() >= 4) {
			pointLine.curveTo(points[i].x, points[i].y, allPaths.size() / 10, 100);
		}
		else {
			pointLine.addVertex(points[i].x, points[i].y, allPaths.size() / 10);
		}
	}
	// pointLine.close();
	pointLine.simplify(1.0);
	return pointLine;
}

void Brush::addWidthToLine(const ofPolyline& pointLine){

	const vector<glm::vec3>& vertices = pointLine.getVertices();

	for (int vertexIndex = 0; vertexIndex < vertices.size(); vertexIndex++) {
		if(linePathWidth.size() < vertexIndex) {
			linePathWidth.push_back(glm::vec2(lineSize * ofRandom(1 - lineSizeVariation, 1), lineSize * ofRandom(1 - lineSizeVariation, 1)));
		}
	}
	
}

vector<glm::vec3> Brush::createVertsFromPath(const ofPolyline& pointLine, const vector<glm::vec2>& width){
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

void Brush::addVertsToPath(vector<glm::vec3>& path, const vector<glm::vec3>& newPath) {
	for (int vertexIndex = 0; vertexIndex < newPath.size(); vertexIndex++){
		// path.push_back(newPath[vertexIndex]);
		if (path.size() < 2) {
			path.push_back(newPath[vertexIndex]);
		}
		else {
			int insertIndex = (int)ceil(path.size() / 2);
			path.insert(path.begin() + insertIndex, newPath[vertexIndex]);
		}
	}
}

ofPath Brush::createPathFromVertices(const vector<glm::vec3>& vertices) {
	ofPath path;
	if (vertices.size() >= 2) {
		path.moveTo(vertices[0]);
		for (int i = 1; i < vertices.size(); i++) {
			path.curveTo(vertices[i]);
		}
		path.close();
	}
	return path;
}

void Brush::draw(){

	drawPath.draw();

	for( int i = 0; i < allPaths.size(); i++){
		allPaths[i].draw();
	}
    
}


void Brush::addBrushPosition(int x, int y){
	linePoints.push_back(glm::vec2(x, y));
	linePath = getLineFromPoints(linePoints);
	addWidthToLine(linePath);
	drawPath = createPathFromVertices(createVertsFromPath(linePath, linePathWidth));
}

//--------------------------------------------------------------
void Brush::startNewPath(){
	linePoints.clear();
}

//--------------------------------------------------------------
void Brush::endNewPath(){
	allPaths.push_back(drawPath);
}