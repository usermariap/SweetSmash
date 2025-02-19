#pragma once
#include "defines.h"
#include <sgg/graphics.h>
#include "game.h"
#include "Sweet.h"
#include "event.h"
#include <iostream>
#include <stdio.h>


void Game:: draw()
{


    graphics::Brush br;
    br.outline_opacity = 0.0f;
    
    if (state == STATE_INIT)
    { 
        //backround rectangle
        SETCOLOR(br.fill_color, 1.0f, 0.5f, 0.8f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

        //png rectangle
        br.texture = ASSET_PATH + std::string("backloading.png");
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH/2, CANVAS_HEIGHT, br);

        //text properties
        SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
        br.outline_opacity = 0.0f;
        graphics::setFont(ASSET_PATH + std::string("a.ttf"));
        graphics::drawText(10.0f, CANVAS_HEIGHT * 0.85f, 2.0f, "loading...", br);


        state = STATE_LOADING;
        return;
    }

    //creates background
    br.outline_opacity = 0.0f;
    SETCOLOR(br.fill_color, 0.6f, 0.5f, 0.9f);
    graphics::setWindowBackground(br);
    graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

    //backround boxes
    SETCOLOR(br.fill_color, 0.5f, 0.5f, 0.0f);
    br.outline_width = 4.0f;
    br.outline_opacity = 1.0f;
    SETCOLOR(br.fill_secondary_color, 1.0f, 1.0f, 0.7f, br);
    br.gradient = true;
    br.gradient_dir_u = 0.74f;
    br.gradient_dir_v = 0.74f;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            graphics::drawRect(CANVAS_WIDTH * (j + 4.0f) / 15.0f, CANVAS_HEIGHT * (i + 2.6f) / 12.0f, PLAYER_SIZE * 1.9f, PLAYER_SIZE * 1.3f, br);
        }
    }
  

    if (state == STATE_MATCHING)
    {
        if (pressed_sweet->getkind() == pr->getkind())
        {    
            if (a(pressed_sweet->geti(), pressed_sweet->getj()) != a(pr->geti(), pr->getj()))
            {
                match = true;
                //red box when match
                br.gradient = false;
                SETCOLOR(br.fill_color, 0.6f, 0.0f, 0.0f);
                graphics::drawRect(pressed_sweet->getposX(), pressed_sweet->getposY(), PLAYER_SIZE * 1.9f, PLAYER_SIZE * 1.3f, br);
                graphics::drawRect(pr->getposX(), pr->getposY(), PLAYER_SIZE * 1.9f, PLAYER_SIZE * 1.3f, br);

                //messages when matching
               
                SETCOLOR(br.fill_color, 1.0f, 0.65f, 0.0f);
                br.outline_opacity = 0.0f;
                graphics::setFont(ASSET_PATH + std::string("b.ttf"));
                std::string s[4] = { "AWESOME!!!","FABULOUS!!!","MARVELOUS!!!","EXCELLENT!!!" };
                int x = rand() % 4;
                graphics::drawText(CANVAS_WIDTH*0.2f, CANVAS_HEIGHT*0.55f, 2.0f, s[x], br);


                delete a(pressed_sweet->geti(),pressed_sweet->getj());
                delete a(pr->geti(),pr->getj());
                a(pressed_sweet->geti(),pressed_sweet->getj(), nullptr);
                a(pr->geti(),pr->getj(), nullptr);
            }

        } 
    }

    // with those for ,we draw the table
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (a(i,j)) a(i,j)->draw();
        }
    }

    for (auto ev : m_events)
    {
        ev->draw();
    }

}

