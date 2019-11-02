#include "Scene.h"

Scene::Scene()
{
	_activeScene_ = MENU;
	_reloadScene_ = false;
	_contentLoaded_ = false;

}

Scene::~Scene()
{
}

void Scene::setReloadScene(bool reload)
{
	_reloadScene_ = reload;
}

void Scene::setScoreManager(ScoreManager* scoreManagerRef)
{
	_scoreManager_ = scoreManagerRef;
}
