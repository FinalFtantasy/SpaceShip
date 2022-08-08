#pragma once
#include "AActor.h"

class AItem : public AActor
{
public:
    void Init() override;
    void Update(const float DeltaTime) override;

private:
    float Speed;
};
