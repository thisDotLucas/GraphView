#pragma once
#include "Runner.h"

class DFSRunner : public Runner
{
public:
	void run(QtDesignArea* designArea, Handle start) override;
};
