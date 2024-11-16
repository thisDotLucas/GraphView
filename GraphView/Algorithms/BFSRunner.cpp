#include "BFSRunner.h"
#include "../Entities/Edge.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

namespace
{
	struct EdgeAnimator
	{
		EdgeAnimator(QtDesignArea* designArea) : m_designArea{ designArea } {}

		~EdgeAnimator()
		{
			sleep_for(1s);

			for (auto& edge : m_edges)
			{
				edge->highlight(false);
			}
			
			m_designArea->viewport()->repaint();
		}

		void addEdge(Edge* edge)
		{
			m_edges.push_back(edge);

			edge->highlight(true);
			m_designArea->viewport()->repaint();

			sleep_for(1s);
		}

		QtDesignArea* m_designArea;
		std::vector<Edge*> m_edges;
	};
}
void BFSRunner::run(QtDesignArea* designArea, Handle start)
{
	graphlite::algorithm::GraphLiteBFS<decltype(designArea->getGraph())> bfs{};

	EdgeAnimator edgeAnimator{ designArea };

	auto f = [&](std::optional<Handle> from, Handle to) 
	{
		if (!from.has_value())
			return false;

		Edge* edge = dynamic_cast<Edge*>(designArea->getItem(designArea->getGraph().edgeData(from.value(), to).value()));
		if (!edge)
			return false;

		edgeAnimator.addEdge(edge);

		return false;
	};

	bfs.BFS(designArea->getGraph(), start, f);
}
