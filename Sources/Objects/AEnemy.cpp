#include "AEnemy.h"

#include "ABullet.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/UBattleLevel.h"

AEnemy* AEnemy::CreateEnemy(EEnemyType EnemyType)
{
    if (AEnemy* Meteorite = CreateActor<AEnemy>(GetImageNameByType(EnemyType)))
    {
        Meteorite->EnemyType = EnemyType;
        Meteorite->BeginPlay();
        return Meteorite;
    }
    return nullptr;
}

void AEnemy::Init()
{
    APawn::Init();
    CanFire = false;
}

void AEnemy::BeginPlay()
{
    APawn::BeginPlay();
    SetScale(1.5);
    FireCD = 0;

    if (EnemyType == EEnemyType::Boss)
    {
        Speed = Config::EnemyBossSpeed;
        HP = Config::EnemyBossHP;
        SetRotation(180);
        SetPosition(Config::WinWidth + Math::Random(200, 400), Math::Random(100, Config::WinHeight - 100));
        CanFire = true;
        RefreshTargetPos();
    }
    else if (EnemyType == EEnemyType::Elite)
    {
        Speed = Config::EnemyEliteSpeed;
        HP = Config::EnemyEliteHP;
    }
    else if (EnemyType == EEnemyType::Normal)
    {
        Speed = Config::EnemyNormalSpeed;
        HP = Config::EnemyNormalHP;
        SetPosition(Config::WinWidth + Math::Random(200, 400), Math::Random(100, Config::WinHeight - 100));
    }
}

void AEnemy::Update(const float DeltaTime)
{
    if (IsDestroy())
    {
        return;
    }
    APawn::Update(DeltaTime);
    if (EnemyType == EEnemyType::Boss)
    {
        UpdateBoss(DeltaTime);
    }
    else if (EnemyType == EEnemyType::Elite)
    {
        UpdateElite(DeltaTime);
    }
    else if (EnemyType == EEnemyType::Normal)
    {
        UpdateNormal(DeltaTime);
    }
    
    UBattleLevel* BattleLevel = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel());
    if (BattleLevel && BattleLevel->CheckHitHero(this))
    {
        if (EnemyType != EEnemyType::Boss)
        {
            Destroy();
        }
    }
}

void AEnemy::OnHitCollision(AActor* Actor)
{
    if (ABullet* Bullet = dynamic_cast<ABullet*>(Actor))
    {
        FDamage Damage(Bullet->GetDamage(),EDamageType::Hit, Bullet);
        TakeDamage(Damage);
    }
}

std::string AEnemy::GetImageNameByType(EEnemyType Type)
{
    if (Type == EEnemyType::Boss)
    {
        return "Enemy_3";
    }
    else if (Type == EEnemyType::Elite)
    {
        return "Enemy_2";
    }
    return "Enemy_1";
}

void AEnemy::UpdateNormal(const float DeltaTime)
{
    if (EnemyType != EEnemyType::Boss)
    {
        UpdatePosX(-Speed * DeltaTime);
    }

    if (GetPosX() < -GetActorWidth()/2)
    {
        Destroy();
    }
}

void AEnemy::UpdateElite(const float DeltaTime)
{
    if (CanFire )
    {
        FireCD += DeltaTime;
        if ( 0 < GetPosX() && GetPosX() < Config::WinWidth && FireCD > Config::EnemyEliteFireCD)
        {
            Fire();
        }
    }
    UpdateNormal(DeltaTime);
}

void AEnemy::UpdateBoss(const float DeltaTime)
{
    if ( abs(GetPosX() - TargetPosX) < Config::EnemyBossSpeed && abs(GetPosY() - TargetPosY) < Config::EnemyBossSpeed )
    {
        if (StayDuration > Config::EnemyBossStayTime)
        {
            RefreshTargetPos();
            StayDuration = 0.f;
        }
        else
        {
            StayDuration += StayDuration;
        }
    }
    else
    {
        float DSpeed = Config::EnemyBossSpeed * DeltaTime;
        if (abs(GetPosX() - TargetPosX) > Config::EnemyBossSpeed)
        {
            if (GetPosX() < TargetPosX)
            {
                UpdatePosX(DSpeed);
            }
            else
            {
                UpdatePosX(-DSpeed);
            }
        }
        if (abs(GetPosY() - TargetPosY) < Config::EnemyBossSpeed)
        {
            if (GetPosY() < TargetPosY)
            {
                UpdatePosY(DSpeed);
            }
            else
            {
                UpdatePosY(-DSpeed);
            }
        }
    }
    UpdateElite(DeltaTime);
}

void AEnemy::OnHpChanged()
{
    APawn::OnHpChanged();

    if (HP == 0)
    {
        UBattleLevel* BattleLevel = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel());
        if (BattleLevel)
        {
            BattleLevel->OnEnemyDeath(this);
        }
        Destroy();
    }
}

void AEnemy::Fire()
{
    FireCD =0.f;

    ABullet* Bullet = ABullet::CreateBullet(EBulletType::EnemyNormal);
    Bullet->SetPosition(GetPosX() - GetActorWidth()/2 - 10, GetPosY());
}

void AEnemy::RefreshTargetPos()
{
    TargetPosX = Math::Floor(Math::Random(Config::WinWidth/2 + 200 , Config::WinWidth - 150));
    TargetPosY = Math::Floor(Math::Random( 200 , Config::WinHeight - 200));
}
