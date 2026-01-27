#include "ofApp.h"
#include "Painter.h"
#include "Brush.h"


Painter::Painter(){

}


Painter::Painter(
	// Behaviour
	int _slowDownThreshhold,
	float _noiseInfluence,
	int _hitRadius,
	float _maxSpeed,
	float _maxForce,
	// Paint Style
	std::vector<ofColor>& _palette,
	int _alpha, 
	float _lifeTime, 
	float _decayTime, 
	float _strokePositionVariation,
	float _lineSize, 
	float _lineSizeVariation, 
	float _simplificationFactor
	) {
	userBrush = std::make_unique<Brush>(
		// For BrushStroke Class
		_alpha, _lifeTime, _decayTime, _strokePositionVariation,
		// For Stroke Class
		_lineSize, _lineSizeVariation, _simplificationFactor
	);
	// Behaviour
	slowDownThreshhold = _slowDownThreshhold;
	noiseInfluence = _noiseInfluence;
	hitRadius = _hitRadius;
	maxSpeed = _maxSpeed;
	maxForce = _maxForce;
	palette = _palette;
}

//--------------------------------------------------------------
void Painter::initalize() {
	width = ofGetWidth();
	height = ofGetHeight();
	acceleration = { 0, 0 };
	location = { ofRandom(0, width), ofRandom(0, height) };
	target = { ofRandom(0, width), ofRandom(0, height) };
	// Create a random direction, then scale it to maxSpeed immediately
	velocity = glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1));
	velocity = glm::normalize(velocity) * maxSpeed;
	// This applies the correct brush settings (Heinrich/Christel)
	// to the active stroke immediately.
	startNewStroke();
}

void Painter::setPalette(std::vector<ofColor>&_palette) {
	width = ofGetWidth();
	height = ofGetHeight();
	acceleration = { 0, 0 };
	velocity = { ofRandom(0, 50) - 25, ofRandom(0, 50) - 25 };
	location = { ofRandom(0, width), ofRandom(0, height) };
	target = { ofRandom(0, width), ofRandom(0, height) };
}
//--------------------------------------------------------------
void Painter::displayCanvas(){
	userBrush->draw();
}
//--------------------------------------------------------------
void Painter::displayDebugCanvas() {
	drawAgent();
}


//--------------------------------------------------------------
void Painter::update() {
	userBrush->decayStrokes();
	updateLocation();
	if (finishedStroke) {
		userBrush->endStroke();
		userBrush->setColor(palette[(int)ofRandom(0,palette.size())]);
		userBrush->startNewStroke();
		finishedStroke = false;
	}
	userBrush->moveBrush(location.x, location.y);
}

void Painter::moveBrush(int x, int y){
	userBrush->moveBrush(x, y);
}

//--------------------------------------------------------------
void Painter::startNewStroke(){
	userBrush->startNewStroke();
}

//--------------------------------------------------------------
void Painter::endStroke(){
	userBrush->endStroke();
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

	checkBorders();

	if (targetHit()) {
		finishedStroke = true;
		location = { ofRandom(0, width), ofRandom(0, height) };
		target = { ofRandom(0, width), ofRandom(0, height) };
		// Create a random direction, then scale it to maxSpeed immediately
		velocity = glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1));
		velocity = glm::normalize(velocity) * maxSpeed;
		// userBrush->endStroke();
	}
}

void Painter::applyForce(glm::vec2 force) {
	acceleration += force;
}

/*  void Painter::seek(glm::vec2 target) {
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
} */

// Seek fix, adds noise properly and should keep agent from getting stuck
void Painter::seek(glm::vec2 target) {
	glm::vec2 desired = target - location;
	float dist = glm::length(desired);

	if (dist > 0) desired = glm::normalize(desired);

	// Calculate the base speed based on distance (Arrival behavior)
	if (dist < slowDownThreshhold) {
		// Slow down as we arrive
		desired *= ofMap(dist, 0, slowDownThreshhold, 0, maxSpeed);
	} else {
		// Go full speed when far away
		desired *= maxSpeed;
	}

	// Calculate Noise
	// We use an angle to create a true 2D direction, avoiding the "diagonal stuck" bug.
	float noiseAngle = ofNoise(location.x * 0.005, location.y * 0.005, ofGetElapsedTimef() * 0.1) * TWO_PI * 4.0;
	glm::vec2 noiseVector(cos(noiseAngle), sin(noiseAngle));

	//Apply Noise
	// If we are close to the target, we MUST reduce noise, or he will never hit it.
	float currentNoiseInfluence = noiseInfluence;
	if (dist < slowDownThreshhold) {
		// Map noise to 0 at 'hitRadius', not at 0.
        // This ensures that when he is close to the finish line, 
        // the noise is COMPLETELY gone, allowing him to step over the line.
        // We add a small buffer (hitRadius + 10) to be safe.
		float safeZone = hitRadius * 1.2;
		currentNoiseInfluence = ofMap(dist, safeZone, slowDownThreshhold, 0, noiseInfluence, true);
	}

	desired += noiseVector * currentNoiseInfluence;

	// Steering Physics
	glm::vec2 steer = desired - velocity;
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

void Painter::checkBorders() {
	// If he flies off-screen, steer him back to center strongly
	// or simply wrap him around. Bouncing is best for this art style.

	bool offScreen = false;
	float margin = 50; // Buffer zone

	if (location.x < -margin) {
		location.x = -margin;
		velocity.x *= -1;
		offScreen = true;
	}
	if (location.x > width + margin) {
		location.x = width + margin;
		velocity.x *= -1;
		offScreen = true;
	}
	if (location.y < -margin) {
		location.y = -margin;
		velocity.y *= -1;
		offScreen = true;
	}
	if (location.y > height + margin) {
		location.y = height + margin;
		velocity.y *= -1;
		offScreen = true;
	}

	// Uncomment this if bouncing looks weird:
	/* if(offScreen) {
        target = { ofRandom(width), ofRandom(height) };
    } 
    */
}
