#include "Edge.h"
#include "Entity.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "../UIComponents/Window.h"

Edge::Edge(Vertex* from, Vertex* to) : m_from{ from }, m_to{ to }
{
	initalize();
	setData(0, getNextHandle());
}

Edge::Edge(QJsonObject json, Vertex* from, Vertex* to) : m_from{ from }, m_to{ to }
{
	initalize();
	setData(0, json["id"].toInt());
	setNextHandle(json["id"].toInt());
}

void Edge::update()
{
	QLineF qline{ m_from->sceneBoundingRect().center(), m_to->sceneBoundingRect().center() };
	setLine(qline);
}

QJsonObject Edge::serialize()
{
	QJsonObject json;
	json["type"] = 2;
	json["id"] = static_cast<int>(getHandle(this));
	json["from"] = static_cast<int>(getHandle(m_from));
	json["to"] = static_cast<int>(getHandle(m_to));

	return json;
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	((QtWindow*)scene()->views().first()->window())->setActiveObject(this);

	QGraphicsLineItem::mousePressEvent(event);
}

void Edge::initalize()
{
	update();

	QColor black{ 0, 0, 0 };
	setPen({ black, 2.0 });

	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);

	setZValue(-1.0);
}
