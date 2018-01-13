#include "OSCController.h"
//Reference: LiveOSC ableton addresses - https://github.com/q-depot/LiveOSC/blob/master/OSCAPI.txt

OSCController::OSCController()
{
	oscSender.setup(HOST, PORTSEND);
	oscRetreive.setup(PORTLISTEN);
	cout << "OSC Control init" << endl;
	cout << "listening for osc on port:" << PORTLISTEN << "\n";
	cout << "Sending messages to Ableton on port:" << PORTSEND << "\n";
}


OSCController::~OSCController() 
{
	kinectCam->destroy_kinectInstance();
}

void OSCController::retreive(vector <Vehicle*> *_vehicles) 
{
	while (oscRetreive.hasWaitingMessages()) {// get the next message
		ofxOscMessage m;
		oscRetreive.getNextMessage(&m);

		//Messages from ym Python Program which collects tweets
		if (m.getAddress() == "/tweetStreamCol") {
			tweetCol = m.getArgAsString(0);
		}

		if (m.getAddress() == "/tweetStreamNum") {
			_vehicles->push_back(new Vehicle(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofRandom(0.1, 2.), ofRandom(0.01, 2.0)));
			currentTweetNum++;
			cout << "current Tweet : " << currentTweetNum << endl;
		}

		//Messages From ableton device paramters
		/*if (m.getAddress() == "/live/device/param")
		{
			cout << m.getArgAsInt(0) << endl;
			cout << m.getArgAsInt(1) << endl;
			cout << m.getArgAsInt(2) << endl;
			cout << m.getArgAsInt(3) << endl;
			cout << m.getArgAsString(4) << endl;
		}*/
	}
}
void OSCController::streamToInstrumentDevice(string address, int track, int device, int parameter, float value) {
	ofxOscMessage m;
	m.setAddress(address);
	m.addIntArg(track);
	m.addIntArg(device);
	m.addIntArg(parameter);
	m.addFloatArg(value);
	oscSender.sendMessage(m);
	m.clear();
}

void OSCController::playScene(int scene) {
	ofxOscMessage m;
	m.setAddress("/live/play/scene");
	m.addIntArg(scene);
	oscSender.sendMessage(m);
	m.clear();

	cout << "Scene :" << scene << endl;

}

void OSCController::play() {
	ofxOscMessage m;
	m.setAddress("/live/play");
	oscSender.sendMessage(m);
	m.clear();
}

void OSCController::stop() {
	ofxOscMessage m;
	m.setAddress("/live/stop");
	oscSender.sendMessage(m);
	m.clear();
}