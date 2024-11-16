#include "DFSRunner.h"
#include "../Entities/Edge.h"
#include "EdgeAnimator.h"
#include <chrono>
#include <thread>

void DFSRunner::run(QtDesignArea* designArea, Handle start)
{
	graphlite::algorithm::GraphLiteDFS<decltype(designArea->getGraph())> dfs{};

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

	dfs.DFS(designArea->getGraph(), start, f);
}
