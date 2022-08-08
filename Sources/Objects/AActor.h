#pragma once
#include "Simple2D.h"
#include "../UObject.h"
#include "../Levels/ULevel.h"

class AActor : public UObject
{
public:
    AActor();
    AActor(Simple2D::Image* InImage);

    virtual void Init() override;

    static AActor* CreateActor(const std::string& ImageFilePath = "", const bool AddToLevel = true)
    {
        return CreateActor<AActor>(ImageFilePath, AddToLevel);
    }

    template<typename T>
    static T* CreateActor(const std::string& ImageFilePath = "", const bool AddToLevel = true)
    {
        T* Object = new T();
        if (AActor* Actor = dynamic_cast<AActor*>(Object))
        {
            if (!ImageFilePath.empty())
            {
                Actor->SetImage(ImageFilePath);
            }
            Actor->Init();
            if (AddToLevel)
            {
                if (ULevel* Level = GetLevel())
                {
                    Level->AddActor(Actor);
                }
            }
            return dynamic_cast<T*>(Actor);
        }

        delete Object;
        return nullptr;
    }

    virtual void Update(float DeltaTime) override;
    virtual void Draw() const;
    virtual void EndPlay() override;

    void GetActorWidthAndHeight(int& OutWidth, int& OutHeight, const bool bOriginal = false) const;

    inline int GetActorWidth(const bool bOriginal = false ) const;
    inline int GetActorHeight(const bool bOriginal = false ) const;

    virtual void OnHitCollision(AActor* Actor);

    inline bool IsHide() const { return bHide; }
    inline void HideInGame() { bHide = true; }
    inline void Show() { bHide = false;}

    bool SetImage(const std::string& FileName);
    bool ShouldDraw();

    static class ULevel* GetLevel();
private:
    Simple2D::Image* Image;

    bool bHide;

    int Width;
    int Height;
};
