/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "GameManager.h"
#include "SpriteCodex.h"
#include "Snake.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	current_game = new Snake();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (current_game->isAlive())
	{
		int input = VK_CANCEL;

		for (int i = 0; i < 50; ++i)
		{
			while (!wnd.kbd.KeyIsEmpty())
			{
				const Keyboard::Event e = wnd.kbd.ReadKey();
				if (e.IsPress())
					input = e.GetCode();
			}

			Sleep(1);
		}

		if (input == VK_LEFT)
			input = INPUT_LEFT;
		else if (input == VK_RIGHT)
			input = INPUT_RIGHT;
		else if (input == VK_UP)
			input = INPUT_UP;
		else if (input == VK_DOWN)
			input = INPUT_DOWN;
		else if (input == VK_SPACE)
			input = INPUT_TOGGLE_BORDER;
		else
			input = INPUT_NONE;

		current_game->update(input);
	}
}

void Game::ComposeFrame()
{
	// this is what happens in arduino main loop
	//get input bluetooth
	// set game if new game

	//update current game with input
	//draw current game by sending array

	for (int i = 0; i < NUM_LEDS; ++i)
		leds[i] = Colors::Black;

	current_game->fillScreenBuf(leds);

	const int padding = 2;
	for (int x = 0; x < DIMS; ++x)
		for (int y = 0; y < DIMS; ++y)
			gfx.DrawRectDim(x * CELL_DIM, y * CELL_DIM, CELL_DIM - 2, CELL_DIM - 2, leds[x + DIMS * y]);
}
