/*******************************************************************************
The block below describes the properties of this module, and is read by
the Projucer to automatically generate project code that uses it.
For details about the syntax and how to create or use a module, see the
JUCE Module Format.txt file.


BEGIN_JUCE_MODULE_DECLARATION

ID:               m_ez_console
vendor:           ezdgit
version:          1.0.1
name:             Standard Output Stream handling classes
description:      Classes for Standard Output Stream in console mode.
license:          ISC

dependencies:     juce_core

END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#define M_EZ_CONSOLE_H_INCLUDED

#include <juce_core/juce_core.h>

#ifdef JUCE_WINDOWS
#include <Windows.h>

#else
#include <iostream>
#endif

//==============================================================================
/**

    @brief Writes data to standard output stream.
	       向标准输出流输出数据。

	This is use to take over the "cout" object in the stardard library.

	The usage of this class is somewhat like the "MemoryOutputStream" in JUCE.

	By using this class, you can have a strong compatibility to the build-in
	JUCE data types.

	And, you can output UTF-8 strings by using this class in whatever compiling
	environment, which is not possible using cout in VC compiler.

	We also provide a "command" method, which have the same function as "system".

	Important: Be sure to call "InitUTF8Console" before any UTF-8 outputs.

	Note that we only support UTF-8 outputs in Windows in current version.

	该类被用于取代C++标准库里的传统"cout"对象。

	该类的使用方法与 JUCE 的 MemoryOutputStream 类很相似。

	该类与 JUCE 的内置数据类型具有很强的兼容性。

	使用该类，您可以在任何编译环境下输出UTF-8字符串。这是使用cout在VC编译器中
	无法实现的。

	同时，我们还提供了了一个"command"方法，该方法与"system"函数作用相同。

	重要！请在输出任何UTF-8数据之前调用"InitUTF8Console"。

	注意：当前版本的UTF-8数据输出功能暂时只支持Windows系统。

*/
class ConsoleOutputStream : public juce::MemoryOutputStream
{
public:
	//==============================================================================
	/** @brief Creates an empty console output stream, ready to be written into.
	           创建一个空的控制台输出流。
	*/
	ConsoleOutputStream()
	{
		reset();
	}

	/** @brief Destructor.
	           析构函数。
	*/
	~ConsoleOutputStream()
	{
		reset();
	}

	//==============================================================================
	/** @brief Initialize console for UTF-8 data outputs (Windows only method). 
	           为UTF-8输出初始化控制台。（该方法只在Windows环境下有效）

		Call this before any UTF-8 outputs!

		在输出UTF-8数据之前请务必先调用此方法！

		@returns the BOOL result of setting console font action in Windows in order
		         to support UTF-8 display, or a 0 in other operating system. 
	    @returns 返回Windows控制台用来支持UTF-8数据显示的修改字体操作的 BOOL 类型
				 结果，或者当编译环境为非Windows的其他系统时返回0。
	*/
	int InitUTF8Console()
	{
#ifdef JUCE_WINDOWS
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		system("chcp 65001");

		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = 16;
		info.FontWeight = FW_NORMAL;
		wcscpy(info.FaceName, L"Consolas");

		return SetCurrentConsoleFontEx(hConsoleOutput, NULL, &info);
#else
		return 0;
#endif
	}

	/** @brief Print the data in the OutputStram to the console.
	           向控制台中输出OutputStream（输出流）中的数据。

		Remember to call "InitUTF8Console" before calling this if
		you have UTF-8 encoded data inserted in your output stream.

		In other OS, this method will use the standard "cout" to
		output the data stored in the output stream.

		如果您的输出内容中有UTF-8编码的数据，请在调用本方法之前先调用
		"InitUTF8Console"方法。

		在非Windows的其他系统中，该方法会使用传统的"cout"来输出输出流
		中的数据。

		@returns the BOOL result of "WriteConsole" function in Windows,
		         or a 0 in other operating system.
		@returns 返回Windows API "WriteConsole"的BOOL结果，或者当编译
				 环境为非Windows的其他系统时返回0。

		@see InitUTF8Console
	*/
	int printData()
	{
#ifdef JUCE_WINDOWS
		DWORD dw;
		BOOL bResult;

		if (hConsoleOutput == nullptr) hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		bResult = WriteConsole(hConsoleOutput, getData(), getDataSize(), &dw, NULL);
#else
		std::cout << toString();
#endif

		reset();

#ifdef JUCE_WINDOWS
		return bResult;
#else
		return 0;
#endif
	}

	//==============================================================================
	/** @brief Same as "system" function. Do nothing but returns 0 in other os.
	           作用同"system"函数。非Windows的其他系统下无任何动作并返回0。
	*/
	int command(char *cmd)
	{
#ifdef JUCE_WINDOWS
		return system(cmd);
#else
		return 0;
#endif
	}

private:
	//==============================================================================
#ifdef JUCE_WINDOWS
	HANDLE hConsoleOutput;
#endif
};
