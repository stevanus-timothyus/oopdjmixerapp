/*
  ==============================================================================

    Tracks.h
    Created: 27 Mar 2022 8:43:22pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

class Tracks
{
    public:
        Tracks(juce::File _file);
        juce::File file;
        juce::URL URL;
        juce::String title;
        juce::String length;

        /**Compare objects title for searching*/
        bool operator==(const juce::String& other) const;


};
