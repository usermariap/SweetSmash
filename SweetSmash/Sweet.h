#pragma once

#include "defines.h"


class Sweet
{
	
	float pos[2] = {0.0f,0.0f};
	std::string kind;

	bool highlighted = false;
	bool pressed = false;
	bool openclose = false;

	int i1,j1;
	
public:
	Sweet(std::string the_kind) {kind = the_kind; };
	void draw();
	void update();

	void setposX(float x) { pos[0] = x; }
	float getposX() { return pos[0]; }

	void setposY(float y) { pos[1] = y; }
	float getposY() { return pos[1]; }

	void setHighlight(bool highlight) { highlighted = highlight; }
	void setPressedSweet(bool s) { pressed = s; }

	bool contains(float x, float y);
	

	void seti(int i) { i1 = i; }
	void setj(int j) { j1 = j; }

	int geti() { return i1; }
	int getj() { return j1; }

	void setkind(std::string k) { kind = k; }
	std::string getkind() { return kind; }

	void setopenclose(bool s) { openclose = s; }
	bool getopenclose() { return openclose; }
};
