#pragma once

#include "Colors.h"

class IGame
{
public:
	virtual ~IGame() {}

	virtual void update(int input) = 0;
	virtual void fillScreenBuf(Color* leds) = 0;
	virtual bool isAlive() const = 0;
};