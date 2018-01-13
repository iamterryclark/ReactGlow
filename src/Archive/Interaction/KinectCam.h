#pragma once
#include "ofMain.h"
#include "ofxKinectForWindows2.h"

class KinectCam
{
private:
	KinectCam();
	~KinectCam();
protected:
public:
	static KinectCam& get_kinectInstance();
	static void destroy_kinectInstance();
	ofxKFW2::Device kinect;
};

