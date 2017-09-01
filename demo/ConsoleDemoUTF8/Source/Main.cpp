/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
int main (int argc, char* argv[])
{

    // ..your code goes here!
	ConsoleOutputStream ezout;

	ezout.InitUTF8Console();
	ezout << L"你好，世界！" << newLine;
	ezout.printData();

	ezout.command("pause");

    return 0;
}
