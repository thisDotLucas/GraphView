#pragma once
#include "QtWidgets/qgraphicsview.h"
#include "Window.h"

class DesignArea
{
};

class QtDesignArea : public DesignArea, public QGraphicsView
{
public:
	QtDesignArea(QtWindow& parent);

protected:
	void mousePressEvent(QMouseEvent* e) override;
};
