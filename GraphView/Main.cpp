#include "QtWidgets/qwidget.h"
#include "QtWidgets/qapplication.h"
#include "QtWidgets/qmainwindow.h"
#include "GraphView.h"
#include "Adapters/Application.h"
#include "Adapters/DesignArea.h"
#include "Adapters/Window.h"

int main(int argc, char *argv[])
{
	GraphViewApplication<QtApplication> application;

	QtWindow window{ "Test" };
	QtDesignArea designArea{ window };

	return application.run();
}
