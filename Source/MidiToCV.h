#pragma once

#include "MidiProcessor.h"
#include "K8055.h"

class MidiToCV : public MidiNoteProcessor
{
public:
	MidiToCV(K8055&);

	void NoteOn(MidiMessage &midiMessage) override;
	void NoteOff(MidiMessage &midiMessage) override;
	void AllNotesOff() override;

	virtual int getPitchCV(MidiMessage &midiMessage);

protected:
	K8055& k8055;
	int midiOrigin;
	int lastNote;
	int notes;
	int cvPitch;
	float modulation;
	int maxValue;
	int maxVolts;
	int pitchMultiplier;
};