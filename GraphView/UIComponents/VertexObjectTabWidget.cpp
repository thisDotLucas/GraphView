#include "VertexObjectTabWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

VertexObjectTabWidget::VertexObjectTabWidget(QWidget* parent, Vertex* vertex) : QWidget(parent), m_vertex{ vertex }
{
    QLabel* nameLabel = new QLabel("Name:");
    m_nameField = new QLineEdit();
    m_nameField->setText(m_vertex->data(1).toString());

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(m_nameField);

    setLayout(layout);
	connect(m_nameField, &QLineEdit::textChanged, this, &VertexObjectTabWidget::onNameChanged);
}

void VertexObjectTabWidget::onNameChanged(QString value)
{
    m_vertex->setData(1, value);
    m_vertex->update();
}

