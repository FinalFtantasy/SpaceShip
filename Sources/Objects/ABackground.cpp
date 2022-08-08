#include "ABackground.h"

#include "AActor.h"
#include "../GlobalConfig.h"
#include "../GlobalFunctionLibrary.h"

ABackground::ABackground(): BG1(nullptr), BG2(nullptr), Moon(nullptr), Speed(Config::DefaultBGSpeed), MoonSpeed(Config::DefaultMoonSpeed)
{
    bMoveMoon = false;
}

void ABackground::Init()
{
    BG1 = AActor::CreateActor("StarLayer", false);
    BG2 = AActor::CreateActor("StarLayer", false);
    Moon = AActor::CreateActor("Moon", false);
    if( BG1 && BG2 && Moon)
    {
        BG1->SetPosition(Config::WinWidth/2, Config::WinHeight/2);
        BG1->SetScale(1.8f);

        BG2->SetScale(1.8f);
        BG2->SetPosition(Config::WinWidth/2 + BG1->GetActorWidth()/2 + BG2->GetActorWidth()/2, Config::WinHeight/2);

        Moon->SetPosition(Config::WinWidth/3*2, Config::WinHeight/3*2);
        return;
    }
    delete BG1;
    delete BG2;
    delete Moon;
    return;
}

void ABackground::ResetMoon()
{
    bMoveMoon = false;
    Moon->SetRotation(0);
    Moon->SetScale(1);
    Moon->SetPosition(Config::WinWidth/3*2, Config::WinHeight/3*2);
}

void ABackground::SpawnMoon()
{
    float PosX = Math::Random(1000, 3000);
    float PosY = Math::Random(0, Config::WinHeight);
    float Rotation = Math::Random(0, 360);
    float Scale = Math::Random(0.5, 2);
    Moon->SetRotation(Rotation);
    Moon->SetScale(Scale);
    Moon->SetPosition(Moon->GetActorWidth()/2 + Config::WinWidth + PosX, PosY);
}

void ABackground::Update(const float DeltaTime)
{
    // update background position
    const float Distance = DeltaTime * Speed;

    BG1->UpdatePosX(-Distance);
    BG2->UpdatePosX(-Distance);

    const FTransform& BG1Trans = BG1->GetTransform();
    const FTransform& BG2Trans = BG2->GetTransform();
    const uint32 DeltaPos = BG1->GetActorWidth()/2 + BG2->GetActorWidth()/2;
    if (BG1Trans.PosX < -BG1->GetActorWidth()/2)
    {
        BG1->SetPosX(BG2Trans.PosX + DeltaPos);
    }

    if (BG2Trans.PosX < -BG2->GetActorWidth()/2)
    {
        BG2->SetPosX(BG1Trans.PosX + DeltaPos);
    }

    if (bMoveMoon)
    {
        Moon->UpdatePosX(-DeltaTime * MoonSpeed);
        if (Moon->GetTransform().PosX < -Moon->GetActorWidth()/2)
        {
            SpawnMoon();
        }
    }
}

void ABackground::Draw() const
{
    BG1->Draw();
    BG2->Draw();
    Moon->Draw();
}

void ABackground::EndPlay()
{
    BG1->Destroy();
    BG2->Destroy();
    Moon->Destroy();
}


