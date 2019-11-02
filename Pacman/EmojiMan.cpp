#include "EmojiMan.h"

EmojiMan::EmojiMan() : cEmojiManFrameTime(500), cMunchieFrameTime(200)
{
	srand(time(0));

	// Misc
	_playerAlive = true;

	// Lose Screen
	_LoseScreenExitGameButton = new Button;
	_LoseScreenExitGameButton->triggered = false;

	// Main Character 
	_emojiMan = new Player;
	_emojiMan->direction = 0;
	_emojiMan->frame = 0;
	_emojiMan->currentFrameTime = 0;
		// Super Mode
	_emojiMan->superMode = false;
	_emojiSuperFrame = 2;
	_superModeDuration = 5000;
	_superModeCounter = _superModeDuration;

	// Munchie
	_MunchieFrame = 0;
	_CurrentMunchieFrameTime = 0;
	_SuperMunchieSpawnDelay = 3000;
	_SpawnSuperMunchie = false;

	// Spawner
	_initialSpawnTime = 3500;
	_currentSpawnTime = 0;
	for (int i = 0; i < AmountOfSpawners; i++)
	{
		_mySpawners[i] = new Spawner();
	}

	// Enemies
	_amountOfEnemiesPresent = 0;

	// Click Pad
	_isOnClickPad = false;
}

EmojiMan::~EmojiMan()
{
	// Misc
	delete _dimScreenTexture;
	delete _dimScreenSource;
	delete _mousePosition;
	delete _BGFX;

	// Lose Screen
	delete _LoseScreenTextTexture;
	delete _LoseScreenTestSourceRect;
	delete _LoseScreenExitGameButton->texture;
	delete _LoseScreenExitGameButton->source;
	delete _LoseScreenExitGameButton->position;
	delete _LoseScreenExitGameButton;

	// EmojiMan
	delete _emojiMan->texture;
	delete _emojiMan->sourceRect;
	delete _emojiMan->positionRect;
	delete _emojiDeathFX;
	delete _emojiMan;

	delete _stringPosition;

	// Enemy Spawner
	delete _enemySpawnerTextureSheet;
	delete _enemySourceRect;
	for (int i = 0; i < AmountOfSpawners; i++)
	{
		delete _mySpawners[i]->texture;
		delete _mySpawners[i]->source;
		delete _mySpawners[i]->position;
	}
	delete[] _mySpawners;

	// Enemy
	delete _enemyTextureSheet;
	delete _enemySourceRect;
	if (!_enemyArray.empty()) {
		for (int i = 0; i < _enemyArray.size(); i++)
		{
			delete _enemyArray[i];
		}
	}

	// Munchie
	delete _MunchieTexture;
	delete _SuperMunchieTexture;
	delete _MunchieSourceRect;
	delete _munchieFX;

	// ClickPad
	delete _clickPadTexture;
	delete _clickPadSource;
	delete _clickPadPosition;

	// Game board
	delete _GameBGTexture;
	delete _GameBGSourceRect;
	delete _GameBGPosition;
}

