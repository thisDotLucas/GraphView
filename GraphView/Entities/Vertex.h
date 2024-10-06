#include "../Utils/Point.h"
#include "../Shapes/Circle.h"
#include "qgraphicsitem.h"

class Vertex : public QGraphicsEllipseItem
{
public:
	Vertex(QPointF point, Circle circle, QColor color);

private:
	Circle m_circle;
	QColor m_color;
};