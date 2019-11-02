#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_Background = new MenuImage;
	m_Title = new MenuImage;

	m_StartGame = new Button;
	m_StartGame->triggered = false;

	m_ExitGame = new Button;
	m_ExitGame->triggered = false;

	mousePosition = new Rect(0.0f, 0.0f, 6, 6);
}


MainMenu::~MainMenu()
{
	delete m_Background->texture;
	delete m_Background->source;
	delete m_Background->position;
	delete m_Background;

	delete m_StartGame->texture;
	delete m_StartGame->source;
	delete m_StartGame->position;
	delete m_StartGame;

	delete m_ExitGame->texture;
	delete m_ExitGame->source;
	delete m_ExitGame->position;
	delete m_ExitGame;
	delete m_BGSound;
}

void MainMenu::Load()
{
	// Sound
	m_BGSound = new SoundEffect();
	//m_BGSound->Load("Sounds/menuBG.wav");
	m_BGSound->SetLooping(true);
	Audio::Play(m_BGSound);

	// BG
	m_Background->texture = new Texture2D();
	m_Background->texture->Load("Textures/Menu/m_bg.jpg", false);
	m_Background->source = new Rect(0.0f, 0.0f, 800, 800);
	m_Background->position = new Rect(0.0f, 0.0f, 800, 800);

	// Title
	m_Title->texture = new Texture2D();
	m_Title->texture->Load("Textures/Menu/m_Title.png", false);
	m_Title->source = new Rect(0.0f, 0.0f, 440, 180);
	m_Title->position = new Rect(180.0f, 50.0f, 440, 180);

	// Buttons 
	m_StartGame->texture = new Texture2D();
	m_StartGame->texture->Load("Textures/Menu/m_StartGame.png", false);
	m_StartGame->source = new Rect(0.0f, 0.0f, 400, 120);
	m_StartGame->position = new Rect(200.0f, 280.0f, 400, 120);

	m_ExitGame->texture = new Texture2D();
	m_ExitGame->texture->Load("Textures/Menu/m_ExitGame.png", false);
	m_ExitGame->source = new Rect(0.0f, 0.0f, 400, 120);
	m_ExitGame->position = new Rect(200.0f, 450.0f, 400, 120);

	// Sets flag for Game Manager
	_contentLoaded_ = true;
}

void MainMenu::Update(int elapsedTime)
{
	Input::MouseState* mouseState = Input::Mouse::GetState();
	mousePosition->X = mouseState->X;
	mousePosition->Y = mouseState->Y;

	// Update Menu Buttons
	if (boxCollisionCheck(mousePosition, m_StartGame->position)) {
		m_StartGame->source->Y = 120;
		if (mouseState->LeftButton == Input::ButtonState::PRESSED) {
			_activeScene_ = EMOJIGAME;
			_reloadScene_ = true;
		}
	}
	else {
		m_StartGame->source->Y = 0;
	}

	if (boxCollisionCheck(mousePosition, m_ExitGame->position)) {
		m_ExitGame->source->Y = 120;
		if (mouseState->LeftButton == Input::ButtonState::PRESSED) {
			_activeScene_ = EXIT;
			_reloadScene_ = true;
		}
	}
	else {
		m_ExitGame->source->Y = 0;
	}
}

void MainMenu::Draw(int elapsedTime)
{
	SpriteBatch::Draw(m_Background->texture, m_Background->position, m_Background->source);
	SpriteBatch::Draw(m_Title->texture, m_Title->position, m_Title->source);
	SpriteBatch::Draw(m_StartGame->texture, m_StartGame->position, m_StartGame->source);
	SpriteBatch::Draw(m_ExitGame->texture, m_ExitGame->position, m_ExitGame->source);
}

bool MainMenu::boxCollisionCheck(Rect* obj1Rect, Rect* obj2Rect)
{
	float left1 = obj1Rect->X;
	float left2 = obj2Rect->X;
	float right1 = obj1Rect->X + obj1Rect->Width;
	float right2 = obj2Rect->X + obj2Rect->Width;
	float top1 = obj1Rect->Y;
	float top2 = obj2Rect->Y;
	float bottom1 = obj1Rect->Y + obj1Rect->Height;
	float bottom2 = obj2Rect->Y + obj2Rect->Height;

	if (bottom1 < top2 || top1 > bottom2 || right1 < left2 || left1 > right2)
	{
		return false;
	}
	return true;
}