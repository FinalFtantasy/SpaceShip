#include "UObject.h"

UObject::UObject(): bDestroy(false), bHasBegunPlay(false)
{
    bNeedUpdate = true;
}

void UObject::Destroy()
{
    EndPlay();
    bDestroy = true;
}

UObject::~UObject()
{
}

void UObject::Init()
{
    bDestroy = false;
    bHasBegunPlay = false;
}

void UObject::BeginPlay()
{
    bHasBegunPlay = true;
}

bool UObject::ShouldUpdate()
{
    return bNeedUpdate && bHasBegunPlay && !bDestroy;
}

void UObject::EndPlay()
{
    
}
