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
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	gakken = new GakkenSX150(k8055);
	midiToCV = new MidiToCV(k8055);
	notes = 0;
	midiNoteProcessor = gakken;
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

#ifndef JucePlugin_PreferredChannelConfigurations
bool MurpatroniAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void MurpatroniAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;

	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		if (m.isNoteOn())
		{
			notes++;
			uint8 newVelocity = (uint8)noteOnVelocity;
			m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVelocity);
			midiNoteProcessor->NoteOn(m);
		}
		if (m.isNoteOff())
		{
			notes--;
			midiNoteProcessor->NoteOff(m);
		}
		processedMidi.addEvent(m, time);
	}
	midiMessages.swapWith(processedMidi);

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
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
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new MurpatroniAudioProcessor();
}
