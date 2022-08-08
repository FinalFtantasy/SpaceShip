#pragma once
#include "ULevel.h"

class AEnemy;
class AMeteorite;
class ABattleUI;
class AExplode;
class AItem;

enum class EMeteoriteType : uint8;

class UBattleLevel : public ULevel
{
public:
    virtual bool InitLevel() override;
    virtual void LevelBegin() override;

    virtual void LevelLogicUpdate(float DeltaTime) override;

    virtual void AddActor(AActor* InActor) override;

    virtual void DrawLevel() override;

    virtual void OnLevelBattleEnd() override;
    virtual void LevelEnd() override;

    virtual void OnHeroHpChanged() override;
    void OnEnemyDeath(AEnemy* Enemy);
    void OnMeteoriteDestroy(AMeteorite* Meteorite);

    inline uint32 GetScore() const { return Score; }

    AEnemy* CheckHitEnemy(AActor* Actor);
    AMeteorite* CheckHitMeteorite(AActor* Bullet);
    bool CheckHitHero(AActor* Actor);

    void ShowExplode(float PosX, float PosY);

private:

#pragma region Meteorite
    void UpdateMeteorite(float DeltaTime);
    void SpawnMeteorite();

    vector<AMeteorite*> Meteorites;
#pragma endregion

#pragma region Enemy
    void UpdateEnemies(float DeltaTime);
    void SpawnEnemies();
    
    vector<AEnemy*> Enemies;
#pragma endregion

#pragma region Enemy
    void UpdateItems(float DeltaTime);
    vector<AItem*> Items;
    float ItemSpawnDuration;
#pragma endregion
    
    vector<AExplode*> Explosions;

    ABattleUI* BattleUI;

    uint32 Score;
    
};
