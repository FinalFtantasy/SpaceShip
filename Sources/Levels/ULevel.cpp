#include "ULevel.h"

#include "../TGame.h"
#include "../Objects/AActor.h"
#include "../Objects/ABackground.h"
#include "../Objects/ABullet.h"
#include "../Objects/AHero.h"

ABackground* ULevel::Background = nullptr;
AHero* ULevel::Hero = nullptr;

ULevel::ULevel()
{
    HasBegunPlay = false;
    bLevelBattleEnd = false;
    bPause = false;
}

void ULevel::UnLoadLevel(ULevel* TargetLevel)
{
    if(TargetLevel)
    {
        TargetLevel->LevelEnd();
    }
}

bool ULevel::InitLevel()
{
    InitBackground();

    Hero = AHero::Get();
    
    return true;
}

void ULevel::LevelBegin()
{
    HasBegunPlay = true;

    LevelBeginTime = TGame::GetGameTimeNow();
    
    Background->BeginPlay();

    Hero->BeginPlay();
    
    for (AActor* Actor : LevelActors)
    {
        Actor->BeginPlay();
    }
}

void ULevel::LevelEnd()
{
    CleanActor(LevelActors);
    CleanActor(Bullets);
}

void ULevel::OnLevelBattleEnd()
{
}

void ULevel::AddActor(AActor* InActor)
{
    if (InActor)
    {
        LevelActors.push_back(InActor);
        if (HasBegunPlay)
        {
            InActor->BeginPlay();
        }
    }
}

void ULevel::AddBullet(ABullet* InBullet)
{
    if (InBullet)
    {
        Bullets.push_back(InBullet);
        if (HasBegunPlay)
        {
            InBullet->BeginPlay();
        }
    }
}

void ULevel::OnHeroHpChanged()
{
}

void ULevel::InitBackground()
{
    if (Background == nullptr)
    {
        Background = AActor::CreateActor<ABackground>("", false);
    }
}

void ULevel::LevelUpdate(float DeltaTime)
{
    LevelGameTimeNow = TGame::GetGameTimeNow() - LevelBeginTime;

    if (!bPause)
    {
        LevelLogicUpdate(DeltaTime);

        if (bLevelBattleEnd)
        {
            Pause();
            OnLevelBattleEnd();
        }
        else
        {
            if (Simple2D::IsKeyPressed(Simple2D::KEY_ESCAPE))
            {
                Pause();
            }
        }
    }
    else
    {
        if (Simple2D::IsKeyPressed(Simple2D::KEY_ESCAPE))
        {
            Resume();
        }
    }
}

void ULevel::LevelLogicUpdate(float DeltaTime)
{
    if (Background && Background->ShouldUpdate())
    {
        Background->Update(DeltaTime);
    }

    if (Hero && Hero->ShouldUpdate())
    {
        Hero->Update(DeltaTime);
    }

    UpdateActors(Bullets, DeltaTime);
    UpdateActors(LevelActors, DeltaTime);
}

void ULevel::DrawLevel()
{
    if (Background)
    {
        Background->Draw();
    }

    DrawActors(LevelActors);
    DrawActors(Bullets);

    if (Hero)
    {
        Hero->Draw();
    }
}

