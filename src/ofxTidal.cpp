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

string getFieldString(ofxOscMessage m, string fieldName){
	// Message scructure: fieldName, value, fieldName, value, ...
	// where field names are strings
	int n = m.getNumArgs();
	for(int i=0; i<n; i++){
		if(m.getArgTypeName(i) == "s" && m.getArgAsString(i) == fieldName){
			int fieldIndex = i+1;
			if(fieldIndex < n && m.getArgTypeName(fieldIndex) == "s"){
				return m.getArgAsString(fieldIndex);
			}
		}
	}
	// TODO: throw exception
	return "";
}

unordered_map<string, function<void(void)>> ofxTidal::callbacks;

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
			if(callbacks.find(synth) != callbacks.end()){
				// TODO: arguments
				callbacks[synth]();
			}
		}else{
			ofLog() << "Invalid message:";
			logMessage(m);
			// TODO: throw exception, maybe
		}
	}
}

//--------------------------------------------------------------
void ofxTidal::addCallback(string synth, function<void(void)> cb){
	callbacks[synth] = cb;
}
