#include "UBattleLevel.h"

#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Objects/ABackground.h"
#include "../Objects/AMeteorite.h"
#include "../Objects/ABattleUI.h"
#include "../Objects/AHero.h"
#include "../Objects/ABullet.h"
#include "../Objects/AEnemy.h"
#include "../Objects/AExplode.h"
#include "../Objects/AItem.h"

bool UBattleLevel::InitLevel()
{
    ULevel::InitLevel();
    Score = 0;
    Background->StartMoveMoon();
    ItemSpawnDuration = 0.f;

    BattleUI = AActor::CreateActor<ABattleUI>("",false);
    return true;
}

void UBattleLevel::LevelBegin()
{
    ULevel::LevelBegin();

    BattleUI->BeginPlay();
}

void UBattleLevel::LevelLogicUpdate(float DeltaTime)
{
    ULevel::LevelLogicUpdate(DeltaTime);

    UpdateMeteorite(DeltaTime);

    UpdateEnemies(DeltaTime);

    UpdateItems(DeltaTime);
    
    UpdateActors(Explosions, DeltaTime);
    
    BattleUI->Update(DeltaTime);

    uint32 FrameNumber = TGame::GetFrameNumber();
    if (FrameNumber % 10 == 0)
    {
        ClearDestroyedActor(Meteorites);
        ClearDestroyedActor(Bullets);
        ClearDestroyedActor(Explosions);
        ClearDestroyedActor(Items);
    }
}

void UBattleLevel::AddActor(AActor* InActor)
{
    if(!InActor)
    {
        return;
    }
    
    if (AMeteorite* Meteorite = dynamic_cast<AMeteorite*>(InActor))
    {
        Meteorites.push_back(Meteorite);
    }
    else if (ABullet* Bullet = dynamic_cast<ABullet*>(InActor))
    {
        Bullets.push_back(Bullet);
    }
    else if (AEnemy* Enemy = dynamic_cast<AEnemy*>(InActor))
    {
        Enemies.push_back(Enemy);
    }
    else if (AExplode* Explode = dynamic_cast<AExplode*>(InActor))
    {
        Explosions.push_back(Explode);
    }
    else if (AItem* Item = dynamic_cast<AItem*>(InActor))
    {
        Items.push_back(Item);
    }
    else
    {
        LevelActors.push_back(InActor);
    }

    if (IsHasBegunPlay())
    {
        InActor->BeginPlay();
    }
}

void UBattleLevel::DrawLevel()
{
    if (Background)
    {
        Background->Draw();
    }

    DrawActors(LevelActors);
    DrawActors(Meteorites);
    DrawActors(Enemies);
    DrawActors(Bullets);

    if (Hero)
    {
        Hero->Draw();
    }

    DrawActors(Explosions);
    DrawActors(Items);

    if(BattleUI)
    {
        BattleUI->Draw();
    }
}

void UBattleLevel::OnLevelBattleEnd()
{
    ULevel::OnLevelBattleEnd();

    TGame* Game = TGame::Instance();
    Game->ShowSettlemmentUi();
}

void UBattleLevel::LevelEnd()
{
    ULevel::LevelEnd();
}

void UBattleLevel::OnHeroHpChanged()
{
    ULevel::OnHeroHpChanged();

    if (BattleUI)
    {
        BattleUI->UpdateHeroLife();
    }

    if (AHero* Hero = AHero::Get())
    {
        if (Hero->GetHP() == 0)
        {
            bLevelBattleEnd = true;
        }
    }
}

void UBattleLevel::OnEnemyDeath(AEnemy* Enemy)
{
    if (Enemy->GetEnemyType() == EEnemyType::Normal )
    {
        Score += Config::EnemyNormalScore;
    }
    else if (Enemy->GetEnemyType() == EEnemyType::Elite)
    {
        Score += Config::EnemyEliteScore;
    }
    else
    {
        Score += Config::EnemyBossScore;
    }
    if (BattleUI)
    {
        BattleUI->UpdateScore(Score);
    }
    ShowExplode(Enemy->GetPosX(),Enemy->GetPosY());
}

void UBattleLevel::OnMeteoriteDestroy(AMeteorite* Meteorite)
{
    switch (Meteorite->GetMeteoriteType())
    {
    case EMeteoriteType::Small:
        Score += Config::EnemyNormalScore;
        break;
    case EMeteoriteType::Middle:
    case EMeteoriteType::Big:
    default:
        Score += Config::EnemyEliteScore;
    }
    if (BattleUI)
    {
        BattleUI->UpdateScore(Score);
    }
}

