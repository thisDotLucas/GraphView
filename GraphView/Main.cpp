#include "GraphView.h"
#include "UIComponents/Application.h"
#include "UIComponents/DesignArea.h"
#include "UIComponents/Window.h"

int main(int argc, char *argv[])
{
	GraphViewApplication application;

	QtWindow window{ "Test" };
	QtDesignArea designArea{ window };

	return application.run();
}
