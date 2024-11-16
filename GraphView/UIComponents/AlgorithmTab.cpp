#include "AlgorithmTab.h"
#include "BFSWidget.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include "../Entities/Vertex.h"

AlgorithmTab::AlgorithmTab(QWidget* parent) : QWidget(parent)
{
    QFormLayout* algorithmLayout = new QFormLayout(this);

    QWidget* algorithmMainWidget = new QWidget();

	m_algorithmComboBox = new QComboBox();
	m_algorithmComboBox->addItem("BFS");
    m_algorithmComboBox->addItem("DFS");

	QVBoxLayout* algorithmMainWidgetLayout = new QVBoxLayout();
	algorithmMainWidgetLayout->addWidget(m_algorithmComboBox);
	algorithmMainWidget->setLayout(algorithmMainWidgetLayout);

    algorithmLayout->addRow(algorithmMainWidget);

	QFrame* separatorLine = new QFrame(this);
    separatorLine->setFrameShape(QFrame::HLine);  // Horizontal line
    separatorLine->setFrameShadow(QFrame::Sunken);
    algorithmLayout->addRow(separatorLine);

    setLayout(algorithmLayout);

	connect(m_algorithmComboBox, &QComboBox::currentIndexChanged, 
		this, &AlgorithmTab::onAlgorithmChanged);

	m_algorithmComboBox->setCurrentIndex(0);
	onAlgorithmChanged(0);
}

void AlgorithmTab::setActiveObject(QGraphicsItem* object)
{
	if (dynamic_cast<Vertex*>(object))
		m_algorithmWidget->setStarVertex(getHandle(object));
}

void AlgorithmTab::onAlgorithmChanged(int index)
{
	if (m_algorithmWidget) 
	{
        ((QFormLayout*)layout())->removeRow(m_algorithmWidget);
        m_algorithmWidget = nullptr;
    }

	QString algorithm = m_algorithmComboBox->currentText();
	
	if (algorithm == "BFS") 
	{
		m_algorithmWidget = new BFSWidget(this);
		((QFormLayout*)layout())->addRow(m_algorithmWidget);
	} 
	else if (algorithm == "DFS")
	{
		qDebug() << "DFS selected";
	}
}