void EmojiMan::Load()
{
	// Load Misc
	_dimScreenTexture = new Texture2D();
	_dimScreenTexture->Load("Textures/dimScreen.png", false);
	_dimScreenSource = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_mousePosition = new Rect(0.0f, 0.0f, 6, 6);

	// Background music
	_BGFX = new SoundEffect();
	_BGFX->Load("Sounds/bg.wav");
	_BGFX->SetGain(0.05f);
	_BGFX->SetLooping(true);
	Audio::Play(_BGFX);

	// Load Lose Screen
	_LoseScreenTextTexture = new Texture2D();
	_LoseScreenTextTexture->Load("Textures/LoseScreen.png", false);
	_LoseScreenTestSourceRect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
		// Lose Screen Buttons
	_LoseScreenExitGameButton->texture = new Texture2D();
	_LoseScreenExitGameButton->texture->Load("Textures/LoseScreenExit.png", false);
	_LoseScreenExitGameButton->source = new Rect(0.0f, 0.0f, 400, 120);
	_LoseScreenExitGameButton->position = new Rect(200.0f, 320.0f, 400, 120);

	// Load Game Board
	_GameBGTexture = new Texture2D();
	_GameBGTexture->Load("Textures/GameBG.png", false);
	_GameBGSourceRect = new Rect(0.0f, 0.0f, 800, 800);
	_GameBGPosition = new Vector2(0.0f, 0.0f);

	// Load EmojiMan
	_emojiMan->texture = new Texture2D();
	_emojiMan->texture->Load("Textures/EmojiManSpriteSheet.png", false);
	_emojiMan->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_emojiMan->positionRect = new Rect(512.0f, 320.0f, 32, 32);
	_emojiDeathFX = new SoundEffect();
	_emojiDeathFX->Load("Sounds/oof.wav");

	// Load Munchie
	_MunchieTexture = new Texture2D();
	_MunchieTexture->Load("Textures/munchie.png", false);
	_MunchieSourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_munchieFX = new SoundEffect();
	_munchieFX->Load("Sounds/munch.wav");
	_munchieFX->SetGain(0.4f);
	_MunchieSpawnDelay = _scoreManager_->getInitialMunchieSpawnDelayTime();
		// Super Munchie
	_SuperMunchieTexture = new Texture2D();
	_SuperMunchieTexture->Load("Textures/SuperMunchie.png", false);

	// Load Spawner
	_enemySpawnerTextureSheet = new Texture2D();
	_enemySpawnerTextureSheet->Load("Textures/GhostSpawnerSpriteSheet.png", false);
	for (int i = 0; i < AmountOfSpawners; i++)
	{
		_mySpawners[i]->texture = _enemySpawnerTextureSheet;
		_mySpawners[i]->source = new Rect((32 * i), 0.0f, 32, 32);
	}
	_mySpawners[0]->position = new Rect((Graphics::GetViewportWidth() / 2) - 6, 0.0f, 32, 32);
	_mySpawners[1]->position = new Rect((Graphics::GetViewportWidth() / 2) - 6, Graphics::GetViewportHeight() - 32, 32, 32);
	_mySpawners[2]->position = new Rect(Graphics::GetViewportWidth() - 32, (Graphics::GetViewportHeight() / 2) - 16, 32, 32);
	_mySpawners[3]->position = new Rect(0.0f, (Graphics::GetViewportHeight() / 2) - 16, 32, 32);

	// Load Enemy
	_enemyTextureSheet = new Texture2D();
	_enemyTextureSheet->Load("Textures/EmojiGhostSpriteSheet.png", false);
	_enemySourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_enemySpawnPoint = new Rect(50.0f, 50.0f, 32, 32);

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	// ClickPad
	_clickPadTexture = new Texture2D();
	_clickPadTexture->Load("Textures/ClickPad.png", false);
	_clickPadSource = new Rect(0.0f, 0.0f, 128, 128);
	_clickPadPosition = new Rect(378.0f, 366.0f, 64, 64);

	// Sets flag for Game Manager
	_contentLoaded_ = true;
}

