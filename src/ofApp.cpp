#include "ofApp.h"
#include "ofAppRunner.h"
#include "ofEvents.h"
#include "ofGraphics.h"
#include "ofMath.h"
#include "ofUtils.h"
#include <string>

// Function to draw a star centered at (centerX, centerY)
void drawStar(float centerX, float centerY, float radius) {

	// Calculate the outer and inner radii of the star
	float outerRadius = radius;
	float innerRadius = radius * 0.5; // Adjust the factor to control the size of the star

	// Calculate the angles for the five points of the star
	float angleIncrement = ofDegToRad(72); // 360 degrees divided by 5 points
	float angle = -ofDegToRad(90); // Start angle

	// Draw the star by connecting the points with lines
	for (int i = 0; i < 5; ++i) {
		float x1 = centerX + outerRadius * cos(angle);
		float y1 = centerY + outerRadius * sin(angle);

		angle += angleIncrement;

		float x2 = centerX + innerRadius * cos(angle);
		float y2 = centerY + innerRadius * sin(angle);

		ofDrawLine(x1, y1, x2, y2);
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(240, 240, 240);
	myFont.load("/usr/share/fonts/TTF/JetBrains Mono Regular Nerd Font Complete.ttf", 12);
	letters = "dreamsmith";
	capitalLetters = "DREAMSMITH";
	atLetter = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSetFrameRate(60);

	time += 0.010314;
}

//--------------------------------------------------------------
void ofApp::draw() {
	int cols = 150;
	int rows = 200;
	float spacing = 10;

	float mouseX = ofGetMouseX();
	float mouseY = ofGetMouseY();

	float hueStart = 200.0;
	float hueEnd = 255.0;
	float hueStep = (hueEnd - hueStart) / ofGetWidth();
	float currentTime = ofGetElapsedTimef();

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {

			// Calculate the x and y position using Perlin noise, time, and mouse position
			float x = i * spacing + ofNoise(i * 0.021, j * 0.1, time) * 50;
			float y = j * spacing + ofNoise(i * 0.1, j * 0.053, 5, time) * 50;

			x -= 50;
			y -= 50;

			// Calculate the direction from the dot to the mouse
			// float dirX = mouseX - x;
			// float dirY = mouseY - y;

			// Middle of screen instead...
			float dirX = (ofGetWidth() / 2) - x;
			float dirY = (ofGetHeight() / 2) - y;

			// gen X and Y coords with noise
			// float noiseX = ofMap(ofNoise(i * 0.001, j * 0.001, time * 0.5, sqrt(ofRandom(1) * 0.1)), 0, 1, 0, ofGetWidth());
			// float noiseY = ofMap(ofNoise(j * 0.001, i * 0.201, time * 0.5, ofRandom(1) * 0.1), 0, 1, 0, ofGetHeight());

			// float dirX = noiseX - x;
			// float dirY = noiseY - y;

			// Normalize the direction
			float length = sqrt(dirX * dirX + dirY * dirY);
			dirX /= length;
			dirY /= length;

			// Move the dot away from the mouse
			// float distance = ofDist(x, y, mouseX, mouseY);

			// Let's try measuring the distance between the middle of the screen instead...
			float distance = ofDist(x, y, dirX, dirY);

			// float distance = ofDist(x, y, noiseX, noiseY);
			// Let's try using noise to generate X and Y coordinates...

			// float repelForce = ofMap(distance, 0, 1000, 100, 0); // Adjust this value to control the repulsion strength
			float repelForce = 100;

			// nmaybe not usedful now but...
			// x -= dirX * ofMap(ofNoise(repelForce * 0.5, time * 0.005, distance * 0.3, x * 0.2), 0, 1, 1, 100);
			// y -= dirY * ofMap(ofNoise(repelForce * 0.5, time * 0.005, distance * 0.3, y * 0.2), 0, 1, 1, 100);

			x -= dirX * repelForce;
			y -= dirY * repelForce;

			// Calculate the hue based on the column index
			// float hue = fmod(j * hueStep, 255.0);
			float hue = fmod((time / 8) * hueStep, 255.0);
			float oscillatingValue = ofMap(sin(time / 2), -1, 1, 35, 80);

			float noiseValue = ofNoise(time * 0.3, i * 0.5, j * 0.3, hue * 0.2); // Adjust the noise frequency as needed
			float greenComponent = ofMap(noiseValue, 0, 1, 20, 200);

			// Create an ofColor with the calculated hue
			// ofColor color;
			// color.setHsb(greenComponent, 255, oscillatingValue);

			// Set the color and draw a circle at the calculated position
			ofSetColor(33, 33, 33);
			// Draw a circle at the calculated position
			//
			// float radNoise = ofNoise(time * 0.005, i * 0.03, distance * 0.08, greenComponent * 0.05);
			// float rad = ofMap(radNoise, 0, 1, 1, 4);
			// ofDrawCircle(x, y, rad);
			// drawStar(x, y, rad);
			float whNoise = ofNoise(time * 0.005, i * 0.03, distance * 0.08, j * 0.28);
			float wh = ofMap(whNoise, 0, 1, -200, -0);
			myFont.drawString(ofToString(letters[ofMap(whNoise, 0, 1, 0, letters.length())]), x, y);
			// ofDrawBitmapString(ofToString(letters[ofMap(x, 0, ofGetWidth(), 0, letters.length())]), x, y, wh);

			// ofDrawRectangle(x, y, wh, wh);
		}
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
