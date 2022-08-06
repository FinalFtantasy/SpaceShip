#pragma once
#include "Simple2D.h"
#include "../UObject.h"

class AActor : public UObject
{
public:
    AActor();
    AActor(Simple2D::Image* InImage);

    virtual void Init();

    template<typename T>
    inline static T* CreateActor(const std::string& ImageFilePath = "", bool AddToLevel = true)
    {
        return dynamic_cast<T*>(CreateActor(ImageFilePath));
    }
    
    static AActor* CreateActor(const std::string& ImageFilePath = "", bool AddToLevel = true);

    virtual void Update(float DeltaTime) override;
    virtual void Draw() const override;
    virtual void EndPlay() override;

    static class ULevel* GetLevel();
private:
    Simple2D::Image* Image;

    int Width;
    int Height;
};
