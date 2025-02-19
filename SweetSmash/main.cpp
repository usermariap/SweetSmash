#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include "game.h"
#include <iostream>
#include "main.h"

// The window content drawing function.
void draw()
{
    Game* mygame = Game::getIstance();
        
    mygame->draw();

}
void update(float ms)
{
    Game* mygame = Game::getIstance();

    mygame->update();
}

int main()
{
    graphics::createWindow(1200, 600, "SWEET_SMASH");

    Game* game = Game::getIstance();
    
    graphics::setUserData(game);
  
    graphics::setCanvasSize(28, 16);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::startMessageLoop();
   
    Game::releaseInstance();
    
    return 0;
}