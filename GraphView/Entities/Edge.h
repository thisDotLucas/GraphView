#pragma once
#include <QGraphicsLineItem>
#include "Vertex.h"

class Edge : public QGraphicsLineItem, public Serializable
{
public:
	Edge(Vertex* from, Vertex* to);
	Edge(QJsonObject json, Vertex* from, Vertex* to);

	void update();

	QJsonObject serialize() override;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
	void initalize();
	Vertex* m_from;
	Vertex* m_to;
};