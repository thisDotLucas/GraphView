#include "DesignArea.h"
#include "qgraphicsitem.h"
#include "qevent.h"

class Grid : public QGraphicsScene
{
public:
    Grid(QObject* parent) : QGraphicsScene{ parent } {}

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override
    {
		QPen pen;
		painter->setPen(pen);

		const qreal left = static_cast<int>(rect.left()) - static_cast<int>(rect.left()) % m_gridsize;
		const qreal top = static_cast<int>(rect.top()) - static_cast<int>(rect.top()) % m_gridsize;
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

class SimpleItem : public QGraphicsItem
{
public:
	SimpleItem(int x, int y) : m_x{ x }, m_y{ y } {}
	
	QRectF boundingRect() const override
    {
        qreal penWidth = 1;
        return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
            20 + penWidth, 20 + penWidth);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
        QWidget* widget) override
    {
        painter->drawRoundedRect(m_x, m_y, 20, 20, 5, 5);
    }

	int m_x;
	int m_y;
};

QtDesignArea::QtDesignArea(QtWindow& parent) : QGraphicsView{ parent.m_window.window() }
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setSceneRect(QRect{ 0, 0, width(), height() });
	setTransformationAnchor(QGraphicsView::NoAnchor);
	setDragMode(QGraphicsView::NoDrag);
	setMouseTracking(true);

    parent.m_window.setCentralWidget(this);

    setScene(new Grid(this));
}

void QtDesignArea::mousePressEvent(QMouseEvent* e)
{
	QGraphicsView::mousePressEvent(e);
	auto pos = mapToScene(e->pos());
	scene()->addItem(new SimpleItem{ (int)pos.x(), (int)pos.y() });
	scene()->update();
}
