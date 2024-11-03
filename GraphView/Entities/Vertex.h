#pragma once
#include "../Shapes/Circle.h"
#include "../Serialization/Serialize.h"
#include <QGraphicsItem>
#include <QColor>
#include <QPoint>

class Vertex : public QGraphicsEllipseItem, public Serializable
{
public:
	Vertex(QPointF point, Circle circle);
	Vertex(QJsonObject json);
	~Vertex();

	QJsonObject serialize() override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	QVariant itemChange(GraphicsItemChange change, const QVariant& value);
private:
	void initialize(QRectF rect);

	std::vector<QGraphicsItem*> getConnectedEdges();
	QColor m_color;
};