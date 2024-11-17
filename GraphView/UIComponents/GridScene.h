#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include "Window.h"

class Grid : public QGraphicsScene
{
public:
    Grid(QObject* parent) : QGraphicsScene{ parent } {}

	int gridSize() const { return m_gridsize; }
	void setSingleSelection(bool useSingleSelection) { m_singleSelection = useSingleSelection; m_selectionOrder.clear(); }
	void removeFirstFromSelectionOrder() { if (m_selectionOrder.size()) m_selectionOrder.erase(std::begin(m_selectionOrder)); }
	const QList<QGraphicsItem*>& getSelectionOrder() const { return m_selectionOrder; }
	void setDirectedEdges(bool isDirected) { m_directedEdges = isDirected; }
	bool isDirectedEdges() const { return m_directedEdges; }
	void setShowWeightLabels(bool show) { m_showWeightLabels = show; }
	bool showWeightLabels() const { return m_showWeightLabels; }

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

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override 
    {
		if (m_singleSelection)
		{
			QGraphicsScene::mousePressEvent(event);

			QGraphicsItem* item = itemAt(event->scenePos(), QTransform());

			if (item && item->flags() & QGraphicsItem::ItemIsSelectable) {
				for (QGraphicsItem* selectedItem : selectedItems()) {
					if (selectedItem != item) {
						selectedItem->setSelected(false);
					}
				}

				item->setSelected(true);
			}
		}
		else
		{
			QGraphicsItem* clickedItem = itemAt(event->scenePos(), QTransform());

			if (event->button() == Qt::LeftButton) 
			{
				if (clickedItem) 
				{
					if (clickedItem->isSelected()) 
					{
						clickedItem->setSelected(false);
						m_selectionOrder.removeOne(clickedItem);
					} 
					else 
					{
						clickedItem->setSelected(true);
						m_selectionOrder.append(clickedItem);
					}
				} 
				else 
				{
					clearSelection();
					m_selectionOrder.clear();
				}
			}

			QGraphicsScene::mousePressEvent(event);
		}
    }

private:
	int m_gridsize = 10;
	bool m_singleSelection{ true };
	bool m_directedEdges{ false };
	bool m_showWeightLabels{ false };
	QList<QGraphicsItem*> m_selectionOrder;
};
