#pragma once
#include <string>

using namespace std;

#define DEBUG

typedef unsigned int uint32;
typedef unsigned char uint8;
typedef signed char int8;

namespace Config
{
	const string GameName = "SpaceShip";
	constexpr float WinWidth = 1920;
	constexpr float WinHeight = 1080;
	constexpr uint32 TargetFPS = 60;

#ifdef DEBUG
	const string ImagePath = "../../Content/Textures/";
#else
	const string ImagePath = "./Content/Textures/";
#endif

#ifdef DEBUG
	const string FontPath = "../../Content/Fonts/AGENCYB.TTF";
#else
	const string FontPath = "./Content/Fonts/AGENCYB.TTF";
#endif

	constexpr uint32 FontSize = 40;

	constexpr float  DefaultBGSpeed = 100;
	constexpr float DefaultMoonSpeed = 200;

	constexpr float ExplosionTime = 0.4f;

	// Hero
	constexpr int DefaultHeroSpeed = 200;
	constexpr float DefaultHeroFireCD = 0.5;
	constexpr uint8 DefaultHeroLife = 3;
	constexpr uint8 MaxLevel = 3;


	// Bullet
	constexpr float DefaultBulletSpeed = 300;
	constexpr float DefaultHeroBulletDamage = 10;

	// Meteorite
	constexpr uint32 MeteoriteSpawnTimeSmall = 3;
	constexpr uint32 MeteoriteSpawnTimeMiddle = 6;
	constexpr uint32 MeteoriteSpawnTimeBig = 10;
	constexpr uint32 MeteoriteSpeed = 100;
	constexpr uint32 MeteoriteHP = 10;

	// enemy
	constexpr uint32 EnemyNormalSpawnTime = 2;
	constexpr uint32 EnemyNormalSpeed = 250;
	constexpr uint32 EnemyNormalHP = 10;
	constexpr uint32 EnemyNormalScore = 1;

	constexpr uint32 EnemyEliteSpawnTime = 5;
	constexpr uint32 EnemyEliteSpeed = 300;
	constexpr uint32 EnemyEliteHP = 40;
	constexpr uint32 EnemyEliteScore = 10;
	constexpr uint32 EnemyEliteFireCD = 1;
	constexpr uint32 EnemyBulletSpeed = 400;

	constexpr uint32 EnemyBossSpawnTime = 30;
	constexpr uint32 EnemyBossSpeed = 100;
	constexpr uint32 EnemyBossHP = 200;
	constexpr uint32 EnemyBossScore = 50;
	constexpr uint32 EnemyBossFireCD = 3;
	constexpr uint32 EnemyBossStayTime = 4;

	// Damage
	constexpr uint32 DefaultCollisionDamage = 1;

	// item
	constexpr uint32 DefaultItemSpeed = 400;
	constexpr uint32 ConfigItemSpawTime = 30;
}