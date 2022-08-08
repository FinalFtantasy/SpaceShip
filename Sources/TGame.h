#pragma once

#include "GlobalConfig.h"
#include "Simple2D.h"
#include "Levels/ULevel.h"

class ULevel;
class AFont;

class TGame
{
public:
	static TGame* Instance();

	void Init(Simple2D::Window* TargetGameWindow);
	void BeginGame();
	void GameStart();
	bool IsGameEnd();
	void Update();
	void EndGame();

	template<typename T>
	void SwitchLevel() const
	{
		 if (ULevel* TargetLevel = ULevel::LoadLevel<T>())
		 {
		 	if (CurrentLevel)
		 	{
		 		ULevel::UnLoadLevel(CurrentLevel);
		 	}
		 	
		 	TargetLevel->LevelBegin();
		 	
		 	CurrentLevel = TargetLevel;
		 }
	}

	static float GetGameTimeNow();
	
	static uint32 GetFrameNumber() { return FrameNumber; }

	static ULevel* GetCurrentLevel() { return CurrentLevel; }
	static uint32 GetFPS() { return FPS; }

	void CheckInput();

	void ShowSettlemmentUi();
	void RestartGame();

private:
	TGame();

	void RestartGameInternal();

	static TGame* ThisGame;

	static ULevel* CurrentLevel; 

	Simple2D::Window* GameWindow;

	AFont* FFPS;
	AFont* FGameTime;
	AFont* Helper;

	class ASettmentUI* SettmentUI;
	
	static float GameBeginTime;

	float LastFrameBeginTime;
	float LastFrameEndTime;

	static uint32 FrameNumber;
	static uint32 FPS;

	bool bReStartGame;
	bool bStartGame;
	bool bShowHelper;
	bool bShowFPS;

};

