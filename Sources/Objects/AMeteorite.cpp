#include "AMeteorite.h"

#include "ABullet.h"
#include "AHero.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/UBattleLevel.h"

AMeteorite* AMeteorite::CreateAMeteorite(EMeteoriteType Type)
{
    if (AMeteorite* Meteorite = CreateActor<AMeteorite>(GetImageNameByType(Type)))
    {
        Meteorite->MeteoriteType = Type;
        return Meteorite;
    }
    return nullptr;
}

void AMeteorite::Init()
{
    AActor::Init();
    
    SetRotation(Math::Random(0,360));
    SetPosition(Config::WinWidth + Math::Random(200, 400), Math::Random(100, Config::WinHeight - 100));
}

void AMeteorite::BeginPlay()
{
    APawn::BeginPlay();

    switch (MeteoriteType)
    {
    case EMeteoriteType::Small:
        MeteoriteSpeed = Config::MeteoriteSpeed * Math::Random(1.4,1.8);
        HP = Config::MeteoriteHP;
        SetScale(1.5);
        break;
    case EMeteoriteType::Middle:
        MeteoriteSpeed = Config::MeteoriteSpeed * Math::Random(1,1.3);
        HP = Config::MeteoriteHP * 5;
        SetScale(1.2);
        break;
    case EMeteoriteType::Big:
        MeteoriteSpeed = Config::MeteoriteSpeed * Math::Random(0.8,1.1);
        HP = Config::MeteoriteHP * 10;
        break;
    default: ;
    }
}

void AMeteorite::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    UpdatePosX(-MeteoriteSpeed * DeltaTime);

    if (MeteoriteType == EMeteoriteType::Small)
    {
        SetRotation(Transform.Rotation + 100 * DeltaTime);
    }
    else if (MeteoriteType == EMeteoriteType::Middle)
    {
        SetRotation(Transform.Rotation + 50 * DeltaTime);
    }
    else if (MeteoriteType == EMeteoriteType::Big)
    {
        SetRotation(Transform.Rotation + 30 * DeltaTime);
    }
    
    CheckHitHero();

    if (!IsDestroy())
    {
        if (GetPosX() < -GetActorWidth() / 2)
        {
            Destroy();
        }
    }
}

void AMeteorite::OnHitCollision(AActor* Actor)
{
    AActor::OnHitCollision(Actor);

    if (ABullet* Bullet = dynamic_cast<ABullet*>(Actor))
    {
        if (Bullet->GetBulletType() == EBulletType::HeroNormal )
        {
            FDamage Damage(Bullet->GetDamage(), EDamageType::Hit,Bullet );
            TakeDamage(Damage);
        }
    }
}

void AMeteorite::OnHpChanged()
{
    APawn::OnHpChanged();
    if (HP == 0)
    {
        UBattleLevel* Level = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel());
        if (Level)
        {
            Level->OnMeteoriteDestroy(this);
            Destroy();
        }
    }
}

void AMeteorite::CheckHitHero()
{
    UBattleLevel* BattleLevel = dynamic_cast<UBattleLevel*>(TGame::GetCurrentLevel());
    if ( BattleLevel && BattleLevel->CheckHitHero(this))
    {
        if (MeteoriteType == EMeteoriteType::Small)
        {
            Destroy();
        }
    }
}

std::string AMeteorite::GetImageNameByType(EMeteoriteType Type)
{
    if (Type == EMeteoriteType::Big)
    {
        return "Meteorite_4";
    }

    if (Type == EMeteoriteType::Middle)
    {
        if (Math::Random(1,100) > 50)
        {
            return "Meteorite_1";
        }
        else
        {
            return "Meteorite_2" ;
        } 
    }
    return "Meteorite_3";
}
