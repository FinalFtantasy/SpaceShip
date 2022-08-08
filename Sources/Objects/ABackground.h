#pragma once

#include "AActor.h"

class ABackground : public AActor
{
public:
    ABackground();

    virtual void Init() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Draw() const override;
    virtual void EndPlay() override;

    inline void StartMoveMoon() { bMoveMoon = true;}
    void ResetMoon();

private:
    void SpawnMoon();
    
    AActor* BG1;
    AActor* BG2;

    AActor* Moon;

    float Speed;
    float MoonSpeed;

    bool bMoveMoon;
};
