#pragma once
#include "event.h"

class Event
{
protected:


	float duration = 3.0f;
	float delay = 0.0f;
	float elapsed_time = 0.0f;
	float elapsed_delay = 0.0f;

	bool m_active = true;

public:
	virtual void draw() {};
	void update();

	Event(float dur, float del );
	virtual ~Event() {};

	bool active() { return m_active; }
	void disable() { m_active = false; }
	bool waiting();
};

class Soundevent : public Event
{	
public:
	Soundevent();
	void draw() override;	
};


class Matchevent : public Event
{
public:
	Matchevent();
	void draw() override;
};


class Winnerevent : public Event
{
public:
	Winnerevent();
	void draw() override;
};