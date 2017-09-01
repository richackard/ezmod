/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, private ButtonListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
	Label label;
	TextBox textBox;
	TextButton textButton;
	TooltipWindow tooltipWindow;

	void buttonClicked(Button *button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
