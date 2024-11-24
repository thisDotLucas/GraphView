#include "VertexAnimator.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

VertexAnimator::VertexAnimator(QtDesignArea* designArea) : m_designArea{ designArea } {}

VertexAnimator::~VertexAnimator()
{
	sleep_for(1s);

	for (auto& vertex : m_verticies)
	{
		vertex->paintOriginalColor();
	}
	
	m_designArea->viewport()->repaint();
}

void VertexAnimator::addVertex(Vertex* vertex)
{
	m_verticies.push_back(vertex);

	vertex->paintAlternativeColor();
	m_designArea->viewport()->repaint();

	sleep_for(1s);
}