void EmojiMan::Update(int elapsedTime)
{
	if (_playerAlive) {
		// Gets the current state of the keyboard
		Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
		movementHandle(keyboardState, elapsedTime);

		// Screen wrapping
		checkViewportCollision();

		// Updates
		updatePlayerAnimation(elapsedTime);
		updateMunchieAnimation(elapsedTime);
		updateMunchie();

		// Spawns additional munchies over time
		_MunchieSpawnDelay -= elapsedTime;
		_SuperMunchieSpawnDelay -= elapsedTime;
		if (_MunchieSpawnDelay <= 0) {
			createMunchie(_SpawnSuperMunchie);
			_MunchieSpawnDelay = _scoreManager_->getInitialMunchieSpawnDelayTime();
		}
		else if (_SuperMunchieSpawnDelay <= 0) {
			_SpawnSuperMunchie = true;
			createMunchie(_SpawnSuperMunchie);
			_SuperMunchieSpawnDelay = 25000;
		}

		// Spawns enemies up to AmountOfEnemies over time
		_currentSpawnTime += elapsedTime;
		if (_currentSpawnTime >= _initialSpawnTime) {
			spawnEnemy();
			_amountOfEnemiesPresent++;
			_initialSpawnTime += 3000;
			_currentSpawnTime = 0;
		}

		// Pass player's position into enemy and update it's position + Check if colliding with player
		if (!_enemyArray.empty()) {
			for (size_t i = 0; i < _enemyArray.size(); i++) {
				_enemyArray[i]->updatePosition(*_emojiMan->positionRect);
				// If any of the ghosts overlaps with player, lose game! and not under super mode
				if (boxCollisionCheck(_enemyArray[i]->_enemyPositionRect, _emojiMan->positionRect) && !_emojiMan->superMode) {
					Audio::Play(_emojiDeathFX);
					_playerAlive = false;
				}
				// If super mode is activated, kill the ghost instead
				else if (boxCollisionCheck(_enemyArray[i]->_enemyPositionRect, _emojiMan->positionRect) && _emojiMan->superMode) {
					delete _enemyArray[i];
					_enemyArray.erase(_enemyArray.begin() + i);
					_scoreManager_->updateScore(3);
					_amountOfEnemiesPresent--;
				}
			}
		}

		// Checks whether player is on the click pad, if yes then launch emojiClicker game state
		updateClickPad();
	}

	// If game is lost, get mouse position to work with buttons
	else {
		Input::MouseState* mouseState = Input::Mouse::GetState();
		_mousePosition->X = mouseState->X;
		_mousePosition->Y = mouseState->Y;

		updateExitButton(*mouseState);
	}
}

void EmojiMan::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _emojiMan->positionRect->X << " Y: " << _emojiMan->positionRect->Y;

	SpriteBatch::Draw(_GameBGTexture, _GameBGPosition, _GameBGSourceRect);
	SpriteBatch::Draw(_clickPadTexture, _clickPadPosition, _clickPadSource);
	SpriteBatch::Draw(_emojiMan->texture, _emojiMan->positionRect, _emojiMan->sourceRect); // Draws Pacman

	// Draw munchies from vector array
	for (size_t i = 0; i < _munchiesArray.size(); i++)
	{
		SpriteBatch::Draw(_munchiesArray[i]->_munchieTexture, _munchiesArray[i]->_munchiePosition, _munchiesArray[i]->_munchieSourceRect);
	}

	for (int i = 0; i < AmountOfSpawners; i++)
	{
		SpriteBatch::Draw(_mySpawners[i]->texture, _mySpawners[i]->position, _mySpawners[i]->source);
	}

	/*SpriteBatch::Draw(_enemyArray[0]->_enemyTexture, _enemyArray[0]->_enemyPositionRect, _enemyArray[0]->_enemySourceRect, _enemyArray[0]->_enemyOrigin , 1.0f, _enemyArray[0]->getEnemyRotation(), Color::White, SpriteEffect::NONE);*/
	if (!_enemyArray.empty()) {
		for (size_t i = 0; i < _enemyArray.size(); i++)
		{
			SpriteBatch::Draw(_enemyArray[i]->_enemyTexture, _enemyArray[i]->_enemyPositionRect, _enemyArray[i]->_enemySourceRect);
		}
	}

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);

	//IF GAME LOST
	if (!_playerAlive) {
		SpriteBatch::Draw(_dimScreenTexture, _GameBGPosition, _dimScreenSource);
		SpriteBatch::Draw(_LoseScreenTextTexture, _GameBGPosition, _LoseScreenTestSourceRect);
		SpriteBatch::Draw(_LoseScreenExitGameButton->texture, _LoseScreenExitGameButton->position, _LoseScreenExitGameButton->source);
	}
}

