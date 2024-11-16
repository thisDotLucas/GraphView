#pragma once
#include <QWidget>
#include <QComboBox>
#include <QGraphicsItem>

class BFSWidget;

class AlgorithmTab : public QWidget
{
public:
	AlgorithmTab(QWidget* parent);

	void setActiveObject(QGraphicsItem* object);

private slots:
	void onAlgorithmChanged(int index);

private:
	QWidget* m_algorithmWidget{};
    QComboBox* m_algorithmComboBox;
};