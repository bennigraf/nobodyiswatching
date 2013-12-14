#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	
	// CAMERA STUFF
	// camWidth 		=   788;	// try to grab at this size. 
	// camHeight 		=   576;
	camWidth = 320;
	camHeight = 240;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted = new unsigned char[camWidth*camHeight*3];
	videoGray = new unsigned char[camWidth*camHeight];
	invTexture.allocate(camWidth,camHeight, GL_RGB);	
	ofSetVerticalSync(true);
	
	// GPIO...
	if(wiringPiSetup() == -1){
	    printf("Error on wiringPi setup");
	} else {
	    pinMode(7,INPUT);
		thedoor = false;
	}
	
		
	// FONTS
	// helli_big.loadFont("HelveticaNeueThin.ttf", 66, true, true);
	// helli_big.setLineHeight(18.0f);
	// helli_big.setLetterSpacing(1.037);
	
	titleimg.loadImage("title.png");
}


//--------------------------------------------------------------
void testApp::update(){
	
	// ofBackground(100,100,100);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()) {
		unsigned char * pixels = vidGrabber.getPixels();
		int counter = 0;
		// convert color image to rgb
		for (int i = 0; i < camHeight; i++) {
			for (int j = 0; j < camWidth*3; j+=3) {
				// get r, g and b components
				int r = (i*camWidth*3) + j;
				int g = (i*camWidth*3) + (j+1);
				int b = (i*camWidth*3) + (j+2);
				int grayPixel;
				if (j < camWidth*3/2) {
					grayPixel = (11 * pixels[r] + 16 * pixels[g] + 5 * pixels[b]) / 32;
				} else {
					grayPixel = (10 * pixels[r] + 12 * pixels[g] + 10 * pixels[b]) / 32;
					// grayPixel = (0 * pixels[r] + 32 * pixels[g] + 0 * pixels[b]) / 32;
				}
				videoGray[counter] = grayPixel;
				counter++;
			}
		}

		// grayTexture.loadData(videoGray, camWidth, camHeight, GL_LUMINANCE);
		
		// mirror grayscale image
		for (int i = 0; i < camHeight; i++) {
			for (int j = 0; j < camWidth; j++) {
				int pix1 = (i*camWidth) + j;
				int mir1 = (i*camWidth)+1 * (camWidth - j-1);
				videoInverted[pix1] = videoGray[mir1];
			}
		}
		invTexture.loadData(videoInverted, camWidth, camHeight, GL_LUMINANCE);
	}
	
	
	// gpio
	if(digitalRead(7)!=0){
	    thedoor = true;
	} else {
	    thedoor = false;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
		// vidGrabber.draw(0, 0); // original
	invTexture.draw(0, 0, 702, 576); // inverted, grayscale, fill the whole screen...
	
	
	// beautifulll
	// ofSetColor(0);
	// helli.drawString("JUST KIDDING", 30, 92);
	if(thedoor) {
		if(titlealpha < 255) {
			titlealpha += ofGetLastFrameTime() * 255 * 5;
		} else {
			titlealpha = 255;
		}
	} else {
		if(titlealpha > 0) {
			titlealpha -= ofGetLastFrameTime() * 255 * 5;
		} else {
			titlealpha = 0;
		}
	}
	
	if(titlealpha > 0) {
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, titlealpha);
		titleimg.draw(0, 0);
		ofDisableAlphaBlending();
	}
	
	
	
	// gpio...

	// ofSetColor(0);
	// if (thedoor == true){
	//     	ofDrawBitmapString("Door closed", 49, 79);
	//     } else {
	//     	ofDrawBitmapString("Door open", 49, 79);
	//     }
	// ofSetColor(190);
	// if (thedoor == true){
	//     	ofDrawBitmapString("Door closed", 50, 90);
	//     } else {
	//     	ofDrawBitmapString("Door open", 50, 90);
	//     }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
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