void EmojiMan::movementHandle(Input::KeyboardState* keyboardState, int elapsedTime)
{
	// Change Character moving orientation depending on button pressed
	if (keyboardState->IsKeyDown(Input::Keys::D)) {
		_emojiMan->direction = 0;
	}
	if (keyboardState->IsKeyDown(Input::Keys::S)) {
		_emojiMan->direction = 1;
	}
	if (keyboardState->IsKeyDown(Input::Keys::A)) {
		_emojiMan->direction = 2;
	}
	if (keyboardState->IsKeyDown(Input::Keys::W)) {
		_emojiMan->direction = 3;
	}
	
	// Move Character depending on orientation, speed's stored in _scoreManager_ for convenience 
	switch (_emojiMan->direction) {
	case 0:
		_emojiMan->positionRect->X += _scoreManager_->getEmojiManMovementSpeed() * elapsedTime;
		break;
	case 1:
		_emojiMan->positionRect->Y += _scoreManager_->getEmojiManMovementSpeed() * elapsedTime;
		break;
	case 2:
		_emojiMan->positionRect->X -= _scoreManager_->getEmojiManMovementSpeed() * elapsedTime;
		break;
	case 3:
		_emojiMan->positionRect->Y -= _scoreManager_->getEmojiManMovementSpeed() * elapsedTime;
		break;
	default:
		_emojiMan->positionRect->X += _scoreManager_->getEmojiManMovementSpeed() * elapsedTime;
		break;
	}
}

void EmojiMan::updatePlayerAnimation(int elapsedTime) 
{
	_emojiMan->sourceRect->Y = _emojiMan->sourceRect->Width * _emojiMan->direction;
	_emojiMan->currentFrameTime += elapsedTime;

	// Turn off super mode once counter hits 0
	if (_superModeCounter <= 0) {
		_emojiMan->superMode = false;
	}

	switch (_emojiMan->superMode)
	{
	// Seperate aniamtion behaviour when under super mode effect
	case true:
		_superModeCounter -= elapsedTime;
		if (_emojiMan->currentFrameTime >= cEmojiManFrameTime) {
			_emojiSuperFrame++;
			if (_emojiSuperFrame > 4) {
				_emojiSuperFrame = 2;
			}
			_emojiMan->sourceRect->X = _emojiMan->sourceRect->Width * _emojiSuperFrame;
			_emojiMan->currentFrameTime = 0;
		}
		break;
	// Regular animation behaviour
	case false:
		if (_emojiMan->currentFrameTime >= cEmojiManFrameTime) {
			_emojiMan->frame++;
			if (_emojiMan->frame > 1) {
				_emojiMan->frame = 0;
			}
			_emojiMan->sourceRect->X = _emojiMan->sourceRect->Width * _emojiMan->frame;
			_emojiMan->currentFrameTime = 0;
		}
		break;

	default:
		break;
	}
	
}

void EmojiMan::checkViewportCollision() 
{
	if (_emojiMan->positionRect->X > Graphics::GetViewportWidth()) {
		_emojiMan->positionRect->X = 0 - _emojiMan->sourceRect->Width;
	}
	if (_emojiMan->positionRect->X + _emojiMan->sourceRect->Width < 0) {
		_emojiMan->positionRect->X = Graphics::GetViewportWidth() ;
	}
	if (_emojiMan->positionRect->Y + _emojiMan->sourceRect->Height < 0) {
		_emojiMan->positionRect->Y = Graphics::GetViewportHeight();
	}
	if (_emojiMan->positionRect->Y > Graphics::GetViewportHeight()) {
		_emojiMan->positionRect->Y = 0 - _emojiMan->sourceRect->Height;
	}
}

void EmojiMan::updateClickPad()
{
	// Switch scene onto EmojiClicker once player overlaps with pressure plate
	if (boxCollisionCheck(_emojiMan->positionRect, _clickPadPosition) && !_isOnClickPad) {
		_isOnClickPad = true;
		_activeScene_ = EMOJICLICKER;
		_reloadScene_ = true;
	}
	else if(!boxCollisionCheck(_emojiMan->positionRect, _clickPadPosition)){
		_isOnClickPad = false;
	}
}

bool EmojiMan::boxCollisionCheck(Rect* obj1Rect, Rect* obj2Rect) 
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

