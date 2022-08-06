#include "AActor.h"
#include "Simple2D.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/ULevel.h"

AActor::AActor(): Image(nullptr)
{
}

AActor::AActor(Simple2D::Image* InImage): Image(InImage)
{
    Simple2D::GetImageSize(InImage, &Width, &Height); 
}

void AActor::Init()
{
}

void AActor::Update(float DeltaTime)
{
    
}

void AActor::Draw() const
{
    Simple2D::DrawImage(Image, Transform.PosX, Transform.PosY, Transform.Rotation, Transform.Scale);
}

void AActor::EndPlay()
{
    if (Image)
    {
        Simple2D::DestroyImage(Image);
    }
}

ULevel* AActor::GetLevel()
{
    return TGame::GetCurrentLevel();
}

AActor* AActor::CreateActor(const std::string& ImageFilePath, bool AddToLevel)
{
    AActor* Actor = nullptr;
    if (ImageFilePath.empty())
    {
       Actor = new AActor();
    }
    else if (Simple2D::Image* Image = Tool::CreateImage(ImageFilePath))
    {
        Actor = new AActor(Image);
    }
    
    if (Actor)
    {
        Actor->Init();
        if (AddToLevel)
        {
            if (ULevel* Level = GetLevel())
            {
                Level->AddActor(Actor);
            }
        }
        
        return Actor;
    }
    
    return nullptr;
}
