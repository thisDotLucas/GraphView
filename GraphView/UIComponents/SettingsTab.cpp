#include "SettingsTab.h"
#include <QVBoxLayout>

SettingsTab::SettingsTab()
{
    QVBoxLayout* settingsLayout = new QVBoxLayout(this);
    settingsLayout->addStretch();
    setLayout(settingsLayout);
}
