#pragma once

struct FTransform
{
    FTransform():PosX(0.f), PosY(0.f), Rotation(0.f), Scale(1.f){}
    FTransform(const float InPosX, const float InPosY, const float InRotation = 0.f, const float InScale = 1.f): PosX(InPosX), PosY(InPosY), Rotation(InRotation), Scale(InScale) {}
    float PosX;
    float PosY;
    float Rotation;
    float Scale;
};

class UObject
{
public:
    UObject();

    virtual void Destroy();
    virtual ~UObject();

    virtual void Update(const float DeltaTime) = 0;

    virtual void Init();
    
    virtual void BeginPlay();

    virtual bool ShouldUpdate();

    inline bool IsDestroy() const { return bDestroy; }
    inline bool IsHasBegunPlay() const {return bHasBegunPlay; }

    inline void SetPosX(const float InPosX) { Transform.PosX = InPosX; }
    inline void SetPosY(const float InPosY) { Transform.PosY = InPosY; }

    inline float GetPosX() const { return Transform.PosX; }
    inline float GetPosY() const { return Transform.PosY; }

    inline void UpdatePosX(const float DeltaPosX) { Transform.PosX += DeltaPosX; }
    inline void UpdatePosY(const float DeltaPosY) { Transform.PosY += DeltaPosY; }
    
    inline void SetPosition(const float InPosX, const float InPosY) { Transform.PosX = InPosX; Transform.PosY = InPosY;}
    inline void SetScale(const float InScale) { Transform.Scale = InScale; }
    inline void SetRotation(const float InRotation) {Transform.Rotation = InRotation; }
    
    inline const FTransform& GetTransform() const { return Transform; }

protected:
    FTransform Transform;
    
private:
    virtual void EndPlay() = 0;

    bool bNeedUpdate;
    
    bool bDestroy;

    bool bHasBegunPlay;
};

