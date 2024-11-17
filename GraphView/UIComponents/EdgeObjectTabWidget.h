#pragma once
#include <QWidget>
#include <QSpinBox>
#include "../Entities/Edge.h"

class EdgeObjectTabWidget : public QWidget
{
	Q_OBJECT
public:
	EdgeObjectTabWidget(QWidget* parent, Edge* edge);

private slots:
    void onWeightInputChanged(int value);

private:
    Edge* m_edge;
    QSpinBox* m_weightInput;
};
