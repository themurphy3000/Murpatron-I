#include "MidiToCV.h"

MidiToCV::MidiToCV(K8055 &k) : k8055(k)
{
	midiOrigin = 36;
	lastNote = 0;
	notes = 0;
	cvPitch = 0;
	modulation = 0.0;
	maxValue = 255;
	maxVolts = 5;
	pitchMultiplier = maxValue / maxVolts / 12;
}

void MidiToCV::NoteOn(MidiMessage & midiMessage)
{
	auto noteNumber = midiMessage.getNoteNumber();
	if (noteNumber >= midiOrigin)
	{
		cvPitch = getPitchCV(midiMessage);
		k8055.OutputAnalog(1, cvPitch);
		notes++;
		lastNote = noteNumber;
	}
}

void MidiToCV::NoteOff(MidiMessage & midiMessage)
{
	notes > 0 ? notes-- : notes;
	if (notes == 0)
	{
		k8055.OutputAnalog(1, 0);
		lastNote = 0;
	}
}

void MidiToCV::AllNotesOff()
{
	notes = 0;
	k8055.OutputAnalog(1, 0);
}

int MidiToCV::getPitchCV(MidiMessage & midiMessage)
{
	auto noteNumber = midiMessage.getNoteNumber();
	return (noteNumber - midiOrigin + 1) * pitchMultiplier;
}
