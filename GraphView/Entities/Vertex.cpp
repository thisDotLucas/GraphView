#include "Vertex.h"
#include "../UIComponents/DesignArea.h"
#include "../UIComponents/GridScene.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "Edge.h"
#include "Entity.h"

Vertex::Vertex(QPointF point, Circle circle, QColor color) : m_circle{ circle }, m_color{ color }
{
	qreal snappedX = round(point.x() / 10) * 10;
	qreal snappedY = round(point.y() / 10) * 10;

	QRectF rect = QRectF(snappedX, snappedY, circle.radius() * 2, circle.radius() * 2);
	rect.translate(-circle.radius(), -circle.radius());
	setRect(rect);

	setPen({ m_color });
	setBrush(m_color);

	setFlag(ItemIsMovable);
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);

	setData(0, getNextHandle());
}

Vertex::~Vertex()
{
	for (auto& edge : getConnectedEdges())
		delete edge;

	auto designArea = ((QtDesignArea*)scene()->parent());
	designArea->removeVertex(this);
}

void Vertex::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (((QtDesignArea*)scene()->parent())->isInEdgeInsertionMode())
		setSelected(!isSelected());

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
