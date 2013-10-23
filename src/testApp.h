#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSyphon.h"
//#include "AppCore.h"

class testApp : public ofBaseApp{
	
public:
    void setup();
    void update();
    void draw();
    //    void exit();

    // Camera
    ofVideoGrabber camera;
    int camWidth, camHeight;
    unsigned char *pixels;
    unsigned char tmpR;
    unsigned char tmpG;
    unsigned char tmpB;
    unsigned char tmpC;
    unsigned char *colorPixels;
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
    
    ofTexture tex;
    ofFbo texFbo;
    ofPixels pixelArray;
	ofxSyphonServer mainOutputSyphonServer;
	ofxSyphonServer individualTextureSyphonServer;
	
	ofxSyphonClient mClient;
};

#endif

