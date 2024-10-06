#include <QPoint>

class Line
{
public:
	Line(QPointF from, QPointF to) : m_from{ from }, m_to{ to } {}

	QPointF from() const { return m_from; }
	QPointF to() const { return m_to; }

private:
	QPointF m_from;
	QPointF m_to;
};