void Game::update()
{

    if (state == STATE_INIT)
    {
        return;
    }
    if (state == STATE_LOADING)
    {
        init();
        state = STATE_IDLE;
        return;
    }

    processedEvents();
        
    

    if (state == STATE_MATCHING)
    {
        if (match)
        {
            addEvent(new Matchevent());          
            match = false;
        }
        
        if (pr)
        {
            
            pressed_sweet->setopenclose(false);
            pr->setopenclose(false); 
            pressed_sweet->setPressedSweet(false);
            pressed_sweet = nullptr;
            pr = nullptr;
        }
          
        sleep(800);
        state = STATE_IDLE;
    }
    if (state == STATE_2OPENSWEET)
    {
        if (pressed_sweet->getkind() == pr->getkind() && a(pressed_sweet->geti(),pressed_sweet->getj()) != a(pr->geti() ,pr->getj()))sleep(200);
        state = STATE_MATCHING;
    }
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);

    Sweet* current_sweet = nullptr;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (!a(i,j)) continue;
            if (a(i,j)->contains(mx, my))
            {
                a(i,j)->setHighlight(true);
                current_sweet = a(i,j);
            }
            else
            {
                a(i,j)->setHighlight(false);
            }
        }
    }

    if (ms.button_left_pressed && current_sweet && pr == nullptr)
    {
        
        pressed_sweet = current_sweet;
        pressed_sweet->setPressedSweet(true);
        addEvent(new Soundevent());
 
        
        //diactivates the other players
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (!a(i,j)) continue;
                if (a(i,j) != pressed_sweet)
                {
                    a(i,j)->setPressedSweet(false);

                }
            }
        }
    }
    
    
    if (ms.button_left_pressed && current_sweet && pr != nullptr)
    {
        
        pressed_sweet = current_sweet;
        pressed_sweet->setPressedSweet(true);
        addEvent(new Soundevent());
        state = STATE_2OPENSWEET;
       
    }
    /*
    * first button press checks both if
    * (firsttime you choose a sweet)firstif then pressed_sweet !=null and buttonreleasefalse--->third if false
    * (firsttime you released)buttonreleasetrue and pressedsweet!=null--->third if true

    * (secondtime you choose a sweet)secondif then pressed_sweet !=null and buttonreleasefalse---> third if false then matching
    * (secondtime you released)pressed_sweet == null and buttonrelease---> third if false

    * again this pattern cause of pr
    */
    

  
    if (ms.button_left_released && pressed_sweet)
    {
        pr = pressed_sweet;   
        pressed_sweet->setPressedSweet(false);
        pressed_sweet = nullptr;
        
    }

    int pl = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (a(i,j)) a(i,j)->update();
            else pl++;
        }
    }

    if (pl == 64) 
    {     
        addEvent(new Winnerevent());
        sleep(2000);
        graphics::stopMessageLoop();
    }
    
}


void Game::init()
{
   
    std::string s[8] = { "candy.png", "choco.png", "chocolate.png", "cookie.png", "ice.png", "marshmallow.png", "muffin.png","glyf.png"}; 
    for (int i = 0; i < 8; i++)
    {
        randomize(s, 8);
        for (int j = 0; j < 8; j++)
        { 
            Sweet* p = new Sweet(s[j]);
            
            a(i, j, p);
            p->seti(i);
            p->setj(j);
            p->setposX(CANVAS_WIDTH * (j + 4.0f) / 15.0f);
            p->setposY(CANVAS_HEIGHT * (i + 2.6f) / 12.0f);

        }
    }
    graphics::preloadBitmaps(ASSET_PATH);

    sleep(2000);
}

Game* Game::getIstance()
{   
    if (!m_instance) 
        m_instance = new Game();  
    return m_instance;
}

Game::~Game()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (!a(i,j)) continue;
            delete a(i,j);
        }
    } 
}

void Game::processedEvents()
{
    for (auto e : m_events)
    {
        e->update();
    }

    m_events.remove_if([](Event* ev) {return !ev->active(); });//lambda expression
}

void Game::addEvent(Event* evnt)
{
    m_events.push_front(evnt);
}
Game* Game::m_instance = nullptr;