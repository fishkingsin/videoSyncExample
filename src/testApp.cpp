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
				
				float position =  ofToFloat(msg);
				if(position>0)
				{
					float curPosition = player.getPosition();
					float dif = curPosition-position;
					ofLogVerbose() << position;
					if( dif > 0.01 )
					{
						speed=1-dif*0.01;
						
						
					}
					else if (dif < -0.01)
					{
						speed=1-dif*0.01;
						
					}
					else{
						speed=1;
					}
					float diff = ofGetElapsedTimeMillis() - currentTime;
					if(diff>3000)
					{
						//					ofLogVerbose("speed") <<speed;
						
						if(abs(dif)>0.001 && position>0)
						{
							//						int frame = position*player.getTotalNumFrames();
							player.setPosition(position);
							speed=1;
							//						player.setSpeed(speed);
							ofLogVerbose() << "Set Frame";
						}
						//					else if(abs(dif)>0.005 ){
						//						player.setSpeed(speed);
						//												ofLogVerbose() << "Set Speed : " <<speed;
						//					}
						//					else if(abs(dif)<0.005){
						//						player.setSpeed(1);
						//						ofLogVerbose() << "Set Speed : " <<1	;
						//					}
						currentTime = ofGetElapsedTimeMillis();
						
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
			z
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