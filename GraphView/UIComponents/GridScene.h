#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>

class Grid : public QGraphicsScene
{
public:
    Grid(QObject* parent) : QGraphicsScene{ parent } {}

	int gridSize() const { return m_gridsize; }

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
