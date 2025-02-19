#include "Player.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>

void Player::draw()
{
	graphics::Brush br;
	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity = 0.0f;
	
	br.texture = ASSET_PATH + std::string("cookie.png");
	
	graphics::drawRect(m_pos[0],m_pos[1],PLAYER_SIZE,PLAYER_SIZE,br);
	

}

void Player::update()
{

}

Player::Player()
{
	SETCOLOR(m_color, RAND0TO1(), RAND0TO1(), RAND0TO1());
}
