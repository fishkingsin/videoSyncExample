#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxMostPixelsEver.h"
class testApp : public ofBaseApp{

	public:
		void setup();
	void exit();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	ofxTCPClient tcp;
	ofQTKitPlayer player;
	ofMesh mesh;
	ofDirectory dir ;
	int currentVideoIdx;
	ofRectangle playerRect;
	float speed;
	float currentTime;
	ofFbo fbo;
};
