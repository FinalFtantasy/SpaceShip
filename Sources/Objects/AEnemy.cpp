#include "AEnemy.h"

#include "ABullet.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/UBattleLevel.h"

AEnemy* AEnemy::CreateEnemy(EEnemyType EnemyType,uint32 Level)
{
    if (AEnemy* Enemy = CreateActor<AEnemy>(GetImageNameByType(EnemyType)))
    {
        Enemy->EnemyType = EnemyType;
        Enemy->Level = Level;
        Enemy->BeginPlay();
        return Enemy;
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
    bMove = true;
    
    if (EnemyType == EEnemyType::Boss)
    {
        ConfigFireCD = Config::EnemyEliteFireCD  * (1 - (Level - 1.f) * 0.15f);
        BulletSpeed = Config::EnemyBulletSpeed + (Level - 1) * 90;

        Speed = Config::EnemyBossSpeed * Level;
        HP = Config::EnemyBossHP * (Level + 1) * 0.5;
        SetRotation(180);
        SetPosition(Config::WinWidth + Math::Random(200, 400), Math::Random(100, Config::WinHeight - 100));
        CanFire = true;
        RefreshTargetPos();
    }
    else if (EnemyType == EEnemyType::Elite)
    {
        ConfigFireCD = Config::EnemyEliteFireCD  * (1 - (Level - 1.f) * 0.1f);
        BulletSpeed = Config::EnemyBulletSpeed + (Level - 1) * 80;
        
        Speed = Config::EnemyEliteSpeed + (Level - 1) * 50;
        HP = Config::EnemyEliteHP * (Level + 1) * 0.5;
    }
    else if (EnemyType == EEnemyType::Normal)
    {
        Speed = Config::EnemyNormalSpeed +  (Level - 1) * 80;
        HP = Config::EnemyNormalHP * Level;
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
        if ( 0 < GetPosX() && GetPosX() < Config::WinWidth && FireCD > ConfigFireCD)
        {
            Fire();
        }
    }
    UpdateNormal(DeltaTime);
}

void AEnemy::UpdateBoss(const float DeltaTime)
{
    if(bMove)
    {
        bMove = false;
        float DSpeed = Config::EnemyBossSpeed;
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
            bMove = true;
        }
        else
        {
            SetPosX(TargetPosX);
        }
        
        if (abs(GetPosY() - TargetPosY) > Config::EnemyBossSpeed)
        {
            if (GetPosY() < TargetPosY)
            {
                UpdatePosY(DSpeed);
            }
            else
            {
                UpdatePosY(-DSpeed);
            }
            bMove = true;
        }
        else
        {
            SetPosY(TargetPosY);
        }
    }
    else
    {
        if (StayDuration > Config::EnemyBossStayTime)
        {
            RefreshTargetPos();
            bMove = true;
            StayDuration = 0.f;
        }
        else
        {
            StayDuration += DeltaTime;
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
    Bullet->SetSpeed(BulletSpeed);
}

void AEnemy::RefreshTargetPos()
{
    TargetPosX = Math::Floor(Math::Random(Config::WinWidth/2 + 200 , Config::WinWidth - 150));
    TargetPosY = Math::Floor(Math::Random( 150 , Config::WinHeight - 150));
}
