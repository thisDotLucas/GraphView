#pragma once
#include "Window.h"
#include "../Drawing/DrawingContext.h"
#include <QGraphicsView>
#include <optional>

class QtDesignArea : public QGraphicsView
{
public:
	QtDesignArea(QtWindow& parent);

	void setDrawingContext(DrawingContext context) { m_drawingContext = context; }

protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void keyPressEvent(QKeyEvent* event) override;
	virtual void wheelEvent(QWheelEvent* e) override;

private:
	std::optional<QPointF> m_lastMousePoint;
	DrawingContext m_drawingContext;
};
