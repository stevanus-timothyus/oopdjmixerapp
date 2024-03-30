/*
  ==============================================================================

    Tracks.cpp
    Created: 27 Mar 2022 8:43:22pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Tracks.h"
#include <filesystem>

//==============================================================================
Tracks::Tracks(juce::File _file) : file(_file),
                                   title(_file.getFileNameWithoutExtension()),
                                   URL(juce::URL{ _file })
{
    DBG("Track Added: " << title);
}

bool Tracks::operator==(const juce::String& other) const
{
    return title == other;
}

