#pragma once
#include "S2D/S2D.h"
#include "ScoreManager.h"
#include <sstream>
#include <iostream>
using namespace S2D;

enum SceneType
{
	MENU = 1,
	EMOJIGAME,
	EMOJICLICKER,
	EXIT
};

class Scene
{
protected:
	SceneType _activeScene_;
	ScoreManager* _scoreManager_;
	bool _reloadScene_;
	bool _contentLoaded_;

public:
	Scene();
	virtual ~Scene();

	virtual void Load() =0;
	virtual void Update(int elapsedTime) =0;
	virtual void Draw(int elapsedTime) =0;

	SceneType getActiveScene() const { return _activeScene_; }
	bool getReloadScene() const { return _reloadScene_; }
	void setReloadScene(bool reload);
	bool getContentLoaded() const { return _contentLoaded_; }
	void setScoreManager(ScoreManager* scoreManagerRef);
};

