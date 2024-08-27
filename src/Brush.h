#pragma once

#include "ofMain.h"
#include "Stroke.h"

class Brush : public ofBaseApp{
	public:
		Brush();
		void draw();

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();
        
		void addBrushPosition(int x, int y);
		void startNewPath();
		void endNewPath();

    private:
        Stroke drawStroke;
        vector<Stroke> allStrokes;

        ofPath drawPath;
        vector<ofPath> allPaths;

        ofMesh drawMesh;
        vector<ofMesh> allMeshes;

        ofPolyline linePath;
        vector<glm::vec2> linePathWidth;
        float lineSize = 12.0;
        float lineSizeVariation = 0.5;
        vector<glm::vec3> pathVerts;
        vector<glm::vec2> linePoints;

		ofPolyline getLineFromPoints(const vector<glm::vec2>& points);
		void addWidthToLine(const ofPolyline& pointLine); 
		vector<glm::vec3> createVertsFromPath(const ofPolyline& pointLine, const vector<glm::vec2>& width); 
		void addVertsToPath(vector<glm::vec3>& path, const vector<glm::vec3>& newPath);
		ofPath createPathFromVertices(const vector<glm::vec3>& vertices);
		void colorMesh(ofMesh& meshToColor);
};
