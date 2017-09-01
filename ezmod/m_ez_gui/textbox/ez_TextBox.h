#pragma once
#define EZ_TEXTBOX_H_INCLUDED

#include "ez_TextEditorEx.h"

#define INIT_MARGIN  2.0f
#define INIT_PADDING 2.0f

using namespace juce;

//==============================================================================
/**

    @brief A read-only text box with settable custom border.
	       一个可设置自定义边框的只读文本框。

	A TextBox can either be in copiable or non-copiable mode, and can be using
	or not using ellipses when the contents are out of bounds.

	In copiable mode, you still cannot copy the contents directly after the
	TextBox is added, but after you double clicked on the TextBox, and a read-only
	TextEditor appears, you than can copy the contents through the TextEditor. 
	Maybe we will improve this in the future version.

	When you click on somewhere else other than the TextEditor after a TextEditor 
	appears in copiable mode, the TextEditor will be hidden and this component
	will switch to a static text box again.

	Because TextBox shared a lot of common behaviors with TextEditor, we decided 
	not to write the entire component, but to integrate a extented TextEditor 
	(the TextEditorEx class) inside it. So to reduce coupling, the TextBox do not
	provide any methods that the TextEditor already have, instead you can call 
	the TextEditor's methods like "setText", "setFont", "setMultiLine"... after
	calling "getEditor()" method and get the pointer of the TextEditorEx inside 
	the TextBox. Lot's of those method will affect not only the inside TextEditorEx 
	component, but also the TextBox itself! 

	Note that this is just a preliminary version, we might change the mechanism in 
	the future updates.

	一个文半框可以处于“可复制”或“不可复制”模式，您也可以在文本超出文本框范围时
	选择使用或不使用结尾的省略号。

	在“可复制”模式中，您依然不能在文本框创建之后直接地拷贝它的内容，但是您可以在
	双击文本框后，在弹出的只读输入框中复制它的内容。或许我们会在后续的版本中改进这
	个功能。

	当您在输入框弹出后的可复制模式中，点击了输入框以外的其他地方，输入框会被隐藏，
	而组件会重新切换回静态的文本框。

	因为TextBox和TextEditor有大量相似的行为，因此我们决定在组件内整合一个扩展的
	TextEditor类（TextEditorEx类），而不是自己从无到有地写一个完整的组件。于是为了
	降低耦合性，TextBox类将不会提供任何TextEditor类中已有的方法。取而代之的是，您
	可以在调用"getEditor()"方法获得组件内TextEditorEx对象的指针后，通过调用TextEditor
	内的方法，如："setText"，"setFont"，"setMultiLine"等等……来同时对输入框和文本
	框本身的表现产生影响。

	注意，现在只是一个初步的版本，我们可能会在后续的更新中改变它的机制。

*/
class TextBox : public SettableTooltipClient, public Component
{
public:
	//==============================================================================
	/** @brief Creates a new, empty text box.
	           创建一个新的空白文本框。

		Except for the parameters in the constructor, we also set the following
		initial parameter value: set margin and padding to 2.0f, set text colour to
		be the same as the TextEditor, set the TextBox's border to none.

		除了构造函数中指定的参数之外，我们还设置了以下初始参数值：设置了初始外边距和
		内边距为2.0f，设置了初始文本颜色为使用输入框的文本颜色，设置了文本框的边框为
		无。

		@param componentName     The name to pass to the component for it to use as its
		                         name.
							     为组件设置的组件名。

		@param shouldCanCopy     Should the TextBox be in copiable mode or non-copiable
		                         mode? Set to true to make it copiable, false to make it
							     non-copiable. The default value is true.
							     该文本框应该是可拷贝的还是不可拷贝的？设为true代表可拷
							     贝，设为false代表不可拷贝。默认值是true。

		@param shouldUseEllipses Should the TextBox use ellipses when the contents are
		                         out of bounds? True to use ellipses, false to not use
								 ellipses. The default value is true.
								 该文本框是否应在文本超出文本框范围时显示结尾的省略号？
								 设为true代表使用结尾省略号，设为false代表不使用省略号。
								 默认值是true。

		@param justificationType The justification type used in single-line mode, and
		                         in multi-line, but non-wordwrap mode. JUCE's TextEditor
								 class does not support justification currently, so the 
								 inside TextEditor will not affect by this param. The
								 default value for this param is Justification::topLeft.
								 单行模式和多行，但非自动换行模式下文本框的对齐方式。
								 由于JUCE的TextEditor类当前暂不支持对齐方式，因此内部的
								 输入框的对齐行为不会受该参数影响。该参数默认值为：
								 Justification::topLeft。
		                     
	*/
	TextBox(const String &componentName = String(), bool shouldCanCopy = true, 
		bool shouldUseEllipses = true, Justification justificationType = Justification::topLeft) :
		textEditorEx(this), justification(justificationType)
	{
		isFirstRender = true;
		isEditorShowing = false;

		textEditorEx.setTopLeftPosition(0, 0);
		textEditorEx.setReadOnly(true);
		textEditorEx.setWantsKeyboardFocus(false);
		addAndMakeVisible(textEditorEx);

		setCanCopy(shouldCanCopy);
		setUsingEllipses(shouldUseEllipses);

		setMargin(INIT_MARGIN);
		setPadding(INIT_PADDING);
		setTextColour(true);
		setBoxBorder(false);

		setWantsKeyboardFocus(true);
		setName(componentName);
	}
	/** @brief Destructor.
	           析构函数。
	*/
	~TextBox(){}

