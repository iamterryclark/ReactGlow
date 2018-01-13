#include "PointCloud.h"

PointCloud::PointCloud() {
	calculatedWorld.setMode(OF_PRIMITIVE_POINTS);

	pcThreshGui.setup("ThresholdGUI");
	pcThreshGui.add(minThresh.set("Min Threshold:", 0, 0, 1));
	pcThreshGui.add(maxThresh.set("Max Threshold", 1, 0, 1));
	
	visualShader.load("vertShader.vert", "fragShader.frag");
	cout << "pointCloud init" << endl;

}


PointCloud::~PointCloud() {
}

PointCloud& PointCloud::get_pCloudInstance() {
	static PointCloud *pointCloud = NULL;

	if (pointCloud == NULL) {
		pointCloud = new PointCloud();
		cout << "Pointcloud Created" << endl;
	}

	return *pointCloud;
}

void PointCloud::destroy_pCloudInstance() {
	PointCloud* pointCloud = &get_pCloudInstance();

	if (pointCloud != NULL) delete pointCloud;

	cout << "PointCLoud Destroyed" << endl;

}

//As at 05/03/2017
//I managed to integrate https://github.com/elliotwoods/ofxKinectForWindows2/example this example into this project
//I found that by doing this I was able to obtain a corrected pointcloud in 3d world view.
//This would now mean that  I can use this in order to create visuals and map this
//perfectly to the subjects form/shape.
void PointCloud::update() {
	if (kinectCam->kinect.isFrameNew()) {

		auto depth = kinectCam->kinect.getDepthSource();

		//This part will only happen once by using {} which acts like a data structure 'struct'
		//Reference: http://stackoverflow.com/questions/17701197/how-to-run-code-inside-a-loop-only-once-without-external-flag
		
		{
			depth->getDepthToWorldTable(depthToWorldTable);
			depthToWorldPreview.loadData(depthToWorldTable);
		}

		//build a mesh using the depthToWorldTable
		{
			auto size = depth->getWidth() * depth->getHeight();

			auto depthPixel = depth->getPixels().getData();
			auto depthToWorldRay = (ofVec2f*)depthToWorldTable.getData();

			this->calculatedWorld.clear();

			for (int i = 0; i < size; i++) {
				// Access ptr to change it with *depthPixel
				//Normalise the value from mm to m by dividing the depthPixel by 1000.0f
				float z = (float)*depthPixel / 1000.0f;
				ofVec3f vertex{ depthToWorldRay->x * z,
					depthToWorldRay->y * z,
					z };

				calculatedWorld.addVertex(vertex);
				depthPixel++;
				depthToWorldRay++;
			}
		}
	}

	//kinectDepthPixels = calculatedWorld;
}


void PointCloud::draw() {
	ofPushStyle();
	{
		ofSetColor(ofColor::red);
		this->calculatedWorld.drawVertices();
	}
	ofPopStyle();
	/*visualShader.begin();
	visualShader.setUniform1f("time", ofGetElapsedTimef());
	visualShader.setUniform2f("mouse", ofVec2f(ofGetMouseX(), ofGetMouseY()));
	visualShader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));*/
	//ofDrawRectangle(-2.5, 1.6, -0.5, 6.4, -3.2);

	//visualShader.end();
	//drawSet();
}

