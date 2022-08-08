#include "AExplode.h"

void AExplode::Init()
{
    AActor::Init();
    Image1 = AActor::CreateActor("Explosion_1",false);
    Image2 = AActor::CreateActor("Explosion_2",false);

    // Image1->SetScale()
}

void AExplode::BeginPlay()
{
    AActor::BeginPlay();
    Image1->BeginPlay();
    Image2->BeginPlay();

    Image2->HideInGame();
    
    Duration = 0.f;
}

void AExplode::Update(const float DeltaTime)
{
    AActor::Update(DeltaTime);

    Duration += DeltaTime;

    Image1->SetPosition(GetPosX(),GetPosY());
    Image2->SetPosition(GetPosX(),GetPosY());

    if (Duration > Config::ExplosionTime/2)
    {
        Image2->Show();
        Image1->HideInGame();
    }
    
    if (Duration > Config::ExplosionTime)
    {
        Destroy();
    }
}

void AExplode::Draw() const
{
    AActor::Draw();

    Image1->Draw();
    Image2->Draw();
}

void AExplode::EndPlay() 
{
    AActor::EndPlay();

    if (Image1)
    {
        Image1->Destroy();
        Image1=nullptr;
    }
    if (Image2)
    {
        Image2->Destroy();
        Image2=nullptr();
    }
}
