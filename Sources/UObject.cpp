#include "UObject.h"

UObject::UObject(): bDestroy(false), bHasBegunPlay(false)
{
}

void UObject::Destroy()
{
    EndPlay();
}

UObject::~UObject()
{
}

void UObject::BeginPlay()
{
    bHasBegunPlay = true;
}

void UObject::EndPlay()
{
    
}
