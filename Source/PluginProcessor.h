/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiToCV.h"
#include "GakkenSX150.h"

//==============================================================================
/**
*/
class MurpatroniAudioProcessor : public AudioProcessor
{
public:
	static const int Gakken = 1;
	static const int Normal = 2;
	float noteOnVelocity;
	bool noteOn;

	//==============================================================================
	MurpatroniAudioProcessor();
	~MurpatroniAudioProcessor();

	void SetMidiNoteProcessor(int id);
	void setHold(bool);
	bool getHold();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;
protected:
	MidiNoteProcessor* midiNoteProcessor;
	bool hold;
	void SetMidiNoteProcessor(MidiNoteProcessor& processor);
private:
	K8055 k8055;
	GakkenSX150* gakken;
	MidiToCV* midiToCV;
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MurpatroniAudioProcessor)
};
