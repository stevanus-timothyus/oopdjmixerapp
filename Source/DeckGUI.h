/*
  ==============================================================================

    DeckGUI.h
    Created: 9 Mar 2022 4:58:20pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::FileDragAndDropTarget,
    public juce::Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
        juce::AudioFormatManager& formatManagerToUse,
        juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI();

    void paint(juce::Graphics&) override;
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked(juce::Button*) override;

    /** implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    /** Detect when a file is being dragged around the DeckGUI */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;

    /** Detect when the file is dropped onto the DeckGUI */
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /** Listen to changes*/
    void timerCallback() override;

    void loadFile(juce::URL audioURL);
private:

    juce::TextButton playButton{ "PLAY" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton restartButton{ "RESTART" };
    juce::TextButton loadButton{ "LOAD" };

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    juce::Label volLabel;
    juce::Label speedLabel;
    juce::Label posLabel;

    

    WaveformDisplay waveformDisplay;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
