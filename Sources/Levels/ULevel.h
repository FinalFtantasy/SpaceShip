#pragma once
#include <vector>
#include "../GlobalConfig.h"
#include "../Objects/AActor.h"

class AActor;
class ABullet;
enum class EBulletType : uint8;

class ULevel 
{
public:
	ULevel();

	template<typename T>
	static ULevel* LoadLevel()
	{
		T* Object = new T();
		ULevel* Level = dynamic_cast<ULevel*>(Object);
		if (Level && Level->InitLevel())
		{
			return Level;	
		}
		delete Object;
		return nullptr;
	}

	virtual bool InitLevel();
	virtual void LevelBegin();

	void LevelUpdate(float DeltaTime);
	virtual void LevelLogicUpdate(float DeltaTime);
	virtual void DrawLevel();

	static void UnLoadLevel(ULevel* TargetLevel);
	virtual void LevelEnd();

	virtual void OnLevelBattleEnd();

	inline bool IsHasBegunPlay() const { return HasBegunPlay; }

	inline float GetLevelTimeNow() const { return LevelGameTimeNow;}

	virtual void AddActor(class AActor* InActor);
	void AddBullet(class ABullet* InBullet);

	virtual void OnHeroHpChanged();

	void Pause() { bPause = true; }
	void Resume() { bPause = false; }

	template<typename T>
	static void UpdateActors(std::vector<T*>& Actors, float DeltaTime)
	{
		for (AActor* Actor : Actors)
		{
			if (Actor->ShouldUpdate())
			{
				Actor->Update(DeltaTime);
			}
		}
	}

	template<typename T>
	static void DrawActors(const std::vector<T*>& Actors)
	{
		for (AActor* Actor : Actors)
		{
			if (Actor->ShouldDraw())
			{
				Actor->Draw();
			}
		}
	}

	template<typename T>
	static void ClearDestroyedActor(std::vector<T*>& Actors)
	{
		if (Actors.empty())
		{
			return ;
		}
		uint32 j = Actors.size() - 1;
		for (uint32 i = 0 ; i < j ; ++i)
		{
			AActor* Actor = Actors[i];
			if(Actor->IsDestroy())
			{
				AActor* ActorJ = Actors[j];
				if (ActorJ->IsDestroy())
				{
					for (;i < j;--j)
					{
						AActor* ActorTemp = Actors[j];
						if (!ActorTemp->IsDestroy())
						{
							ActorJ = ActorTemp;
							break;
						}
					}
				}
				if (!ActorJ->IsDestroy() && i < j)
				{
					swap(Actors[i], Actors[j]);
				}
				else
				{
					break;
				}
			}
		}
		
		Actors.erase(Actors.begin() + j + 1, Actors.end());
	}

	template<typename T>
	static void CleanActor(std::vector<T*>& Actors)
	{
		for (AActor* Actor : Actors)
		{
			Actor->Destroy();
			delete Actor;
		}
		Actors.clear();
	}
	
protected:
	std::vector<class AActor*> LevelActors;
	std::vector<class ABullet*> Bullets;

	static class ABackground* Background;

	static class AHero* Hero;

	float LevelBeginTime;
	float LevelGameTimeNow;
	
	bool bLevelBattleEnd;
private:
	void InitBackground();
	
	bool HasBegunPlay;

	
	bool bPause;
};
