#include "Edge.h"
#include <QPainter>

Edge::Edge(Line line) : m_line{ line } 
{
	QLineF qline{ line.from(), line.to() };
	setLine(qline);

	QColor black{ 0, 0, 0 };
	setPen({ black });

	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);

	setZValue(-1.0);
}

