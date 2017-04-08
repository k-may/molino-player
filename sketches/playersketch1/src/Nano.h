#pragma once


#include "ofMain.h"
#include "ofxMidi.h"

class Nano : public ofxMidiListener
{
public:

	void setup();
	void update();
	void draw();
	void exit();
	void newMidiMessage(ofxMidiMessage& eventArgs);

	stringstream text;
	string NoteOnOff;

	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;

	ofxMidiOut midiOut;
	int channel, note, velocity;

	//Midi Fighter Variables
	int mfSlider1, mfSlider2;
	int mfKnob1, mfKnob2;
	bool mfButton[16];
	bool mfToggle[4];

	/*Livid Variables*/

	//Knobs
	int knobs[8];

	//Sliders
	int sliders[8];

	//Middle Buttons
	bool buttonsSolo[8];
	bool buttonsMute[8];
	bool buttonsRec[8];

	bool buttonTrackLeft, buttonTrackRight;
	bool buttonCycle;
	bool buttonMarkerSet, buttonMarkerLeft, buttonMarkerRight;
	bool buttonRewind, buttonFastForward;
	bool buttonStop, buttonPlay, buttonRecord;

	ofEvent<void> onMarkerRight;
	ofEvent<void> onMarkerLeft;
	ofEvent<void> onRecord;

	int i;
};

