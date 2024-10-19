#pragma once
#include "Window.h"
#include "../Drawing/DrawingContext.h"
#include "CppGraphLite.h"
#include <QGraphicsView>
#include <optional>
#include "../Entities/Entity.h"

class QtDesignArea : public QGraphicsView
{
public:
	QtDesignArea(QtWindow& parent);

	void setDrawingContext(DrawingContext context) { m_drawingContext = context; }
	void addVertex(QGraphicsItem* vertex);
	void removeVertex(QGraphicsItem* vertex);
	void addEdge(QGraphicsItem* from, QGraphicsItem* to, QGraphicsItem* edge);
	QGraphicsItem* getItem(Handle handle) { return m_items.at(handle); }
	std::vector<Handle> getEdgesConnectedTo(QGraphicsItem* vertex);

	bool isInEdgeInsertionMode() const;

protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void keyPressEvent(QKeyEvent* event) override;
	virtual void wheelEvent(QWheelEvent* e) override;

private:
	graphlite::Graph<Handle, graphlite::EdgeType::Undirected, Handle> m_graph;
	std::unordered_map<Handle, QGraphicsItem*> m_items;
	std::optional<QPointF> m_lastMousePoint;
	DrawingContext m_drawingContext;
};
