#include "StartLevel.h"

#include "../GlobalConfig.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Objects/ABackground.h"
#include "../Objects/AFont.h"
#include "../Objects/AHero.h"

bool StartLevel::InitLevel()
{
    ULevel::InitLevel();

    StartFont = AFont::CreateFont("Press Enter To Start Game",45);
    StartFont->SetPosition(Config::WinWidth/2, Config::WinHeight/4);

    if (Hero)
    {
        Hero->SetPosition(Config::WinWidth/4, Config::WinHeight/2);
        Hero->Reset();
    }

    Background->ResetMoon();
    
    return true;
}

void StartLevel::LevelLogicUpdate(float DeltaTime)
{
    ULevel::LevelLogicUpdate(DeltaTime);

    if (Simple2D::IsKeyPressed(Simple2D::KEY_ENTER))
    {
        TGame* Game = TGame::Instance();
        Game->GameStart();
    }
}

void StartLevel::DrawLevel()
{
    ULevel::DrawLevel();

    StartFont->Draw();
}

void StartLevel::LevelEnd()
{
    StartFont->Destroy();
    ULevel::LevelEnd();
}
