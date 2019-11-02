#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
	// Global Score
	score = 0;
	scoreMultiplier = 1;
	scorePosition = new Vector2(15.0f, 50.0f);

	// Automatic Score
	upgradeScoreBonus = 1;
	automaticInitialScoreDelay = 2500;
	automaticCurrentScoreDelay = automaticInitialScoreDelay;
	automaticScore = false;

	// EmojiMan Data
	emojiManMovementSpeed = 0.1f;
	initialMunchieSpawnDelayTime = 2000;
	collectiblePickUpValue = 1;
}

ScoreManager::~ScoreManager()
{
	delete scorePosition;
}

void ScoreManager::drawScore()
{
	scoreStream << "Score: " << score;
	SpriteBatch::DrawString(scoreStream.str().c_str(), scorePosition, Color::Red);
	scoreStream.str("");
}

void ScoreManager::updateScore(int amount)
{
	// Check in case of adding negative number so it doesn't get multiplied.
	if (amount > 0) {
		score += amount * scoreMultiplier;
	}
	else{
		score += amount;
	}
}

void ScoreManager::automaticScoreGatherer(int elapsedTime)
{
	if (automaticScore) {
		automaticCurrentScoreDelay -= elapsedTime;
		if (automaticCurrentScoreDelay <= 0) {
			// Add points to global score, amount affected by upgrades purchased.
			score += upgradeScoreBonus;
			// Reset Cycle
			automaticCurrentScoreDelay = automaticInitialScoreDelay;
		}
	}
}

void ScoreManager::setEmojiManMovementSpeed(float value) {
	emojiManMovementSpeed = value;
}

void ScoreManager::addCollectiblePickUpValue(int value) {
	collectiblePickUpValue += value;
}

void ScoreManager::setInitialMunchieSpawnDelayTime(int value){
	initialMunchieSpawnDelayTime = value;
}
