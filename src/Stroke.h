#pragma once

#include "ofMain.h"

class Stroke : public ofBaseApp{
	public:
		Stroke();
		Stroke(float zHeight);
		void draw();
        
		void addStrokePosition(int x, int y);
		void startNewPath();
		void endNewPath();

    private:
		float zPosition;
		float birthtime;

        ofPath drawPath;
        ofMesh drawMesh;
        ofPolyline linePath;
        vector<glm::vec2> linePathWidth;
        float lineSize = 5.0;
        float lineSizeVariation = 0.5;
        float simplificationFactor = 1.66;
        vector<glm::vec3> pathVerts;
        vector<glm::vec2> linePoints;

		ofPolyline getLineFromPoints(const vector<glm::vec2>& points);
		void addWidthToLine(const ofPolyline& pointLine); 
		vector<glm::vec3> createVertsFromPath(const ofPolyline& pointLine, const vector<glm::vec2>& width);
		ofPath createPathFromVertices(const vector<glm::vec3>& vertices);
		void colorMesh(ofMesh& meshToColor);
};
