#pragma once

#include "ofxOsc.h"

#define PORT 57120

class ofxTidal {
	public:
		void setup();
		void update();
		void addCallback(string synth, function<void(void)> cb);

	private:
		ofxOscReceiver oscReceiver;
		static unordered_map<string, function<void(void)>> callbacks;
};
