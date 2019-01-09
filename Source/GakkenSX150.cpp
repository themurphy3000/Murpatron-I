#include "GakkenSX150.h"


const int GakkenSX150::noteValues[] = {
	   116, 119, 121, 124, 126, 128, 131, 133, 136, 138, 141, 143,
	   146, 148, 151, 153, 156, 158, 161, 163, 166, 168, 170, 173,
	   175, 178, 180, 183, 185, 188, 190, 193, 195, 198, 200, 203,
	   205, 208, 210, 213, 215, 218, 220, 223, 225, 228, 231, 233,
	   235, 238, 240, 242, 245, 248, 250, 253, 255
};

GakkenSX150::GakkenSX150(K8055& k) : MidiToCV(k)
{

}

int GakkenSX150::getPitchCV(MidiMessage & midiMessage)
{
	int note = midiMessage.getNoteNumber() - midiOrigin;
	return noteValues[note];
}
