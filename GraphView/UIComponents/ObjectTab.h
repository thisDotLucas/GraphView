#pragma once
#include <QWidget>
#include <QGraphicsItem>
#include <QLineEdit>

class ObjectTab : public QWidget
{
public:
	ObjectTab();

	void setActiveObject(QGraphicsItem* object);

private:
	void setWidget(QGraphicsItem* object);

	QGraphicsItem* m_object{};
	QLineEdit* m_idField;
};