AEnemy* UBattleLevel::CheckHitEnemy(AActor* Actor)
{
    for (AEnemy* Enemy : Enemies)
    {
        if (!Enemy->IsDestroy() && Math::CheckHit(Actor, Enemy))
        {
            Enemy->OnHitCollision(Actor);
            return Enemy;
        }
    }
    return nullptr;
}

AMeteorite* UBattleLevel::CheckHitMeteorite(AActor* Actor)
{
    for (AMeteorite* Meteorite : Meteorites)
    {
        if (!Meteorite->IsDestroy() && Math::CheckHit(Actor, Meteorite))
        {
            Meteorite->OnHitCollision(Actor);
            return Meteorite;
        }
    }
    return nullptr;
}

bool UBattleLevel::CheckHitHero(AActor* Actor)
{
    if (AHero* Hero = AHero::Get())
    {
        if (Math::CheckHit(Actor, Hero))
        {
            Hero->OnHitCollision(Actor);
            return true;
        }
    }
    return false;
}

void UBattleLevel::ShowExplode(float PosX, float PosY)
{
    AExplode* Explode = AActor::CreateActor<AExplode>();
    Explode->SetPosition(PosX, PosY);
}

void UBattleLevel::UpdateMeteorite(float DeltaTime)
{
    UpdateActors(Meteorites, DeltaTime);
    
    SpawnMeteorite();
}

void UBattleLevel::SpawnMeteorite()
{
    uint32 FrameNumber = TGame::GetFrameNumber();
    if (FrameNumber % (Config::MeteoriteSpawnTimeSmall * Config::TargetFPS) == 0)
    {
        AMeteorite* MeteoriteSmall = AMeteorite::CreateAMeteorite(EMeteoriteType::Small);
    }
    if (FrameNumber % (Config::MeteoriteSpawnTimeMiddle * Config::TargetFPS) == 0)
    {
        AMeteorite* MeteoriteMiddle = AMeteorite::CreateAMeteorite(EMeteoriteType::Middle);
    }
    if (FrameNumber % (Config::MeteoriteSpawnTimeBig * Config::TargetFPS) == 0)
    {
        AMeteorite::CreateAMeteorite(EMeteoriteType::Big);
    }
}

void UBattleLevel::UpdateEnemies(float DeltaTime)
{
    UpdateActors(Enemies, DeltaTime);

    SpawnEnemies();
}

void UBattleLevel::SpawnEnemies()
{
    uint32 FrameNumber = TGame::GetFrameNumber();
    if (FrameNumber % (Config::EnemyNormalSpawnTime * Config::TargetFPS) == 0)
    {
        AEnemy* Enemy = AEnemy::CreateEnemy(EEnemyType::Normal);
    }
    if (FrameNumber % (Config::EnemyEliteSpawnTime * Config::TargetFPS) == 0)
    {
        uint8 GroupType = Math::Floor(Math::Random(1,4));
        float BeginPosX = Config::WinWidth + 200;
        float BeginPosY = Math::Random(100,Config::WinHeight - 100);

        if (GroupType == 1 || GroupType == 2)
        {
            uint8 num = Math::Floor(Math::Random(4,8));
            for (uint32 i = 0; i < num; ++i)
            {
                AEnemy* Enemy = AEnemy::CreateEnemy(EEnemyType::Elite);
                if (GroupType == 1)
                {
                    Enemy->SetPosition(BeginPosX + i * Enemy->GetActorWidth() + 20, BeginPosY);
                }
                else if (GroupType == 2)
                {
                    Enemy->SetPosition(BeginPosX, BeginPosY + (i - num/2) * Enemy->GetActorHeight() + 20);
                }
            }
        }
        else
        {
            AEnemy* Enemy = AEnemy::CreateEnemy(EEnemyType::Elite);
            Enemy->SetPosition(BeginPosX, BeginPosY);
            Enemy->SetCanFire(true);
        }
    }
    if (FrameNumber % (Config::EnemyBossSpawnTime * Config::TargetFPS) == 0)
    {
        AEnemy* Enemy = AEnemy::CreateEnemy(EEnemyType::Boss);
    }
}

void UBattleLevel::UpdateItems(float DeltaTime)
{
    UpdateActors(Items,DeltaTime);

    if (ItemSpawnDuration > Config::ConfigItemSpawTime)
    {
        ItemSpawnDuration = 0.f;
        AActor::CreateActor<AItem>();
    }
    else
    {
        ItemSpawnDuration += DeltaTime;
    }
}
