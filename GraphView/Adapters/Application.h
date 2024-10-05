#pragma once
#include "QtWidgets/qapplication.h"
#include "Window.h"

class Application
{
public:
	virtual ~Application() = default;
	virtual int run() = 0;
};

class QtApplication : public Application
{
public:
	QtApplication() : m_application{ m_nArgs, &m_args } {};
	int run() override;

private:
	int				m_nArgs{};
	char*			m_args{};
	QApplication	m_application;
};