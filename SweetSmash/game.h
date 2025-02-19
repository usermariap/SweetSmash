#pragma once
#include <list>
#include "Sweet.h"
#include "event.h"
#include "table.h"

class Game 
{
public:
	 
	enum game_state {STATE_INIT,STATE_LOADING, STATE_IDLE,STATE_2OPENSWEET,STATE_MATCHING};
protected:
	
	table a ;

	Sweet* pressed_sweet = nullptr;
	Sweet* pr = nullptr;

	static Game* m_instance;

	std::list<Event*> m_events;//list me  events

	bool match = false;

	game_state state = STATE_INIT;

	

	Game() {};
public:
	static Game* getIstance();
	void draw();
	void update();
	void init();
	~Game();
	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }

	void processedEvents();
	void addEvent(Event* evnt);
};
