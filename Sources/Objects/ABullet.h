#pragma once
#include "AActor.h"
#include "../GlobalConfig.h"

enum class EBulletType : uint8
{
    HeroNormal = 0,
    EnemyNormal,
};

class ABullet : public AActor
{
public:
    static ABullet* CreateBullet(const EBulletType InType); 

    virtual void BeginPlay() override;
    
    virtual void Update(const float DeltaTime) override;
    
    inline void SetSpeed(const float InSpeed) { Speed = InSpeed; }
    inline void SetDamage(const float InDamage) { Damage = InDamage; }

    inline float GetSpeed() const { return Speed; }
    inline float GetDamage() const { return Damage; }

    inline EBulletType GetBulletType() const { return BulletType; }

private:
    float Speed;
    float Damage;

    EBulletType BulletType;
};
