#include "Window.h"

QtWindow::QtWindow(const std::string& title)
{
	m_window.setWindowTitle(title.c_str());
	m_window.setWindowState(Qt::WindowMaximized);
	m_window.show();
}
