#pragma once
#include "EmojiMan.h"
#include "MainMenu.h"
#include "EmojiClicker.h"
#include "ScoreManager.h"
// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif
using namespace S2D;

class GameManager : public Game //inherit from game
{
private:
	Scene* currentScene;
	Scene* mainMenuScene;
	Scene* emojiManScene;
	Scene* emojiClickerScene;
	ScoreManager* scoreManager;

	void changeCurrentScene(SceneType scene);

public:
	GameManager(int argc, char* argv[]);
	~GameManager();

	void virtual LoadContent();
	void virtual Update(int elapsedTime);
	void virtual Draw(int elapsedTime);
};