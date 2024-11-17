#include "ObjectTab.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include "../Entities/Entity.h"
#include "VertexObjectTabWidget.h"
#include "EdgeObjectTabWidget.h"
#include "../Entities/Vertex.h"
#include "../Entities/Edge.h"


ObjectTab::ObjectTab()
{
    QFormLayout* objectLayout = new QFormLayout(this);

    QWidget* idWidget = new QWidget();

    QLabel* idLabel = new QLabel("ID:");
    m_idField = new QLineEdit();
    m_idField->setReadOnly(true);

    QVBoxLayout* idLayout = new QVBoxLayout();
    idLayout->addWidget(idLabel);
    idLayout->addWidget(m_idField);
    idWidget->setLayout(idLayout);

    objectLayout->addRow(idWidget);
    setLayout(objectLayout);
}

void ObjectTab::setActiveObject(QGraphicsItem* object)
{
    m_object = object;
    m_idField->setText(std::to_string(getHandle(object)).c_str());
    setWidget(object);
}

void ObjectTab::setWidget(QGraphicsItem* object)
{
    QFormLayout* _layout = (QFormLayout*)layout();

    if (_layout->rowCount() > 1)
    {
        QLayoutItem* item = _layout->itemAt(_layout->rowCount() - 1, QFormLayout::FieldRole);
        if (item && item->widget())
            delete item->widget();

        _layout->removeRow(_layout->rowCount() - 1);
    }

    if (auto vertex = dynamic_cast<Vertex*>(object))
    {
        _layout->addRow(new VertexObjectTabWidget(this, vertex));
    }
    else if (auto edge = dynamic_cast<Edge*>(object))
    {
        _layout->addRow(new EdgeObjectTabWidget(this, edge));
    }
}
