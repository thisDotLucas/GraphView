#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QWidget>
#include <QStatusBar>
#include <QGraphicsItem>
#include "ObjectTab.h"
#include "AlgorithmTab.h"
#include "SettingsTab.h"

class QtWindow :public QMainWindow
{
	Q_OBJECT
public:
	QtWindow(const std::string& title);

	void activateAlgorithmTab();
	void activateObjectTab();
	void activateSettingsTab();
	void setActiveObject(QGraphicsItem* object);

private slots:
	void onOpen();
	void onSaveAs();
	void onSettings() {}
	void onInsertVertex();
	void onInsertEdge();
	void onRunAlgorithm() {}

private:

	void notifySceneAboutEdgeDirectionChange(bool isDirected);

	QTabWidget* m_tab{};
	ObjectTab* m_objectTab{};
	AlgorithmTab* m_algorithmTab{};
	SettingsTab* m_settingsTab{};

	friend class QtDesignArea;
};
