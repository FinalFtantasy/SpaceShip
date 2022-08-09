#include "AHero.h"

#include "ABullet.h"
#include "AItem.h"
#include "Simple2D.h"
#include "../GlobalConfig.h"
#include "../TGame.h"
#include "AMeteorite.h"
#include "../Levels/UBattleLevel.h"

using namespace Simple2D;

AHero* AHero::Hero = nullptr;

AHero::AHero()
{
    Speed = Config::DefaultHeroSpeed;
    MoveX = 0;
    MoveY = 0;
    ConfigFireCD = Config::DefaultHeroFireCD;
    FireCD = 0.f;
    bOpenFire = false;
    HP = Config::DefaultHeroLife;
}

AHero* AHero::Get()
{
    if (Hero == nullptr)
    {
        Hero = new AHero();
        Hero->Init();
        Hero->SetScale(1.5F);
    }
    return Hero;
}

void AHero::Init()
{
    AActor::Init();

    HP = Config::DefaultHeroLife;
    Speed = Config::DefaultHeroSpeed;
    ConfigFireCD = Config::DefaultHeroFireCD;
    Damage = Config::DefaultHeroBulletDamage;
    BulletSpeed = Config::DefaultBulletSpeed;
    SetImage("Player_1");
    Level = 1;
}

void AHero::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    UpdateInput(DeltaTime);

    if (MoveX != 0)
    {
        UpdatePosX(static_cast<float>(Speed) * DeltaTime * MoveX);
        if (GetPosX() < 0)
        {
            SetPosX(0);
        }
        else if(GetPosX() > Config::WinWidth)
        {
            SetPosX(Config::WinWidth);
        }
    }
    if (MoveY != 0)
    {
        UpdatePosY(static_cast<float>(Speed) * DeltaTime * MoveY);
        if (GetPosY() < 0)
        {
            SetPosY(0);
        }
        else if(GetPosY() > Config::WinHeight)
        {
            SetPosY(Config::WinHeight);
        }
    }

    if (FireCD <= 0.f && bOpenFire)
    {
        Fire();
    }

    if (FireCD > 0)
    {
        FireCD -= DeltaTime;
    }
}

void AHero::Fire()
{
    FireCD = ConfigFireCD;
    ABullet* Bullet = ABullet::CreateBullet(EBulletType::HeroNormal);
    float PosX = Transform.PosX + GetActorWidth()/2 + Bullet->GetActorWidth()/2 + 5;
    Bullet->SetPosition(PosX, Transform.PosY);
    Bullet->SetDamage(Damage);
    Bullet->SetSpeed(BulletSpeed);
}

void AHero::TakeDamage(FDamage& damage)
{
    APawn::TakeDamage(damage);
}

void AHero::OnHpChanged()
{
    APawn::OnHpChanged();

    if( ULevel* Level = TGame::GetCurrentLevel())
    {
        Level->OnHeroHpChanged();
    }
}

void AHero::OnHitCollision(AActor* Actor)
{
    APawn::OnHitCollision(Actor);

    if (AItem* Item = dynamic_cast<AItem*>(Actor))
    {
        Upgrade();
    }
    else
    {
        FDamage STDamage = FDamage(Config::DefaultCollisionDamage, EDamageType::Collision, Actor);
        TakeDamage(STDamage);
    }
}

void AHero::Reset()
{
    Init();
    ResetInput();
}

void AHero::ResetInput()
{
    MoveY = 0;
    MoveX = 0;
    bOpenFire = false;
    FireCD = 0;
}

void AHero::Upgrade()
{
    if (Level < Config::MaxLevel)
    {
        Level += 1;

        if (Level == 2)
        {
            SetImage("Player_2");
            Speed = Config::DefaultHeroSpeed * 1.2;
            Damage = Config::DefaultHeroBulletDamage * 2;
            BulletSpeed = Config::DefaultBulletSpeed * 1.5f;
            ConfigFireCD = Config::DefaultHeroFireCD * 0.5f;
        }
        else if (Level == 3)
        {
            SetImage("Player_3");
            Speed = Config::DefaultHeroSpeed * 1.5f;
            Damage = Config::DefaultHeroBulletDamage * 4;
            BulletSpeed = Config::DefaultBulletSpeed * 2;
            ConfigFireCD = Config::DefaultHeroFireCD * 0.3f;
        }
    }

    if (HP < Config::DefaultHeroLife)
    {
        HP++;
        OnHpChanged();
    }
}

void AHero::UpdateInput(const float DeltaTime)
{
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP_ARROW))
    {
        MoveY = 1;
    }
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN_ARROW))
    {
        MoveY = -1;
    }
    else if ( MoveY > 0 && ( IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP_ARROW)) || MoveY < 0 && (IsKeyReleased(KEY_S) || IsKeyReleased(KEY_DOWN_ARROW)))
    {
        MoveY = 0;
    }

    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT_ARROW))
    {
        MoveX = 1;
    }
    else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT_ARROW))
    {
        MoveX = -1;
    }
    else if ( MoveX > 0 && (IsKeyReleased(KEY_D) || IsKeyReleased(KEY_RIGHT_ARROW)) || MoveX < 0 && (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_LEFT_ARROW)))
    {
        MoveX = 0;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        bOpenFire = true;
    }else if (IsKeyReleased(KEY_SPACE))
    {
        bOpenFire = false;
    }
}
