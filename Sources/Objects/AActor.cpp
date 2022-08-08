#include "AActor.h"
#include "AActor.h"
#include "Simple2D.h"
#include "../GlobalFunctionLibrary.h"
#include "../TGame.h"
#include "../Levels/ULevel.h"

AActor::AActor(): Image(nullptr), bHide(false)
{
    Width = 0;
    Height = 0;
}

AActor::AActor(Simple2D::Image* InImage): Image(InImage)
{
    Simple2D::GetImageSize(InImage, &Width, &Height); 
}

void AActor::Init()
{
    UObject::Init();
}

void AActor::Update(float DeltaTime)
{
    
}

void AActor::Draw() const
{
    if (Image && !IsHide())
    {
        Simple2D::DrawImage(Image, Transform.PosX, Transform.PosY, Transform.Rotation, Transform.Scale);
    }
}

void AActor::EndPlay()
{
    if (Image)
    {
        Simple2D::DestroyImage(Image);
        Image = nullptr;
    }
}

void AActor::GetActorWidthAndHeight(int& OutWidth, int& OutHeight, const bool bOriginal) const
{
    OutWidth = GetActorWidth(bOriginal);
    OutHeight = GetActorHeight(bOriginal);
}

int AActor::GetActorWidth(const bool bOriginal) const
{
    return static_cast<int>(static_cast<float>(Width) * (bOriginal ? 1 : Transform.Scale));
}

int AActor::GetActorHeight(const bool bOriginal) const
{
    return static_cast<int>(static_cast<float>(Height) * (bOriginal ? 1 : Transform.Scale));
}

void AActor::OnHitCollision(AActor* Actor)
{
}

bool AActor::SetImage(const std::string& FileName)
{
    if (Simple2D::Image* TargetImage = Tool::CreateImage(FileName))
    {
        if (Image)
        {
            Simple2D::DestroyImage(Image);
        }

        Image = TargetImage;

        // update width and height
        Simple2D::GetImageSize(Image, &Width, &Height); 
        return true;
    }

    return false;
}

bool AActor::ShouldDraw()
{
    return IsHasBegunPlay() && !IsDestroy();
}

ULevel* AActor::GetLevel()
{
    return TGame::GetCurrentLevel();
}


