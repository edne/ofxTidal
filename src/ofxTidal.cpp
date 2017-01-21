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

//--------------------------------------------------------------
void ofxTidal::setup(){
    // TODO: int portIn, int portOut, bool proxy=false
	receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofxTidal::update(){
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        // log called synth
		if(validateMessage(m)){
			ofLog() << "synth: " << getFieldString(m, "s");
		}else{
			ofLog() << "Invalid message:";
			logMessage(m);
		}
	}
}

