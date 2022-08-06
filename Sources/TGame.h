#pragma once

#include "Simple2D.h"

class ULevel;

class TGame
{
public:
	static TGame* Instance();

	void Init(Simple2D::Window* TargetGameWindow);
	void BeginGame();
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

	float GetGameTimeNow();
	
	inline uint32_t GetFrameNumber() const { return FrameNumber; }

	static ULevel* GetCurrentLevel() { return CurrentLevel; }

private:
	TGame();

	static TGame* ThisGame;

	static ULevel* CurrentLevel; 

	Simple2D::Window* GameWindow;
	
	float GameBeginTime;

	float LastFrameBeginTime;
	float LastFrameEndTime;

	uint32_t FrameNumber;

};

