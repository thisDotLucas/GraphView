#include "DesignArea.h"
#include "GridScene.h"
#include <QEvent>
#include <QMouseEvent>
#include "../Utils/Point.h"
#include "../Entities/Vertex.h"
#include "../Drawing/DrawingFunctions.h"


QtDesignArea::QtDesignArea(QtWindow& parent) : QGraphicsView{ parent.window() }
{
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setTransformationAnchor(QGraphicsView::NoAnchor);
	setDragMode(QGraphicsView::NoDrag);
	setMouseTracking(true);

	parent.setCentralWidget(this);

    setScene(new Grid(this));
	setSceneRect(QRect{ 0, 0, width(), height() });

	m_drawingContext = NoneDrawingContext{};

	QCursor cursor{ getCursorShape(m_drawingContext) };
	setCursor(cursor);
}

void QtDesignArea::addVertex(QGraphicsItem* vertex)
{
	m_undirectedGraph.insert(getHandle(vertex)); 
	m_directedGraph.insert(getHandle(vertex)); 
	m_items[getHandle(vertex)] = vertex; 
}

void QtDesignArea::removeVertex(QGraphicsItem* vertex)
{
	m_undirectedGraph.erase(getHandle(vertex));
	m_directedGraph.erase(getHandle(vertex));
}

void QtDesignArea::addEdge(QGraphicsItem* from, QGraphicsItem* to, QGraphicsItem* edge)
{
	Handle fromHandle = getHandle(from);
	Handle toHandle = getHandle(to);

	m_undirectedGraph.insert(fromHandle, toHandle, getHandle(edge));
	m_directedGraph.insert(fromHandle, toHandle, getHandle(edge));
	m_items[getHandle(edge)] = edge;
}

std::vector<Handle> QtDesignArea::getEdgesConnectedTo(QGraphicsItem* vertex)
{
	std::vector<Handle> edges;
	for (auto&& to : m_undirectedGraph.edges(getHandle(vertex)))
	{
		const Handle from = getHandle(vertex);
		edges.push_back(m_undirectedGraph.edgeData(from, to).value());
	}

	return edges;
}

void QtDesignArea::setSingleSelectionMode()
{
	((Grid*)scene())->setSingleSelection(true);
}

void QtDesignArea::setMultiSelectionMode()
{
	((Grid*)scene())->setSingleSelection(false);
}

bool QtDesignArea::isInEdgeInsertionMode() const
{
	return std::holds_alternative<EdgeDrawingContext>(m_drawingContext);
}

void QtDesignArea::mousePressEvent(QMouseEvent* e)
{
	QGraphicsView::mousePressEvent(e);
	mousePress(*this, m_drawingContext, *e);
}

void QtDesignArea::mouseMoveEvent(QMouseEvent* e)
{
	QCursor cursor{ getCursorShape(m_drawingContext) };
	setCursor(cursor);

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

void QtDesignArea::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		m_drawingContext = NoneDrawingContext{};
		((Grid*)scene())->setSingleSelection(true);
		std::ranges::for_each(scene()->items(), [](QGraphicsItem* item) { item->setSelected(false); });
	}

	if (event->key() == Qt::Key_Delete)
	{
		QList<QGraphicsItem*> selectedItems = scene()->selectedItems();
		for (QGraphicsItem* item : selectedItems)
		{
			delete item;
		}
	}

	QWidget::keyPressEvent(event);
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
