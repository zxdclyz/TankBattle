#pragma once
#include"Model.h"
#include<list>

class Bullet :public Object
{
public:
	Bullet(Point, DIR, COLORREF, int);

	void Display();
	void Move();
	bool IsExist();
	void Destory();
	void CalPhysicalSize();
	int GetDamage();

protected:
	int speed;
	int damage;
};