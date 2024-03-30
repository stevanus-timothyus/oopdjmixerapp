/*
  ==============================================================================

    PlaylistComponent.h
    Created: 9 Mar 2022 4:59:36pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include "Tracks.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
                      DeckGUI* _deckGUI2,
                      DJAudioPlayer* _playerForParsingMetaData
    );
    ~PlaylistComponent() override;

    int getNumRows() override;
    void paintRowBackground(juce::Graphics&,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected) override;
    void paintCell(juce::Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;
    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override;

    juce::Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

private:
    std::vector<Tracks> tracks;

    juce::TableListBox libraryTable;
    juce::TextEditor searchField;
    juce::TextButton importButton{ "IMPORT TRACKS" };
    juce::TextButton addToPlayer1Button{ "ADD TO DECK 1" };
    juce::TextButton addToPlayer2Button{ "ADD TO DECK 2" };

    juce::String getLength(juce::URL audioURL);
    juce::String secondsToMinutes(double seconds);

    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    DJAudioPlayer* playerForParsingMetaData;

    void importToLibrary();
    void searchLibrary(juce::String searchText);
    void saveLibrary();
    void loadLibrary();
    void deleteFromTracks(int id);
    bool isInTracks(juce::String fileNameWithoutExtension);
    int findTracksIndex(juce::String searchText);
    void loadInPlayer(DeckGUI* deckGUI);




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
