#pragma once
#include "AActor.h"

enum class EDamageType : uint8
{
    Collision,
    Hit,
};

struct FDamage
{
    FDamage(const int InDamage, const EDamageType InDamageType, AActor* InCauser)
        : DamageType(InDamageType), Damage(InDamage), Causer(InCauser)
    {
    }

    EDamageType DamageType;
    int Damage;
    AActor* Causer;
};

class APawn : public AActor
{
public:

    inline uint32 GetHP() const { return HP; }
    virtual void TakeDamage(FDamage& damage);
    
protected:

    virtual void OnHpChanged();
    
    int Speed;

    uint32 HP;
};
