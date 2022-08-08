#pragma once
#include "APawn.h"
#include "../GlobalConfig.h"

enum class EMeteoriteType : uint8
{
    Small,
    Middle,
    Big,
};

class AMeteorite : public  APawn
{
public:
    static AMeteorite* CreateAMeteorite(EMeteoriteType Type);

    static std::string GetImageNameByType(EMeteoriteType Type);
    
    virtual void Init() override;
    virtual void BeginPlay() override;
    virtual void Update(const float DeltaTime) override;

    inline void SetSpeed(float InSpeed) {MeteoriteSpeed = InSpeed;}
    inline EMeteoriteType GetMeteoriteType() { return MeteoriteType;}

    virtual void OnHitCollision(AActor* Actor) override;
    virtual void OnHpChanged() override;

private:
    void CheckHitHero();
    
    EMeteoriteType MeteoriteType;
    float MeteoriteSpeed;
};
