#pragma once

#include "ofMain.h"
#include "Brush.h"

class Painter : public ofBaseApp{
	public:
		Painter();
		void displayCanvas();
		void displayDebugCanvas();
		void update();

		void moveBrush(int x, int y);
		void startNewStroke();
		void endStroke();

    private:
		// Helper
		bool finishedStroke = false;
		int width = 500;
		int getWidth() const { return width; }
		int height = 500;
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

		glm::vec2 location = { ofRandom(0, width), ofRandom(0, height) };
		glm::vec2 lastLocation;
		glm::vec2 velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
		glm::vec2 acceleration = { 0, 0 };
		glm::vec2 target;
};
