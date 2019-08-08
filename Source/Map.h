#pragma once
#include"Model.h"

#define BLOCKS 14

class Block :public Object
{
public:
	Block();
	Block(COLORREF,Point,Point);
	virtual void Display();
	virtual bool IsExist();
	virtual void CalPhysicalSize();
	virtual void Destory();

	void SetPosition(Point, Point);
	void SetColor(COLORREF);
};

class Map
{
public:
	static void Create(Block*);
	static void Display(Block*);
};