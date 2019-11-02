#pragma once
#include "S2D/S2D.h"
#include <sstream>
#include <fstream>
//#include <string>
using namespace S2D;

class ScoreManager
{
private:
	long int score;
	Vector2* scorePosition;
	std::string playerName;
	std::stringstream scoreStream;

	// EmojiMan Data
	float emojiManMovementSpeed;
	int initialMunchieSpawnDelayTime;
	int collectiblePickUpValue;

public:
	int scoreMultiplier;
	int upgradeScoreBonus;
	int automaticInitialScoreDelay;
	int automaticCurrentScoreDelay;
	bool automaticScore;

	ScoreManager();
	~ScoreManager();
	
	// Score Related
	void drawScore();
	void updateScore(int amount);

	void automaticScoreGatherer(int elapsedTime);

	// EmojiMan Data
	void setEmojiManMovementSpeed(float value);
	void setInitialMunchieSpawnDelayTime(int value);
	void addCollectiblePickUpValue(int value);

	// Getters
	int getScore() const { return score; }
	int getCollectiblePickUpValue() const { return collectiblePickUpValue; }
	int getInitialMunchieSpawnDelayTime() const { return initialMunchieSpawnDelayTime; }
	float getEmojiManMovementSpeed() const { return emojiManMovementSpeed; }
};

