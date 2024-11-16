#include "DFSWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

DFSWidget::DFSWidget(QWidget* parent) : QWidget(parent)
{
    m_startVertexField = new QLineEdit(this);
    m_startVertexField->setReadOnly(true);
    m_startVertexField->setPlaceholderText("Select Start Vertex");

    m_runButton = new QPushButton("Run", this);
    m_runButton->setEnabled(false);
    connect(m_runButton, &QPushButton::clicked, this, &DFSWidget::onRunButton);

    QHBoxLayout* firstRowLayout = new QHBoxLayout();
    firstRowLayout->addWidget(m_startVertexField);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(firstRowLayout);
    mainLayout->addWidget(m_runButton);

    setLayout(mainLayout);

    m_runner = std::make_unique<DFSRunner>();
}

void DFSWidget::setStarVertex(Handle handle)
{
    m_startVertexField->setText(std::to_string(handle).c_str());
    m_runButton->setEnabled(true);
}

void DFSWidget::onRunButton()
{
    QtWindow* w{};
    QObject* curr{ this };
    while (!dynamic_cast<QtWindow*>(curr))
        curr = curr->parent();

    auto designArea = (QtDesignArea*)curr->children().back();
    m_runner->run(designArea, std::stoi(m_startVertexField->text().toStdString()));
}
