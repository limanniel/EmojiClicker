#include "EmojiClicker.h"

EmojiClicker::EmojiClicker()
{
	// Misc
	_scoreDelay = 2500;

	// Clicker
	_Clicker = new Button();
	_Clicker->triggered = false;
	_ClickValue = 1;

	// Evolve
	_Evolve = new Button();
	_Evolve->triggered = false;
	_EvolveCost = 80;

	// Exit
	_Exit = new Button();
	_Exit->triggered = false;

	// Upgrades
	int cost = 5;
	int initialID = 1;
	for (int i = 0; i < AmountOfUpgrades; i++)
	{
		_Upgrades[i] = new Upgrade();
		_Upgrades[i]->triggered = false;
		_Upgrades[i]->cost = cost;
		_Upgrades[i]->upgradeID = initialID;
		cost *= 2;
		initialID++;
	}
}

EmojiClicker::~EmojiClicker()
{
	// BG
	delete _BGTexture;
	delete _BGSource;
	delete _BGPosition;

	// Clicker
	delete _Clicker->texture;
	delete _Clicker->source;
	delete _Clicker->position;
	delete _Clicker;

	// Evolve
	delete _Evolve->texture;
	delete _Evolve->source;
	delete _Evolve->position;
	delete _Evolve;

	// Exit
	delete _Exit->texture;
	delete _Exit->source;
	delete _Exit->position;
	delete _Exit;

	// Upgrades
	delete _UpgradesTextureSheet;
	for (int i = 0; i < AmountOfUpgrades; i++)
	{
		delete _Upgrades[i]->texture;
		delete _Upgrades[i]->source;
		delete _Upgrades[i]->position;
		delete _Upgrades[i];
	}
	delete[] _Upgrades;

	// Misc
	delete _mousePosition;
	delete _myScorePosition;
	delete _CostInfoPosition;
}

void EmojiClicker::Load()
{
	// BG
	_BGTexture = new Texture2D();
	_BGTexture->Load("Textures/EmojiClicker/EmojiClickerBG.png", false);
	_BGSource = new Rect(0.0f, 0.0f, 800, 800);
	_BGPosition = new Vector2(0.0f, 0.0f);

	// Clicker
	_Clicker->texture = new Texture2D();
	_Clicker->texture->Load("Textures/EmojiClicker/EmojiClickerSpriteSheet.png", false);
	_Clicker->source = new Rect(0.0f, 0.0f, 128, 128);
	_Clicker->position = new Rect(336.0f, 336.0f, 128, 128);
	_ClickSound = new SoundEffect();
	_ClickSound->Load("Sounds/click.wav");

	// Evolve
	_Evolve->texture = new Texture2D();
	_Evolve->texture->Load("Textures/EmojiClicker/EmojiClickerEvolve.png", false);
	_Evolve->source = new Rect(0.0f, 0.0f, 270, 100);
	_Evolve->position = new Rect(265.0f, 605.0f, 270, 100);

	// Exit
	_Exit->texture = new Texture2D();
	_Exit->texture->Load("Textures/EmojiClicker/EmojiClickerExit.png", false);
	_Exit->source = new Rect(0.0f, 0.0f, 270, 100);
	_Exit->position = new Rect(20.0f, 605.0f, 135, 100);

	// Upgrades
	_UpgradesTextureSheet = new Texture2D();
	_UpgradesTextureSheet->Load("Textures/EmojiClicker/EmojiClickerUpgradesSheet.png", false);

	for (int i = 0; i < AmountOfUpgrades; i++)
	{
		_Upgrades[i]->texture = _UpgradesTextureSheet;
		_Upgrades[i]->source = new Rect(0.0f, (i * 128), 128, 128);
	}
	_Upgrades[0]->position = new Rect(538.0f, 286.0f, 64, 64);
	_Upgrades[1]->position = new Rect(633.0f, 286.0f, 64, 64);
	_Upgrades[2]->position = new Rect(728.0f, 286.0f, 64, 64);
	_Upgrades[3]->position = new Rect(538.0f, 370.0f, 64, 64);
	_Upgrades[4]->position = new Rect(633.0f, 370.0f, 64, 64);
	_Upgrades[5]->position = new Rect(728.0f, 370.0f, 64, 64);
	_Upgrades[6]->position = new Rect(538.0f, 455.0f, 64, 64);
	_Upgrades[7]->position = new Rect(633.0f, 455.0f, 64, 64);
	_Upgrades[8]->position = new Rect(728.0f, 455.0f, 64, 64);

	_mousePosition = new Rect(0.0f, 0.0f, 6, 6);
	_CostInfoPosition = new Vector2(198.0f, 600.0f);
	_myScorePosition = new Vector2(100.0f, 240.0f);

	// Flag for Game Manager
	_contentLoaded_ = true;

}

