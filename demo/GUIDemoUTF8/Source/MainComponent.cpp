/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : label("select",L"选择文件夹："), textButton(L"选择")
{
    setSize (600, 400);

	setLookAndFeel(new EZLookAndFeel);

	addAndMakeVisible(label);
	addAndMakeVisible(textBox);
	addAndMakeVisible(textButton);

	Font font;
	font = textBox.getEditor()->getFont();
	font.setTypefaceName("STZhongsong");

	textBox.setJustificationType(Justification::centredLeft);
	textBox.getEditor()->setFont(font);

	label.setJustificationType(Justification::centredRight);
	label.setTooltip(L"请选择您想选择的文件夹");
	label.attachToComponent(&textBox, true);

	textButton.setTooltip(L"点击即可选择");
	textButton.addListener(this);

	textBox.setTopLeftPosition(100, 150);
	textBox.setSize(400, 28);
	
	textButton.setTopLeftPosition(520, 150);
	textButton.setSize(60, 28);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::buttonClicked(Button * button)
{
	if (button == &textButton)
	{
		FileChooser fileChooser(L"请选择文件夹", File::getCurrentWorkingDirectory(), "*");

		if (fileChooser.browseForDirectory())
		{
			textBox.getEditor()->setText(fileChooser.getResult().getFullPathName());
		}
	}
}
