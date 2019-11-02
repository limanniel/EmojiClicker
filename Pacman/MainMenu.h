#pragma once
#include "Scene.h"

class MainMenu : public Scene
{
private:
	struct Button {
		Texture2D* texture;
		Rect* source;
		Rect* position;
		bool triggered;
	};

	struct MenuImage {
		Texture2D* texture;
		Rect* source;
		Rect* position;
	};

private:
	Rect* mousePosition;
	SoundEffect* m_BGSound;

	// Menu BG
	MenuImage* m_Background;

	// Title
	MenuImage* m_Title;

	// Buttons
	Button* m_StartGame;
	Button* m_ExitGame;

public:
	MainMenu();
	virtual ~MainMenu();

	void Load();
	void Update(int elapsedTime);
	void Draw(int elapsedTime);
	bool boxCollisionCheck(Rect* obj1Rect, Rect* obj2Rect);
};

