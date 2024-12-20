#pragma once
#include <QWidget>

class SettingsTab : public QWidget
{
    Q_OBJECT
public:
	SettingsTab(QWidget* parent);

signals:
    void directedEdgesToggled(bool enabled);
    void showWeightLabelsToggled(bool enabled);

private slots:
    void onDirectedEdgesToggled(int state) { emit directedEdgesToggled(state == Qt::Checked); }
    void onShowWeightLabelsToggled(int state) { emit showWeightLabelsToggled(state == Qt::Checked); }
};