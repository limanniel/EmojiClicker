#pragma once
#include "Scene.h"
#include "Munchie.h"
#include "Enemy.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace S2D;
constexpr int AmountOfSpawners = 4;

struct Player {
	Texture2D* texture;
	Rect* sourceRect;
	Rect* positionRect;
	int direction;
	int frame;
	int currentFrameTime;
	bool superMode;
};

struct Spawner {
	Texture2D* texture;
	Rect* source;
	Rect* position;
};

class EmojiMan : public Scene
{
private:
	struct Button {
		Texture2D* texture;
		Rect* source;
		Rect* position;
		bool triggered;
	};

// Private Variables
private:
	// Data to represent Game Board
	Texture2D* _GameBGTexture;
	Rect* _GameBGSourceRect;
	Vector2* _GameBGPosition;

	// Misc Data
	Texture2D* _dimScreenTexture;
	Rect* _dimScreenSource;
	Rect* _mousePosition;
	bool _playerAlive;
	SoundEffect* _BGFX;

	// Lose Screen
	Texture2D* _LoseScreenTextTexture;
	Rect* _LoseScreenTestSourceRect;
	Button* _LoseScreenExitGameButton;

	// Data to represent EmojiMan
	Player* _emojiMan;
	int _emojiSuperFrame;
	int _superModeCounter;
	int _superModeDuration;
	const int cEmojiManFrameTime;
	SoundEffect* _emojiDeathFX;

	// Data to represent Munchies
	Texture2D* _MunchieTexture;
	Rect* _MunchieSourceRect;
	std::vector<Munchie*> _munchiesArray;
	SoundEffect* _munchieFX;
	int _MunchieSpawnDelay;
		// Super Munchie
	Texture2D* _SuperMunchieTexture;
	int _SuperMunchieSpawnDelay;
	bool _SpawnSuperMunchie;

		// Munchie Animation Data
	const int cMunchieFrameTime;
	int _MunchieFrame;
	int _CurrentMunchieFrameTime;

	// Enemy Spawner
	Texture2D* _enemySpawnerTextureSheet;
	Spawner* _mySpawners[AmountOfSpawners];
	int _amountOfEnemiesPresent;
	int _initialSpawnTime;
	int _currentSpawnTime;

	// Enemy
	Texture2D* _enemyTextureSheet;
	Rect* _enemySourceRect;
	Rect* _enemySpawnPoint;
	std::vector<Enemy*> _enemyArray;

	// Position for String
	Vector2* _stringPosition;

	// ClickPad
	Texture2D* _clickPadTexture;
	Rect* _clickPadSource;
	Rect* _clickPadPosition;
	bool _isOnClickPad;

// Private Functions
private:
	void movementHandle(Input::KeyboardState* keyboardState, int elapsedTime);
	void updatePlayerAnimation(int elapsedTime);

	void checkViewportCollision();
	void updateClickPad();
	bool boxCollisionCheck(Rect* obj1Rect, Rect* obj2Rect);

	// Munchies Functions
	void createMunchie(bool superMunchie);
	void updateMunchie();
	void updateMunchieAnimation(int elapsedTime);
	bool checkPositionForNewMunchie(Rect& posRef);

	// Lose Game Functions
	void updateExitButton(Input::MouseState& mouseStateRef);

	// Enemies
	void spawnEnemy();

public:
	EmojiMan();
	virtual ~EmojiMan();

	void Load();
	void Update(int elapsedTime);
	void Draw(int elapsedTime);
};