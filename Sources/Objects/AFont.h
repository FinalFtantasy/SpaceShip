#pragma once
#include "AActor.h"
#include "Simple2D.h"
#include "../GlobalConfig.h"

class AFont : public AActor
{
public:
    AFont() = default;
    AFont(Simple2D::Font* InFont) : Font(InFont) {}
    static AFont* CreateFont(const std::string& InString = "", const uint32 FontSize = Config::FontSize);

    inline void SetText(const std::string& InText) { Text = InText; }

    virtual void Draw() const override;
    virtual void Update(float DeltaTime) override;
    virtual void EndPlay() override;

private:
    Simple2D::Font* Font;

    std::string Text;
};
