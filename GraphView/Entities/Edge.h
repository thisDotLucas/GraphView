#pragma once
#include "../Shapes/Line.h"
#include <QGraphicsLineItem>

class Edge : public QGraphicsLineItem
{
public:
	Edge(Line line);

private:
	Line m_line;
};