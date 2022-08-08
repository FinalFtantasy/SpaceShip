#include "TGame.h"
#include <sstream>
#include "Levels/ULevel.h"
#include "GlobalFunctionLibrary.h"
#include "Levels/StartLevel.h"
#include "Levels/UBattleLevel.h"
#include "Objects/AFont.h"
#include "Objects/ASettmentUI.h"

TGame* TGame::ThisGame = nullptr;
ULevel* TGame::CurrentLevel = nullptr;
float TGame::GameBeginTime = 0.F;
uint32 TGame::FrameNumber = 0;
uint32 TGame::FPS = 0;

TGame::TGame()
{
	GameWindow = nullptr;
	FFPS = nullptr;
	FGameTime = nullptr;
	FrameNumber = 0;
	LastFrameBeginTime = 0.f;
	LastFrameEndTime = 0.f;
	bShowHelper = true;
	bShowFPS = true;
	bStartGame = false;
	SettmentUI = nullptr;
	bReStartGame = false;
}

void TGame::RestartGameInternal()
{
	bReStartGame = false;
	if (SettmentUI)
	{
		SettmentUI->Destroy();
		delete SettmentUI;
		SettmentUI = nullptr;
	}

	SwitchLevel<StartLevel>();
	BeginGame();
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

	Math::InitRandomSeed();

	FFPS = AFont::CreateFont();
	FFPS->SetPosition(Config::WinWidth - 80, Config::WinHeight - 45);
	
	FGameTime = AFont::CreateFont("TIME: 00:00:00");
	FGameTime->SetPosition(150, 45);

	Helper = AFont::CreateFont("WASD or Up Down Right Left To Move, Space To Fire. F8 Hide This Message", 35);
	Helper->SetPosition(Config::WinWidth/2, 40);
	
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

void TGame::GameStart()
{
	Log("Game Start");

	SwitchLevel<UBattleLevel>();

	bStartGame = true;
}

bool TGame::IsGameEnd()
{
	return false;
}

void TGame::Update()
{
	const float FrameBeginTime = Simple2D::GetGameTime();
	if (++FrameNumber >1000)
	{
		FrameNumber = 0;
	}

	CheckInput();
	
	// in second
	const float DeltaTime = FrameBeginTime - LastFrameBeginTime;

	if (CurrentLevel && CurrentLevel->IsHasBegunPlay())
	{
		CurrentLevel->LevelUpdate(DeltaTime);

		CurrentLevel->DrawLevel();
	}

	if (SettmentUI)
	{
		SettmentUI->Update(DeltaTime);
		SettmentUI->Draw();
	}

	const float FrameEndTime = Simple2D::GetGameTime();
	
	if (Math::Floor(LastFrameEndTime) == Math::Floor(FrameEndTime))
	{
		FPS++;
	}
	else
	{
		char Buff[10];
		sprintf(Buff, "FPS: %d", FPS);
		FFPS->SetText(Buff);
		
		FPS = 0;
	}

	LastFrameBeginTime = FrameBeginTime;
	LastFrameEndTime = FrameEndTime;

	if (bStartGame && CurrentLevel)
	{
		FGameTime->SetText("TIME: " + Tool::FormatTimestamp(CurrentLevel->GetLevelTimeNow()));
	}
	
	FGameTime->Draw();

	if(bShowFPS)
	{
		FFPS->Draw();
	}

	if (bShowHelper)
	{
		Helper->Draw();
	}

	if (bReStartGame)
	{
		RestartGameInternal();
	}
}

void TGame::CheckInput()
{
	if(Simple2D::IsKeyPressed(Simple2D::KEY_F8))
	{
		bShowHelper = !bShowHelper;
	}

	if (Simple2D::IsKeyPressed(Simple2D::KEY_F7))
	{
		bShowFPS = !bShowFPS;
	}
}

void TGame::ShowSettlemmentUi()
{
	SettmentUI = AActor::CreateActor<ASettmentUI>("",false);
	SettmentUI->BeginPlay();
}

void TGame::RestartGame()
{
	bReStartGame = true;
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
