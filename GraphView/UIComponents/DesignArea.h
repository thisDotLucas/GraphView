#pragma once
#include <QGraphicsView>
#include "Window.h"

class QtDesignArea : public QGraphicsView
{
public:
	QtDesignArea(QtWindow& parent);

protected:
	void mousePressEvent(QMouseEvent* e) override;
};