void EmojiClicker::Update(int elapsedTime)
{
	// Get and store mouse state + update cursor's position
	Input::MouseState* mouseState = Input::Mouse::GetState();
	_mousePosition->X = mouseState->X;
	_mousePosition->Y = mouseState->Y;

	updateClicker(mouseState, _Clicker);
	updateEvolve(mouseState, _Evolve);
	updateExit(mouseState, _Exit);
	for (int i = 0; i < AmountOfUpgrades; i++)
	{
		updateUpgrade(mouseState, _Upgrades[i]);
		if (_Upgrades[i]->triggered) {
			applyUpgradeEffect(_Upgrades[i], elapsedTime);
		}
	}
}

void EmojiClicker::Draw(int elapsedTime)
{
	SpriteBatch::Draw(_BGTexture, _BGPosition, _BGSource);
	SpriteBatch::Draw(_Clicker->texture, _Clicker->position, _Clicker->source);
	SpriteBatch::Draw(_Evolve->texture, _Evolve->position, _Evolve->source);
	SpriteBatch::Draw(_Exit->texture, _Exit->position, _Exit->source);

	for (int i = 0; i < AmountOfUpgrades; i++)
	{
		SpriteBatch::Draw(_Upgrades[i]->texture, _Upgrades[i]->position, _Upgrades[i]->source);
		displayUpgradeCostInfo(_Upgrades[i]);
	}

	// Draw strings
	displayEvolveCostInfo(_Evolve);
}

bool EmojiClicker::boxCollisionCheck(Rect* obj1, Rect* obj2)
{
	if (obj1->Intersects(*obj2)) {
		return true;
	}
	return false;
}

void EmojiClicker::updateClicker(Input::MouseState* mouseState, Button* clicker)
{
	// Detect if mouse is over clicker
	if (boxCollisionCheck(_mousePosition, clicker->position)) {
		// Update Score if mouse over clicker was detcted and clicked
		if (mouseState->LeftButton == Input::ButtonState::PRESSED && !clicker->triggered) {
			Audio::Play(_ClickSound);
			clicker->source->X = 128;
			_scoreManager_->updateScore(_ClickValue);
			clicker->triggered = true;
		}
		// When button is released go to initial state
		if (mouseState->LeftButton == Input::ButtonState::RELEASED) {
			clicker->source->X = 0;
			clicker->triggered = false;
		}
	}
}

void EmojiClicker::updateUpgrade(Input::MouseState* mouseState, Upgrade* upgrade)
{
	// Detect if cursor is over upgrade and wasn't triggered already
	if (boxCollisionCheck(_mousePosition, upgrade->position) && !upgrade->triggered) {
		upgrade->source->X = 128;
		// If can afford, change state of the upgrade
		if (mouseState->LeftButton == Input::ButtonState::PRESSED && _scoreManager_->getScore() >= upgrade->cost) {
			upgrade->source->X = 256;
			upgrade->triggered = true;
			_scoreManager_->updateScore(-upgrade->cost);
		}
	}
	// Return to grayed out state if wasn't bought and cursor isn't over it anymore
	else if (!upgrade->triggered){
		upgrade->source->X = 0;
	}
}

void EmojiClicker::displayUpgradeCostInfo(Upgrade* upgrade)
{
	// If cursor over upgrade, display according info depending on score status
	if (boxCollisionCheck(_mousePosition, upgrade->position) && !upgrade->triggered) {

		if (_scoreManager_->getScore() >= upgrade->cost) {
			costInfoStream << "You can purchase this upgrade!";
			SpriteBatch::DrawString(costInfoStream.str().c_str(), _CostInfoPosition, Color::Yellow);
		}

		if (_scoreManager_->getScore() < upgrade->cost) {
			costInfoStream << "Cannot afford this upgrade, you need " << (upgrade->cost - _scoreManager_->getScore()) << " more points!";
			SpriteBatch::DrawString(costInfoStream.str().c_str(), _CostInfoPosition, Color::Red);
		}
	}
	// Clear Stringstream once mouse is not over upgrade anymore
	else {
		costInfoStream.str("");
	}
}

