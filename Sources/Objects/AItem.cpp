#include "AItem.h"

#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/UBattleLevel.h"

void AItem::Init()
{
    AActor::Init();

    SetImage("Upgrade");

    Speed = Config::DefaultItemSpeed;
    SetPosition(Config::WinWidth + Math::Random(200, 400), Math::Random(100, Config::WinHeight - 100));
}

void AItem::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    UpdatePosX(-Speed * DeltaTime);

    if(UBattleLevel* Level = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel()))
    {
        if (Level->CheckHitHero(this))
        {
            Destroy();
        }
    }

    if (GetPosX() < -GetActorWidth()/2)
    {
        Destroy();
    }
}
