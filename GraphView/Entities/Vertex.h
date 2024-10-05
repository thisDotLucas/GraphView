#include "../Utils/Point.h"
#include "../Shapes/Circle.h"

class Vertex
{
public:
	Vertex(Point point, Circle circle) : m_point{ point }, m_circle{ circle } {}

private:
	Point m_point;
	Circle m_circle;
};