#include "GlobalFunctionLibrary.h"
#include <iostream>
#include <cstdarg>
#include <cmath>
#include <random>
#include <ctime>
#include "TGame.h"
#include "GlobalConfig.h"
#include "Objects/AActor.h"

using namespace std;

string Tool::FormatTimestamp(float TimeStamp)
{
	int Second = Math::Floor(TimeStamp);
	int h = Math::Floor(Second/3600);
	int m = Math::Floor(Second%3600/60);
	int s = Math::Floor(Second%3600%60%60);

	char buff[20];
	sprintf(buff, "%02d:%02d:%02d", h,m,s);
	return buff;
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
	if (ImageFileName.empty())
	{
		return nullptr;
	}
	return Simple2D::CreateImage(Config::ImagePath + ImageFileName + ".png");
}

Simple2D::Font* Tool::CreateFont(const uint32 FontSize)
{
	return Simple2D::CreateFont(Config::FontPath, FontSize);
}

std::default_random_engine Math::RandEngine;

int Math::Floor(const float InValue)
{
	return static_cast<int>(floor(InValue));
}

int Math::Ceil(const float InValue)
{
	return static_cast<int>(ceil(InValue));
}

void Math::InitRandomSeed()
{
	RandEngine.seed(time(0));
}

float Math::Random(const float a, const float b)
{
	return RandEngine() % Floor(b - a + 1) + a;
}

float Math::CheckHit(AActor* A, AActor* B)
{
	float DWidth = (A->GetActorWidth() + B->GetActorWidth())/2;
	float DHeight = (A->GetActorHeight() + B->GetActorHeight())/2;

	return abs(A->GetPosX() - B->GetPosX()) < DWidth && abs(A->GetPosY() - B->GetPosY()) < DHeight;
}
