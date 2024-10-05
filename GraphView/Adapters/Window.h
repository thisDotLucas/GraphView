#pragma once
#include "QtWidgets/qmainwindow.h"

class Window
{
public:
	virtual ~Window() = default;
};

class QtWindow : public Window
{
public:
	QtWindow(const std::string& title);

private:
	QMainWindow m_window;

	friend class QtDesignArea;
};
