#pragma once
#include"Model.h"
#include"Tank.h"

enum Func
{
	SPEED, COOLDOWN, HEALTH, SUPERSHOOT, POWER
};

class Item :public Object
{
public:
	void Deploy();
	void SetRandomPos();
	void SetRandomFunc();
	void Activate(PlayerTank&);

	virtual void Display();
	virtual bool IsExist();
	virtual void CalPhysicalSize();
	virtual void Destory();
protected:
	Func func;
};