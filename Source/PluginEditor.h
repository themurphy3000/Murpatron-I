/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MurpatroniAudioProcessorEditor : public AudioProcessorEditor,
	private Timer
{
public:
	MurpatroniAudioProcessorEditor(MurpatroniAudioProcessor&);
	~MurpatroniAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:
	const int groupCvMode = 1;
	void timerCallback() override;

	MurpatroniAudioProcessor& processor;

	ToggleButton cvGakken;
	ToggleButton cvNormal;

	void updateCVMode(Button* button);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MurpatroniAudioProcessorEditor)
};
