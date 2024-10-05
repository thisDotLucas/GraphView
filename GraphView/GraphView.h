#pragma once

template <typename Application>
class GraphViewApplication
{
public:
	int run()
	{
		return m_application.run();
	}

private:
	Application m_application;
};
