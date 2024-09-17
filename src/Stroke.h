#pragma once

#include "ofMain.h"

class Stroke : public ofBaseApp{
	public:
		Stroke();
		Stroke(float zHeight, ofColor& paintColor);
		Stroke(float zHeight, ofColor& paintColor, float& _lineSize, float& _lineSizeVariation, float& _simplificationFactor);


		void draw();
        
		void addStrokePosition(int x, int y);
		void startNewPath();
		void endNewPath();

		void setAlphaColor(float newAlpha);

		int getStrokeVertices();

    private:
		float zPosition;
		ofColor drawColor;

        ofPath drawPath;
        ofMesh drawMesh;
        ofPolyline linePath;
        vector<glm::vec2> linePathWidth;
        float lineSize = 2.0;
        float lineSizeVariation = 1.0;
        float simplificationFactor = 1.66;
        vector<glm::vec3> pathVerts;
        vector<glm::vec2> linePoints;
		int currentStrokeVertices;

		ofPolyline getLineFromPoints(const vector<glm::vec2>& points);
		void addWidthToLine(const ofPolyline& pointLine); 
		vector<glm::vec3> createVertsFromPath(const ofPolyline& pointLine, const vector<glm::vec2>& width);
		ofPath createPathFromVertices(const vector<glm::vec3>& vertices);
		void colorMesh(ofMesh& meshToColor);
};
