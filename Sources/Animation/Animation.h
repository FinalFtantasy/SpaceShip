#pragma once

class UObject;

class Animation 
{
public:

    static Animation* CreateAnimation(UObject* Target);
    
    virtual void Update(const float DeltaTime) = 0;
    
protected:
    UObject* Target; 
    
};
