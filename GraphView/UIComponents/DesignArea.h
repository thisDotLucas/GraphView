#pragma once
#include "QtWidgets/qgraphicsview.h"
#include "Window.h"

class QtDesignArea : public QGraphicsView
{
public:
	QtDesignArea(QtWindow& parent);

protected:
	void mousePressEvent(QMouseEvent* e) override;
};
