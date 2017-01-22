# ofxTidal

OpenFramewoks backend for the [TidalCycles](https://tidalcycles.org/) language
for live coding patterns.


## Current status

Very experimental, contributions are welcome.



## Example

```C++
void ofApp::setup(){
	tidalProxy.setup();

	tidalProxy.addCallback("bd", [](){
		ofBackground(0, 0, 0);
	});
	tidalProxy.addCallback("sn", [](){
		ofBackground(255, 255, 255);
	});
}

void ofApp::update(){
	tidalProxy.update();
}

```
