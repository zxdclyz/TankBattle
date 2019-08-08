#pragma once
#include<graphics.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAME(x) (1000/x)//x represent frames in 1s

class Screen //main screen
{
public:
	static void Create();
	static void Close();

	//return screen info
	static int GetWidth();
	static int GetHeight();

private:
	static int screen_width;
	static int screen_height;
};
