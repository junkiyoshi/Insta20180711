#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(39);
	ofSetColor(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int circle_radius = 72;
	int rect_len = 144;

	for (int x = rect_len / 2; x <= ofGetWidth() - rect_len / 2; x += rect_len) {

		for (int y = rect_len / 2; y <= ofGetHeight() - rect_len / 2; y += rect_len) {

			for (int deg = 0; deg < 360; deg += 10) {

				ofPoint noise_point = ofPoint(circle_radius * cos(deg * DEG_TO_RAD) + x, circle_radius * sin(deg * DEG_TO_RAD) + y);
				float noise_value = ofMap(ofNoise(noise_point.x * 0.005, noise_point.y * 0.005, ofGetFrameNum() * 0.005), 0, 1, 0.2, 1.2);

				ofPushMatrix();
				ofTranslate(x, y);

				ofPoint circle_point = ofPoint(circle_radius * noise_value * cos(deg * DEG_TO_RAD), circle_radius * noise_value * sin(deg * DEG_TO_RAD));
				ofPoint rect_point = this->make_rect_point(rect_len, deg);

				ofDrawLine(circle_point, rect_point);
				ofDrawCircle(circle_point, 2);

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
ofPoint ofApp::make_rect_point(float len, int deg, int z) {

	int half_len = len * 0.5;
	int param = (deg + 45) / 90;

	ofPoint point;

	switch (param % 4) {

	case 0:

		return ofPoint(half_len, ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), z);
	case 1:

		return  ofPoint(ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), half_len, z);
	case 2:

		return ofPoint(-half_len, ofMap((deg + 45) % 90, 0, 89, half_len, -half_len), z);
	case 3:

		return ofPoint(ofMap((deg + 45) % 90, 0, 89, -half_len, half_len), -half_len, z);
	default:

		return ofPoint(0, 0, 0);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}