#pragma once
#include <QWidget>
#include "../Entities/Vertex.h"
#include <QLineEdit>

class VertexObjectTabWidget : public QWidget
{
	Q_OBJECT
public:
	VertexObjectTabWidget(QWidget* parent, Vertex* vertex);

private slots:
    void onNameChanged(QString value);

private:
	Vertex* m_vertex;
	QLineEdit* m_nameField;
};
