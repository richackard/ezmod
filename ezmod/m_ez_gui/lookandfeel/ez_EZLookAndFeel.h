#pragma once
#define EZ_EZLOOKANDFEEL_H_INCLUDED

#define COMP_COUNT 9

using namespace juce;

//==============================================================================
/**

    @brief An easy LookAndFeel class derived from LookAndFeel_V4 which you can
	       easily setup your custom font for JUCE build-in components.
		   一个简易的，可以轻松为JUCE内置组件设置字体的LookAndFeel类。继承自
		   LookAndFeel_V4。

	By using this class, you can set up a common font for all the component that
	JUCE currently supports, or you can set up font for a specific component
	type that differs form others.

	使用该类，您可以为JUCE当前支持的所有组件设置通用字体，或者为某个组件类型单独
	设置与其他组件不同的字体。

*/
class EZLookAndFeel : public LookAndFeel_V4
{
public:
	//==============================================================================
	/** @brief Creates a new EZLookAndFeel object with a default LookAndFeel_V4 
	           colour scheme and a designated font name.
			   按照指定的字体名创建一个新的，默认LookAndFeel_V4配色方案的
			   EZLookAndFeel对象。

		@param name common font name for all the component that JUCE currently
		            support. The default value is "STZhongsong".
		            JUCE当前支持的所有组件的通用字体名。默认值为“华文中宋”
		           （"STZhongsong"）。
	*/
	EZLookAndFeel(String name = "STZhongsong")
	{
		fontName_all = name;

		for (int i = 0; i < COMP_COUNT; ++i)
		{
			useSpecificFont[i] = false;
			fontName_spec[i] = name;
		}
	}
	/** @brief Destructor.
	           析构函数。
	*/
	~EZLookAndFeel()
	{

	}

	//==============================================================================
	/** @brief A set of component types that are supported in current version. 
	           当前版本支持的所有组件类型枚举。

		These constants can be used via "setComponentFontName", and "unsetComponentFont"
		methods to setup or unset font for a specific component.

		这些枚举常量可以在“setComponentFontName”和“unsetComponentFont”函数中使用，
		以为某些特定的组件类型指定或解除指定使用单独的字体。
	*/
	enum COMP_TYPE
	{
		EZLAF_ALERT_TITLE,   /**< The title of the alert window.
						   
						          警告窗的标题。 */

		EZLAF_ALERT_MESSAGE, /**< The message of the alert window.
							 
							      警告窗的消息内容。 */

		EZLAF_ALERT,         /**< The alert window.
							 
							      警告窗。 */

		EZLAF_TEXT_BUTTON,   /**< The TextButton.
							     
								  文本按钮（TextButton）组件。 */

		EZLAF_LABEL,         /**< The Label.
							 
							      标签（Label）组件。 */

		EZLAF_COMBO_BOX,     /**< The ComboBox.
							  
							      下拉菜单（ComboBox）组件。 */

		EZLAF_POPUP_MENU,    /**< The PopupMenu. 
							  
							      弹出菜单（PopupMenu）组件。 */

		EZLAF_MENU_BAR,      /**< The MenuBar. 
							 
							      MenuBar 组件。 */

		EZLAF_SLIDER_POPUP   /**< The SliderPopup. 
							      
								  SliderPopup 组件。 */
	};

	//==============================================================================
	/** @brief Set common font name for all the component that currently supports.
	           为当前支持的所有组件设置通用的字体名。

		By calling this method, all the components and their child components which
		are using this LookAndFeel will be displayed using the designated font name.

		调用此方法后，所有使用该LookAndFeel的组件及其子组件都会按照指定的字体名来显示。

		@param name The name of the font.
		            字体名。

		@see EZLookAndFeel()
	*/
	void setFontNameToAll(String name)
	{
		fontName_all = name;
	}

	/** @brief Set font name for a specific component type.
	           为特定的组件类型设置单独的字体。

		@param name The name of the font.
		            字体名。

		@param type The type of the component that you want the font to apply to.
		            你希望设置单独字体的组件类型。
	*/
	void setComponentFontName(String name, COMP_TYPE type)
	{
		fontName_spec[type] = name;
		useSpecificFont[type] = true;
	}

	/** @brief Unset using individual font for the designated component type.
	           解除指定组件类型使用的单独字体。

		By calling this method, the designated component type will use the
		common/global font, instead of the individual one.

		调用这个方法后，指定的组件类型将会使用通用（全局）的字体，来替代原先
		使用的单独字体。

		@param type The type of the component that you want its individual
		            font to unset.
		            你希望解除设置单独字体的组件类型。

		@see setComponentFontName
	*/
	void unsetComponentFont(COMP_TYPE type)
	{
		useSpecificFont[type] = false;
	}

	//==============================================================================
	Font getAlertWindowTitleFont() override
	{
		Font font = LookAndFeel_V4::getAlertWindowTitleFont();
		return setFont(font, EZLAF_ALERT_TITLE);
	}
	Font getAlertWindowMessageFont() override
	{
		Font font = LookAndFeel_V4::getAlertWindowMessageFont();
		return setFont(font, EZLAF_ALERT_MESSAGE);
	}
	Font getAlertWindowFont() override
	{
		Font font = LookAndFeel_V4::getAlertWindowFont();
		return setFont(font, EZLAF_ALERT);
	}
	Font getTextButtonFont(TextButton &textButton, int buttonHeight) override
	{
		Font font = LookAndFeel_V4::getTextButtonFont(textButton, buttonHeight);
		return setFont(font, EZLAF_TEXT_BUTTON);
	}
	Font getLabelFont(Label &label) override
	{
		Font font = LookAndFeel_V4::getLabelFont(label);
		return setFont(font, EZLAF_LABEL);
	}
	Font getComboBoxFont(ComboBox &comboBox) override
	{
		Font font = LookAndFeel_V4::getComboBoxFont(comboBox);
		return setFont(font, EZLAF_COMBO_BOX);
	}
	Font getPopupMenuFont() override
	{
		Font font = LookAndFeel_V4::getPopupMenuFont();
		return setFont(font, EZLAF_POPUP_MENU);
	}
	Font getMenuBarFont(MenuBarComponent &menuBarComponent, int itemIndex, const String &itemText) override
	{
		Font font = LookAndFeel_V4::getMenuBarFont(menuBarComponent, itemIndex, itemText);
		return setFont(font, EZLAF_MENU_BAR);
	}
	Font getSliderPopupFont(Slider &slider) override
	{
		Font font = LookAndFeel_V4::getSliderPopupFont(slider);
		return setFont(font, EZLAF_SLIDER_POPUP);
	}

private:
	//==============================================================================
	String fontName_all;
	String fontName_spec[COMP_COUNT];
	bool useSpecificFont[COMP_COUNT];

	Font setFont(Font font, COMP_TYPE index)
	{
		if (!useSpecificFont[index]) font.setTypefaceName(fontName_all);
		else font.setTypefaceName(fontName_spec[index]);

		return font;
	}
};
