#pragma once
#include "UIComponents/Application.h"

class GraphViewApplication
{
public:
	int run()
	{
		return m_application.run();
	}

private:
	QtApplication m_application;
};
