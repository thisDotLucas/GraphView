#include "Window.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QToolButton>
#include "DesignArea.h"

QtWindow::QtWindow(const std::string& title)
{
    QToolBar* toolbar = addToolBar("Main Toolbar");
    toolbar->setContextMenuPolicy(Qt::PreventContextMenu);

    QToolButton* fileButton = new QToolButton(this);
    fileButton->setText("File");
    fileButton->setPopupMode(QToolButton::InstantPopup);
    fileButton->setStyleSheet("QToolButton::menu-indicator { image: none; }");

    QMenu* fileMenu = new QMenu(this);
    QAction* openAction = fileMenu->addAction("Open");
    QAction* saveAsAction = fileMenu->addAction("Save As");
    QAction* settingsAction = fileMenu->addAction("Settings");
    fileButton->setMenu(fileMenu);

    QToolButton* insertButton = new QToolButton(this);
    insertButton->setText("Insert");
    insertButton->setPopupMode(QToolButton::InstantPopup);
    insertButton->setStyleSheet("QToolButton::menu-indicator { image: none; }");

    QMenu* insertMenu = new QMenu(this);
    QAction* vertexAction = insertMenu->addAction("Vertex");
    QAction* edgeAction = insertMenu->addAction("Edge");
    insertButton->setMenu(insertMenu);

    QToolButton* runAlgorithmButton = new QToolButton(this);
    runAlgorithmButton->setText("Run Algorithm");

    toolbar->addWidget(fileButton);
    toolbar->addWidget(insertButton);
    toolbar->addWidget(runAlgorithmButton);

    connect(openAction, &QAction::triggered, this, &QtWindow::onOpen);
    connect(saveAsAction, &QAction::triggered, this, &QtWindow::onSaveAs);
    connect(settingsAction, &QAction::triggered, this, &QtWindow::onSettings);
    connect(vertexAction, &QAction::triggered, this, &QtWindow::onInsertVertex);
    connect(edgeAction, &QAction::triggered, this, &QtWindow::onInsertEdge);
    connect(runAlgorithmButton, &QToolButton::clicked, this, &QtWindow::onRunAlgorithm);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setStretch(0, 1);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowFlags(Qt::Window);
	setWindowTitle(title.c_str());
	setWindowState(Qt::WindowFullScreen);
    showMaximized();
}

void QtWindow::onInsertVertex()
{
    ((QtDesignArea*)(children().back()))->setDrawingContext(VertexDrawingContext{});
}

void QtWindow::onInsertEdge()
{
    ((QtDesignArea*)(children().back()))->setDrawingContext(EdgeDrawingContext{});
}
