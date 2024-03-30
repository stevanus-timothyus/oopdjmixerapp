/*
  ==============================================================================

    DeckGUI.cpp
    Created: 9 Mar 2022 4:58:20pm
    Author:  User

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse
) : player(_player),
waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Make components visible
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(restartButton);
    addAndMakeVisible(loadButton);
    getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colour::fromRGB(43, 76, 125));
    getLookAndFeel().setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(98, 147, 220));

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(posLabel);

    addAndMakeVisible(waveformDisplay);

    // Add listeners to components that involves user interactions
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    restartButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    // Configure sliders and labels
        //Volume
    volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volSlider.setRange(0.0, 1.0);
    volSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    volSlider.setValue(0.5);
    volSlider.setSkewFactorFromMidPoint(0.5);
    volLabel.setText("Volume", juce::dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);
    volLabel.setJustificationType(juce::Justification::centredBottom);
        //Speed
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setRange(0.25, 4.0); //reaches breakpoint if sliderValue == 0
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    speedSlider.setValue(1.0);
    speedSlider.setSkewFactorFromMidPoint(1.0);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, false);
    speedLabel.setJustificationType(juce::Justification::centredBottom);
        //Position
    posSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50,20);
    posLabel.setText("Position", juce::dontSendNotification);
    posLabel.attachToComponent(&posSlider, false);
    posLabel.setJustificationType(juce::Justification::centredBottom);

    //Update 2 frames per second.
    startTimer(500);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
    g.fillAll(juce::Colour::fromRGB(30, 80, 156));
    g.setColour(juce::Colour::fromRGB(199, 171, 143));
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::aliceblue);
 
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth()/2, rowH);
    stopButton.setBounds(getWidth()/2, 0, getWidth()/2, rowH);
    restartButton.setBounds(0, rowH * 1, getWidth(), rowH);

    volSlider.setBounds(0, rowH * 2.5, getWidth()/3, rowH * 2);
    speedSlider.setBounds(getWidth()/3, rowH * 2.5, getWidth()/3, rowH * 2);
    posSlider.setBounds(2 * getWidth() / 3, rowH * 2.5, getWidth()/3, rowH * 2);

    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);

}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        DBG("Play button was clicked ");
        //player->setPosition(0);
        player->start();
    }
    if (button == &stopButton)
    {
        DBG("Stop button was clicked ");
        player->stop();

    }
    if (button == &restartButton)
    {
        player->stop();
        posSlider.setValue(0.0);
        player->start();
    }
    if (button == &loadButton)
    {
        DBG("Load button was clicked ");
        juce::FileChooser chooser{ "Select a file..." };
        if (chooser.browseForFileToOpen())
        {
            loadFile(juce::URL{ chooser.getResult() });

        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    DBG("DeckGUI::isInterestedInFileDrag");
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    DBG("DeckGUI::filesDropped");
    if (files.size() == 1)
    {
        loadFile(juce::URL{ juce::File{files[0]} });
        return;
    }
}

/** Load song for audio player &  for waveform display*/
void DeckGUI::loadFile(juce::URL audioURL)
{
    DBG("DeckGUI::loadFile called");
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}



void DeckGUI::timerCallback()
{
    //DBG("DeckGUI::timerCallback");
    waveformDisplay.setPositionRelative(
        player->getPositionRelative());
    if (player->getPositionRelative() >= 0.0 && player->getPositionRelative() <= 1.0)
    {
        posSlider.setValue(player->getPositionRelative());
    }
}
