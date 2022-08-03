#pragma once

#include "Simple2D.h"

class Game
{
public:
	static Game* Instance();

	void Init(Simple2D::Window* TargetGameWindow);
	void BeginGame();
	void Update();
	void EndGame();

private:
	Game();

	static Game* ThisGame; 

	Simple2D::Window* GameWindow;
};

