#include "SceneController.h"
/*
The SceneController handles all the different interactions between the scenes throughout the performance.
It will help to activate all the necessary components between scenes and deactivate those which are not needed to help computing performance.

Components Include: 
- Tweepy: Runs throughout the performance
- Pointcloud: Runs at intervals
- Particle system: Runs throughout the performance
- Skeleton Tracking: Runs throughout the performance
- OSC: Runs throughout the performance to retrieve tweets and send to Ableton.


The space is set in a kinect sense of space which is 6 meters cubed. This allowed a high accuracy in measurments to set up the physical space.
*/

SceneController::SceneController()
{
	//Text currently not working
	introText.load("fonts/OpenSans-Light.ttf", 45);
	introTextHash.load("fonts/OpenSans-BoldItalic.ttf", 40);
	outroText.load("fonts/OpenSans-Bold.ttf", 30);

	//Setup camera to show everything in the center
	cam.rotate(180, 0, 1, 0);
	cam.setNearClip(-1);
	cam.setFarClip(1);

	//Gui
	flockingGui.setup("Flocking Gui");
	flockingParams.setName("Sep/Ali/Coh Params");
	flockingParams.add(desiredSep.set("Desired Sep: ", 3.0f, 0, 10.0f));
	flockingParams.add(neighborDistAli.set("NeighborDistAli: ", 3.0f, 0, 10.0f));
	flockingParams.add(neighborDistCoh.set("NeighborDistCoh: ", 3.0f, 0, 10.0f));
	flockingGui.add(flockingParams);

	path.points.clear();

	cam.setPosition(0, 0, 0);

	//Need to add afirst point otherwise program crashes
	path.addPoint(ofVec3f(0, 0, 100));

	cout << "SceneController Init" << endl;
}

SceneController::~SceneController()
{
	//delete flowfield;
}

void SceneController::update() {
	
	//This means the kinect updates both the gestures and pointcloud as it is a singleton
	kinectCam->kinect.update();
	
	//Updates need to happen through out the performance
	pointcloud->update();
	joints.update();
	gestures.poseChecker();
	flock.run(path, desiredSep, neighborDistAli, neighborDistCoh);
	
	//Checks for all incoming osc messages i.e tweets
	oscCtrler.retreive(&flock);

	//Constantly change lighting position based on dancer position.
	lights.update();

	//Main scene switch statements
	switch (scene) {
		case 0:	introScene(); break;
		case 1:	firstScene(); break;
		case 2:	secondScene(); break;
		case 3:	thirdScene(); break;
		case 4:	fourthScene(); break;
		case 5:	outroScene(); break;
	}
}

/*
Instructions to tweet displayed and audio-reactive, shader dots appear gradually.
*Note: Music starts when first dot appears.*
Dancer enteres and Pose1 activates the scene switch.
*/

void SceneController::introScene() {
	
	ofPushMatrix();
		ofPushStyle();
			ofTranslate(0,0,500);
			ofRotate(180, 0, 1,0);
			ofScale(0.5, 0.5);
			ofSetColor(255);
			introText.drawStringCentered("This is a tweetable performance", 0, -1);
			introText.drawStringCentered("Participate throughout the show by tweeting", 0,0);
			introTextHash.drawStringCentered("#ReactGlow", 0,1);
		ofPopStyle();
	ofPopMatrix();

	opacity += fade;

	if (opacity >= 255.0) fade = fade;
	if (opacity <= 0.0) fade = -fade;
	
	if (oscCtrler.currentTweetNum == 6) {
		oscCtrler.playScene(0);
		cout << oscCtrler.currentTweetNum << endl;
	}

	if (oscCtrler.currentTweetNum == 10) {
		scene = 1;
		oscCtrler.playScene(1);
	}

	call_once(coutOnce, [] { cout << "Intro Scene" << endl; });
}

/*
Lights fade up and dots repel from dancer - ParticleSystem behaviour 1.
Dancer interacts with music
Pose 2 changes scene
*/

void SceneController::firstScene() {

	ofVec3f rightHand = ofVec3f(joints.normalisedRightHand);
	ofVec3f leftHand = ofVec3f(joints.normalisedLeftHand);

	if (ofGetFrameNum() % streamLimit == 0)
	{
		//Adjusts the distortion in the first scene to create turbulance
		oscCtrler.streamToInstrumentDevice("/live/device", 10, 1, 3, ofMap(rightHand.x, 0, 1, 0, 90)); //Motion
		oscCtrler.streamToInstrumentDevice("/live/device", 10, 1, 4, ofMap(rightHand.y, 0, 1, 0, 90)); //Effects Amounts
		oscCtrler.streamToInstrumentDevice("/live/device", 10, 1, 7, ofMap(leftHand.x, 1, -1, 0, 127)); //Distortiqon amount
	}

	call_once(coutOnce, [] { cout << "Frist Scene" << endl; });
}

