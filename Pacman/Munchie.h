#pragma once
#include "S2D/S2D.h"

using namespace S2D;

enum MunchieType {
	NORMAL,
	SUPER
};

class Munchie
{
private:
	MunchieType _munchieType;

public:
	Texture2D* _munchieTexture;
	Rect* _munchieSourceRect;
	Rect* _munchiePosition;
	bool _munchieTriggered;

public:
	Munchie();
	Munchie(Texture2D& textureRef, Rect& sourceRef, float xPos, float yPos, MunchieType type);
	~Munchie();

	MunchieType getMunchieType() const { return _munchieType; }
};

