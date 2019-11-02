#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Texture2D& textureReference, Rect& sourceReference, Rect& positionReference) 
	: _enemyTexture(&textureReference), _enemySourceRect(&sourceReference)
{
	_enemyPositionRect = new Rect(positionReference.X, positionReference.Y, 32, 32);
}

Enemy::~Enemy()
{
	delete _enemyPositionRect;
}

void Enemy::updatePosition(Rect& playerPosition)
{
	// Get direction x & y vector
	_enemyToPlayerDirection.x = playerPosition.X - _enemyPositionRect->X;
	_enemyToPlayerDirection.y = playerPosition.Y - _enemyPositionRect->Y;

	// Normalize vector 
	float hyp = sqrt(_enemyToPlayerDirection.x * _enemyToPlayerDirection.x + _enemyToPlayerDirection.y * _enemyToPlayerDirection.y);
	_enemyToPlayerDirection.x /= hyp;
	_enemyToPlayerDirection.y /= hyp;

	moveEnemy();
}

void Enemy::moveEnemy()
{
	_enemyPositionRect->X += _enemyToPlayerDirection.x * 1.1f;
	_enemyPositionRect->Y += _enemyToPlayerDirection.y * 1.1f;
}