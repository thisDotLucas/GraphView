#include "DesignArea.h"
#include <QEvent>
#include <QMouseEvent>
#include "../Utils/Point.h"
#include "../Entities/Vertex.h"

class Grid : public QGraphicsScene
{
public:
    Grid(QObject* parent) : QGraphicsScene{ parent } {}

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override
    {
		// At some point displaying gridpoints does not make any sense when zoomed out to far.
		if (views()[0]->transform().m11() < 0.3)
			return;
	
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

void QtDesignArea::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() & Qt::MiddleButton && m_lastMousePoint.has_value())
	{
		const QPointF delta = mapToScene(e->pos()) - m_lastMousePoint.value();

		QRectF sceneR = sceneRect();
		sceneR.translate(-delta.x(), -delta.y());
		setSceneRect(sceneR);

		update();
		e->accept();
	}

	m_lastMousePoint = mapToScene(e->pos());

	QGraphicsView::mouseMoveEvent(e);
}

void QtDesignArea::wheelEvent(QWheelEvent* e)
{
	const QPointF pos = mapToScene(e->position().toPoint());

	// scale from wheel angle
	const float delta = 1.0f + e->angleDelta().y() / 1000.0f;

	QRectF sceneR = sceneRect();
	sceneR.translate((pos - sceneR.center()));
	setSceneRect(sceneR);

	cursor().setPos(mapToGlobal(mapFromScene(pos.toPoint())));

	scale(delta, delta);

	update();
	e->accept();

	QGraphicsView::wheelEvent(e);
}
