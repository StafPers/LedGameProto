#include "Snake.h"
#include "defines.h"
#include <cstdlib>
#include <time.h>

Snake::Snake()
{
	srand(time(NULL));
	spawnApple();
	colors[0] = Color(10, 100, 32);
	colors[1] = Color(10, 130, 48);
	colors[2] = Color(18, 160, 48);
	colors[3] = Color(10, 130, 48);
	segments[0].x = 2;
	segments[0].y = 1;
	segments[1].x = 1;
	segments[1].y = 1;
}

void Snake::update(int input)
{
	if (input == INPUT_DOWN && direction.y != -1)
	{
		direction.y = 1;
		direction.x = 0;
	}
	else if (input == INPUT_LEFT && direction.x != 1)
	{
		direction.x = -1;
		direction.y = 0;
	}
	else if (input == INPUT_RIGHT && direction.x != -1)
	{
		direction.x = 1;
		direction.y = 0;
	}
	else if (input == INPUT_UP && direction.y != 1)
	{
		direction.y = -1;
		direction.x = 0;
	}
	else if(input == INPUT_TOGGLE_BORDER)
	{
		use_borders = !use_borders;
	}

	Location new_head_pos = segments[0];
	new_head_pos.x += direction.x;
	new_head_pos.y += direction.y;

	if (willDie(new_head_pos))
	{
		if (about_to_die)
			is_alive = false;
		else
			about_to_die = true;
	}
	else 
		about_to_die = false;

	if (!is_alive || about_to_die)
		return;

	if (new_head_pos == apple_pos) // grow
	{
		spawnApple();
		++length;
	}
	else if (!use_borders) // wrap
	{
		if (new_head_pos.x < 0)
			new_head_pos.x += DIMS;
		else if (new_head_pos.x >= DIMS)
			new_head_pos.x -= DIMS;
		else if (new_head_pos.y < 0)
			new_head_pos.y += DIMS;
		else if (new_head_pos.y >= DIMS)
			new_head_pos.y -= DIMS;
	}

	if(direction.x != 0 || direction.y != 0)
		for (int i = length - 1; i > 0; --i)
			segments[i] = segments[i - 1];

	segments[0] = new_head_pos;
}

void Snake::fillScreenBuf(Color * leds)
{
	leds[apple_pos.x + DIMS * apple_pos.y] = Colors::Red;
	leds[segments[0].x + DIMS * segments[0].y] = Colors::Yellow;

	if (use_borders)
	{
		for (int x = 0; x < DIMS; ++x)
			leds[x] = leds[x + DIMS * (DIMS - 1)] =
			leds[DIMS * x] = leds[DIMS - 1 + DIMS * x] = Colors::Blue;
	}

	if (is_alive)
	{
		for (int i = 1; i < length; ++i)
			leds[segments[i].x + DIMS * segments[i].y] = colors[i % NUM_BODY_COLORS];
	}
	else
	{
		for (int i = 0; i < death_animation_progress; ++i)
			leds[segments[i].x + DIMS * segments[i].y] = Colors::Red;

		for (int i = death_animation_progress; i < length; ++i)
			leds[segments[i].x + DIMS * segments[i].y] = colors[i % NUM_BODY_COLORS];
	}
	
}

bool Snake::progressDeathAnimation()
{
	if (death_animation_progress == length)
		return false;

	++death_animation_progress;
	return true;
}

void Snake::spawnApple()
{
	do
	{
		int min = use_borders ? 1 : 0;
		int max = use_borders ? DIMS - 2 : DIMS;
		apple_pos.x = rand() % max + min;
		apple_pos.y = rand() % max + min;
	} while (!isValidPos(apple_pos));
}

bool Snake::isValidPos(const Location & loc) const
{
	for (int i = 0; i < length; ++i)
		if (segments[i] == loc)
			return false;

	return true;
}

bool Snake::willDie(const Location & loc) const
{
	if (use_borders &&
		(loc.x == 0 || loc.x == DIMS - 1 ||
			loc.y == 0 || loc.y == DIMS - 1))
		return true;

	for (int i = 1; i < length; ++i)
		if (loc == segments[i])
			return true;

	return false;
}
