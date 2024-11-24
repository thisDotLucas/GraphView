#include "DijkstraWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

DijkstraWidget::DijkstraWidget(QWidget* parent)
{
    m_startVertexField = new QLineEdit(this);
    m_startVertexField->setReadOnly(true);
    m_startVertexField->setPlaceholderText("Select Start Vertex");

    m_toVertexField = new QLineEdit(this);
    m_toVertexField->setReadOnly(true);
    m_toVertexField->setPlaceholderText("Select End Vertex");

    m_runButton = new QPushButton("Run", this);
    m_runButton->setEnabled(false);
    connect(m_runButton, &QPushButton::clicked, this, &DijkstraWidget::onRunButton);

    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    firstRowLayout->addWidget(m_startVertexField);
    firstRowLayout->addWidget(m_toVertexField);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(firstRowLayout);
    mainLayout->addWidget(m_runButton);

    setLayout(mainLayout);

    m_runner = std::make_unique<DijkstraRunner>();
}

void DijkstraWidget::setVertex(Handle handle)
{
    if (m_startVertexField->text().isEmpty() || m_toVertexField->text().size())
    {
        m_startVertexField->setText(std::to_string(handle).c_str());
        m_toVertexField->setText("");
    }
    else
    {
        m_toVertexField->setText(std::to_string(handle).c_str());
    }
    
    m_runButton->setEnabled(m_startVertexField->text().size() && m_toVertexField->text().size());
}

void DijkstraWidget::onRunButton()
{
    QtWindow* w{};
    QObject* curr{ this };
    while (!dynamic_cast<QtWindow*>(curr))
        curr = curr->parent();

    auto designArea = (QtDesignArea*)curr->children().back();
    m_runner->run(designArea, std::stoi(m_startVertexField->text().toStdString()), std::stoi(m_toVertexField->text().toStdString()));
}

