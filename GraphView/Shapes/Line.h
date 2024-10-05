#include "../Utils/Point.h"

class Line
{
public:
	Line(Point from, Point to) : m_from{ from }, m_to{ to } {}

	Point from() const { return m_from; }
	Point to() const { return m_to; }

private:
	Point m_from;
	Point m_to;
};