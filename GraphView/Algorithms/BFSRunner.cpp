#include "BFSRunner.h"
#include "../Entities/Edge.h"
#include <chrono>
#include <thread>

void BFSRunner::run(QtDesignArea* designArea, Handle start)
{
	graphlite::algorithm::GraphLiteBFS<decltype(designArea->getGraph())> bfs{};

	auto f = [&](std::optional<Handle> from, Handle to) 
	{
		if (!from.has_value())
			return false;

		auto edge = designArea->getItem(designArea->getGraph().edgeData(from.value(), to).value());

		((Edge*)edge)->highlight(true);
		((Edge*)edge)->update();
		designArea->viewport()->repaint();

		using namespace std::this_thread;
		using namespace std::chrono_literals;
		using std::chrono::system_clock;

		sleep_for(1s);

		((Edge*)edge)->highlight(false);
		((Edge*)edge)->update();
		designArea->viewport()->repaint();

		return false;
	};

	bfs.BFS(designArea->getGraph(), start, f);
}
