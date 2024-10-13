#include "../Utils/Point.h"
#include "../Shapes/Circle.h"
#include "qgraphicsitem.h"
#pragma once
#include "../Shapes/Circle.h"
#include <QGraphicsItem>
#include <QColor>
#include <QPoint>

class Vertex : public QGraphicsEllipseItem
{
public:
	Vertex(QPointF point, Circle circle, QColor color);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        // Toggle the selection state without requiring Ctrl
        setSelected(!isSelected());
        QGraphicsEllipseItem::mousePressEvent(event);  // Call the base class method
    }

private:
	Circle m_circle;
	QColor m_color;
};