#pragma once
#include "../Shapes/Circle.h"
#include <QGraphicsItem>
#include <QColor>
#include <QPoint>

class Vertex : public QGraphicsEllipseItem
{
public:
	Vertex(QPointF point, Circle circle, QColor color);
	~Vertex();

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);
private:
	std::vector<QGraphicsItem*> getConnectedEdges();
	Circle m_circle;
	QColor m_color;
};