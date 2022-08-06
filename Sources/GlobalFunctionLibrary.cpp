#include "GlobalFunctionLibrary.h"
#include <iostream>
#include <cstdarg>
#include "TGame.h"
#include "GlobalConfig.h"

using namespace std;

char* Tool::FormatTimestamp(float TimeStamp)
{
	return "";
}

void Tool::LogHead()
{
	cout << "[";
	if (TGame* TheGame = TGame::Instance())
	{
		 cout << FormatTimestamp(TheGame->GetGameTimeNow()) << " #" << TheGame->GetFrameNumber();
	}
	cout << "]";
}

void Tool::Log(const char* Text, ...)
{
	LogHead();
	cout<<Text;

	va_list ArgsPtr;
	va_start(ArgsPtr, Text);
	char* Value = va_arg(ArgsPtr, char*);
	while (Value != nullptr)
	{
		cout<<" "<< Value;
		Value = va_arg(ArgsPtr, char*);
	}

	va_end(ArgsPtr);
	cout << endl;
}

Simple2D::Image* Tool::CreateImage(const std::string& ImageFileName)
{
	return Simple2D::CreateImage(Config::ImagePath + ImageFileName + ".png");
}

Simple2D::Font* Tool::CreateFont()
{
	return Simple2D::CreateFont(Config::FontPath, Config::FontSize);
}
