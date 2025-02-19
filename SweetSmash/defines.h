#pragma once
#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>



#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f

#define ASSET_PATH ".\\assets\\"

#define PLAYER_SIZE 1.0f

#define SETCOLOR(c,r,g,b){c[0] = r; c[1] = g; c[2] = b;}



inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

inline void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}



inline void swap(std::string* a, std::string* b)
{
	std::string temp = *a;
	*a = *b;
	*b = temp;
}

inline void randomize(std::string arr[], int n)
{
	
	srand(time(NULL));
	
	for (int i = n - 1; i > 0; i--)
	{	
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
	}
}

