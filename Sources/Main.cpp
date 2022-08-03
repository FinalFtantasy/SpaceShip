#include "Simple2D.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	Simple2D::Window* pWindow = Simple2D::CreateWindow("ShooterGame", 1024, 768);
	
	Game* TheGame = Game::Instance();
	TheGame->Init(pWindow);
	TheGame->BeginGame();

	while (!Simple2D::ShouldWindowClose(pWindow))
	{
		TheGame->Update();
		Simple2D::RefreshWindowBuffer(pWindow);
	}

	TheGame->EndGame();
	Simple2D::DestroyWindow(pWindow);

	return 0;
}

