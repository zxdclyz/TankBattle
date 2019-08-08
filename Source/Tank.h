#pragma once
#pragma warning(disable:4996)
#include"Model.h"
#include"Bullet.h"
#include"Map.h"

//May have a AITank
class Tank:public Object
{
	friend class Item;
	friend class Status;
public:
	virtual void Move(DIR) = 0;
	virtual void Shoot(std::list<Bullet*>&) = 0;
	virtual void CoolDown() = 0;
protected:
	int hp;
	int speed;
	int cool_down_limit;
	int shoot_cool_down;
	int super_shoot;
	int bullet_power;
};

class PlayerTank:public Tank
{
public:
	PlayerTank();

	void SetDir(DIR);

	//for initialization
	void SetColor(COLORREF);
	void SetPosition(int, int);

	virtual void Display();
	virtual void Move(DIR);
	virtual void Shoot(std::list<Bullet*>&);
	virtual void CoolDown();
	virtual void Destory();
	void DestoryByDamage(int);

	virtual void CalPhysicalSize();

	virtual bool IsExist();

	bool MoveCheck(DIR);

protected:
	void DrawTank(DIR);
};



//save tank status to show
class Status
{
public:
	int hp;
	int speed;
	int cool_down_limit;
	int shoot_cool_down;
	int super_shoot;
	int bullet_power;
	COLORREF color;

	void RefreshStatus(const PlayerTank& tank)
	{
		hp = tank.hp;
		speed = tank.speed;
		cool_down_limit = tank.cool_down_limit;
		shoot_cool_down = tank.shoot_cool_down;
		super_shoot = tank.super_shoot;
		bullet_power = tank.bullet_power;
		color = tank.color;
	}
};
