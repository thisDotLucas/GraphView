#include "BFSRunner.h"
#include "../Entities/Edge.h"
#include "EdgeAnimator.h"
#include <chrono>
#include <thread>

void BFSRunner::run(QtDesignArea* designArea, Handle start, std::optional<Handle>)
{
	if (designArea->isDirected())
	{
		graphlite::algorithm::GraphLiteBFS<decltype(designArea->getDirectedGraph())> bfs{};

		EdgeAnimator edgeAnimator{ designArea };

		auto f = [&](std::optional<Handle> from, Handle to) 
		{
			if (!from.has_value())
				return false;

			Edge* edge = dynamic_cast<Edge*>(designArea->getItem(designArea->getDirectedGraph().edgeData(from.value(), to).value()));
			if (!edge)
				return false;

			edgeAnimator.addEdge(edge);

			return false;
		};

		bfs.BFS(designArea->getDirectedGraph(), start, f);
	}
	else
	{
		graphlite::algorithm::GraphLiteBFS<decltype(designArea->getUndirectedGraph())> bfs{};

		EdgeAnimator edgeAnimator{ designArea };

		auto f = [&](std::optional<Handle> from, Handle to) 
		{
			if (!from.has_value())
				return false;

			Edge* edge = dynamic_cast<Edge*>(designArea->getItem(designArea->getUndirectedGraph().edgeData(from.value(), to).value()));
			if (!edge)
				return false;

			edgeAnimator.addEdge(edge);

			return false;
		};

		bfs.BFS(designArea->getUndirectedGraph(), start, f);
	}
}
