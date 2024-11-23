#include "Window.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QToolButton>
#include <QDockWidget>
#include <QComboBox>
#include <QFileDialog>
#include <QString>
#include "DesignArea.h"
#include "../Serialization/Serialize.h"
#include "GridScene.h"

namespace
{
    QString getSaveFilePath(QWidget* parent = nullptr) 
    {
        QString filePath = QFileDialog::getSaveFileName(parent, "Save File", "", "JSON Files (*.json);;All Files (*)");
        return filePath;
    }

    QString getOpenFilePath(QWidget* parent = nullptr) 
    {
		QString filePath = QFileDialog::getOpenFileName(parent, "Open File", "", "JSON Files (*.json);;All Files (*)");
		return filePath;
    }
}

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

    toolbar->addWidget(fileButton);
    toolbar->addWidget(insertButton);

    connect(openAction, &QAction::triggered, this, &QtWindow::onOpen);
    connect(saveAsAction, &QAction::triggered, this, &QtWindow::onSaveAs);
    connect(settingsAction, &QAction::triggered, this, &QtWindow::onSettings);
    connect(vertexAction, &QAction::triggered, this, &QtWindow::onInsertVertex);
    connect(edgeAction, &QAction::triggered, this, &QtWindow::onInsertEdge);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setStretch(0, 1);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    QDockWidget* leftPane = new QDockWidget("", this);
    leftPane->setAllowedAreas(Qt::LeftDockWidgetArea);
    leftPane->setFeatures(QDockWidget::NoDockWidgetFeatures);    
    leftPane->setTitleBarWidget(new QWidget());

    m_tab = new QTabWidget(leftPane);

    m_algorithmTab = new AlgorithmTab(this);
    m_tab->addTab(m_algorithmTab, "Algorithm");

    m_objectTab = new ObjectTab();
    m_tab->addTab(m_objectTab, "Object");

    m_settingsTab = new SettingsTab(this);
    connect(m_settingsTab, &SettingsTab::directedEdgesToggled, this,
        [&](bool enabled) { notifySceneAboutEdgeDirectionChange(enabled); });
    connect(m_settingsTab, &SettingsTab::showWeightLabelsToggled, this,
        [&](bool enabled) { notifySceneAboutWeightLabelsToggle(enabled); });

    m_tab->addTab(m_settingsTab, "Settings");

    leftPane->setWidget(m_tab);

    addDockWidget(Qt::LeftDockWidgetArea, leftPane);

    setWindowFlags(Qt::Window);
	setWindowTitle(title.c_str());
	setWindowState(Qt::WindowFullScreen);
    showMaximized();
}

void QtWindow::activateAlgorithmTab()
{
    m_tab->setCurrentIndex(0);
}

void QtWindow::activateObjectTab()
{
    m_tab->setCurrentIndex(1);
}

void QtWindow::activateSettingsTab()
{
    m_tab->setCurrentIndex(2);
}

void QtWindow::setActiveObject(QGraphicsItem* object)
{
    m_algorithmTab->setActiveObject(object);
    m_objectTab->setActiveObject(object);
}

void QtWindow::onSaveAs()
{
    QString path = getSaveFilePath(this);
	if (!path.isEmpty()) 
        saveSceneToFile(((QtDesignArea*)(children().back()))->scene(), path);
}

void QtWindow::onOpen()
{
    QString path = getOpenFilePath(this);
	if (!path.isEmpty()) 
        loadSceneFromFile(((QtDesignArea*)(children().back()))->scene(), path);
}

void QtWindow::onInsertVertex()
{
    ((QtDesignArea*)(children().back()))->setSingleSelectionMode();
    ((QtDesignArea*)(children().back()))->setDrawingContext(VertexDrawingContext{});
}

void QtWindow::onInsertEdge()
{
    ((QtDesignArea*)(children().back()))->setMultiSelectionMode();
    ((QtDesignArea*)(children().back()))->setDrawingContext(EdgeDrawingContext{});
}

void QtWindow::notifySceneAboutEdgeDirectionChange(bool isDirected)
{
    ((Grid*)((QtDesignArea*)(children().back()))->scene())->setDirectedEdges(isDirected);
    ((QtDesignArea*)(children().back()))->setIsDirected(isDirected);
    ((QtDesignArea*)(children().back()))->viewport()->repaint();
}

void QtWindow::notifySceneAboutWeightLabelsToggle(bool show)
{
    ((Grid*)((QtDesignArea*)(children().back()))->scene())->setShowWeightLabels(show);
    ((QtDesignArea*)(children().back()))->viewport()->repaint();
}
