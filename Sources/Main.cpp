#include "Simple2D.h"
#include "TGame.h"
#include "GlobalConfig.h"

int main(int argc, char *argv[])
{
	Simple2D::Window* pWindow = Simple2D::CreateWindow(Config::GameName, Config::WinWidth, Config::WinHeight);

	TGame* TheGame = TGame::Instance();
	TheGame->Init(pWindow);
	TheGame->BeginGame();

	while (!Simple2D::ShouldWindowClose(pWindow) || TheGame->IsGameEnd())
	{
		TheGame->Update();
		Simple2D::RefreshWindowBuffer(pWindow);
	}

	TheGame->EndGame();
	Simple2D::DestroyWindow(pWindow);

	return 0;
}

