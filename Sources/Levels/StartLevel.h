#pragma once
#include "ULevel.h"

class StartLevel final : public ULevel 
{
public:

    virtual bool InitLevel() override;

    virtual void LevelLogicUpdate(float DeltaTime) override;
    
    virtual void DrawLevel() override;

    virtual void LevelEnd() override;
private:

    class AFont* StartFont; 
};
