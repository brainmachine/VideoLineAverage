#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Screen
    ofBackground(255);
    
    // Font
    font.loadFont("font/Courier New Bold.ttf", 9);
    
    // Misc
    verbose = true;
    
    // Pd
    int ticksPerBuffer = 8;
    ofSoundStreamSetup(2, 1, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
    core.setup(2, 1, 44100, ticksPerBuffer);
    
    // OSC
    sender.setup(HOST, PORT);
    
    
    // Camera
    camWidth = 640;
    camHeight = 480;
    lineCounter = 0;
    tmpR = 0;
    tmpG = 0;
    tmpB = 0;
    tmpC = 0;
    
    /*  vector<ofVideoDevice> devices = camera.listDevices();
     if(verbose) {
     for(int i = 0; i < devices.size(); i++){
     cout << devices[i].id << ": " << devices[i].deviceName;
     if( devices[i].bAvailable ){
     cout << endl;
     }else{
     cout << " - unavailable " << endl;
     }
     }
     }*/
	camera.setDeviceID(0);
	camera.setDesiredFrameRate(60);
    camera.setVerbose(true);
    camera.initGrabber(camWidth, camHeight);
    
    videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
    
    cout << " -- END OF SETUP -- " << endl;
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Camera
    camera.update();
    if (camera.isFrameNew()){
        
        pixels = camera.getPixels();
        int totalPixels = camWidth * camHeight;
        lineCounter = 0;
        int tmpR = 0;
        int tmpG = 0;
        int tmpB = 0;
        
        int tempCounter = 0;
        
        for (int i = 0; i < totalPixels; i++) {
            
          //  videoInverted[i] = 255 - pixels[i];
            
            // Adding Colors
            tmpR += pixels[i*3];
            tmpG += pixels[i*3+1];
            tmpB += pixels[i*3+2];
            //tmpC += pixels[i];
            tempCounter++;
            // Store Color
            if(i % camWidth == 0) {
                // Get the average value
                tmpR = tmpR/camWidth;
                tmpG = tmpG/camWidth;
                tmpB = tmpB/camWidth;
               
                // Set Avg Colours To Color Array
                lineColors[lineCounter].r = int(tmpR);
                lineColors[lineCounter].g = int(tmpG);
                lineColors[lineCounter].b = int(tmpB);
                
                
                // Reset Temp Colors
                tmpR = 0;
                tmpG = 0;
                tmpB = 0;
                
                // Iterate
                lineCounter++;
                
            }
        }
        
        // Pack everything in an OSC message
        
        ofxOscMessage message;
        message.setAddress("/colorArray");
        for (int i = 0; i < 10; i++) {
            
            //message.addInt64Arg(lineColors[i].r);
            message.addIntArg(lineColors[i].r);
            
        }
        sender.sendMessage(message);
        
       // message.clear();
        
        
       // videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // Raw Camera
    ofSetColor(255);
    camera.draw(50, 50, camWidth, camHeight);
    //videoTexture.draw(50 ,camHeight + 50, camWidth, camHeight);
    
    // Lines
    for (int i = 0; i < camHeight; i++) {
        ofSetColor(lineColors[i]);
        //cout << lineColors[i] << endl;
        ofLine(camWidth + 100, 50 + i, camWidth*2 + 100, 50 + i);
    }
    
    
    
    
    // Debug
    ofSetColor(0);
    char fpsStr[255];
    sprintf(fpsStr, "frame rate: %f", ofGetFrameRate());
    ofDrawBitmapString(fpsStr, 50, 700);
    
}

//--------------------------------------------------------------
void testApp::exit() {
    ofLogNotice("Exiting App");
    
    // Close Pd
	core.exit();
    
    // Close Camera
    camera.close();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    // Camera Settings
    if (key == 's' || key == 'S'){
		camera.videoSettings();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
//    ofxOscMessage message;
//    message.setAddress("/colorArray");
//    message.addIntArg(x);
//	message.addIntArg(y);
//	sender.sendMessage(message);
    
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
