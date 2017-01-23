#include "ofxTidal.h"

void logMessage(ofxOscMessage m){
	ofLog() << "Addr: "<< m.getAddress();
	for(int i=0; i<m.getNumArgs(); i++){
		if(m.getArgTypeName(i) == "s"){
			ofLog() << "string: " << m.getArgAsString(i);
		}else if(m.getArgTypeName(i) == "f"){
			ofLog() << "float: " << m.getArgAsFloat(i);
		}else if(m.getArgTypeName(i) == "i"){
			ofLog() << "int: " << m.getArgAsInt(i);
		}else{
			ofLog() << m.getArgTypeName(i);
		}
	}
	ofLog();
}

bool validateMessage(ofxOscMessage m){
	// Check if even arguments are valid field names
	for(int i=0; i<m.getNumArgs(); i+=2){
		if(m.getArgTypeName(i) != "s"){
			return false;
		}
	}
	return true;
}

// Message scructure:
//     fieldName, value, fieldName, value, ...
// where field names are strings

string getFieldString(ofxOscMessage m, string fieldName){
	int n = m.getNumArgs();
	for(int i=0; i<n; i++){
		if(m.getArgTypeName(i) == "s" && m.getArgAsString(i) == fieldName){
			int fieldIndex = i+1;
			if(fieldIndex < n && m.getArgTypeName(fieldIndex) == "s"){
				return m.getArgAsString(fieldIndex);
			}
		}
	}
	return "";  // keep "" as default?
}

int getFieldInt(ofxOscMessage m, string fieldName){
	int n = m.getNumArgs();
	for(int i=0; i<n; i++){
		if(m.getArgTypeName(i) == "s" && m.getArgAsString(i) == fieldName){
			int fieldIndex = i+1;
			if(fieldIndex < n && m.getArgTypeName(fieldIndex) == "i"){
				return m.getArgAsInt(fieldIndex);
			}
		}
	}
	return 0;  // default value
}

unordered_map<string, tidalCb> ofxTidal::callbacks;

//--------------------------------------------------------------
void ofxTidal::setup(int inPort, int outPort, string outHost){
	oscReceiver.setup(inPort);
	oscSender.setup(outHost, outPort);
}

//--------------------------------------------------------------
void ofxTidal::update(){
	// check for waiting messages
	while(oscReceiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(m);
		oscSender.sendMessage(m, false);

		if(validateMessage(m)){
			string synth = getFieldString(m, "s");
            int n = getFieldInt(m, "n");

			if(callbacks.find(synth) != callbacks.end()){
				// TODO: effects argument
				callbacks[synth](n);
			}
			logMessage(m);
		}else{
			ofLog() << "Invalid message:";
			logMessage(m);
			// TODO: throw exception, maybe
		}
	}
}

//--------------------------------------------------------------
void ofxTidal::addCallback(string synth, tidalCb cb){
	callbacks[synth] = cb;
}
