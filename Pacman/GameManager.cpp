#include "GameManager.h"

GameManager::GameManager(int argc, char* argv[]) : Game(argc, argv)
{
	// Create scenes for different Game States to flip through on the heap
	scoreManager = new ScoreManager;
	mainMenuScene = new MainMenu;
	emojiManScene = new EmojiMan;
	emojiClickerScene = new EmojiClicker;

	// Current Game State
	currentScene = mainMenuScene;

	//Initialise important Game aspects
	Graphics::Initialise(argc, argv, this, 800, 800, false, 500, 300, "EmojiMan", 60);
	Audio::Initialise();
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

GameManager::~GameManager()
{
	currentScene = nullptr;
	delete mainMenuScene;
	delete emojiManScene;
	delete emojiClickerScene;
	delete scoreManager;
}

void GameManager::LoadContent() 
{
	currentScene->setScoreManager(scoreManager);
	currentScene->Load();
}

void GameManager::Update(int elapsedTime)
{
	// Invoke scene change
	if (currentScene->getReloadScene()) {
		changeCurrentScene(currentScene->getActiveScene());
	}

	currentScene->Update(elapsedTime);
}

void GameManager::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw();

	currentScene->Draw(elapsedTime);

	// Prevents Drawing Score in the MainMenu
	if (currentScene != mainMenuScene) {
		scoreManager->automaticScoreGatherer(elapsedTime);
		scoreManager->drawScore();
	}

	SpriteBatch::EndDraw();
}

void GameManager::changeCurrentScene(SceneType scene)
{
	currentScene->setReloadScene(false);

	switch (scene)
	{
	case MENU:
		currentScene = mainMenuScene;
		break;
	case EMOJIGAME:
		currentScene = emojiManScene;
		break;
	case EMOJICLICKER:
		currentScene = emojiClickerScene;
		break;
	case EXIT:
		Audio::Destroy();
		Input::Destroy();
		Graphics::Destroy();
		
	default:
		break;
	};

	// To make sure content for each scene is being loaded only once!
	if (!currentScene->getContentLoaded()) {
		LoadContent();
	}
}