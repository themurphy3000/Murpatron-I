/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MurpatroniAudioProcessor::MurpatroniAudioProcessor()
	: AudioProcessor(BusesProperties()
		.withInput("Input", AudioChannelSet::stereo())
		.withOutput("Output", AudioChannelSet::stereo())
		.withInput("Sidechain", AudioChannelSet::stereo())
	)
{
	gakken = new GakkenSX150(k8055);
	midiToCV = new MidiToCV(k8055);
	noteOn = false;
	midiNoteProcessor = gakken;
	hold = false;
}

MurpatroniAudioProcessor::~MurpatroniAudioProcessor()
{
}

void MurpatroniAudioProcessor::SetMidiNoteProcessor(int id)
{
	if (id == Gakken)
	{
		SetMidiNoteProcessor(*gakken);
	}
	if (id == Normal)
	{
		SetMidiNoteProcessor(*midiToCV);
	}
}

void MurpatroniAudioProcessor::setHold(bool h)
{
	hold = h;
	if (!hold) {
		noteOn = false;
		midiNoteProcessor->AllNotesOff();
	}
}

bool MurpatroniAudioProcessor::getHold()
{
	return hold;
}

//==============================================================================
const String MurpatroniAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool MurpatroniAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool MurpatroniAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool MurpatroniAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double MurpatroniAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int MurpatroniAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int MurpatroniAudioProcessor::getCurrentProgram()
{
	return 0;
}

void MurpatroniAudioProcessor::setCurrentProgram(int index)
{
}

const String MurpatroniAudioProcessor::getProgramName(int index)
{
	return {};
}

void MurpatroniAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void MurpatroniAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	//gakken.OpenDevice(0);
}

void MurpatroniAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

bool MurpatroniAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
	return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet()
		&& !layouts.getMainInputChannelSet().isDisabled();
}

void MurpatroniAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	auto mainInputOutput = getBusBuffer(buffer, true, 0);
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	auto sideChainInput = getBusBuffer(buffer, true, 1);

	int time;
	MidiMessage m;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		if (m.isNoteOn())
		{
			noteOn = true;;
			midiNoteProcessor->NoteOn(m);
		}

		if (m.isNoteOff())
		{
			noteOn = false;
			if (!hold)
			{
				midiNoteProcessor->NoteOff(m);
			}
		}
	}

	auto sample = sideChainInput.getMagnitude(0, buffer.getNumSamples());
	auto level = 1.0f - 255.0f / (255.0f + sample);
	auto cv = 117 + (sample * 255);
	k8055.OutputAnalog(1, (int)cv);

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		mainInputOutput.clear(i, 0, buffer.getNumSamples());
}

//==============================================================================
bool MurpatroniAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MurpatroniAudioProcessor::createEditor()
{
	return new MurpatroniAudioProcessorEditor(*this);
}

//==============================================================================
void MurpatroniAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void MurpatroniAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

void MurpatroniAudioProcessor::SetMidiNoteProcessor(MidiNoteProcessor& processor)
{
	if (midiNoteProcessor) midiNoteProcessor->AllNotesOff();
	midiNoteProcessor = &processor;
	noteOn = false;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new MurpatroniAudioProcessor();
}