void EmojiMan::updateMunchie()
{
	// Checks whether any of the munchies exist first
	if (!_munchiesArray.empty()) {
		for (size_t i = 0; i < _munchiesArray.size(); i++)
		{
			// If player overlaps with any of the munchies, that particualr one will get deleted from heap as well as from the vector array
			if (boxCollisionCheck(_emojiMan->positionRect, _munchiesArray[i]->_munchiePosition)) {
				if (_munchieFX->GetState() != SoundEffectState::PLAYING) {
					Audio::Play(_munchieFX);
				}
				// If super munchie is picked, activate super mode
				if (_munchiesArray[i]->getMunchieType() == MunchieType::SUPER) {
					_emojiMan->superMode = true;
					_superModeCounter = _superModeDuration;
				}
				// Get rid off that munchie from array and delete it's object as is picked up.
				delete _munchiesArray[i];
				_munchiesArray.erase(_munchiesArray.begin() + i);
				_scoreManager_->updateScore(_scoreManager_->getCollectiblePickUpValue());
			}
		}
	}
}

void EmojiMan::updateMunchieAnimation(int elapsedTime)
{
	_CurrentMunchieFrameTime += elapsedTime;
	if (_CurrentMunchieFrameTime >= cMunchieFrameTime) {
		_MunchieFrame++;
		if (_MunchieFrame > 7) {
			_MunchieFrame = 0;
		}
		_MunchieSourceRect->X = _MunchieSourceRect->Width * _MunchieFrame;
		_CurrentMunchieFrameTime = 0;
	}
}

void EmojiMan::createMunchie(bool superMunchie)
{
	// Generate Random Seed and Potential Position for munchie to spawn
	srand(time(0));

	// Temporary variables that get created with each function call and then dispose them.
	float tempX = rand() % (Graphics::GetViewportWidth() - 64) + 32;
	float tempY = rand() % (Graphics::GetViewportHeight() - 32) + 32;
	Rect* tempRect = new Rect(tempX, tempY, 24, 24);

	// Check if potential Position doesn't overlap with any other munchie
	if (checkPositionForNewMunchie(*tempRect)) {
		// Once super munchie is spawned, toggle off the flag
		if (superMunchie) {
			_SpawnSuperMunchie = false;
			_munchiesArray.push_back(new Munchie(*_SuperMunchieTexture, *_MunchieSourceRect, tempX, tempY, SUPER));
		}
		// if super munchie flag is off, spawn regular munchie
		else {
			_munchiesArray.push_back(new Munchie(*_MunchieTexture, *_MunchieSourceRect, tempX, tempY, NORMAL));
		}
	}

	// Dispose Temporary Position from the heap
	delete tempRect;
}

bool EmojiMan::checkPositionForNewMunchie(Rect& posRef)
{
	// Check if munchies array is empty
	if (!_munchiesArray.empty()) {
		// If not, loop thorugh all objects and check whether potential position is valid
		for (size_t i = 0; i < _munchiesArray.size(); i++)
		{
			// If Potential Position overlaps with any of them return false
			if (boxCollisionCheck(_munchiesArray[i]->_munchiePosition, &posRef)) {
				return false;
			}
		}
		// If Potential Position doesn't overlap with any of the objects return true
		return true;
	}

	// If empty just return true
	else {
		return true;
	}
}

void EmojiMan::spawnEnemy()
{
	if (_amountOfEnemiesPresent < 4) {
		int spawnerID = rand() % 3 + 1;
		_enemyArray.push_back(new Enemy(*_enemyTextureSheet, *_enemySourceRect, *_mySpawners[spawnerID]->position));

	}
}

void EmojiMan::updateExitButton(Input::MouseState& mouseStateRef) {
	if (boxCollisionCheck(_mousePosition, _LoseScreenExitGameButton->position)) {
		_LoseScreenExitGameButton->source->Y = 120;
		if (mouseStateRef.LeftButton == Input::ButtonState::PRESSED && !_LoseScreenExitGameButton->triggered) {
			_LoseScreenExitGameButton->triggered = true;
			_activeScene_ = EXIT;
			_reloadScene_ = true;
		}
		else if (mouseStateRef.LeftButton == Input::ButtonState::RELEASED && _LoseScreenExitGameButton->triggered) {
			_LoseScreenExitGameButton->triggered = false;
		}
	}
	else {
		_LoseScreenExitGameButton->source->Y = 0;
	}
}