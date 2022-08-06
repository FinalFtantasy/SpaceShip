#include "ABackground.h"

#include "AActor.h"
#include "../GlobalConfig.h"

ABackground* ABackground::CreateBackground()
{
    if (auto Background = new ABackground())
    {
        if (Background->Init())
        {
            return Background;
        }
        delete Background;
    }
    return nullptr;
}

bool ABackground::Init()
{
    BG1 = AActor::CreateActor("StarLayer", false);
    BG2 = AActor::CreateActor("Moon", false);
    if( BG1 && BG2)
    {
        BG1->SetPosition(Config::WinWidth/2, Config::WinHeight/2);
        BG1->SetScale(1.8f);

        BG2->SetPosition(Config::WinWidth/2 + 500, Config::WinHeight/2);
        BG2->SetScale(1.8f);
        
        return true;
    }
    delete BG1;
    delete BG2;
    return false;
}

void ABackground::Update(float DeltaTime)
{
}

void ABackground::Draw() const
{
    BG1->Draw();
    BG2->Draw();
}

void ABackground::EndPlay()
{
}


