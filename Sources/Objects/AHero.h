#pragma once

#include "APawn.h"
#include "../GlobalConfig.h"

class AMeteorite;

class AHero : public APawn
{
public:
    AHero();
    static AHero* Get();

    virtual void Init() override;

    virtual void Update(const float DeltaTime) override;

    void UpdateInput(const float DeltaTime);

    void Fire();

    virtual void TakeDamage(FDamage& damage) override;
    virtual void OnHpChanged() override;

    void OnHitCollision(AActor* Actor) override;
    void Reset();
    void ResetInput();

    void Upgrade();
    
private:
    static AHero* Hero;
    
    int8 MoveX;
    int8 MoveY;

    uint8 Level;
    
    float Damage;
    float BulletSpeed;

    float ConfigFireCD;
    float FireCD;

    bool bOpenFire;
};