	//==============================================================================
	/** @brief   Get the pointer of the inside TextEditorEx
	             获取组件内部的输入框TextEditorEx的指针

		@returns The pointer of the inside TextEditorEx
		@returns 组件内部的输入框TextEditorEx的指针
	*/
	TextEditorEx* getEditor()
	{
		return &textEditorEx;
	}

	//==============================================================================
	/** @brief Set the component to copiable mode or non-copiable mode.
	           设置组件至可复制模式，或不可复制模式。

		@param shouldCanCopy True for copiable mode, and false for non-copiable mode.
		                     True表示可复制，false表示不可复制。

		@see TextBox()
	*/
	void setCanCopy(bool shouldCanCopy)
	{
		canCopy = shouldCanCopy;
	}

	/** @brief   Get the copyablility set by "setCanCopy".
	             获取由"setCanCopy"确定的组件的可拷贝性。

		@returns True for copiable, false for non-copiable.
		@returns True表示可拷贝，false表示不可拷贝。

		@see setCanCopy
	*/
	bool getCanCopy() const
	{
		return canCopy;
	}

	/** @brief Set the margin of the component.
	           设置组件的外边距。

		The margin is the distance from the component's bounds to the border's bounds.
		外边距是组件的边界到组件边框的边界之间的距离。
	*/
	void setMargin(float borderMargin)
	{
		margin = borderMargin;
	}

	/** @brief Get the margin of the component.
	           获取组件的外边距。

		@see setMargin
	*/
	float getMargin() const
	{
		return margin;
	}

	/** @brief Set the padding of the component.
	           设置组件的内边距。

	    The padding is the distance from the border's bounds or the component's
		bounds (when there's no border around the component) to the component's 
		contents' bounds.
	    内边距是组件边框或组件本身（当组件没有边框时）的边界到组件内容的边界之间
		的距离。
	*/
	void setPadding(float textPadding)
	{
		padding = textPadding;
	}

	/** @brief Get the padding of the component.
	           获取组件的内边距。

		@see setPadding
	*/
	float getPadding() const
	{
		return padding;
	}

	/** @brief Set if using ellipses when the contents are out of bounds.
	           设置是否在内容超出边界时显示结尾省略号。

		@param shouldUseEllipses True for use ellipses, false for not use ellipses.
		                         True表示使用结尾省略号，false表示不使用结尾省略号。

		@see TextBox()
	*/
	void setUsingEllipses(bool shouldUseEllipses)
	{
		useEllipses = shouldUseEllipses;
	}

	/** @brief Get whether the component is using ellipses or not.
	           获取组件是否使用结尾省略号。

		@see setUsingEllipses
	*/
	bool getUsingEllipese() const
	{
		return useEllipses;
	}

	/** @brief Set the justification type of the component.
	           设置组件的对齐方式。

	    The justification type is only valid in single-line and
	    multi-line, but non-wordwrap mode.

		JUCE's TextEditor class does not support justification 
		currently, so the inside TextEditor will not affect by
		this method.

		对齐方式仅在单行模式，以及多行但非自动换行模式下有效。

		由于JUCE的TextEditor类当前暂不支持对齐方式，因此内部的
		输入框的对齐行为不会受该方法影响。

		@see TextBox()
	*/
	void setJustificationType(Justification justificationType)
	{
		justification = justificationType;
	}

	/** @brief Get the justification type of the component.
	           获取组件的对齐方式。

		@see setJustificationType
	*/
	Justification getJustificationType() const
	{
		return justification;
	}

