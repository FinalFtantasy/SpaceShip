#pragma once
#include "iostream"
#include "Simple2D.h"

class Tool
{
public:
	static char* FormatTimestamp(float TimeStamp);

	static void LogHead();

	static void Log(const char* Text,...);

	static Simple2D::Image* CreateImage(const std::string& ImageFileName);

	static Simple2D::Font* CreateFont();
};

template <typename... Args>
void Log(const char* Text, Args&&... args)
{
	Tool::Log(Text, std::forward<Args>(args)... , nullptr);
}