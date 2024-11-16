#pragma once
#include <QGraphicsLineItem>
#include <QGraphicsDropShadowEffect>
#include "Vertex.h"

class Edge : public QGraphicsLineItem, public Serializable
{
public:
	Edge(Vertex* from, Vertex* to);
	Edge(QJsonObject json, Vertex* from, Vertex* to);

	void updateLine();

	QJsonObject serialize() override;

	void highlight(bool on);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
	void initalize();
	Vertex* m_from;
	Vertex* m_to;
	QGraphicsLineItem* m_highlightLine;
	QGraphicsDropShadowEffect* glowEffect;
};