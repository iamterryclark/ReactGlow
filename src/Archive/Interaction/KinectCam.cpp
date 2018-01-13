#include "KinectCam.h"
//Reference: https://www.youtube.com/watch?v=uTG-cSGdcAE
//Reference: https://www.youtube.com/watch?v=zC6dWIr5804

/*  
	I created this class as a Singleton so I could have one instance of the Kinect running.
	The mian reason for this is that I am unable to open the kinect twice in order to get information
	passed to the gestures (Skelteon Tracking) and Pointcloud which as two seperate features of the kinect.
*/

KinectCam::KinectCam()
{
	//Open and initialise streams from the kinect
	kinect.open();

	kinect.initBodySource();
	kinect.initColorSource();
	kinect.initDepthSource();

	cout << "Kinect init" << endl;
}


KinectCam::~KinectCam()
{
}

//This returns a reference to the instance;
KinectCam& KinectCam::get_kinectInstance() {
	
	static KinectCam *kinectCam = NULL;

	if (kinectCam == NULL) {
		kinectCam = new KinectCam();
		cout << "KinectCam Created" << endl;
	}

	return *kinectCam;
}

void KinectCam::destroy_kinectInstance() {
	KinectCam* kinectCam = &get_kinectInstance();

	if (kinectCam != NULL) delete kinectCam;

	cout << "Kinect Destroyed" << endl;
}
