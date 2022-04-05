#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	// 配色デザイン ソフトグリーン P114
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(97, 157, 110));
	color_palette.push_back(ofColor(119, 180, 106));
	color_palette.push_back(ofColor(143, 173, 91));
	color_palette.push_back(ofColor(145, 195, 161));
	color_palette.push_back(ofColor(93, 169, 145));
	color_palette.push_back(ofColor(255, 255, 255));
	color_palette.push_back(ofColor(131, 193, 215));
	color_palette.push_back(ofColor(249, 229, 128));

	auto source_deg = ofRandom(360);
	auto target_deg = source_deg + ofRandom(45, 315);

	this->source_deg_list.push_back(source_deg);
	this->target_deg_list.push_back(target_deg);
	this->color_list.push_back(color_palette[ofRandom(color_palette.size())]);

	while (this->source_deg_list.size() > 80) {

		this->source_deg_list.erase(this->source_deg_list.begin());
		this->target_deg_list.erase(this->target_deg_list.begin());
		this->color_list.erase(this->color_list.begin());
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	float radius = 250;


	for(int i = 0; i < this->source_deg_list.size(); i++){

		auto base_location = glm::vec2(radius * cos(source_deg_list[i] * DEG_TO_RAD), radius * sin(source_deg_list[i] * DEG_TO_RAD));
		auto color = this->color_list[i];
		color.setHsb(color.getHue(), color.getSaturation(), ofMap(i, 0, 80, 0, 255));

		this->draw_arrow(base_location, glm::vec2(radius * cos(target_deg_list[i] * DEG_TO_RAD), radius * sin(target_deg_list[i] * DEG_TO_RAD)), 30, color);
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	ofPushMatrix();
	ofTranslate(target);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofSetColor(0);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.5);
	ofEndShape();

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}