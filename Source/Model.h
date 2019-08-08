#pragma once
#include<graphics.h>
#include"Graphics.h"

enum DIR { UP, DOWN, RIGHT, LEFT };

struct Point
{
	int x, y;
};

class Rect
{
public:
	Rect(Point = { 0,0 }, Point = { 0,0 });

	void SetStartPoint(Point);
	void SetEndPoint(Point);

	bool PointInRect(Point);
	bool CollisionCheck(Rect&);
	bool operator ==(Rect&);

	Point GetStartPoint();
	Point GetEndPoint();
protected:
	Point start_point, end_point;
};

class Object//can be everything
{
public:
	virtual void Display() = 0;
	virtual bool IsExist() = 0;
	virtual void CalPhysicalSize() = 0;
	virtual void Destory() = 0;

	Rect physical_size;
protected:
	COLORREF color;
	DIR dir = UP;
	Point pos;
	bool existing = true;
};