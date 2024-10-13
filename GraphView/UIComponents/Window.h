#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QWidget>
#include <QStatusBar>

class QtWindow :public QMainWindow
{
public:
	QtWindow(const std::string& title);

private slots:
	void onOpen() { statusBar()->showMessage("Open", 2000); }
    void onSaveAs() { statusBar()->showMessage("Save As", 2000); }
	void onSettings() { statusBar()->showMessage("Settings", 2000); }
	void onInsertVertex();
	void onInsertEdge();
	void onRunAlgorithm() { statusBar()->showMessage("Run Algorithm", 2000); }

private:

	friend class QtDesignArea;
};
