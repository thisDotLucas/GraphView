#pragma once
#include "../UIComponents/DesignArea.h"

class Runner
{
public:
	virtual void run(QtDesignArea* designArea, Handle start) = 0;
};