void EmojiClicker::updateEvolve(Input::MouseState* mouseState, Button* evolve)
{
	if (boxCollisionCheck(_mousePosition, evolve->position)) {
		evolve->source->X = evolve->source->Width * 1;
		if (mouseState->LeftButton == Input::ButtonState::PRESSED && _scoreManager_->getScore() >= _EvolveCost && !evolve->triggered) {
			evolve->triggered = true;
			_scoreManager_->updateScore(-_EvolveCost);
			if (_Clicker->source->Y <= 1024) {
				_Clicker->source->Y += 128;
			}
			_ClickValue += 1;
			_scoreManager_->addCollectiblePickUpValue(1);
			_EvolveCost *= 3;
		}
		if (evolve->triggered && mouseState->LeftButton == Input::ButtonState::RELEASED) {
			evolve->triggered = false;
		}
	}
	else {
		evolve->source->X = evolve->source->Width * 0;
	}
}

void EmojiClicker::displayEvolveCostInfo(Button* evolve)
{
	// If cursor over evolve, display according info depending on score status
	if (boxCollisionCheck(_mousePosition, evolve->position)) {
		if (_scoreManager_->getScore() >= _EvolveCost) {
			costInfoStream << "You can evolve!";
			SpriteBatch::DrawString(costInfoStream.str().c_str(), _CostInfoPosition, Color::Yellow);
		}

		if (_scoreManager_->getScore() < _EvolveCost) {
			costInfoStream << "Cannot afford evolution, you need " << (_EvolveCost - _scoreManager_->getScore()) << " more points!";
			SpriteBatch::DrawString(costInfoStream.str().c_str(), _CostInfoPosition, Color::Red);
		}
	}
	// Clear Stringstream once mosue is not over evolve anymore
	else {
		costInfoStream.str("");
	}
}

void EmojiClicker::applyUpgradeEffect(Upgrade* upgrade, int elapsedTime)
{
	switch (upgrade->upgradeID)
	{
	// Activate Automatic Score Generation
	case 1:
		_scoreManager_->automaticScore = true;
		break;
	// Speed Up Automatic Score Generation
	case 2:
		_scoreManager_->automaticInitialScoreDelay = 1800;
		break;
	// Speed Up EmojiMan Movement Speed
	case 3:
		_scoreManager_->setEmojiManMovementSpeed(0.15f);
		break;
	// Increase amount of points being acquired from automatic generation
	case 4:
		_scoreManager_->upgradeScoreBonus = 2;
		break;
	// Further Speed Up Automatic Score Generation
	case 5:
		_scoreManager_->automaticInitialScoreDelay = 1400;
		break;
	// Speeds up spawn of munchies in emojiMan
	case 6:
		_scoreManager_->setInitialMunchieSpawnDelayTime(1600);
		break;
	// Increase amount of points being acquired from automatic generation
	case 7:
		_scoreManager_->upgradeScoreBonus = 3;
		break;
	// Last Speed Up Automatic Score Generation
	case 8:
		_scoreManager_->automaticInitialScoreDelay = 1000;
		break;
	// WIN GAME
	case 9:
		break;

	default:
		break;
	}
}

void EmojiClicker::updateExit(Input::MouseState* mouseState, Button* exit)
{
	if (boxCollisionCheck(_mousePosition, exit->position)) {
		exit->source->X = exit->source->Width * 1;
		if (mouseState->LeftButton == Input::ButtonState::PRESSED && !exit->triggered) {
			exit->triggered = true;
			_activeScene_ = EMOJIGAME;
			_reloadScene_ = true;
		}
		if (mouseState->LeftButton == Input::ButtonState::RELEASED && exit->triggered) {
			exit->triggered = false;
		}
	}
	else {
		exit->source->X = exit->source->Width * 0;
	}
}