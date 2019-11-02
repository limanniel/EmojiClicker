#pragma once
#include "Scene.h"
using namespace S2D;
constexpr int AmountOfUpgrades = 9;

class EmojiClicker : public Scene
{
private:
	// Private Structs
	struct Button {
		Texture2D* texture;
		Rect* source;
		Rect* position;
		bool triggered;
	};

	struct Upgrade {
		Texture2D* texture;
		Rect* source;
		Rect* position;
		int upgradeID;
		int cost;
		bool triggered;
	};

private:
	// BG
	Texture2D* _BGTexture;
	Rect* _BGSource;
	Vector2* _BGPosition;

	// Clicker
	Button* _Clicker;
	int _ClickValue;
	SoundEffect* _ClickSound;

	// Evolve Button
	Button* _Evolve;
	int _EvolveCost;

	// Upgrades
	Upgrade* _Upgrades[AmountOfUpgrades];
	Texture2D* _UpgradesTextureSheet;

	// Exit
	Button* _Exit;

	// Misc
	int _scoreDelay;
	Vector2* _myScorePosition;
	Vector2* _CostInfoPosition;
	std::stringstream costInfoStream;
	Rect* _mousePosition;

private:
	bool boxCollisionCheck(Rect* obj1, Rect* obj2);
	void updateUpgrade(Input::MouseState* mouseState, Upgrade* upgrade);
	void updateClicker(Input::MouseState* mouseState, Button* clicker);
	void updateEvolve(Input::MouseState* mouseState, Button* evolve);
	void updateExit(Input::MouseState* mouseState, Button* exit);
	void applyUpgradeEffect(Upgrade* upgrade, int elapsedTime);
	void displayUpgradeCostInfo(Upgrade* upgrade);
	void displayEvolveCostInfo(Button* evolve);

public:
	EmojiClicker();
	virtual ~EmojiClicker();

	void virtual Load();
	void virtual Update(int elapsedTime);
	void virtual Draw(int elapsedTime);
};