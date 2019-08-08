#include"Model.h"

Rect::Rect(Point start, Point end)
{
	start_point = start;
	end_point = end;
}

void Rect::SetStartPoint(Point start)
{
	start_point = start;
}

void Rect::SetEndPoint(Point end)
{
	end_point = end;
}

bool Rect::PointInRect(Point p)
{
	if (p.x<start_point.x || p.x>end_point.x
		|| p.y<start_point.y || p.y>end_point.y)
		return false;
	else return true;
}

bool Rect::CollisionCheck(Rect& r)//to be finished
{
	if (PointInRect(r.GetStartPoint())
		|| PointInRect(r.GetEndPoint())
		|| PointInRect({ r.GetStartPoint().x, r.GetEndPoint().y })
		|| PointInRect({ r.GetEndPoint().x, r.GetStartPoint().y }))
		return true;
	else return false;
}

bool Rect::operator ==(Rect& r)
{
	return CollisionCheck(r);
}

Point Rect::GetStartPoint()
{
	return start_point;
}

Point Rect::GetEndPoint()
{
	return end_point;
}