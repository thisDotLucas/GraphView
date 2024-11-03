#include "Vertex.h"
#include "../UIComponents/DesignArea.h"
#include "../UIComponents/GridScene.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include "Edge.h"
#include "Entity.h"

Vertex::Vertex(QPointF point, Circle circle)
{

	qreal snappedX = round(point.x() / 10) * 10;
	qreal snappedY = round(point.y() / 10) * 10;

	QRectF rect = QRectF(snappedX, snappedY, circle.radius() * 2, circle.radius() * 2);
	rect.translate(-circle.radius(), -circle.radius());

	initialize(rect);

	setData(0, getNextHandle());
}

void Vertex::initialize(QRectF rect)
{
	setRect(rect);

	QColor color = QColor{ 3, 136, 252 };
	setPen({ color });
	setBrush(color);

	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);
}

Vertex::Vertex(QJsonObject json)
{
	initialize(QRectF{ json["x"].toDouble(), json["y"].toDouble(), json["width"].toDouble(), json["height"].toDouble() });
	setData(0, json["id"].toInt());
	setNextHandle(json["id"].toInt());
}

Vertex::~Vertex()
{
	for (auto& edge : getConnectedEdges())
		delete edge;

	auto designArea = ((QtDesignArea*)scene()->parent());
	designArea->removeVertex(this);
}

QJsonObject Vertex::serialize()
{
	QJsonObject json;
	json["type"] = 1;
	json["id"] = static_cast<int>(getHandle(this));
	json["x"] = rect().x();
	json["y"] = rect().y();
	json["width"] = rect().width();
	json["height"] = rect().height();

	return json;
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (((QtDesignArea*)scene()->parent())->isInEdgeInsertionMode())
		setSelected(!isSelected());

	((QtWindow*)scene()->views().first()->window())->setActiveObject(this);

	QGraphicsEllipseItem::mousePressEvent(event);
}

QVariant Vertex::itemChange(GraphicsItemChange change, const QVariant& value)
{
	if (scene() && change == QGraphicsItem::ItemPositionChange)
	{
		int gridSize = dynamic_cast<Grid*>(scene())->gridSize();
		qreal snappedX = round(value.toPointF().x() / gridSize) * gridSize;
		qreal snappedY = round(value.toPointF().y() / gridSize) * gridSize;

		return QPointF{ snappedX, snappedY };
	}
	else if (QGraphicsItem::ItemPositionHasChanged)
	{
		for (const auto& edge : getConnectedEdges())
			dynamic_cast<Edge*>(edge)->update();
	}

	return QGraphicsEllipseItem::itemChange(change, value);
}

std::vector<QGraphicsItem*> Vertex::getConnectedEdges()
{
	if (!scene())
		return {};

	auto designArea = ((QtDesignArea*)scene()->parent());

	std::vector<QGraphicsItem*> edges;
	for (const auto& handle : designArea->getEdgesConnectedTo(this))
	{
		if (Edge* edge = dynamic_cast<Edge*>(designArea->getItem(handle)))
			edges.push_back(edge);
	}

	return edges;
}
