#include "SettingsTab.h"
#include <QVBoxLayout>
#include <QCheckBox>

SettingsTab::SettingsTab(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* settingsLayout = new QVBoxLayout(this);

	QCheckBox* directedEdgesCheckBox = new QCheckBox("Directed edges", this);
    settingsLayout->addWidget(directedEdgesCheckBox);

	QCheckBox* weightLabelCheckBox = new QCheckBox("Show weight labels", this);
    settingsLayout->addWidget(weightLabelCheckBox);

    settingsLayout->addStretch();
    setLayout(settingsLayout);
    
    connect(directedEdgesCheckBox, &QCheckBox::stateChanged, this, &SettingsTab::onDirectedEdgesToggled);
    connect(weightLabelCheckBox, &QCheckBox::stateChanged, this, &SettingsTab::onShowWeightLabelsToggled);
}
