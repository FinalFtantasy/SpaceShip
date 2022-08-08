#pragma once
#include "AActor.h"

class AFont;

class ABattleUI : public AActor
{
public:
    virtual void Init() override;
    virtual void BeginPlay() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Draw() const override;
    virtual void EndPlay() override;

    void UpdateHeroLife();

    void UpdateLifePos();
    void UpdateScore(uint32 Score);
private:
    AFont* FLife;
    AFont* FScore;

    std::vector<AActor*> HeroLife;
};
