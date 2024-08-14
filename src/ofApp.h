#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		ofShader shader;

		ofPolyline getLineFromPoints(vector<glm::vec2> points);
		void addWidthToLine(ofPolyline pointLine); 
		vector<glm::vec3> createVertsFromPath(ofPolyline pointLine, vector<glm::vec2> width); 
		void addVertsToPath(vector<glm::vec3>& path, const vector<glm::vec3>& newPath);
		ofPath createPathFromVertices(const vector<glm::vec3>& vertices);
};
