#pragma once
#include "IGame.h"
#include "Location.h"
#include "Colors.h"

#define MAX_SEGMENTS 150
#define NUM_BODY_COLORS 4

class Snake : public IGame
{
public:
	Snake();

	void update(int input) override;
	void fillScreenBuf(Color* leds) override;
	bool isAlive() const override { return is_alive; };

private:
	void spawnApple();
	bool isValidPos(const Location& loc) const;
	bool willDie(const Location& loc) const;

	bool about_to_die = false;
	bool is_alive = true;
	Location segments[MAX_SEGMENTS];
	Location direction = { 0, 0 };
	Location apple_pos;
	char length = 2;
	bool use_borders = true;
	Color colors[NUM_BODY_COLORS];
};
