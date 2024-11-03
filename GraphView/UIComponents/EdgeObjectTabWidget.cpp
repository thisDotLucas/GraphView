#include "EdgeObjectTabWidget.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

EdgeObjectTabWidget::EdgeObjectTabWidget(QWidget* parent) : QWidget(parent)
{
    QFormLayout* layout = new QFormLayout(this);

    QLabel* weightLabel = new QLabel("Weight:");
    QLineEdit* weightInput = new QLineEdit();
    weightInput->setValidator(new QIntValidator(0, 10000, this));
    layout->addRow(weightLabel);
    layout->addRow(weightInput);

    setLayout(layout);
}
