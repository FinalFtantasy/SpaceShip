#pragma once
#include "../UObject.h"

class ABackground : public UObject
{
public:
    static ABackground* CreateBackground();
    
    virtual void Update(float DeltaTime) override;
    virtual void Draw() const override;
    virtual void EndPlay() override;

private:
    bool Init();
    
    class AActor* BG1;
    class AActor* BG2;
};
