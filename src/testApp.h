#pragma once

#include "ofMain.h"
#include "wiringPi.h"
// gpio-stuff from here: http://openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Using-the-GPIO-pins-with-Wiring-Pi-and-openFrameworks.html
// pin-belegung: http://wiringpi.com/pins/

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		unsigned char * 	videoGray;
		ofTexture			invTexture;
		int 				camWidth;
		int 				camHeight;
		
		
		// gpio-stuff
		bool thedoor;
		
		// font stuff
		// ofTrueTypeFont	helli; // helvetica light...
		
		// image
		ofImage titleimg;
		int 	titlealpha;
};
