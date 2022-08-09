#pragma once
#include "APawn.h"
#include "../GlobalConfig.h"

enum class EEnemyType : uint8
{
    Normal,
    Elite,
    Boss,
};

class AEnemy : public APawn
{
public:

    static AEnemy* CreateEnemy(EEnemyType EnemyType, uint32 Level = 1);

    virtual  void Init() override;
    virtual  void BeginPlay() override;
    virtual void Update(const float DeltaTime) override;

    virtual  void OnHitCollision(AActor* Actor) override;
    static std::string GetImageNameByType(EEnemyType Type);

    void UpdateNormal(const float DeltaTime);
    void UpdateElite(const float DeltaTime);
    void UpdateBoss(const float DeltaTime);

    virtual void OnHpChanged() override;

    void Fire();

    inline EEnemyType GetEnemyType() const {return EnemyType;}
    inline void SetCanFire(bool fire) { CanFire = fire;}

    void RefreshTargetPos();

private:
    EEnemyType EnemyType;

    uint32 TargetPosX;
    uint32 TargetPosY;
    float StayDuration;
    uint32 Level;
    uint32 ConfigFireCD;

    bool CanFire;
    float FireCD;
};
