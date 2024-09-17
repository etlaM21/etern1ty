#pragma once

#include "ofMain.h"
#include "Brush.h"

class Painter : public ofBaseApp{
	public:
		Painter();

		void initalize();

		void displayCanvas();
		void displayDebugCanvas();
		void update();

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();

    private:
		// Helper
		bool finishedStroke = false;
		int width;
		int getWidth() const { return width; }
		int height;
		int getHeight() const { return height; }

		// Behaviour
		int slowDownThreshhold = 30;
		float noiseInfluence = 1.75f;
		int hitRadius = 10;
		float maxSpeed = 8.5f;
		float maxForce = 0.4f;

		void updateLocation();
		void seek(glm::vec2 target);
		void applyForce(glm::vec2 force);
		bool targetHit();
		void drawAgent();

		glm::vec2 location;
		glm::vec2 lastLocation;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		glm::vec2 target;

		ofColor palette[10] = {
			ofColor(100, 255, 255),
			ofColor(100, 80, 255),
			ofColor(250, 125, 255),
			ofColor(250, 125, 186),
			ofColor(250, 225, 123),
			ofColor(125, 175, 186),
			ofColor(0, 0, 25),
			ofColor(0, 0, 25),
			ofColor(0, 0, 25),
			ofColor(0, 0, 25),
		};
};
