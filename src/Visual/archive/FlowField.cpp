#include "FlowField.h"

//Reference: https://github.com/shiffman/The-Nature-of-Code-Examples/tree/master/chp06_agents/NOC_6_04_Flowfield

FlowField::FlowField(int _resolution, ofVec3f _screen, ofVec3f _screenPos) : 
resolution(_resolution),
screen(_screen),
screenPos(_screenPos)
{
	cols = ofGetWidth() / resolution;
	rows = ofGetHeight() / resolution;
	
	field.resize(cols);

	for (int i = 0; i < cols; ++i) {
		field[i].resize(rows);
	}
}


FlowField::~FlowField()
{

}

void FlowField::update() {
	float xoff = 0;
	for (int i = 0; i < cols; i++) {
		float yoff = 0;
		for (int j = 0; j < rows; j++) {
			float theta = ofMap(ofNoise(xoff, yoff, zoff), 0, 1, 0, TWO_PI);
			//ofVec2f v = ofVec2f(ofGetMouseX(), ofGetMouseY());
			//float theta = heading2d(v);

			//Polar to Cartesian coordinate transformation to get x and y componets of the vector
			field[i][j] = ofVec2f(cos(theta), sin(theta));
			yoff += 0.1;
		}
		xoff += 0.1;
	}
	zoff += 0.01;
}

void FlowField::display() {
	ofPushMatrix();
		ofTranslate(screenPos);
		ofScale(screen.x/ofGetWidth(), screen.y/ofGetHeight(), 0);
		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				drawVector(field[i][j], i * resolution, j * resolution, resolution - 2);
			}
		}
	ofPopMatrix();
}

// Renders a vector object 'v' as an arrow and a position 'x,y'
void FlowField::drawVector(ofVec2f v, float x, float y, float scayl) {
	ofPushMatrix();
	float arrowsize = 6;
	// Translate to position to render vector
	ofTranslate(x, y);
	ofSetColor(200, 100);
	ofSetLineWidth(1);

	// Call vector heading function to get direction (note that pointing to the right is a heading of 0) and rotate

	ofRotate(ofRadToDeg(heading2d(v)));

	// Calculate length of vector & scale it to be bigger or smaller if necessary
	float len = v.length()*scayl;

	// Draw three lines to make an arrow (draw pointing up since we've rotate to the proper direction)
	ofDrawLine(0, 0, len, 0);
	ofDrawLine(len, 0, len - arrowsize, +arrowsize / 2);
	ofDrawLine(len, 0, len - arrowsize, -arrowsize / 2);
	ofPopMatrix();
}

ofVec2f FlowField::lookup(ofVec2f lookup) {
	int column = int(ofClamp(lookup.x / resolution, 0, cols - 1));
	int row = int(ofClamp(lookup.y / resolution, 0, rows - 1));

	return field[column][row];
}

float FlowField::heading2d(ofVec3f _vel) {
	_vel.normalize();
	return atan2(_vel.y, _vel.x);
}