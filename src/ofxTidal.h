#pragma once

#include "ofxOsc.h"

class ofxTidal {
	public:
		void setup(int inHost=57120, int outPort=57121,
		           string outHost="127.0.0.1");
		void update();
		void addCallback(string synth, function<void(void)> cb);

	private:
		ofxOscReceiver oscReceiver;
		ofxOscSender oscSender;
		static unordered_map<string, function<void(void)>> callbacks;
};