	/** @brief Set the text box's text colour.
	           设置文本框的文本颜色。

		@param shouldUseEditorColour Wether to use the same text colour as in the
		                             TextEditor.
									 是否使用与输入框相同的文本颜色。

		@param expectTextColour      The text colour to set to the text box. Ignored
		                             if shouldUseEditorColour is true. The default
									 colour text colour is black.
									 文本框的文本颜色。当 shouldUseEditorColour 为 true
									 时，该参数被忽略。默认文本颜色为黑色。
	*/
	void setTextColour(bool shouldUseEditorColour, Colour expectTextColour = Colours::black)
	{
		useEditorColour = shouldUseEditorColour;
		textColour = expectTextColour;
	}

	/** @brief   Get if the component is using the same text colour as in the TextEditor.
	             获取该组件是否使用与输入框相同的文本颜色。

		@returns True for same as TextEditor, false for using individual colour.
		@returns true代表使用与输入框相同的文本颜色，false代表使用单独的文本颜色。

		@see setTextColour
	*/
	bool isUsingEditorColour() const
	{
		return useEditorColour;
	}

	/** @brief Get the text colour the text box is currently using.
	           获取文本框当前正在使用的文本颜色。

		If the TextBox is using the editor colour, than this method will return the text
		colour that the inside TextEditorEx is currently using.
		如果TextBox当前正在使用输入框的字体，那么该方法会返回内部的TextEditorEx正在使用的
		文本颜色。

		@see isUsingEditorColour, setTextColour
	*/
	Colour getTextColour() const
	{
		if (useEditorColour) return textEditorEx.findColour(TextEditor::textColourId);
		else return textColour;
	}

	/** @brief Set the custom border of the TextBox.
	           设置文本框的用户边框。

		@param shouldUseBorder      Wether to use a border or not.
		                            是否使用边框。

		@param shouldUseRoundedRect Wether to use a rounded rectangle for the border. Ignored
		                            if shouldUseBorder is set to false.
									是否设置边框使用圆角矩形。当 shouldUseBorder 为 false 时，
									该参数被忽略。

		@param expectLineThickness  The thickness of the border's outline. Ignored if shouldUseBorder 
		                            is set to false.
									边框轮廓的粗细。当 shouldUseBorder 为 false 时，该参数被忽略。

		@param expectCornerSize     The corner size (radius) of the rounded border. Ignored if 
		                            shouldUseRoundedRect is set to false.
									圆角边框的边角大小（半径）。当 shouldUseRoundedRect 为 false 时，
									该参数被忽略。

		@param expectBorderColour   The colour of the TextBox's border. Ignored if shouldUseBorder
		                            is set to false.
									文本框的边框颜色。当 shouldUseBorder 为 false 时，该参数被忽略。
	*/
	void setBoxBorder(bool shouldUseBorder, bool shouldUseRoundedRect = false,
		float expectLineThickness = 1.0f, float expectCornerSize = 0.0f, Colour expectBorderColour = Colours::black)
	{
		useBorder = shouldUseBorder;
		useRoundedRect = shouldUseRoundedRect;
		lineThickness = expectLineThickness;
		cornerSize = expectCornerSize;
		borderColour = expectBorderColour;
	}

	/** @brief Get the thickness of the TextBox's border's outline.
	           获取文本框边框轮廓的粗细。

		If the TextBox is not using a border currently, this method will return 0.0f.
		如果TextBox当前没有使用边框，该方法将返回0.0f。

		@see setBoxBorder
	*/
	float getBorderLineThickness() const
	{
		if (useBorder) return lineThickness;
		else return 0.0f;
	}

	/** @brief Get the corner size (radius) of the TextBox's rounded border.
	           获取文本框圆角边框的边角大小（半径）。

	    If the TextBox is not using a rounded border currently, this method will return 0.0f.
		如果TextBox当前没有使用圆角边框，该方法将返回0.0f。

		@see setBoxBorder
	*/
	float getBorderCornerSize() const
	{
		if (useRoundedRect) return cornerSize;
		else return 0.0f;
	}

	/** @brief Get the colour of the TextBox's border.
	           获取文本框的边框颜色。

		@see setBoxBorder
	*/
	Colour getBorderColour() const
	{
		return borderColour;
	}

