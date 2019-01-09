#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MidiNoteProcessor
{
public:
	virtual void NoteOn(MidiMessage &midiMessage) = 0;
	virtual void NoteOff(MidiMessage &midiMessage) = 0;
	virtual void AllNotesOff() = 0;
};