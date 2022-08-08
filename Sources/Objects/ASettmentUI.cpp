#include "ASettmentUI.h"

#include "AFont.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/UBattleLevel.h"

void ASettmentUI::Init()
{
    AActor::Init();

    SetImage("Blur");
    SetPosition(Config::WinWidth/2, Config::WinHeight/2);

    FInfo = AFont::CreateFont("Death is always the end, but glory is not.");
    FInfo->SetPosition(Config::WinWidth/2, Config::WinHeight/2 + 150);
    
    UBattleLevel* Level = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel());
    FTime = AFont::CreateFont("Alive Time: " + Tool::FormatTimestamp(Level->GetLevelTimeNow()));
    FTime->SetPosition(Config::WinWidth/2, Config::WinHeight/2 + 50);

    char Buff[20];
    sprintf(Buff, "Score: %d", Level->GetScore());
    FScore = AFont::CreateFont(Buff);
    FScore->SetPosition(Config::WinWidth/2, Config::WinHeight/2 - 50);
    
    Tips = AFont::CreateFont("Press Enter To Restart.");
    Tips->SetPosition(Config::WinWidth/2, Config::WinHeight/2 - 150);
}

void ASettmentUI::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    if (Simple2D::IsKeyPressed(Simple2D::KEY_ENTER))
    {
        TGame* Game = TGame::Instance();
        Game->RestartGame();
    }
}

void ASettmentUI::Draw() const
{
    AActor::Draw();

    FInfo->Draw();
    FTime->Draw();
    FScore->Draw();
    Tips->Draw();
}

void ASettmentUI::EndPlay()
{
    FInfo->Destroy();
    FTime->Destroy();
    FScore->Destroy();
    Tips->Destroy();

    delete FInfo;
    delete FTime;
    delete FScore;
    delete Tips;
    
    AActor::EndPlay();
}