/*
Dancer Controls music params through movement
Visual fade in and out with dancer movement
*/
void SceneController::secondScene() {

	call_once(coutOnce, [] { cout << "Second Scene" << endl; });
}

/*
Dancer can control dots with path finder style gestures in certain z space
No music Control
*/

void SceneController::thirdScene() {
	call_once(coutOnce, [] { cout << "Third Scene" << endl; });
}

/*
Dancer on floor ParticleSystem and PointCloud connect and points surround dancer
Dancer controlled music with hands
*/

void SceneController::fourthScene() {
	call_once(coutOnce, [] { cout << "Fouth Scene" << endl; });
}

/*
Display the dots in rows and coloumns onscreen to audience 
only to those who participated and shows their usernames. 
Extra dots I add will disapear
*/

void SceneController::outroScene() {

	ofVec3f rightHand = ofVec3f(joints.normalisedRightHand);
	ofVec3f leftHand = ofVec3f(joints.normalisedLeftHand);

	if (ofGetFrameNum() % streamLimit == 0)
	{
		//This adjusts the arpegio in the outro to get intersting glitchy effects
		oscCtrler.streamToInstrumentDevice("/live/device", 21, 0, 5, ofMap(rightHand.x/rightHand.y, 0.5, -0.5, 0, 13));
		oscCtrler.streamToInstrumentDevice("/live/device", 21, 0, 8, ofMap(leftHand.x/leftHand.y, 0.5, -0.5, 0, 200));
	}

	call_once(coutOnce, [] { cout << "Outro Scene" << endl; });
}

void SceneController::display() {
	cam.begin();
	ofScale(100,100,100);

	if (pcDraw) pointcloud->draw();

	if (jointsDraw)	
		joints.draw();

	if (drawScene) 
	{
		lights.display();
		drawSet();
	}

	flock.display();

	drawProjectionSurface();

	cam.end();
	
	ofDisableDepthTest(); //Must disable so that gui is then drawn properly
	
	//Maybe I also need to put the text here to render properly this has been a bug for me recently

	//Gui's
	if (flockDraw) flockingGui.draw();
}
 
void SceneController::drawSet() {
	//6meter container box (due to kinect range)
	ofPushMatrix();
		ofPushStyle();
			ofSetColor(255);
			ofNoFill();
			ofSetLineWidth(3);
			ofTranslate(kinectPos);
			ofScale(1.5, 1);
			ofDrawBox(kinectView);
		ofPopStyle();
	ofPopMatrix();
}

void SceneController::drawProjectionSurface() {
	ofPushStyle();
		ofSetColor(255, 50);
		ofFill();
		ofDrawRectangle(screenPos, screen.x, screen.y);
	ofPopStyle();
}

void SceneController::keyPressed(int key) {
	switch (key) {
	
	//Draw Scene for debugging
	case 'p':
		pcDraw = !pcDraw;
		cout << "pcDraw: " << pcDraw << endl;
		break;
	case 'f':
		shaderDraw = !shaderDraw;
		cout << "shaderDraw: " << shaderDraw << endl;
		break;
	case 'j':
		jointsDraw = !jointsDraw;
		cout << "jointsDraw: " << jointsDraw << endl;
		break;
	case 'd':
		dotsDraw = !dotsDraw;
		cout << "dotsDraw: " << dotsDraw << endl;
		break;
	case 's':
		drawScene = !drawScene;
		cout << "drawScene: " << drawScene << endl;
		break;

	//Path Clearing
	case ' ':
		path.points.clear();
		path.addPoint(ofVec3f(0, 0, 0));
		break;

	//Save & Load poses
	case 'z':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestureStored.setValue("joint" + ofToString(i), ofToString(*joints.skelJoints[i]));
		}
		gestureStored.save("stored_poses/pose1.xml");
		cout << "pose 1 stored" << endl;
		break;
	case 'x':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestureStored.setValue("joint" + ofToString(i), ofToString(*joints.skelJoints[i]));
		}
		gestureStored.save("stored_poses/pose2.xml");
		cout << "pose 2 stored" << endl;
		break;
	case 'c':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestureStored.setValue("joint" + ofToString(i), ofToString(*joints.skelJoints[i]));
		}
		gestureStored.save("stored_poses/pose3.xml");
		cout << "pose 3 stored" << endl;
		break;
	case 'v':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestureStored.setValue("joint" + ofToString(i), ofToString(*joints.skelJoints[i]));
		}
		gestureStored.save("stored_poses/pose4.xml");
		cout << "pose 4 stored" << endl;
		break;
	case 'b':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestureStored.setValue("joint" + ofToString(i), ofToString(*joints.skelJoints[i]));
		}
		gestureStored.save("stored_poses/pose5.xml");
		cout << "pose 5 stored" << endl;
		break;
	case 'l':
		//Load all poses into software
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			//gestureLoad.loadFile("");
			//ofFromString<ofVec3f>();
		}

		break;
	}

}

