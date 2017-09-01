#pragma once
#define EZ_TEXTEDITOREX_H_INCLUDED

using namespace juce;

class TextEditorEx : public TextEditor
{
public:
	TextEditorEx(Component *comp, const String &componentName = String(), juce_wchar passwordCharacter = 0)
		: TextEditor(componentName, passwordCharacter)
	{
		useWordWrap = true;
		component = comp;
	}
	~TextEditorEx()
	{

	}

	//==============================================================================
	/** Puts the editor into either multi- or single-line mode.

	    By default, the editor will be in single-line mode, so use this if you need a multi-line
	    editor.

	    See also the setReturnKeyStartsNewLine() method, which will also need to be turned
	    on if you want a multi-line editor with line-breaks.

	    @see isWordWrap, TextEditor::isMultiLine, TextEditor::setReturnKeyStartsNewLine
	*/
	void setMultiLine(bool shouldBeMultiLine, bool shouldWordWrap = true)
	{
		useWordWrap = shouldWordWrap;

		TextEditor::setMultiLine(shouldBeMultiLine, shouldWordWrap);
	}

	/** Sets the entire content of the editor.

	    This will clear the editor and insert the given text (using the current text colour
	    and font). You can set the current text colour using
	    @code setColour (TextEditor::textColourId, ...);
	    @endcode

	    @param newText                  the text to add
	    @param sendTextChangeMessage    if true, this will cause a change message to
	                                    be sent to all the listeners.
	    @see TextEditor::insertTextAtCaret
	*/
	void setText(const String &newText, bool sendTextChangeMessage = true)
	{
		component->repaint();

		TextEditor::setText(newText, sendTextChangeMessage);
	}

	bool isWordWrap() const
	{
		return useWordWrap;
	}

private:
	bool useWordWrap;
	Component *component;
};
