#include "ULevel.h"

#include "../Objects/AActor.h"
#include "../Objects/ABackground.h"

ULevel::ULevel()
{
    HasBegunPlay = false;
}

void ULevel::UnLoadLevel(ULevel* TargetLevel)
{
    if(TargetLevel)
    {
        TargetLevel->LevelEnd();
    }
}

bool ULevel::InitLevel()
{
    InitBackground();
    return true;
}

void ULevel::LevelBegin()
{
    HasBegunPlay = true;
    
    Background->BeginPlay();
    
    for (AActor* Actor : LevelActors)
    {
        Actor->BeginPlay();
    }
}

void ULevel::LevelEnd()
{
    for (AActor* Actor : LevelActors)
    {
        Actor->Destroy();
    }
}

void ULevel::AddActor(AActor* InActor)
{
    if (InActor)
    {
        LevelActors.push_back(InActor);
    }
}

void ULevel::InitBackground()
{
    Background = ABackground::CreateBackground();
}

void ULevel::LevelUpdate(float DeltaTime)
{
    Background->Update(DeltaTime);

    for (AActor* Actor : LevelActors)
    {
        Actor->Update(DeltaTime);
    }
}

void ULevel::DrawLevel()
{
    Background->Draw();

    for (const AActor* Actor : LevelActors)
    {
        Actor->Draw();
    }
}


