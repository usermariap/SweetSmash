#pragma once
#include "event.h"
#include "defines.h"
#include "sgg/graphics.h"
#include <random>


Event::Event(float dur, float del)
	:duration(dur), delay(del)
{

}


void Event::update()
{
	if (!m_active) return;

	if (waiting())
	{
		elapsed_time += graphics::getDeltaTime() / 1000.0f;
		return;
	
	}
	elapsed_time += graphics::getDeltaTime() / 1000.0f;
	if (elapsed_time > duration)
	{
		m_active = false;
	}
}


bool Event::waiting()
{
	return elapsed_delay < delay;

}

void Soundevent::draw()
{ 
	graphics::playSound(ASSET_PATH + std::string("opencard.mp3"),1);
}

Soundevent::Soundevent()
	:Event(0.0f,0.0f)
{

}


Matchevent::Matchevent()
	:Event(0.2f,0.0f)
{

}

void Matchevent::draw()
{
	graphics::playSound(ASSET_PATH + std::string("matchcard.mp3"), 1);

}

Winnerevent::Winnerevent()
	:Event(0.5f,0.5f)
{
}

void Winnerevent::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;

	br.texture = ASSET_PATH + std::string("party.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	
	br.texture = ASSET_PATH + std::string("partyyy.png");
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 2, CANVAS_HEIGHT, br);


	SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
	br.outline_opacity = 0.0f;
	graphics::setFont(ASSET_PATH + std::string("a.ttf"));
	graphics::drawText(CANVAS_WIDTH * 0.15f, CANVAS_HEIGHT * 0.55f, 5.0f, "WINNER", br);

	graphics::playSound(ASSET_PATH + std::string("clapss.mp3"), 1);
}
