#include "EdgeAnimator.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

EdgeAnimator::EdgeAnimator(QtDesignArea* designArea) : m_designArea{ designArea } {}

EdgeAnimator::~EdgeAnimator()
{
	sleep_for(1s);

	for (auto& edge : m_edges)
	{
		edge->highlight(false);
	}
	
	m_designArea->viewport()->repaint();
}

void EdgeAnimator::addEdge(Edge* edge)
{
	m_edges.push_back(edge);

	edge->highlight(true);
	m_designArea->viewport()->repaint();

	sleep_for(1s);
}
