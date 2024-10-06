#pragma once
#include <QGraphicsView>
#include "Window.h"
#include <optional>

class QtDesignArea : public QGraphicsView
{
public:
	QtDesignArea(QtWindow& parent);

protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	virtual void wheelEvent(QWheelEvent* e) override;

private:
	std::optional<QPointF> m_lastMousePoint;
};
