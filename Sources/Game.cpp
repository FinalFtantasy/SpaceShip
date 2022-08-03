#include "Game.h"

Game* Game::ThisGame = nullptr;

Game::Game()
{
	GameWindow = nullptr;
}

Game* Game::Instance()
{
	if (ThisGame == nullptr)
	{
		ThisGame = new Game();
	}
	return ThisGame;
}

void Game::Init(Simple2D::Window* TargetGameWindow)
{
	GameWindow = TargetGameWindow;
}

void Game::BeginGame()
{

}

void Game::Update()
{

}

void Game::EndGame()
{

}
