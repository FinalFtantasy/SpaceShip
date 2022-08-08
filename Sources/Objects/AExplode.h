#pragma once
#include "AActor.h"

class AExplode : public AActor
{
public:
    void Init() override;
    void BeginPlay() override;
    void Update(const float DeltaTime) override;
    void Draw() const override;
    void EndPlay() override;
public:
    AActor* Image1;
    AActor* Image2;

    float Duration;
};
