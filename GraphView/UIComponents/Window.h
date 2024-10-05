#pragma once
#include "QtWidgets/qmainwindow.h"


class QtWindow
{
public:
	QtWindow(const std::string& title);

private:
	QMainWindow m_window;

	friend class QtDesignArea;
};
