#pragma once
#include "ofMain.h"
#include "KinectCam.h"
#include "Joints.h"
#include "ofxGui.h"

#define kinectWidth 512
#define kinectHeight 424

class PointCloud
{
private:
	PointCloud();
	~PointCloud();

protected:

public:
	static PointCloud& get_pCloudInstance();
	static void destroy_pCloudInstance();

	void update();
	void draw();

	ICoordinateMapper* m_pCoordinateMapper; // For Skeleton Tracking
	DepthSpacePoint m_pDepthCoordinates[1024 * 768]; //For Pointcloud depth across the width of the display screen

	ofMesh nativeWorld;
	ofMesh calculatedWorld;

	ofFloatPixels depthToWorldTable;
	ofTexture depthToWorldPreview;

	ofxPanel pcThreshGui;
	ofParameterGroup pcParams;
	ofParameter<float> minThresh, maxThresh;
	bool drawGui;
	int steps = 10;

	Joints joints;

	//I needed the kinct cam to be a singleton in order to pass
	//the kinect source information to both the gestures and pointcloud as one instance.
	KinectCam *kinectCam = &KinectCam::get_kinectInstance();

	//This shader for passing depth values to GPU to display faster
	//I learnt about passing textures through to the shader from 
	//working with a small South London Company Kimatica. Nesto, their
	//programmer gave me an overview of the structure on how they acheive
	//their effects and this is by passing the texture through to the shader
	//once it is there the vertex and frag shader can be combined and this not
	//only speeds up the processing of the mesh but also can help to create
	//interesting visual affects
	ofShader visualShader;
	ofFloatPixels kinectDepthPixels;

};

