#include "DesignArea.h"
#include <QEvent>
#include "../Utils/Point.h"
#include "../Entities/Vertex.h"

class Grid : public QGraphicsScene
{
public:
    Grid(QObject* parent) : QGraphicsScene{ parent } {}

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override
    {
		QPen pen;
		painter->setPen(pen);

		const qreal left = int(rect.left()) - (int(rect.left()) % m_gridsize);
		const qreal top = int(rect.top()) - (int(rect.top()) % m_gridsize);
		QVector<QPointF> points;
		for (qreal x = left; x < rect.right(); x += m_gridsize) 
		{
			for (qreal y = top; y < rect.bottom(); y += m_gridsize) 
				points.append(QPointF(x, y));
		}

		painter->drawPoints(points.data(), points.size());
    }

private:
	int m_gridsize = 10;
};

QtDesignArea::QtDesignArea(QtWindow& parent) : QGraphicsView{ parent.window() }
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setTransformationAnchor(QGraphicsView::NoAnchor);
	setDragMode(QGraphicsView::NoDrag);
	setMouseTracking(true);

	parent.setCentralWidget(this);

    setScene(new Grid(this));
	setSceneRect(QRect{ 0, 0, width(), height() });
}

void QtDesignArea::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::MouseButton::RightButton)
	{
		scene()->addItem(new Vertex{ mapToScene(e->pos()), Circle{ 15 }, QColor{ 3, 136, 252 } });
		scene()->update();
	}

	QGraphicsView::mousePressEvent(e);
}
