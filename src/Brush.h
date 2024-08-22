#pragma once

#include "ofMain.h"

class Brush : public ofBaseApp{
	public:
		Brush();
		void draw();
        
		void addBrushPosition(int x, int y);
		void startNewPath();
		void endNewPath();

		ofPolyline getLineFromPoints(const vector<glm::vec2>& points);
		void addWidthToLine(const ofPolyline& pointLine); 
		vector<glm::vec3> createVertsFromPath(const ofPolyline& pointLine, const vector<glm::vec2>& width); 
		void addVertsToPath(vector<glm::vec3>& path, const vector<glm::vec3>& newPath);
		ofPath createPathFromVertices(const vector<glm::vec3>& vertices);
};
