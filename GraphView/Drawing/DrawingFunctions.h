#pragma once
#include "DrawingContext.h"
#include <QCursor>
#include "../UIComponents/DesignArea.h"

Qt::CursorShape getCursorShape(DrawingContext context);
void mousePress(QtDesignArea& designArea, DrawingContext context, QMouseEvent& e);
