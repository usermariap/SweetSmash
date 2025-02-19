#pragma once
#include "defines.h"
#include <sgg/graphics.h>
#include "game.h"
#include "Sweet.h"
#include <random>
#include <iostream>

void Sweet::draw()
{
	
	graphics::Brush br;
	
	std::string k = "cherries.png";

	//png rectangle
	if (openclose)
	{
		k = getkind();
	}
	
	br.texture = ASSET_PATH + std::string(k);
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::drawRect(pos[0], pos[1], PLAYER_SIZE, PLAYER_SIZE, br);

	//draws the borders of the table
	br.outline_opacity = 1.0f;
	br.fill_opacity = 0.0f;
	br.outline_width = 1.5f;
	
	if (highlighted)	SETCOLOR(br.outline_color, 0.0f, 1.0f, 1.0f);	
	
	if (pressed)	SETCOLOR(br.outline_color, 1.0f, 0.5f, 0.5f);
	
	
	graphics::drawRect(pos[0], pos[1], PLAYER_SIZE * 1.9f, PLAYER_SIZE * 1.3f, br);
}


void Sweet::update()
{
	if (pressed)	setopenclose(true);

}


bool Sweet::contains(float x, float y)
{

	return distance(x,y,pos[0],pos[1])<PLAYER_SIZE;
}


