#include "StartLevel.h"

#include "../GlobalConfig.h"
#include "../GlobalFunctionLibrary.h"
#include "../Objects/ABackground.h"
#include "../Objects/AFont.h"

bool StartLevel::InitLevel()
{
    ULevel::InitLevel();

    StartFont = AFont::CreateFont("Start Game");
    StartFont->SetPosition(Config::WinWidth/2, Config::WinHeight/3);
    
    return true;
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
