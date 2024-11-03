#include "VertexObjectTabWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

VertexObjectTabWidget::VertexObjectTabWidget(QWidget* parent) : QWidget(parent)
{
    QLabel* nameLabel = new QLabel("Name:");
    QLineEdit* nameInput = new QLineEdit();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(nameInput);

    setLayout(layout);
}
