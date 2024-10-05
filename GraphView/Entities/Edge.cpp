#include "../Shapes/Line.h"

class Edge
{
public:
	Edge(Line line) : m_line{ line } {}

private:
	Line m_line;
};