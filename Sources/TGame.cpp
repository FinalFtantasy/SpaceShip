#include "TGame.h"
#include "Levels/ULevel.h"
#include "GlobalFunctionLibrary.h"
#include "Levels/StartLevel.h"

TGame* TGame::ThisGame = nullptr;
ULevel* TGame::CurrentLevel = nullptr;

TGame::TGame()
{
	GameWindow = nullptr;
	GameBeginTime = 0.f;
	FrameNumber = 0;
	LastFrameBeginTime = 0.f;
	LastFrameEndTime = 0.f;
}

TGame* TGame::Instance()
{
	if (ThisGame == nullptr)
	{
		ThisGame = new TGame();
	}
	return ThisGame;
}

void TGame::Init(Simple2D::Window* TargetGameWindow)
{
	Log("Game Init");
	GameWindow = TargetGameWindow;

	SwitchLevel<StartLevel>();
}

void TGame::BeginGame()
{
	Log("Game Begin");
	GameBeginTime = Simple2D::GetGameTime();
	
	if (CurrentLevel)
	{
		CurrentLevel->LevelBegin();
	}
}

bool TGame::IsGameEnd()
{
	return false;
}

void TGame::Update()
{
	const float FrameBeginTime = Simple2D::GetGameTime();
	++FrameNumber;

	// in second
	const float DeltaTime = FrameBeginTime - LastFrameBeginTime;

	if (CurrentLevel && CurrentLevel->IsHasBegunPlay())
	{
		CurrentLevel->LevelUpdate(DeltaTime);

		CurrentLevel->DrawLevel();
	}

	const float FrameEndTime = Simple2D::GetGameTime();

	LastFrameBeginTime = FrameBeginTime;
	LastFrameEndTime = FrameEndTime;
}

void TGame::EndGame()
{
	Log("Game End");
	delete ThisGame;
}

float TGame::GetGameTimeNow()
{
	return Simple2D::GetGameTime() - GameBeginTime;
}
