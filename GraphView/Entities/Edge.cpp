#include "Edge.h"
#include "Entity.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include "../UIComponents/Window.h"
#include <QLineF>
#include "../UIComponents/GridScene.h"

Edge::Edge(Vertex* from, Vertex* to) : m_from{ from }, m_to{ to }
{
	initalize();
	setData(0, getNextHandle());
	setData(1, 0);
}

Edge::Edge(QJsonObject json, Vertex* from, Vertex* to) : m_from{ from }, m_to{ to }
{
	initalize();
	setData(0, json["id"].toInt());
	setData(1, json["weight"].toInt());
	setNextHandle(json["id"].toInt());
}

void Edge::updateLine()
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
	json["weight"] = data(1).toInt();

	return json;
}

void Edge::highlight(bool on)
{
	glowEffect->setEnabled(on);
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(pen());
    painter->drawLine(line());

	const double vertexRadius = 15.0; 

	QLineF adjustedLine = line();
	if (adjustedLine.length() > vertexRadius)
		adjustedLine.setLength(adjustedLine.length() - vertexRadius);

	if (((Grid*)scene())->isDirectedEdges())
	{
		const double arrowHeadSize = 10.0;

		QPointF tipPoint = adjustedLine.p2(); 

		double dx = adjustedLine.dx(); 
		double dy = adjustedLine.dy();
		double length = std::sqrt(dx * dx + dy * dy);
		QPointF basePoint = tipPoint - QPointF((dx / length) * arrowHeadSize, (dy / length) * arrowHeadSize);

		// Calculate the perpendicular offsets
		double perpendicularOffsetX = (-dy / length) * arrowHeadSize / 2;
		double perpendicularOffsetY = (dx / length) * arrowHeadSize / 2;

		// Calculate the left and right points
		QPointF leftPoint = basePoint + QPointF(perpendicularOffsetX, perpendicularOffsetY);
		QPointF rightPoint = basePoint - QPointF(perpendicularOffsetX, perpendicularOffsetY);

		QPainterPath arrowHeadPath;
		arrowHeadPath.moveTo(tipPoint);
		arrowHeadPath.lineTo(leftPoint);
		arrowHeadPath.lineTo(rightPoint);
		arrowHeadPath.closeSubpath();

		painter->setBrush(pen().color());
		painter->drawPath(arrowHeadPath);
	}

	if (((Grid*)scene())->showWeightLabels())
	{
		QPointF midpoint = adjustedLine.pointAt(0.5);

		double angleDegrees = adjustedLine.angle();
		QPointF labelPosition{};
		if (angleDegrees >= 45 && angleDegrees <= 135)
		{
			// Line is roughly vertical; place the label to the right
			labelPosition = midpoint + QPointF(10, 0);
		}
		else 
		{
			// Line is roughly horizontal; place the label above
			labelPosition = midpoint + QPointF(0, -10);
		}

		QFont font = painter->font();
		font.setBold(true);
		font.setPointSizeF(12.0);
		painter->setFont(font);

		painter->setPen(Qt::black);
		painter->drawText(labelPosition, QString::number(data(1).toInt()));
	}
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	((QtWindow*)scene()->views().first()->window())->setActiveObject(this);

	QGraphicsLineItem::mousePressEvent(event);
}

void Edge::initalize()
{
	updateLine();

	QColor black{ 0, 0, 0 };
	setPen({ black, 2.0 });

	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setFlag(ItemIsSelectable);
	setFlag(ItemIsFocusable);

	setZValue(-1.0);

	QPen highlightPen;
	highlightPen.setColor(QColor(255, 0, 0, 255));
    highlightPen.setWidth(8);

	glowEffect = new QGraphicsDropShadowEffect();
    glowEffect->setBlurRadius(15);
	glowEffect->setColor(QColor(255, 50, 50, 255));
	glowEffect->setOffset(0, 0);
    glowEffect->setEnabled(false);
    setGraphicsEffect(glowEffect);
}
