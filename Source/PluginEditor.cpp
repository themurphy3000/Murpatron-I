/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MurpatroniAudioProcessorEditor::MurpatroniAudioProcessorEditor(MurpatroniAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	setSize(200, 200);

	cvGakken.setName("cv-gakken");
	cvGakken.setButtonText("Gakken");
	cvGakken.setRadioGroupId(groupCvMode);
	cvGakken.setToggleState(true, NotificationType::dontSendNotification);

	cvNormal.setName("cv-normal");
	cvNormal.setButtonText("Normal");
	cvNormal.setRadioGroupId(groupCvMode);

	addAndMakeVisible(&cvGakken);
	addAndMakeVisible(&cvNormal);
	cvGakken.onClick = [this] {updateCVMode(&cvGakken); };
	cvNormal.onClick = [this] {updateCVMode(&cvNormal); };

	startTimer(40);
}

MurpatroniAudioProcessorEditor::~MurpatroniAudioProcessorEditor()
{
}

//==============================================================================
void MurpatroniAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setColour(Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("CV Mode", 0, 0, getWidth(), 30, Justification::centred, 1);

	if (processor.notes)
	{
		g.fillEllipse(cvGakken.getWidth(), 10, 13.0, 13.0);
	}
	else
	{
		g.drawEllipse(cvGakken.getWidth(), 10, 13.0, 13.0, 1.0);
	}
}

void MurpatroniAudioProcessorEditor::resized()
{
	cvGakken.setBounds(40, 30, getWidth() - 30, 20);
	cvNormal.setBounds(40, cvGakken.getBottom() + 5, getWidth() - 30, 20);
}

void MurpatroniAudioProcessorEditor::timerCallback()
{
	repaint();
}

void MurpatroniAudioProcessorEditor::updateCVMode(Button * button)
{
	auto state = button->getToggleState();
	if (state && button->getName() == "cv-gakken")
	{
		processor.SetMidiNoteProcessor(MurpatroniAudioProcessor::Gakken);
	}
	if (state && button->getName() == "cv-normal")
	{
		processor.SetMidiNoteProcessor(MurpatroniAudioProcessor::Normal);
	}
}
