#include "EdgeObjectTabWidget.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

EdgeObjectTabWidget::EdgeObjectTabWidget(QWidget* parent, Edge* edge) : QWidget(parent), m_edge{ edge }
{
    QFormLayout* layout = new QFormLayout(this);

    m_weightInput = new QSpinBox(this);
    m_weightInput->setRange(0, 1000); 
    m_weightInput->setValue(edge->data(1).toInt());      

    layout->addRow("Weight:", m_weightInput);

	connect(m_weightInput, SIGNAL(valueChanged(int)), this, SLOT(onWeightInputChanged(int)));
}

void EdgeObjectTabWidget::onWeightInputChanged(int value)
{
    m_edge->setData(1, value);
    m_edge->update();
}
