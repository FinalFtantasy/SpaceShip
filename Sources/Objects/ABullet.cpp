#include "ABullet.h"

#include "../TGame.h"
#include "../Levels/UBattleLevel.h"


void ABullet::BeginPlay()
{
    AActor::BeginPlay();

    if (BulletType == EBulletType::HeroNormal)
    {
        SetImage("PlayerBullet");
        Speed = Config::DefaultBulletSpeed;
    }
    else if (BulletType == EBulletType::EnemyNormal)
    {
        SetImage("EnemyBullet");
        SetRotation(180);
        Speed = Config::EnemyBulletSpeed;
        Damage = 1;
    }
}

ABullet* ABullet::CreateBullet(const EBulletType InType)
{
    if (ABullet* Bullet = AActor::CreateActor<ABullet>())
    {
        Bullet->BulletType = InType;
        Bullet->BeginPlay();
        return Bullet;
    }
    
    return nullptr;
}

void ABullet::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    UBattleLevel* BattleLevel = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel());

    if (BulletType == EBulletType::HeroNormal)
    {
        UpdatePosX(Speed * DeltaTime);
        if (BattleLevel && BattleLevel->CheckHitEnemy(this))
        {
            Destroy();
        }
        else if (BattleLevel && BattleLevel->CheckHitMeteorite(this))
        {
            Destroy();
        }
    }
    else if (BulletType == EBulletType::EnemyNormal)
    {
        UpdatePosX(-Speed * DeltaTime);
        if (BattleLevel && BattleLevel->CheckHitHero(this))
        {
            Destroy();
        }
    }

    if (!IsDestroy())
    {
        if (GetPosX() < -GetActorWidth()/2 || GetPosX() > Config::WinWidth +  GetActorWidth()/2)
        {
            Destroy();
        }
    }
}
