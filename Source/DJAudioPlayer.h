/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 9 Mar 2022 5:01:07pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class DJAudioPlayer  : public juce::AudioSource
{
public:
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);


    void start();
    void stop();

    /** get the relative position of the playhead */
    double getPositionRelative();
    /**Gets the length of transport source in seconds*/
    double getLengthInSeconds();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

    //do i need this?
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DJAudioPlayer)
};
