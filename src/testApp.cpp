#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	dir.allowExt("mov");
	dir.listDir("movies");
	
	ofBackground(127,127,127);
	currentVideoIdx = 0;
	
	ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
	if(dir.getFiles().size()>0)player.loadMovie(dir.getPath(currentVideoIdx),decodeMode);
	player.setSynchronousSeeking(true);
	player.play();
	player.setLoopState(OF_LOOP_NORMAL);
	
	tcp.setup("127.0.0.1",2838);
	tcp.setMessageDelimiter("\n");
	playerRect.set(0,0,1024, player.getHeight()*(1024/player.getWidth()));
	playerRect.y = (ofGetHeight()*0.5)-playerRect.height*0.5;
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	
	mesh.addVertex(ofVec2f(playerRect.x,playerRect.y));
	mesh.addTexCoord(ofVec2f(0,0));
	
	mesh.addVertex(ofVec2f(playerRect.x+playerRect.width,playerRect.y));
	mesh.addTexCoord(ofVec2f(player.getWidth(),0));
	
	mesh.addVertex(ofVec2f(playerRect.x+playerRect.width,playerRect.y+playerRect.height));
	mesh.addTexCoord(ofVec2f(player.getWidth(),player.getHeight()));
	
	mesh.addVertex(ofVec2f(playerRect.x+playerRect.width,playerRect.y+playerRect.height));
	mesh.addTexCoord(ofVec2f(player.getWidth(),player.getHeight()));
	
	mesh.addVertex(ofVec2f(playerRect.x,playerRect.y+playerRect.height));
	mesh.addTexCoord(ofVec2f(0,player.getHeight()));
	mesh.addVertex(ofVec2f(playerRect.x,playerRect.y));
	mesh.addTexCoord(ofVec2f(0,0));
	fbo.allocate(player.getWidth(),player.getHeight());
	//	player.setPaused(true);
	
}
void testApp::exit()
{
	tcp.close();
}
//--------------------------------------------------------------
void testApp::update(){

	if(tcp.isConnected())
	{
		string msg = tcp.receive();
		if(msg!=" OF")
		{
			if(player.isLoaded())
			{
				if(msg.find("video_")!=string::npos)
				{
					vector<string>sub = ofSplitString(msg.substr(6,string::npos),";");;
					ofLogVerbose()<< sub[0];
					int index = ofToInt(sub[0]);
					if(index >=0 && index<dir.getFiles().size())
					{
						player.stop();
						ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
						currentVideoIdx = index;
						player.loadMovie(dir.getPath(currentVideoIdx),decodeMode);
						player.setSynchronousSeeking(true);
						player.play();
						player.setLoopState(OF_LOOP_NORMAL);

					}
					
				}
				else if(msg.find("timecode_")!=string::npos)
				{

					vector<string>sub1 = ofSplitString(msg.substr(9,string::npos),";");;
					
					vector<string>sub2 = ofSplitString(sub1[0],"_");
//					ofLogVerbose()<<sub2[0];
					ofLogVerbose()<<sub2[1];
					float position =  ofToFloat(sub2[0]);
					unsigned long   timestamp =  strtoul(sub2[1].c_str(),NULL,10);
					unsigned long   mytimeStamp = ofGetSystemTime();
					unsigned long   diffTimeStamp = abs(long(mytimeStamp-timestamp));
					ofLogVerbose("mytimeStamp")<< ofToString(mytimeStamp);
					ofLogVerbose("timestamp")<< ofToString(timestamp);
					ofLogVerbose("diffTimeStamp")<< ofToString(diffTimeStamp);
					
					if(position>0)
					{
						float curPosition = player.getPosition();
						float dif = curPosition-position;
//						ofLogVerbose("position") << position;
//						ofLogVerbose("curPosition") << curPosition;
						
						float diff = ofGetElapsedTimeMillis() - currentTime;
						//if time difference larger than 1% wouls set the current position to target
						if(diff>1000)
						{
							
							if(abs(dif)>0.001 )
							{
								
								player.setPosition(position+(diffTimeStamp/1000000.0f));
//								player.setSpeed(1);
								ofLogVerbose() << "Set Frame";
							}
//							else
//							{
//								if(dif>0)
//								{
//									ofLogVerbose() << "Slower";
//
//									player.setSpeed(0.9);
//								}
//								else if(dif<0)
//								{
//									ofLogVerbose() << "Faster";
//									player.setSpeed(1.1);
//								}
//								else
//								{
//									player.setSpeed(1);
//								}
//							}
							currentTime = ofGetElapsedTimeMillis();
							
						}
					}
				}
			}
		}
		
	}
	if(player.isLoaded())player.update();
	if(player.getTexture())
	{
		fbo.begin();
		player.draw(0,0);
		
		
		fbo.end();
	}
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	
	
	fbo.draw(playerRect.x,playerRect.y,playerRect.width, playerRect.height);
	//	if(player.getTexture())
	//	{
	//		player.bind();
	//		mesh.drawFaces();
	//		player.unbind();
	//	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key)
	{
		case OF_KEY_BACKSPACE:
			speed = 1;
			player.setFrame(1);
			break;
		case OF_KEY_LEFT:
			
			break;
		case OF_KEY_RIGHT:
			break;
			
	}
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