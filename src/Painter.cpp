#include "ofApp.h"
#include "Painter.h"
#include "Brush.h"

Brush userBrush;

Painter::Painter(){
    
}
//--------------------------------------------------------------
void Painter::initalize() {
	width = ofGetWidth();
	height = ofGetHeight();
	acceleration = { 0, 0 };
	velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
	location = { ofRandom(0, width), ofRandom(0, height) };
	target = { ofRandom(0, width), ofRandom(0, height) };
}
//--------------------------------------------------------------
void Painter::displayCanvas(){
	userBrush.draw();
}
//--------------------------------------------------------------
void Painter::displayDebugCanvas() {
	drawAgent();
}


//--------------------------------------------------------------
void Painter::update() {
	userBrush.decayStrokes();
	if (finishedStroke) {
		userBrush.endStroke();
		userBrush.startNewStroke();
	}
	else {
		userBrush.moveBrush(location.x, location.y);
	}
	updateLocation();
}

void Painter::moveBrush(int x, int y){
	userBrush.moveBrush(x, y);
}

//--------------------------------------------------------------
void Painter::startNewStroke(){
	userBrush.startNewStroke();
}

//--------------------------------------------------------------
void Painter::endStroke(){
	userBrush.endStroke();
}
//--------------------------------------------------------------
// BEHAVIOUR
//--------------------------------------------------------------
void Painter::updateLocation() {
	finishedStroke = false;
	seek(target);
	velocity += acceleration;
	// Limit
	if (glm::length(velocity) > maxSpeed) {
		velocity = glm::normalize(velocity) * maxSpeed;
	}
	location += velocity;
	acceleration *= 0;
	if (targetHit()) {
		finishedStroke = true;
		location = { ofRandom(0, width), ofRandom(0, height) };
		target = { ofRandom(0, width), ofRandom(0, height) };
		velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
	}
}

void Painter::applyForce(glm::vec2 force) {
	acceleration += force;
}

void Painter::seek(glm::vec2 target) {
	glm::vec2 desired = target - location;
	desired = glm::normalize(desired);
	float distance = glm::distance(location, target);
	if (distance < slowDownThreshhold) {
		desired *= ofMap(distance, 0, slowDownThreshhold, 0, maxSpeed);
	}
	else {
		desired *= maxSpeed;
	}
	desired += (ofNoise(location) * 2 - 1) * noiseInfluence;
	glm::vec2 steer = desired - velocity;
	// Limit
	if (glm::length(steer) > maxForce) {
		steer = glm::normalize(steer) * maxForce;
	}
	applyForce(steer);
}

bool Painter::targetHit() {
	if (glm::distance(location, target) < hitRadius) {
		return true;
	}
	return false;
}

void Painter::drawAgent() {
	ofSetColor(0, 0, 255);
	ofFill();
	ofDrawCircle(location, 10);
	ofSetColor(0, 255, 0);
	ofFill();
	ofDrawCircle(target, 10);
	ofSetColor(120, 255, 100);
	std::string speedStr = "MaxSpeed = ";
	speedStr += ofToString(maxSpeed);
	ofDrawBitmapString(speedStr, 10, 25);
	std::string forceStr = "MaxForce = ";
	forceStr += ofToString(maxForce);
	ofDrawBitmapString(forceStr, 10, 50);
	std::string thresholdStr = "SlowDownThreshhold = ";
	thresholdStr += ofToString(slowDownThreshhold);
	ofDrawBitmapString(thresholdStr, 10, 75);
	std::string noiseInfluenceStr = "NoiseInfluence = ";
	noiseInfluenceStr += ofToString(noiseInfluence);
	ofDrawBitmapString(noiseInfluenceStr, 10, 100);
	std::string hitRadiusStr = "HitRadius = ";
	hitRadiusStr += ofToString(hitRadius);
	ofDrawBitmapString(hitRadiusStr, 10, 125);
}