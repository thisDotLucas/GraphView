#pragma once
#include "QtWidgets/qapplication.h"
#include "Window.h"

class QtApplication
{
public:
	QtApplication() : m_application{ m_nArgs, &m_args } {};
	int run();

private:
	int				m_nArgs{};
	char*			m_args{};
	QApplication	m_application;
};