#include "AlgorithmTab.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>

AlgorithmTab::AlgorithmTab()
{
    QVBoxLayout* algorithmLayout = new QVBoxLayout(this);
    QComboBox* algorithmComboBox = new QComboBox();
	algorithmComboBox->addItem("BFS");
    algorithmComboBox->addItem("DFS");
    algorithmLayout->addWidget(algorithmComboBox);

    QPushButton* runButton = new QPushButton("Run");
    algorithmLayout->addWidget(runButton);

    algorithmLayout->addStretch();
    setLayout(algorithmLayout);
}
