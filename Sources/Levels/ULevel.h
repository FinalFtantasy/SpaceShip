#pragma once
#include <vector>

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

	virtual void LevelUpdate(float DeltaTime);
	virtual void DrawLevel();

	static void UnLoadLevel(ULevel* TargetLevel);
	virtual void LevelEnd();

	inline bool IsHasBegunPlay() const { return HasBegunPlay; }

	void AddActor(class AActor* InActor);
	
private:

	void InitBackground();

	std::vector<class AActor*> LevelActors;

	class ABackground* Background;
	
	bool HasBegunPlay;
};
