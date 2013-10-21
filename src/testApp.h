#pragma once

#include "ofMain.h"
#include "AppCore.h"
#include "ofxOsc.h"
#include "ofxSyphonClient.h"
#import <Syphon/Syphon.h>
#import "SyphonNameboundClient.h"

#define HOST "localhost"
#define PORT 12345

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // Pd
    AppCore core;
    
    //OSC
    ofxOscSender sender;
    
    // Camera
    ofVideoGrabber  camera;
    int camWidth, camHeight;
    unsigned char *pixels;
    unsigned char tmpR;
    unsigned char tmpG;
    unsigned char tmpB;
    unsigned char tmpC;
    int lineCounter;
    ofColor lineColors[480];
    ofColor tempColor;
    
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    
    // Font
    ofTrueTypeFont font;
    
    // Misc
    Boolean verbose;
    
    // Interesting stuff
    int shadow; //doesn't work yet
    int highlight; //works
    
    // Syphon
    ofTexture tex; //tex to send
    
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
	
	ofxSyphonClient mClient;
    
    
    
};
