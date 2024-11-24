#pragma once
#include "../UIComponents/DesignArea.h"
#include <optional>

class Runner
{
public:
	virtual void run(QtDesignArea* designArea, Handle start, std::optional<Handle> to = std::nullopt) = 0;
};