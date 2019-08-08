#include"Graphics.h"
#pragma warning(disable:4996)

int Screen::screen_height = SCREEN_HEIGHT;
int Screen::screen_width = SCREEN_WIDTH;

void Screen::Create()
{
	initgraph(1100, 600);//easyx
	setbkcolor(0x4F4F4F);
}

void Screen::Close()
{
	closegraph();//easyx
}

int Screen::GetWidth()
{
	return screen_width;
}

int Screen::GetHeight()
{
	return screen_height;
}
