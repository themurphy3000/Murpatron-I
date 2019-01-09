#pragma once

#include "MidiProcessor.h"
#include "K8055.h"
#include "MidiToCV.h"

class GakkenSX150 : public MidiToCV
{
public:
	const static int noteValues[];

	GakkenSX150(K8055&);

	int getPitchCV(MidiMessage & midiMessage) override;
};
