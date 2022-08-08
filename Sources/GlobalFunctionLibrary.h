#pragma once
#include <random>

#include "GlobalConfig.h"
#include "iostream"
#include "Simple2D.h"

class AActor;

class Tool
{
public:
	static std::string FormatTimestamp(float TimeStamp);

	static void LogHead();

	static void Log(const char* Text,...);

	static Simple2D::Image* CreateImage(const std::string& ImageFileName);

	static Simple2D::Font* CreateFont(const uint32 FontSize = Config::FontSize);
};

template <typename... Args>
void Log(const char* Text, Args&&... args)
{
	Tool::Log(Text, std::forward<Args>(args)... , nullptr);
}

template <typename T>
T* RemoveAtSwap(std::vector<T*>& vec, uint32 Index)
{
	if (Index < vec.size())
	{
		T* temp = vec[Index];
		vec[Index] = vec.back();
		vec.pop_back();
		return temp;
	}
	return nullptr;
}

class Math
{
public:
	static int Floor(const float InValue);

	static int Ceil(const float InValue);

	static void InitRandomSeed();
	
	static float Random(const float a, const float b);

	static float CheckHit(AActor* A, AActor* B);

private:
	static 	std::default_random_engine RandEngine;
};