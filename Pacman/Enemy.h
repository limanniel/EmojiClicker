#pragma once
#include "S2D/S2D.h"
using namespace S2D;

class Enemy
{
private:
	struct Direction {
		float x;
		float y;
	};

	Direction _enemyToPlayerDirection;

public:
	Texture2D* _enemyTexture;
	Rect* _enemySourceRect;
	Rect* _enemyPositionRect;

public:
	Enemy();
	Enemy(Texture2D& textureReference, Rect& sourceReference, Rect& positionReference);
	~Enemy();

	void updatePosition(Rect& playerPosition);
	void moveEnemy();
};

