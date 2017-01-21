#pragma once

#include "ofxOsc.h"

#define PORT 57120

class ofxTidal {
	public:
		void setup();
		void update();

	private:
		ofxOscReceiver receiver;
};
