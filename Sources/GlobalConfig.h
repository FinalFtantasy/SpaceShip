#pragma once
#include <string>

using namespace std;
#define DEBUG

namespace Config
{
	const string GameName = "SpaceShip";
	constexpr float WinWidth = 1920;
	constexpr float WinHeight = 1080;

#ifdef DEBUG
	const string ImagePath = "../../Content/Textures/";
#else
	const string ImagePath = "./Content/Textures/";
#endif

#ifdef DEBUG
	const string FontPath = "../../Content/Fonts/AGENCYB.TTF";
#else
	const string FontPath = "./Content/Fonts/AGENCYB.TTF";
#endif

	constexpr uint32_t FontSize = 30;
}