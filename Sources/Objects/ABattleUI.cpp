#include "ABattleUI.h"

#include "AActor.h"
#include "AFont.h"
#include "AHero.h"
#include "../GlobalFunctionLibrary.h"

void ABattleUI::Init()
{
    AActor::Init();

    FLife = AFont::CreateFont("Life: ", 45);
    FLife->SetPosition(50, Config::WinHeight - 50);

    FScore = AFont::CreateFont("Score: 0", 50);
    FScore->SetPosition(Config::WinWidth/2, Config::WinHeight - 50);

    FNotice = AFont::CreateFont("Enemy Upgrade!", 40);
    FNotice->SetPosition(Config::WinWidth/2, Config::WinHeight - 150);
    FNotice->HideInGame();
    NoticeDuration = 0.f;

    for(uint32 i = 0; i < Config::DefaultHeroLife; ++i)
    {
        AActor* Life = AActor::CreateActor("Life",false);
        HeroLife.push_back(Life);
    }
    
    UpdateLifePos();
}

void ABattleUI::BeginPlay()
{
    AActor::BeginPlay();

    for(AActor* Life : HeroLife)
    {
        Life->BeginPlay();
    }
}

void ABattleUI::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    if (!FNotice->IsHide())
    {
        if (NoticeDuration > 1.5f)
        {
            FNotice->HideInGame();
            NoticeDuration= 0.f;
        }
        else
        {
            NoticeDuration += DeltaTime;
        }
    }
}

void ABattleUI::Draw() const
{
    AActor::Draw();

    FLife->Draw();
    FScore->Draw();
    FNotice->Draw();
    ULevel::DrawActors(HeroLife);
}

void ABattleUI::EndPlay()
{
    AActor::EndPlay();

    FLife->Destroy();
    FScore->Destroy();

    delete FLife;
    delete FScore;
    
    for(AActor* Life : HeroLife)
    {
        Life->Destroy();
        delete Life;
    }
    HeroLife.clear();
}

void ABattleUI::UpdateHeroLife()
{
    if (AHero* Hero = AHero::Get())
    {
        uint32 HeroHP = Hero->GetHP();
        if (HeroHP > HeroLife.size())
        {
            for(uint32 i = 0; i < (HeroHP - HeroLife.size()); ++i)
            {
                AActor* Life = AActor::CreateActor("Life",false);
                HeroLife.push_back(Life);
            }
        }
        for(uint32 i = 0; i < HeroLife.size(); ++i)
        {
            AActor* Life = HeroLife[i];
            if (i < HeroHP)
            {
                if (Life->IsHide())
                {
                    Life->Show();
                }
            }
            else
            {
                Life->HideInGame();
            }
        }

        UpdateLifePos();
    }
}

void ABattleUI::UpdateLifePos()
{
    for(uint32 i = 0; i < HeroLife.size(); ++i)
    {
        AActor* Life = HeroLife[i];
        float PosX = FLife->GetPosX() + 70 + i * 70;
        Life->SetPosition(PosX, FLife->GetPosY());
    }
}

void ABattleUI::UpdateScore(uint32 Score)
{
    char Buff[20];
    sprintf(Buff,"Score: %d", Score);
    FScore->SetText(Buff);
}

void ABattleUI::ShowEnemyUpGrade()
{
    FNotice->Show();
    FNotice->SetScale(1.3);
}
