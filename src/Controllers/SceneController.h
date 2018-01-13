#pragma once

//Setup and font
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include "ofxXmlSettings.h"
#include "ofxGui.h"

//Kinect classes
#include "Joints.h"
#include "Gestures.h"
#include "PointCloud.h"

//Visual classes
#include "Flock.h"
#include "Path.h"

//Controller classes
#include "OSCController.h"
#include "LightController.h"

class SceneController
{
public:
	SceneController();
	~SceneController();
	void update();
	void display();
	void drawSet();
	void drawProjectionSurface();
	void keyPressed(int key);

	//Scene functions
	void introScene();
	void firstScene();
	void secondScene();
	void thirdScene();
	void fourthScene();
	void outroScene();

	int scene = 0;
	int vehicleNum = 1;
	int streamLimit = 4;

	float opacity = 0.1;
	float fade = 3;

	//For Switching on and off viual debugging
	bool pcDraw, flowDraw, jointsDraw, dotsDraw, drawScene;

	once_flag coutOnce;

	ofxCenteredTrueTypeFont introText, introTextHash;
	ofxCenteredTrueTypeFont outroText;

	ofEasyCam cam;

	//ofShader visualShader;
	//ofFbo visualBuffer;
	float kinectView =  6;
	ofVec3f screen = ofVec3f(5.713, 3.2);
	ofVec3f screenPos = ofVec3f(-screen.x / 2, -0.54, -1);
	ofVec3f kinectPos = ofVec3f(0, 1.5, kinectView / 2);

	ofxXmlSettings gestureStored;
	ofxXmlSettings gestureLoad;


	//Regular Classes
	//ParticleSystem particleSystem;
	OSCController oscCtrler;
	Joints joints;

	//Classes that take references
	Gestures gestures = Gestures(joints);

	//Singleton Classes
	KinectCam *kinectCam = &KinectCam::get_kinectInstance();
	//FlowField *flowfield = new FlowField(20, screen, screenPos);
	PointCloud* pointcloud = &PointCloud::get_pCloudInstance();

	LightController lights = LightController(ofVec3f(2.64, 4.05, 0), ofVec3f(-2.64, 4.05, 0), gestures.joints.middle);

	Flock flock;
	ofxPanel flockingGui;
	ofParameterGroup flockingParams;
	ofParameter <float> desiredSep;
	ofParameter <float> neighborDistAli;
	ofParameter <float> neighborDistCoh;

	Path path;

	bool pathDraw, shaderDraw, flockDraw = true;


};

