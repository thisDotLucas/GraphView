#pragma once
#include "Runner.h"

class BFSRunner : public Runner
{
public:
	void run(QtDesignArea* designArea, Handle start, std::optional<Handle> = std::nullopt) override;
};
