#pragma once

#include "ofxOsc.h"

typedef function<void(int n)> tidalCb;

class ofxTidal {
	public:
		void setup(int inPort=57120, int outPort=57121,
		           string outHost="127.0.0.1");
		void update();
		void addCallback(string synth, tidalCb cb);

	private:
		ofxOscReceiver oscReceiver;
		ofxOscSender oscSender;
		static unordered_map<string, tidalCb> callbacks;
};
