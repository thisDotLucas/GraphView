#include "Edge.h"
#include "Entity.h"
#include <QPainter>

Edge::Edge(Vertex* from, Vertex* to) : m_from{ from }, m_to{ to }
{
	update();

	QColor black{ 0, 0, 0 };
	setPen({ black });

	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);

	setZValue(-1.0);
	setData(0, getNextHandle());
}

void Edge::update()
{
	QLineF qline{ m_from->sceneBoundingRect().center(), m_to->sceneBoundingRect().center() };
	setLine(qline);
}
