#pragma once
#include "AActor.h"

class AFont;

class ASettmentUI : public AActor
{
public:
    virtual void Init() override;
    virtual void Update(const float DeltaTime) override;
    virtual void Draw() const override;
    virtual void EndPlay() override;
private:
    AFont* FInfo; 
    AFont* FTime;
    AFont* FScore;
    AFont* Tips;
};
