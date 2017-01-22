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

The setup method takes some optional parameters:

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


## Contributing guidelines

- [OpenFrameworks conding style](https://github.com/openframeworks/openFrameworks/wiki/oF-code-style)
  (TL;DR: tabs and camelCase)
- Keep it simple
- Please read [this](https://www.python.org/dev/peps/pep-0020/) a couple of times
