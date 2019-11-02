#include "Munchie.h"

Munchie::Munchie()
{

}

Munchie::Munchie(Texture2D& textureRef, Rect& sourceRef, float xPos, float yPos, MunchieType type)
	: _munchieTexture(&textureRef), _munchieSourceRect(&sourceRef), _munchieType(type)
{
	_munchiePosition = new Rect(xPos, yPos, 24, 24);
}

Munchie::~Munchie()
{
	delete _munchiePosition;
}
