#include "Entity.h"

static Handle NextHandle = 0;

Handle getHandle(QGraphicsItem* item)
{
	return item->data(0).toUInt();
}

Handle getNextHandle()
{
	return NextHandle++;
}
