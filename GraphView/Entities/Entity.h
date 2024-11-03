#pragma once
#include <QGraphicsItem>

using Handle = unsigned int;

Handle getHandle(QGraphicsItem* item);
Handle getNextHandle();
void setNextHandle(Handle handle);
