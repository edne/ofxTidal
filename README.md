# ofxTidal

OpenFramewoks backend for the [TidalCycles](https://tidalcycles.org/) language
for live coding patterns.


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


## Use as proxy

The setup method take some optional parameters:

```C++
void setup(int inPort=57120, int outPort=57121, string outHost="127.0.0.1");
```

In Supercollider:

```supercollider
include("SuperDirt")
SuperDirt.start(port: 57121)
```


## Current status

Very experimental, contributions are welcome.
