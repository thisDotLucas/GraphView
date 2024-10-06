#include "Vertex.h"
#include <QPainter>

Vertex::Vertex(QPointF point, Circle circle, QColor color) : m_circle{ circle }, m_color{ color }
{
	QRectF rect = QRectF(point.x(), point.y(), circle.radius() * 2, circle.radius() * 2);
	rect.translate(-circle.radius(), -circle.radius());
	setRect(rect);

	setPen({ m_color });
	setBrush(m_color);

	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
}
