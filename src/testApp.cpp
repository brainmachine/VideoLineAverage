#include "testApp.h"


const int width = 800;
const int height = 600;

//--------------------------------------------------------------
void testApp::setup(){
    
	ofSetWindowTitle("beeeeeeeer");
    // Screen
    ofBackground(255);
    
    // Font
    font.loadFont("font/Courier New Bold.ttf", 9);
    
    // Misc
    verbose = true;
    
    // Camera
    camWidth = 640;
    camHeight = 480;
    lineCounter = 0;
    tmpR = 0;
    tmpG = 0;
    tmpB = 0;
    tmpC = 0;
    
	camera.setDeviceID(0);
	camera.setDesiredFrameRate(60);
    camera.setVerbose(true);
    camera.initGrabber(camWidth, camHeight);
    
    videoInverted 	= new unsigned char[camWidth*camHeight*3];
    
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
    
    //Interesting stuff
    
    shadow = 255;
    highlight = 0; // This is !wrong
    
    // Syphon stuff
    
	mainOutputSyphonServer.setName("Screen Output");
	individualTextureSyphonServer.setName("Texture Output");
    
	mClient.setup();
    
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
	
    tex.allocate(640, 480, GL_RGBA);
    pixelArray.allocate(640, 480, OF_PIXELS_RGBA);
    texFbo.allocate(640, 480, GL_RGBA);
    texFbo.begin();
    ofClear(255,255,255,0); // -> is this right?
    texFbo.end();
    
    cout << " -- END OF SETUP -- " << endl;
	pixels = new unsigned char[640*480*4];
    colorPixels = new unsigned char[640*480*4];
}

void testApp::update() {
    //--------------------------------------------------------------
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
        
        //Reset highlight and shadow before checking each frame:
        shadow = 255;
        highlight = 0;
        
        // Go through all the pixels in a single frame
        for (int i = 0; i < totalPixels; i++) {
            // Adding Colors
            tmpR += pixels[i*3];
            tmpG += pixels[i*3+1];
            tmpB += pixels[i*3+2];
            //tmpC += pixels[i];
            tempCounter++;
        
            // Store Color for each line
            if(i % camWidth == 0) {
                // Get the average value
                tmpR = tmpR/camWidth;
                tmpG = tmpG/camWidth;
                tmpB = tmpB/camWidth;
                
                // Write Avg Colours To Color Array
                lineColors[lineCounter].r = int(tmpR);
                lineColors[lineCounter].g = int(tmpG);
                lineColors[lineCounter].b = int(tmpB);
                
                colorPixels[i*3] = lineColors[lineCounter].r;
                colorPixels[i*3+1] = lineColors[lineCounter].g;
                colorPixels[i*3+2] = lineColors[lineCounter].g;
                
                // Determine brightness
                int lineBrightness = (int(tmpR)+int(tmpG)+int(tmpB))/3;
                
                //Find highest value
                if (lineBrightness > highlight) {
                    highlight = lineBrightness;
                }
                
                //Find lowest value
                if (lineBrightness < shadow) {
                    shadow = lineBrightness;
                }
                
                // Reset Temp Colors
                tmpR = 0;
                tmpG = 0;
                tmpB = 0;
                
                // Iterate
                lineCounter++;
            } //end of if
            
        } //end of for loop
        
        texFbo.begin();
        ofClear(128, 128, 128, 255); // --->>> CALIBRATE
        // Lines
        for (int i = 0; i < camHeight; i++) {
            ofSetColor(lineColors[i]);
            //cout << lineColors[i] << endl;
            ofLine(0, i, camWidth, i);
        }
        texFbo.end();

        texFbo.readToPixels(pixelArray);
        colorPixels =  pixelArray.getPixels();
        tex.loadData(colorPixels, 640, 480, GL_RGBA);
    } //end of if camera new
    
} //end of update


//--------------------------------------------------------------
void testApp::draw(){
    
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Raw Camera
    ofSetColor(255);
     camera.draw(camWidth+50, 50, camWidth, camHeight);
    
    //ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    
    //texFbo.draw(0,0);
    tex.draw(50, 50);
    // Syphon Stuff
    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();
    individualTextureSyphonServer.publishTexture(&tex);

    // Debug
    ofSetColor(0);
    char fpsStr[255];
    sprintf(fpsStr, "frame rate: %f", ofGetFrameRate());
    ofDrawBitmapString(fpsStr, 50, 700);
    
}



