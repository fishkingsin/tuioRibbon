#pragma once

#include "ofMain.h"
#include "ofxTuio.h"
#define STRIP_LEN 200
class testApp : public ofBaseApp{

	public:
		void setup();
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
	void	tuioAdded(ofxTuioCursor & tuioCursor);
	void	tuioRemoved(ofxTuioCursor & tuioCursor);
	void	tuioUpdated(ofxTuioCursor & tuioCursor);
	struct Strip{
		ofVec3f point[STRIP_LEN];
		long strip_id;
	};
	vector< Strip > strips;
	
	ofxTuioClient tuioClient;
	bool isRemoving;
};
