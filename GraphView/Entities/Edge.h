#pragma once
#include <QGraphicsLineItem>
#include "Vertex.h"

class Edge : public QGraphicsLineItem
{
public:
	Edge(Vertex* from, Vertex* to);

	void update();

private:
	Vertex* m_from;
	Vertex* m_to;
};