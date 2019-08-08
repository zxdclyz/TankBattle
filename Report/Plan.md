<center>
    <font face="仿宋" size=23>
        小学期自主选题开题报告
    </font>
</center>
<div style="text-align: right"> 
    <font size=3.5 face="华文楷体" >
    无82 李煜泽 2018011060
    </font>
</div>

# Tank Battle

> for c++ summer term 2019

**计划完成自主创新选题**<br>**计划在小学期中完成**

*Tank Battle*(暂定名)为一个基于经典游戏*Battle City*(中译名:坦克大战)的游戏设定与模式设计、编写的坦克射击游戏。传统的坦克大战游戏为防守基地并且击败敌方坦克，本游戏为了加强多人互动性，将游戏设定改为玩家双方的坦克对战，同时保留原作通过道具来加强坦克的设定。

## 计划开发的内容

1. **基础内容**（小学期内一定完成）：实现本地的双人对战<br>**以下为拓展内容，将尽可能实现，但不一定会全部完成(至少实现一个)**
2. 可破坏的地图环境
3. 局域网双人对战
4. 人机对战（电脑AI）

## 技术实现

### 对于基本要求的满足

- 至少包含3个类
- 运算符重载与函数重载
- 类的继承与抽象基类
- 动态内存分配
- 数据结构:链表(使用List)

### 界面的实现

使用 [easyx](https://easyx.cn/)库

### 具体技术实现:类结构

#### struct Point

用于储存x,y坐标

#### class Rect

保存物体的左上以及右下坐标,用来计算碰撞体积,同时设置一个参数为`Rect&`的函数,来计算两个物体是否发生碰撞

```c++
class Rect
{
  public:
    CollisionCheck(const Rect&);
    Point GetStartPoint();//返回左上点坐标,用于绘制
    Point GetEndPoint();
    ...
  private:
    Point start_point;
    Point end_point;
    ...
};
```

#### class Object

抽象类,作为一切物体的基础来保存他们的公有属性,包含:位置,碰撞体积,颜色,以及成员函数--绘制,判断是否存在,计算碰撞体积等

```c++
class Object
{
    public:
    virtual void Dispaly()=0;
    virtual bool isExist()=0;
    virtual void CalphysicalSize()=0;
    
    private:
    COLORREF color;
    DIR dir;//方向枚举
    Point pos;
    Rect physical_size;
};
```

#### class Tank, PlayerTank, AITank

`Tank`继承`Object`,加入纯虚函数--移动,射击,绘制车身以及自定义的构造函数,其余两个类继承`Tank`,其中`AITank`需要进行不同的设计加入新的功能, 后期再修改

```c++
class Tank:public Object
{
    public:
    virtual void Shoot()=0;
    virtual void Move()=0;
    virtual void DrawTank()=0;
    
    private: 
    int health;
};
```

#### class Bullet

子弹类,继承`Object`,加入自定义构造函数来方便地进行"发射的操作"

```c++
class Bullet:public Object
{
	public:
	virtual void Move();
	Bullet(Point, DIR, COLORREF);
};
```

#### class Block

障碍物, 继承`Object`

### 具体技术实现:数据结构, 算法

#### 链表的使用

用来保存子弹,为了方便插入和删除,并且不需要在其中进行查找,只需要遍历,决定使用链表(List)

#### 人机对战的AI设计

将地图按照障碍物和可移动区域编制为二维数组,对AI坦克用寻路算法(A*),引导至可以攻击到玩家的点,然后发射子弹

## DEMO

在附件中有坦克绘制+移动的DEMO