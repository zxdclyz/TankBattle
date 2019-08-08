#include"Map.h"

Block::Block(){}

Block::Block(COLORREF c, Point start, Point end)
{
	SetColor(c);
	SetPosition(start, end);
	pos = { 0,0 };
}

void Block::CalPhysicalSize(){}

bool Block::IsExist()
{
	return existing;
}

void Block::Display()
{
	COLORREF color_save = getcolor(),
		color_fill_save = getfillcolor();

	setcolor(color);
	setfillcolor(color);

	fillrectangle(physical_size.GetStartPoint().x, physical_size.GetStartPoint().y,
		physical_size.GetEndPoint().x, physical_size.GetEndPoint().y);

	setcolor(color_save);
	setfillcolor(color_fill_save);
}

void Block::Destory()
{
	existing = false;
}

void Block::SetColor(COLORREF c)
{
	color = c;
}

void Block::SetPosition(Point start, Point end)
{
	physical_size.SetStartPoint(start);
	physical_size.SetEndPoint(end);
}

void Map::Create(Block* blocks)
{
	blocks[0] = Block(RGB(160, 82, 45), { 75,180 }, { 180,210 });
	blocks[1] = Block(RGB(160, 82, 45), { 180,75 }, { 210,180 });
	blocks[2] = Block(RGB(160, 82, 45), { 590,75 }, { 620,180 });
	blocks[3] = Block(RGB(160, 82, 45), { 620,180 }, { 725,210 });
	blocks[4] = Block(RGB(160, 82, 45), { 75,390 }, { 180,420 });
	blocks[5] = Block(RGB(160, 82, 45), { 180,420 }, { 210,525 });
	blocks[6] = Block(RGB(160, 82, 45), { 620,390 }, { 725,420 });
	blocks[7] = Block(RGB(160, 82, 45), { 590,420 }, { 620,525 });
	blocks[8] = Block(RGB(160, 82, 45), { 300,180 }, { 500,210 });
	blocks[9] = Block(RGB(160, 82, 45), { 300,390 }, { 500,420 });
	blocks[10] = Block(RGB(160, 82, 45), { 0,285 }, { 100,315 });
	blocks[11] = Block(RGB(160, 82, 45), { 700,285 }, { 800,315 });
	blocks[12] = Block(RGB(160, 82, 45), { 170,270 }, { 230,330 });
	blocks[13] = Block(RGB(160, 82, 45), { 570,270 }, { 630,330 });
}

void Map::Display(Block* blocks)
{
	for (int i = 0; i < BLOCKS; i++)
		blocks[i].Display();
}