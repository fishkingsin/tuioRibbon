#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableSmoothing();
	tuioClient.start(3333);
    
    ofAddListener(tuioClient.cursorAdded,this,&testApp::tuioAdded);
	ofAddListener(tuioClient.cursorRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuioClient.cursorUpdated,this,&testApp::tuioUpdated);
	isRemoving = false;
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(255);
	tuioClient.getMessage();
	if(!isRemoving)
	{
		vector<Strip>::iterator itr;
		for(itr=strips.begin() ; itr!=strips.end() ; itr++)
		{
			Strip *s = &(*itr);
			
			for(int i = STRIP_LEN-1 ; i > 0 ; i--)
			{
				s->point[i].x = s->point[i-1].x;
				s->point[i].y = s->point[i-1].y;
			}
			
		}
	}

}
//--------------------------------------------------------------
void testApp::tuioAdded(ofxTuioCursor &tuioCursor){
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	ofLogVerbose() << "Point n" << tuioCursor.getSessionId() << " add at " << loc << endl;
	Strip strip;
	strip.strip_id=tuioCursor.getSessionId();
	for(int i = 0 ; i < STRIP_LEN ; i++)
	{
		strip.point[i] = loc;
		strip.point[i].z = i*-10;
	}
	strips.push_back(strip);
}
//--------------------------------------------------------------
void testApp::tuioUpdated(ofxTuioCursor &tuioCursor){
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	ofLogVerbose() << "Point n" << tuioCursor.getSessionId() << " updated at " << loc << endl;
	//	if(!strips.empty())
	{
		vector<Strip>::iterator itr;
		for(itr=strips.begin() ; itr!=strips.end() ; itr++)
		{
			Strip *s = &(*itr);
			if(s->strip_id==tuioCursor.getSessionId())
			{
				
				s->point[0] = loc;
				
			}
		}
	}
}
//--------------------------------------------------------------
void testApp::tuioRemoved(ofxTuioCursor &tuioCursor){
	isRemoving = true;
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(),tuioCursor.getY()*ofGetHeight());
	ofLogVerbose() << "Point n" << tuioCursor.getSessionId() << " remove at " << loc << endl;
	if(!strips.empty())
	{
		vector<Strip>::iterator itr;
		for(itr=strips.begin() ; itr!=strips.end() ; itr++)
		{
			Strip s = *itr;
			if(s.strip_id==tuioCursor.getSessionId())
			{
				strips.erase(itr);
				itr--;
			}
		}
	}
	isRemoving = false;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	if(!isRemoving)
	{
		ofSetColor(0);
		vector<Strip>::iterator itr;
		for(itr=strips.begin() ; itr!=strips.end() ; itr++)
		{
			Strip s = *itr;
			
			ofMesh mesh;
			mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
			for(int i = 1; i < STRIP_LEN; i++){
				
				//find this point and the next point
				ofVec3f thisPoint = s.point[i-1];
				ofVec3f nextPoint = s.point[i];
				
				//get the direction from one to the next.
				//the ribbon should fan out from this direction
				ofVec3f direction = (nextPoint - thisPoint);
				
				//get the distance from one point to the next
				float distance = direction.length();
				
				//get the normalized direction. normalized vectors always have a length of one
				//and are really useful for representing directions as opposed to something with length
				ofVec3f unitDirection = direction.normalized();
				
				//find both directions to the left and to the right
				ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
				ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
				
				//use the map function to determine the distance.
				//the longer the distance, the narrower the line.
				//this makes it look a bit like brush strokes
				float thickness = ofMap(distance, 0, 60, 20, 2, true);
				
				//calculate the points to the left and to the right
				//by extending the current point in the direction of left/right by the length
				ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
				ofVec3f rightPoint = thisPoint+toTheRight*thickness;
				
				//add these points to the triangle strip
				mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
				mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
				
			}
			
			//end the shape
			mesh.draw();
			ofLogVerbose() << s.point[0];
//			ofCircle(s.point[0],10);
		}
	}
//	tuioClient.drawCursors();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}