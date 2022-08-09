#include "AFont.h"
#include "AFont.h"

#include "../GlobalFunctionLibrary.h"

AFont* AFont::CreateFont(const std::string& InString, const uint32 FontSize )
{
    if (Simple2D::Font* Font = Tool::CreateFont(FontSize))
    {
        if (const auto tFont = new AFont(Font))
        {
            if (!InString.empty())
            {
                tFont->SetText(InString);
            }
            return tFont;
        }
    }
    return nullptr;
}

void AFont::Draw() const 
{
    if (Font && !IsHide())
    {
        Simple2D::DrawString(Font, Text, Transform.PosX, Transform.PosY, Transform.Rotation, Transform.Scale);
    }
}

void AFont::Update(float DeltaTime)
{
}

void AFont::EndPlay()
{
    if (Font)
    {
        Simple2D::DestroyFont(Font);
    }
}