	//==============================================================================
	void paint(Graphics& g) override
	{
		CheckForFirstRender();

		if (isEditorShowing)
		{
			//obsoleted
		}
		else
		{
			//begin drawing textbox

			float offset = 0.0f;

			if (useBorder)
			{
				offset += margin;
				g.setColour(borderColour);

				if (useRoundedRect)
				{
					g.drawRoundedRectangle(offset, offset, getWidth() - 2 * offset, getHeight() - 2 * offset, cornerSize, lineThickness);
				}
				else
				{
					g.drawRect(offset, offset, getWidth() - 2 * offset, getHeight() - 2 * offset, lineThickness);
				}

				offset += lineThickness;
			}

			offset += padding;
			g.setColour(getTextColour());
			g.setFont(textEditorEx.getFont());

			if (!textEditorEx.isMultiLine())
			{
				g.drawText(textEditorEx.getText(), offset, offset, getWidth() - 2 * offset, getHeight() - 2 * offset, justification, useEllipses);
			}
			else
			{
				if (textEditorEx.isWordWrap())
				{
					g.drawMultiLineText(textEditorEx.getText(), offset, offset + textEditorEx.getFont().getHeight(), getWidth() - 2 * offset);
				}
				else
				{
					StringArray lines = StringArray::fromLines(textEditorEx.getText());
					float y_off = offset;

					for (int i = 0; i < lines.size(); i++)
					{
						g.drawText(textEditorEx.getText(), offset, y_off, getWidth() - 2 * offset,
							textEditorEx.getFont().getHeight(), justification, useEllipses);

						y_off = y_off + textEditorEx.getFont().getHeight() * textEditorEx.getLineSpacing();
					}
				}
			}
		}
	}

	//==============================================================================
	void mouseDoubleClick(const MouseEvent &mouseEvent) override
	{
		if (mouseEvent.mods.isLeftButtonDown())
		{
			if (!isEditorShowing)
			{
				showEditor();
			}
		}
	}

	void focusLost(FocusChangeType focusChangeType) override
	{
		if (isEditorShowing)
		{
			if (focusChangeType == focusChangedByMouseClick)
			{
				hideEditor();
			}
		}
	}

	//==============================================================================
	/** @brief Show the inside TextEditor.
	           显示输入框。

		This method is only valid in copiable mode.
		该方法仅在“可复制”模式下有效。
	*/
	void showEditor()
	{
		if (canCopy)
		{
			CheckEditorState();
			CheckSelfState();
			textEditorEx.setVisible(true);
			isEditorShowing = true;
		}
	}

	/** @brief Hide the inside TextEditor.
	           隐藏内部的输入框。
	*/
	void hideEditor()
	{
		textEditorEx.setVisible(false);
		isEditorShowing = false;
	}

	//==============================================================================
	/** @brief   Get whether the inside TextEditor is showing or not.
	             获取内部的输入框是否在显示状态。

		@returns True for being shown, false for being hidden.
		@returns 返回true表示显示中，返回false表示隐藏中。
	*/
	bool getEditorShowingState() const
	{
		return isEditorShowing;
	}
	
private:
	//==============================================================================
	bool canCopy;
	bool isFirstRender, isEditorShowing;
	bool useEllipses;

	Justification justification;

	float margin, padding;

	bool useBorder, useRoundedRect;
	float lineThickness, cornerSize;
	Colour borderColour;

	bool useEditorColour;
	Colour textColour;

	TextEditorEx textEditorEx;

	void CheckForFirstRender()
	{
		if (isFirstRender)
		{
			hideEditor();
			textEditorEx.setSize(getWidth(), getHeight());
			setTooltip(textEditorEx.getTooltip());
			isFirstRender = false;
		}
	}

	void CheckSelfState()
	{
		if (getParentComponent()->getWantsKeyboardFocus() == false)
		{
			getParentComponent()->setWantsKeyboardFocus(true);
		}

		if (getWantsKeyboardFocus() == false)
		{
			setWantsKeyboardFocus(true);
		}
	}

	void CheckEditorState()
	{
		if (textEditorEx.getX() != 0 || textEditorEx.getY() != 0)
		{
			textEditorEx.setTopLeftPosition(0, 0);
		}

		if (!textEditorEx.isReadOnly())
		{
			textEditorEx.setReadOnly(true);
		}

		if (textEditorEx.getWantsKeyboardFocus())
		{
			textEditorEx.setWantsKeyboardFocus(false);
		}

		if (textEditorEx.getHeight() != getHeight() || textEditorEx.getWidth() != getWidth())
		{
			textEditorEx.setSize(getWidth(), getHeight());
		}
	}
};
