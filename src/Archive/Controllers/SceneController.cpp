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

*/

SceneController::SceneController()
{
	introText.load("open-sans/OpenSans-Light.ttf", 40);
	introTextHash.load("open-sans/OpenSans-BoldItalic.ttf", 45);
	outroText.load("open-sans/OpenSans-Bold.ttf", 15);

	//Setup camera to show everything in the center
	cam.rotate(180, 0, 1, 0);
	cam.setNearClip(-1);
	cam.setFarClip(1);

	//visualShader.load("vertShader.vert", "fragShader.frag");
	
	cout << "SceneController Init" << endl;
}

SceneController::~SceneController()
{
	//kinectCam->destroy_kinectInstance();
	//pointcloud->destroy_pCloudInstance();
	delete flowfield;

}

void SceneController::update() {
	//This means the kinect updates both the gestures and pointcloud as it is a singleton
	kinectCam->kinect.update();
	
	//Updates need to happen through out the performance
	pointcloud->update();
	joints.update();
	gestures.poseChecker();
	
	//Particle system runs on a defined behaviour
	//particleSystem.run(coordNum);
	flowfield->update();
	//Checks for all incoming and outgoing osc messages
	oscCtrler.retreive(&vehicles);
	lights.update();

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
			//ofTranslate(0,0,0);
			//ofRotate(180, 0, 1,0);
			ofSetColor(255, opacity);
			introText.drawStringCentered("This is a tweetable performance", 0, 0);
			introText.drawStringCentered("Participate throughout the show by tweeting", 0,0);
			introTextHash.drawStringCentered("#ReactGlow", 0,0);
		ofPopStyle();
	ofPopMatrix();

	opacity += fade;

	if (opacity >= 255.0) fade = fade;
	if (opacity <= 0.0) fade = -fade;
	
	if (oscCtrler.currentTweetNum > 1) {
		oscCtrler.playScene(1);
	}

	if (oscCtrler.currentTweetNum > 10) {
		scene = 1;
		oscCtrler.playScene(2);
	}

	call_once(coutOnce, [] { cout << "Intro Scene" << endl; });
}

/*
Lights fade up and dots repel from dancer - ParticleSystem behaviour 1.
Dancer interacts with music
Pose 2 changes scene
*/

void SceneController::firstScene() {



	if (ofGetFrameNum() % 2 == 0)
	{
		oscCtrler.streamToInstrumentDevice("/live/device", 10, 1, 3, ofMap(ofGetMouseX(), 0, ofGetWidth() / 2, 0, 90)); //Motion
		oscCtrler.streamToInstrumentDevice("/live/device", 10, 1, 4, ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 90)); //Effects Amounts
		oscCtrler.streamToInstrumentDevice("/live/device", 10, 1, 7, ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 70)); //Distortiqon amount
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
	if (ofGetFrameNum() % 2 == 0)
	{
		oscCtrler.streamToInstrumentDevice("/live/device", 21, 0, 5, ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 13));
		oscCtrler.streamToInstrumentDevice("/live/device", 21, 0, 8, ofMap(ofGetMouseY(), 0, ofGetWidth(), 0, 200));

	}
	call_once(coutOnce, [] { cout << "Outro Scene" << endl; });
}

void SceneController::display(int _avgRms) {
	cam.begin();
	ofScale(100,100,100);

	if (pcDraw) pointcloud->draw();
	
	if (flowDraw) flowfield->display();

	ofPushMatrix();
		ofTranslate(screenPos);
		ofScale(screen.x / ofGetWidth(), screen.y / ofGetHeight(), 0);
		for (Vehicle * v : vehicles) {
			v->follow(flowfield);
			v->run();
		};
	ofPopMatrix();

	if (jointsDraw)	joints.draw();
	//if (dotsDraw) particleSystem.display(_avgRms);

	if (drawScene) {
		lights.display();
		drawSet();
	}

	drawProjectionSurface();

	cam.end();
	
	ofDisableDepthTest();
	
	//Gui's
	if (pcDraw) pointcloud->pcThreshGui.draw();
}
 
void SceneController::drawSet() {
	//6meter container box (due to kinect range)
	ofPushMatrix();
		ofPushStyle();
			ofSetColor(255);
			ofNoFill();
			ofSetLineWidth(3);
			ofTranslate(kinectPos);
			ofDrawBox(kinectView);
		ofPopStyle();
	ofPopMatrix();
}

void SceneController::drawProjectionSurface() {
	ofPushStyle();
	/*visualShader.begin();
	visualShader.setUniform1f("time", ofGetElapsedTimef());
	visualShader.setUniform2f("mouse", ofVec2f(ofGetMouseX(), ofGetMouseY()));
	visualShader.setUniform2f("resolution", ofVec2f(ofGetWidth(), ofGetHeight()));
	visualShader.setUniform1i("particleNum", particleSystem.particles.size());

	if (particleSystem.particles.size() > 0) {
		for (int i = 0; i < particleSystem.particles.size(); i++) {
			visualShader.setUniform2f("particle" + to_string(i), particleSystem.particles[i].pos);
		}
	}

	
	visualShader.end();*/
		ofSetColor(0, 50);
		ofFill();
		ofDrawRectangle(screenPos, screen.x, screen.y);
	ofPopStyle();
}

void SceneController::keyPressed(int key) {
	switch(key) {
	case 'p':
		pcDraw = !pcDraw;
		cout << "pcDraw: " << pcDraw << endl;
		break;
	case 'f':
		flowDraw = !flowDraw;
		cout << "flowDraw: " << flowDraw << endl;
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
	case ' ':
		vehicles.push_back(new Vehicle(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofRandom(0.1, 2.), ofRandom(0.01, 2.0)));
		//particleSystem.addParticle("white");
		cout << "particle added" << endl;
		break;
	/*case '1':
		coordNum = 0;
		cout << "coordNum" << coordNum << endl;
		break;
	case '2':
		coordNum = 1;
		cout << "coordNum" << coordNum << endl;
		break;
	case '3':
		coordNum = 2;
		cout << "coordNum" << coordNum << endl;
		break;
	case '4':
		coordNum = 3;
		cout << "coordNum" << coordNum << endl;
		break;
	case '5':
		coordNum = 4;
		cout << "coordNum" << coordNum << endl;
		break;*/
	case 'z':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestures.storedPose1[i] = *joints.skelJoints[i];
		}
		cout << "pose 1 stored" << endl;
		break;
	case 'x':
		for (int i = 0; i <  joints.skelJoints.size(); i++) {
			gestures.storedPose2[i] = *joints.skelJoints[i];
		}
		cout << "pose 2 stored" << endl;
		break;
	case 'c':
		for (int i = 0; i <  joints.skelJoints.size(); i++) {
			gestures.storedPose3[i] = *joints.skelJoints[i];
		}
		cout << "pose 3 stored" << endl;
		break;
	case 'v':
		for (int i = 0; i < joints.skelJoints.size(); i++) {
			gestures.storedPose4[i] = *joints.skelJoints[i];
		}
		cout << "pose 4 stored" << endl;
		break;
	case 'b':
		for (int i = 0; i <  gestures.joints.skelJoints.size(); i++) {
			gestures.storedPose5[i] = *joints.skelJoints[i];
		}
		cout << "pose 5 stored" << endl;
		break;
	}
}

